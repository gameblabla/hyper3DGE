//
// Copyright (C) 2016 Alexey Khokholov (Nuke.YKT)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
//
//  MUS/MIDI player.
//
// version: 1.0
//
#ifndef OPL_OPLTABLES_H
#define OPL_OPLTABLES_H
#include "opldef.h"

Bit8u opl_slotoffset[9] =
{
    0x00, 0x01, 0x02, 0x08, 0x09, 0x0a, 0x10, 0x11, 0x12
};

Bit8u opl_voltable[128] =
{
    0x00, 0x01, 0x03, 0x05, 0x06, 0x08, 0x0a, 0x0b,
    0x0d, 0x0e, 0x10, 0x11, 0x13, 0x14, 0x16, 0x17,
    0x19, 0x1a, 0x1b, 0x1d, 0x1e, 0x20, 0x21, 0x22,
    0x24, 0x25, 0x27, 0x29, 0x2b, 0x2d, 0x2f, 0x31,
    0x32, 0x34, 0x36, 0x37, 0x39, 0x3b, 0x3c, 0x3d,
    0x3f, 0x40, 0x42, 0x43, 0x44, 0x45, 0x47, 0x48,
    0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4f, 0x50, 0x51,
    0x52, 0x53, 0x54, 0x54, 0x55, 0x56, 0x57, 0x58,
    0x59, 0x5a, 0x5b, 0x5c, 0x5c, 0x5d, 0x5e, 0x5f,
    0x60, 0x60, 0x61, 0x62, 0x63, 0x63, 0x64, 0x65,
    0x65, 0x66, 0x67, 0x67, 0x68, 0x69, 0x69, 0x6a,
    0x6b, 0x6b, 0x6c, 0x6d, 0x6d, 0x6e, 0x6e, 0x6f,
    0x70, 0x70, 0x71, 0x71, 0x72, 0x72, 0x73, 0x73,
    0x74, 0x75, 0x75, 0x76, 0x76, 0x77, 0x77, 0x78,
    0x78, 0x79, 0x79, 0x7a, 0x7a, 0x7b, 0x7b, 0x7b,
    0x7c, 0x7c, 0x7d, 0x7d, 0x7e, 0x7e, 0x7f, 0x7f
};

Bit16u opl_freqtable[284 + 384] =
{
    0x0133, 0x0133, 0x0134, 0x0134, 0x0135, 0x0136, 0x0136, 0x0137,
    0x0137, 0x0138, 0x0138, 0x0139, 0x0139, 0x013a, 0x013b, 0x013b,
    0x013c, 0x013c, 0x013d, 0x013d, 0x013e, 0x013f, 0x013f, 0x0140,
    0x0140, 0x0141, 0x0142, 0x0142, 0x0143, 0x0143, 0x0144, 0x0144,
    0x0145, 0x0146, 0x0146, 0x0147, 0x0147, 0x0148, 0x0149, 0x0149,
    0x014a, 0x014a, 0x014b, 0x014c, 0x014c, 0x014d, 0x014d, 0x014e,
    0x014f, 0x014f, 0x0150, 0x0150, 0x0151, 0x0152, 0x0152, 0x0153,
    0x0153, 0x0154, 0x0155, 0x0155, 0x0156, 0x0157, 0x0157, 0x0158,
    0x0158, 0x0159, 0x015a, 0x015a, 0x015b, 0x015b, 0x015c, 0x015d,
    0x015d, 0x015e, 0x015f, 0x015f, 0x0160, 0x0161, 0x0161, 0x0162,
    0x0162, 0x0163, 0x0164, 0x0164, 0x0165, 0x0166, 0x0166, 0x0167,
    0x0168, 0x0168, 0x0169, 0x016a, 0x016a, 0x016b, 0x016c, 0x016c,
    0x016d, 0x016e, 0x016e, 0x016f, 0x0170, 0x0170, 0x0171, 0x0172,
    0x0172, 0x0173, 0x0174, 0x0174, 0x0175, 0x0176, 0x0176, 0x0177,
    0x0178, 0x0178, 0x0179, 0x017a, 0x017a, 0x017b, 0x017c, 0x017c,
    0x017d, 0x017e, 0x017e, 0x017f, 0x0180, 0x0181, 0x0181, 0x0182,
    0x0183, 0x0183, 0x0184, 0x0185, 0x0185, 0x0186, 0x0187, 0x0188,
    0x0188, 0x0189, 0x018a, 0x018a, 0x018b, 0x018c, 0x018d, 0x018d,
    0x018e, 0x018f, 0x018f, 0x0190, 0x0191, 0x0192, 0x0192, 0x0193,
    0x0194, 0x0194, 0x0195, 0x0196, 0x0197, 0x0197, 0x0198, 0x0199,
    0x019a, 0x019a, 0x019b, 0x019c, 0x019d, 0x019d, 0x019e, 0x019f,
    0x01a0, 0x01a0, 0x01a1, 0x01a2, 0x01a3, 0x01a3, 0x01a4, 0x01a5,
    0x01a6, 0x01a6, 0x01a7, 0x01a8, 0x01a9, 0x01a9, 0x01aa, 0x01ab,
    0x01ac, 0x01ad, 0x01ad, 0x01ae, 0x01af, 0x01b0, 0x01b0, 0x01b1,
    0x01b2, 0x01b3, 0x01b4, 0x01b4, 0x01b5, 0x01b6, 0x01b7, 0x01b8,
    0x01b8, 0x01b9, 0x01ba, 0x01bb, 0x01bc, 0x01bc, 0x01bd, 0x01be,
    0x01bf, 0x01c0, 0x01c0, 0x01c1, 0x01c2, 0x01c3, 0x01c4, 0x01c4,
    0x01c5, 0x01c6, 0x01c7, 0x01c8, 0x01c9, 0x01c9, 0x01ca, 0x01cb,
    0x01cc, 0x01cd, 0x01ce, 0x01ce, 0x01cf, 0x01d0, 0x01d1, 0x01d2,
    0x01d3, 0x01d3, 0x01d4, 0x01d5, 0x01d6, 0x01d7, 0x01d8, 0x01d8,
    0x01d9, 0x01da, 0x01db, 0x01dc, 0x01dd, 0x01de, 0x01de, 0x01df,
    0x01e0, 0x01e1, 0x01e2, 0x01e3, 0x01e4, 0x01e5, 0x01e5, 0x01e6,
    0x01e7, 0x01e8, 0x01e9, 0x01ea, 0x01eb, 0x01ec, 0x01ed, 0x01ed,
    0x01ee, 0x01ef, 0x01f0, 0x01f1, 0x01f2, 0x01f3, 0x01f4, 0x01f5,
    0x01f6, 0x01f6, 0x01f7, 0x01f8, 0x01f9, 0x01fa, 0x01fb, 0x01fc,
    0x01fd, 0x01fe, 0x01ff, 0x0200, 0x0201, 0x0201, 0x0202, 0x0203,
    0x0204, 0x0205, 0x0206, 0x0207, 0x0208, 0x0209, 0x020a, 0x020b,
    0x020c, 0x020d, 0x020e, 0x020f, 0x0210, 0x0210, 0x0211, 0x0212,
    0x0213, 0x0214, 0x0215, 0x0216, 0x0217, 0x0218, 0x0219, 0x021a,
    0x021b, 0x021c, 0x021d, 0x021e, 0x021f, 0x0220, 0x0221, 0x0222,
    0x0223, 0x0224, 0x0225, 0x0226, 0x0227, 0x0228, 0x0229, 0x022a,
    0x022b, 0x022c, 0x022d, 0x022e, 0x022f, 0x0230, 0x0231, 0x0232,
    0x0233, 0x0234, 0x0235, 0x0236, 0x0237, 0x0238, 0x0239, 0x023a,
    0x023b, 0x023c, 0x023d, 0x023e, 0x023f, 0x0240, 0x0241, 0x0242,
    0x0244, 0x0245, 0x0246, 0x0247, 0x0248, 0x0249, 0x024a, 0x024b,
    0x024c, 0x024d, 0x024e, 0x024f, 0x0250, 0x0251, 0x0252, 0x0253,
    0x0254, 0x0256, 0x0257, 0x0258, 0x0259, 0x025a, 0x025b, 0x025c,
    0x025d, 0x025e, 0x025f, 0x0260, 0x0262, 0x0263, 0x0264, 0x0265,
    0x0266, 0x0267, 0x0268, 0x0269, 0x026a, 0x026c, 0x026d, 0x026e,
    0x026f, 0x0270, 0x0271, 0x0272, 0x0273, 0x0275, 0x0276, 0x0277,
    0x0278, 0x0279, 0x027a, 0x027b, 0x027d, 0x027e, 0x027f, 0x0280,
    0x0281, 0x0282, 0x0284, 0x0285, 0x0286, 0x0287, 0x0288, 0x0289,
    0x028b, 0x028c, 0x028d, 0x028e, 0x028f, 0x0290, 0x0292, 0x0293,
    0x0294, 0x0295, 0x0296, 0x0298, 0x0299, 0x029a, 0x029b, 0x029c,
    0x029e, 0x029f, 0x02a0, 0x02a1, 0x02a2, 0x02a4, 0x02a5, 0x02a6,
    0x02a7, 0x02a9, 0x02aa, 0x02ab, 0x02ac, 0x02ae, 0x02af, 0x02b0,
    0x02b1, 0x02b2, 0x02b4, 0x02b5, 0x02b6, 0x02b7, 0x02b9, 0x02ba,
    0x02bb, 0x02bd, 0x02be, 0x02bf, 0x02c0, 0x02c2, 0x02c3, 0x02c4,
    0x02c5, 0x02c7, 0x02c8, 0x02c9, 0x02cb, 0x02cc, 0x02cd, 0x02ce,
    0x02d0, 0x02d1, 0x02d2, 0x02d4, 0x02d5, 0x02d6, 0x02d8, 0x02d9,
    0x02da, 0x02dc, 0x02dd, 0x02de, 0x02e0, 0x02e1, 0x02e2, 0x02e4,
    0x02e5, 0x02e6, 0x02e8, 0x02e9, 0x02ea, 0x02ec, 0x02ed, 0x02ee,
    0x02f0, 0x02f1, 0x02f2, 0x02f4, 0x02f5, 0x02f6, 0x02f8, 0x02f9,
    0x02fb, 0x02fc, 0x02fd, 0x02ff, 0x0300, 0x0302, 0x0303, 0x0304,
    0x0306, 0x0307, 0x0309, 0x030a, 0x030b, 0x030d, 0x030e, 0x0310,
    0x0311, 0x0312, 0x0314, 0x0315, 0x0317, 0x0318, 0x031a, 0x031b,
    0x031c, 0x031e, 0x031f, 0x0321, 0x0322, 0x0324, 0x0325, 0x0327,
    0x0328, 0x0329, 0x032b, 0x032c, 0x032e, 0x032f, 0x0331, 0x0332,
    0x0334, 0x0335, 0x0337, 0x0338, 0x033a, 0x033b, 0x033d, 0x033e,
    0x0340, 0x0341, 0x0343, 0x0344, 0x0346, 0x0347, 0x0349, 0x034a,
    0x034c, 0x034d, 0x034f, 0x0350, 0x0352, 0x0353, 0x0355, 0x0357,
    0x0358, 0x035a, 0x035b, 0x035d, 0x035e, 0x0360, 0x0361, 0x0363,
    0x0365, 0x0366, 0x0368, 0x0369, 0x036b, 0x036c, 0x036e, 0x0370,
    0x0371, 0x0373, 0x0374, 0x0376, 0x0378, 0x0379, 0x037b, 0x037c,
    0x037e, 0x0380, 0x0381, 0x0383, 0x0384, 0x0386, 0x0388, 0x0389,
    0x038b, 0x038d, 0x038e, 0x0390, 0x0392, 0x0393, 0x0395, 0x0397,
    0x0398, 0x039a, 0x039c, 0x039d, 0x039f, 0x03a1, 0x03a2, 0x03a4,
    0x03a6, 0x03a7, 0x03a9, 0x03ab, 0x03ac, 0x03ae, 0x03b0, 0x03b1,
    0x03b3, 0x03b5, 0x03b7, 0x03b8, 0x03ba, 0x03bc, 0x03bd, 0x03bf,
    0x03c1, 0x03c3, 0x03c4, 0x03c6, 0x03c8, 0x03ca, 0x03cb, 0x03cd,
    0x03cf, 0x03d1, 0x03d2, 0x03d4, 0x03d6, 0x03d8, 0x03da, 0x03db,
    0x03dd, 0x03df, 0x03e1, 0x03e3, 0x03e4, 0x03e6, 0x03e8, 0x03ea,
    0x03ec, 0x03ed, 0x03ef, 0x03f1, 0x03f3, 0x03f5, 0x03f6, 0x03f8,
    0x03fa, 0x03fc, 0x03fe, 0x036c
};
#endif
