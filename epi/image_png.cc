//------------------------------------------------------------------------
//  PNG Image Handling
//------------------------------------------------------------------------
//
//  Copyright (c) 2003-2017  The EDGE Team.
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------

#include "epi.h"
#include "endianess.h"

#include "image_png.h"

#define LIBPNG17 0

#undef _SETJMP_H  // workaround for some weirdness in pngconf.h

#include <png.h>
#include <zlib.h>
#ifdef LIBPNG17
				// Needed for libpng17 support!
#define PNG_COMPRESSION_HIGH_SPEED
#define PNG_READ_IMAGE_SUPPORTED
#define PNG_SEQUENTIAL_READ_SUPPORTED
#define PNG_WRITE_PNG_SUPPORTED
#define PNG_TEXT_SUPPORTED
#define PNG_OLD_COMPRESSION_CODES_SUPPORTED
#define PNG_STORE_UNKNOWN_CHUNKS_SUPPORTED
#define PNG_USER_CHUNKS_SUPPORTED
#define PNG_PROGRESSIVE_READ_SUPPORTED
#define PNG_HANDLE_CHUNK_IF_SAFE  
#endif // 0




// if we can't use C++11 or aren't using VS2015, resort to gross hacks
#if __cplusplus < 201103L && (!defined(_MSC_VER) || _MSC_VER < 1900)
#define nullptr NULL
#endif


namespace epi
{

	namespace PNG
	{
#define CHECK_PNG_BYTES  4

		void local_read_fn(png_structp png_ptr, png_bytep data, png_size_t length)
		{
			file_c *f = (file_c *)png_get_io_ptr(png_ptr);

			if (f->Read(data, length) != length)
			{
				png_error(png_ptr, "Read Error");
			}
		}

	}  // namespace PNG


	bool PNG_IsDataPNG(const byte *data, int length)
	{
		if (length < CHECK_PNG_BYTES)
			return false;

		// BLEH, the PNG API is not using const here

		return png_sig_cmp((png_bytep)data, (png_size_t)0, CHECK_PNG_BYTES) == 0;
	}

	image_data_c *PNG_Load(file_c *f, int read_flags)
	{
		/* -AJA- all these volatiles here may seem strange.  They are needed
		* because the ANSI C standard (which GCC adheres to) says that when
		* setjmp/longjmp is being used, only volatile local variables are
		* guaranteed to keep their state if longjmp() gets called.
		*/
		image_data_c * volatile img = 0;

		png_bytep * volatile row_pointers = 0;

		/* we take the address of these two, so we shouldn't need the
		* volatile.  (GCC complains about discarding qualifiers if the
		* volatile is there).
		*/
		png_structp /*volatile*/ png_ptr = 0;
		png_infop   /*volatile*/ info_ptr = 0;

		png_byte sig_buf[CHECK_PNG_BYTES];

		/* check the signature */

		if (f->Read(sig_buf, CHECK_PNG_BYTES) != CHECK_PNG_BYTES ||
			(png_sig_cmp(sig_buf, (png_size_t)0, CHECK_PNG_BYTES) != 0))
		{
			fprintf(stderr, "PNG_Load - File is not a PNG image !\n");
			goto failed;
		}

		/* pass NULLs for the error functions -- therefore use setjump */

		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr)
			goto failed;

		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
			goto failed;

		/* set error handling since we are using the setjmp/longjmp method
		* (this is the normal method of doing things with libpng).
		*/
#ifndef DREAMCAST
		if (setjmp(png_jmpbuf(png_ptr)))
#else
		if (setjmp(png_jmpbuf(png_ptr)))
#endif
		{
			fprintf(stderr, "PNG_Load - Possible Error loading PNG image !\n");
			goto failed;
		}

		png_set_read_fn(png_ptr, (void *)f, &PNG::local_read_fn);
		png_set_sig_bytes(png_ptr, CHECK_PNG_BYTES);

		/* read the header information */

		png_set_keep_unknown_chunks(png_ptr, PNG_HANDLE_CHUNK_ALWAYS, nullptr, 0);
		png_read_info(png_ptr, info_ptr);

		png_uint_32 width, height;
		int bit_depth, color_type, interlace_type;

		int tot_W, tot_H;
		bool solid;

		png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth,
			&color_type, &interlace_type, NULL, NULL);

		solid = ((color_type & PNG_COLOR_MASK_ALPHA) == 0);

		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
			solid = false;

		tot_W = (int)width;
		tot_H = (int)height;

		if (read_flags & IRF_Round_POW2)
		{
			tot_W = 1; while (tot_W < (int)width)  tot_W <<= 1;
			tot_H = 1; while (tot_H < (int)height) tot_H <<= 1;
		}

		img = new image_data_c(tot_W, tot_H, solid ? 3 : 4);

		img->used_w = width;
		img->used_h = height;

		if (img->used_w != tot_W || img->used_h != tot_H)
			img->Clear();

		/* tell libpng to strip 16 bits/color down to 8 bits/color */
		png_set_strip_16(png_ptr);

		/* convert low depths (1, 2 or 4) */
		if (bit_depth < 8)
			png_set_packing(png_ptr);

		/* expand paletted colors into true RGB triplets */
		if (color_type == PNG_COLOR_TYPE_PALETTE)
			png_set_palette_to_rgb(png_ptr);

		/* expand greyscale into RGB */
		if (color_type == PNG_COLOR_TYPE_GRAY ||
			color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		{
			png_set_gray_to_rgb(png_ptr);
		}

		/* read alpha channel */
		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
			png_set_tRNS_to_alpha(png_ptr);

		/* let all the above calls take effect */
		png_read_update_info(png_ptr, info_ptr);

		row_pointers = new png_bytep[height];

		for (png_uint_32 y = 0; (short)y < img->used_h; y++)
		{
			row_pointers[y] = (png_bytep)img->PixelAt(0, img->used_h - 1 - y);
		}

		/* now read in the image.  Yeah baby ! */

		png_read_image(png_ptr, row_pointers);
		png_read_end(png_ptr, info_ptr);

		/* read grAb chunk */
		png_unknown_chunk *unknowns;
		int num_unknowns;
		num_unknowns = png_get_unknown_chunks(png_ptr, info_ptr, &unknowns);

		for (int i = 0; i < num_unknowns; i++)
		{
			if (!memcmp(unknowns[i].name, "grAb", 4))
			{
				/* png_grAb_t *grAb = reinterpret_cast<png_grAb_t
				*>(unknowns[i].data); */
				png_grAb_t *grAb = new png_grAb_t;
				memcpy(grAb, unknowns[i].data, sizeof(png_grAb_t));
				grAb->x = EPI_BE_S32(grAb->x);
				grAb->y = EPI_BE_S32(grAb->y);
				I_Printf("Got grAb struct: %d/%d\n", grAb->x, grAb->y);
				if (grAb->x)
					grAb->x += (160 - width / 2);
					//grAb->x = width / 2 - grAb->x;
				if (grAb->y)
					grAb->y += (200 - 32 - height);
					///grAb->y = height - grAb->y;
				//                grAb->x += (160 - width / 2);
				//                grAb->y += (200 - 32 - height);
				img->grAb = grAb;
				break;
			}
		}

		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

		delete[] row_pointers;
		//delete[] unknowns;


		return img;

		/* -AJA- Normally I don't like gotos.  In this situation where there
		* are lots of points of possible failure and a growing set of
		* things to be undone, it makes for nicer code.
		*/
	failed:

		if (img)
		{
			delete img;
			img = 0;
		}

		if (png_ptr)
		{
			if (info_ptr)
				png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			else
				png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		}

		if (row_pointers)
			delete[] row_pointers;

		return 0;
	}

	bool PNG_GetInfo(file_c *f, int *width, int *height, bool *solid)
	{
		png_structp /*volatile*/ png_ptr = 0;
		png_infop   /*volatile*/ info_ptr = 0;

		png_byte sig_buf[CHECK_PNG_BYTES];

		/* check the signature */

		if (f->Read(sig_buf, CHECK_PNG_BYTES) != CHECK_PNG_BYTES ||
			(png_sig_cmp(sig_buf, (png_size_t)0, CHECK_PNG_BYTES) != 0))
		{
			fprintf(stderr, "PNG: File is not a PNG image !\n");
			goto failed;
		}

		/* pass NULLs for the error functions -- therefore use setjump */

		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr)
			goto failed;

		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
			goto failed;

		/* set error handling since we are using the setjmp/longjmp method
		* (this is the normal method of doing things with libpng).
		*/
#ifndef DREAMCAST
		if (setjmp(png_jmpbuf(png_ptr)))
#else
		if (setjmp(png_jmpbuf(png_ptr)))
#endif
		{
			fprintf(stderr, "PNG: Error loading PNG image !\n");
			goto failed;
		}

		png_set_read_fn(png_ptr, (void *)f, &PNG::local_read_fn);
		png_set_sig_bytes(png_ptr, CHECK_PNG_BYTES);

		/* read the header information */

		png_read_info(png_ptr, info_ptr);

		png_uint_32 pu_width, pu_height;
		int bit_depth, color_type, interlace_type;

		png_get_IHDR(png_ptr, info_ptr, &pu_width, &pu_height, &bit_depth,
			&color_type, &interlace_type, NULL, NULL);

		*width = (int)pu_width;
		*height = (int)pu_height;
		*solid = ((color_type & PNG_COLOR_MASK_ALPHA) == 0);

		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			*solid = false;
		}

		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

		return true;

		/* -AJA- Normally I don't like gotos.  In this situation where there
		* are lots of points of possible failure and a growing set of
		* things to be undone, it makes for nicer code.
		*/
	failed:

		if (png_ptr)
		{
			if (info_ptr)
				png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
			else
				png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		}

		return false;
	}


	//------------------------------------------------------------------------

	bool PNG_Save(FILE *fp, const image_data_c *img, int compress)
	{
		SYS_ASSERT(compress >= Z_NO_COMPRESSION);
		SYS_ASSERT(compress <= Z_BEST_COMPRESSION);

		SYS_ASSERT(img->bpp >= 3);

		png_bytep * volatile row_pointers = 0;

		png_structp /*volatile*/ png_ptr = 0;
		png_infop   /*volatile*/ info_ptr = 0;

		/* pass NULLs for the error functions -- therefore use setjump */

		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr)
			goto failed;

		info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr)
			goto failed;

		/* set error handling since we are using the setjmp/longjmp method
		* (this is the normal method of doing things with libpng).
		*/
#ifndef DREAMCAST
		if (setjmp(png_jmpbuf(png_ptr)))
#else
		if (setjmp(png_jmpbuf(png_ptr)))
#endif
		{
			fprintf(stderr, "PNG: Error saving PNG image !\n");
			goto failed;
		}

		png_init_io(png_ptr, fp);
		png_set_compression_level(png_ptr, compress);

		png_set_IHDR(png_ptr, info_ptr, img->used_w, img->used_h, 8,
			(img->bpp == 4) ? PNG_COLOR_TYPE_RGB_ALPHA : PNG_COLOR_TYPE_RGB,
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT);

		row_pointers = new png_bytep[img->used_h];

		for (int y = 0; y < img->used_h; y++)
		{
			row_pointers[y] = (png_bytep)img->PixelAt(0, img->used_h - 1 - y);
		}

		png_set_rows(png_ptr, info_ptr, (png_bytep*)row_pointers);

		png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

		//png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

		delete[] row_pointers;

		return true;

	failed:
		if (png_ptr)
		{
			if (info_ptr)
				png_destroy_write_struct(&png_ptr, &info_ptr);
			else
				png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		}

		if (row_pointers)
			delete[] row_pointers;

		return false;
	}

}  // namespace epi

   //--- editor settings ---
   // vi:ts=4:sw=4:noexpandtab
