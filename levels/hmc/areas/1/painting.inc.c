#include "game/paintings.h"

// 0x070241B8 - 0x070241D0
static const Lights1 hmc_seg7_lights_070241B8 =
    gdSPDefLights1(0x50, 0x50, 0x50, 0xff, 0xff, 0xff, 0x32, 0x32, 0x32);

// 0x070241D0 - 0x070241E8
// No gdSPDefLights1 macro defined because of odd different light value (0xff and 0xfa)
static const Lights1 hmc_seg7_lights_070241D0 = {
    { { { 0x40, 0x40, 0x80 }, 0, { 0x40, 0x40, 0x80 }, 0 } },
    { { { { 0x64, 0x64, 0xff }, 0, { 0x64, 0x64, 0xfa }, 0, { 0x28, 0x28, 0x28 }, 0 } } }
};

// Appears to lock 4 of the sides when shimmering and in use. Unused.
// 0x070241E8 - 0x07024228
static const Vtx hmc_seg7_vertex_070241E8[] = {
    { { { 0, 0, 0 }, 0, { -32, 990 }, { 0x00, 0x00, 0x7f, 0xff } } },
    { { { 614, 0, 0 }, 0, { 6100, 990 }, { 0x00, 0x00, 0x7f, 0xff } } },
    { { { 614, 614, 0 }, 0, { 6100, -5142 }, { 0x00, 0x00, 0x7f, 0xff } } },
    { { { 0, 614, 0 }, 0, { -32, -5142 }, { 0x00, 0x00, 0x7f, 0xff } } },
};

// 0x07024228 - 0x07024268
static const Vtx hmc_seg7_vertex_07024228[] = {
    { { { 0, 0, 0 }, 0, { 0, 0 }, { 0x00, 0x00, 0x7f, 0xff } } },
    { { { 614, 0, 0 }, 0, { 0, 0 }, { 0x00, 0x00, 0x7f, 0xff } } },
    { { { 614, 614, 0 }, 0, { 0, 0 }, { 0x00, 0x00, 0x7f, 0xff } } },
    { { { 0, 614, 0 }, 0, { 0, 0 }, { 0x00, 0x00, 0x7f, 0xff } } },
};

// Unused
// 0x07024268 - 0x070242A0
const Gfx hmc_seg7_dl_07024268[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPLight(&hmc_seg7_lights_070241B8.l, 1),
    gsSPLight(&hmc_seg7_lights_070241B8.a, 2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(hmc_seg7_vertex_070241E8, 4, 0),
    gsSPEndDisplayList(),
};

// Unused
// 0x070242A0 - 0x070242D0
const Gfx hmc_seg7_dl_070242A0[] = {
    gsSP2Triangles(0, 1, 2, 0x0, 0, 2, 3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x070242D0 - 0x070242F0
static const Gfx hmc_seg7_painting_dl_070242D0[] = {
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5,
                G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x070242F0 - 0x07024CD2
static const PaintingData hmc_seg7_pool_texture_map_070242F0[] = {
    157, // num mappings
         // Format:
         // mesh vtx ID, texture X, texture Y
    0,
    6100,
    -4832,
    1,
    6100,
    -5142,
    2,
    5582,
    -5142,
    3,
    5582,
    -4526,
    4,
    6100,
    -4218,
    5,
    5070,
    -4832,
    6,
    5070,
    -5142,
    7,
    3030,
    -5142,
    8,
    3030,
    -4832,
    9,
    3540,
    -5142,
    10,
    2520,
    -5142,
    11,
    2520,
    -4526,
    12,
    3030,
    -4218,
    13,
    3540,
    -4526,
    14,
    4050,
    -4832,
    15,
    4560,
    -5142,
    16,
    5070,
    -4218,
    17,
    4560,
    -4526,
    18,
    4050,
    -4218,
    19,
    5582,
    -2074,
    20,
    6100,
    -2380,
    21,
    5582,
    -3300,
    22,
    6100,
    -2994,
    23,
    5582,
    -2686,
    24,
    5070,
    -2380,
    25,
    4560,
    -2074,
    26,
    4560,
    -3300,
    27,
    5070,
    -2994,
    28,
    5070,
    -3606,
    29,
    4050,
    -2380,
    30,
    4560,
    -2686,
    31,
    3540,
    -2074,
    32,
    4050,
    -3606,
    33,
    3540,
    -3300,
    34,
    4050,
    -2994,
    35,
    3540,
    -2686,
    36,
    3030,
    -2380,
    37,
    2520,
    -2074,
    38,
    3030,
    -2994,
    39,
    2520,
    -3300,
    40,
    3030,
    -3606,
    41,
    6100,
    -3606,
    42,
    5582,
    -3912,
    43,
    4560,
    -3912,
    44,
    3540,
    -3912,
    45,
    2520,
    -3912,
    46,
    4050,
    -1768,
    47,
    5070,
    -1768,
    48,
    3030,
    -1768,
    49,
    6100,
    684,
    50,
    6100,
    990,
    51,
    5582,
    990,
    52,
    5582,
    -236,
    53,
    6100,
    70,
    54,
    5070,
    684,
    55,
    5582,
    378,
    56,
    4560,
    990,
    57,
    5070,
    990,
    58,
    4560,
    -236,
    59,
    5070,
    70,
    60,
    5070,
    -542,
    61,
    4050,
    684,
    62,
    4560,
    378,
    63,
    3540,
    990,
    64,
    4050,
    990,
    65,
    4050,
    70,
    66,
    3540,
    -236,
    67,
    4050,
    -542,
    68,
    3030,
    684,
    69,
    3540,
    378,
    70,
    2520,
    990,
    71,
    3030,
    990,
    72,
    2520,
    -236,
    73,
    3030,
    70,
    74,
    3030,
    -542,
    75,
    6100,
    -542,
    76,
    5582,
    -1462,
    77,
    6100,
    -1154,
    78,
    5582,
    -848,
    79,
    4560,
    -1462,
    80,
    5070,
    -1154,
    81,
    4560,
    -848,
    82,
    3540,
    -1462,
    83,
    4050,
    -1154,
    84,
    3540,
    -848,
    85,
    2520,
    -1462,
    86,
    3030,
    -1154,
    87,
    2010,
    -4832,
    88,
    0,
    -5142,
    89,
    0,
    -4832,
    90,
    478,
    -5142,
    91,
    478,
    -4526,
    92,
    988,
    -4832,
    93,
    2010,
    -4218,
    94,
    1498,
    -4526,
    95,
    1498,
    -5142,
    96,
    988,
    -4218,
    97,
    2520,
    -2686,
    98,
    2010,
    -2380,
    99,
    1498,
    -2074,
    100,
    1498,
    -3300,
    101,
    2010,
    -2994,
    102,
    2010,
    -3606,
    103,
    1498,
    -2686,
    104,
    988,
    -2380,
    105,
    478,
    -2074,
    106,
    478,
    -3300,
    107,
    988,
    -2994,
    108,
    988,
    -3606,
    109,
    478,
    -2686,
    110,
    0,
    -2380,
    111,
    0,
    -3606,
    112,
    1498,
    -3912,
    113,
    478,
    -3912,
    114,
    1498,
    -1462,
    115,
    988,
    -1768,
    116,
    2010,
    -1768,
    117,
    0,
    -1768,
    118,
    478,
    -1462,
    119,
    2010,
    684,
    120,
    2520,
    378,
    121,
    2010,
    990,
    122,
    1498,
    990,
    123,
    2010,
    -542,
    124,
    2010,
    70,
    125,
    1498,
    -236,
    126,
    988,
    684,
    127,
    1498,
    378,
    128,
    988,
    990,
    129,
    478,
    990,
    130,
    478,
    -236,
    131,
    988,
    70,
    132,
    988,
    -542,
    133,
    0,
    684,
    134,
    478,
    378,
    135,
    0,
    -542,
    136,
    2520,
    -848,
    137,
    2010,
    -1154,
    138,
    1498,
    -848,
    139,
    988,
    -1154,
    140,
    478,
    -848,
    141,
    4050,
    -5142,
    142,
    6100,
    -2074,
    143,
    6100,
    -1768,
    144,
    5070,
    -2074,
    145,
    4050,
    -2074,
    146,
    3030,
    -2074,
    147,
    2010,
    -5142,
    148,
    0,
    -4218,
    149,
    988,
    -5142,
    150,
    2010,
    -2074,
    151,
    988,
    -2074,
    152,
    0,
    -2994,
    153,
    0,
    -2074,
    154,
    0,
    -1154,
    155,
    0,
    70,
    156,
    0,
    990,

    264, // num groups
         // Grouped by 5 + one remainder group,
         // = 15 vertices per group + a few extra triangles
    8,
    12,
    13,
    0,
    1,
    2,
    3,
    0,
    2,
    4,
    0,
    3,
    5,
    2,
    6,
    2,
    5,
    3,
    7,
    8,
    9,
    8,
    7,
    10,
    11,
    8,
    10,
    12,
    8,
    11,
    9,
    8,
    13,
    13,
    14,
    9,
    14,
    141,
    9,
    5,
    6,
    15,
    5,
    16,
    3,
    16,
    5,
    17,
    17,
    5,
    15,
    14,
    15,
    141,
    15,
    14,
    17,
    18,
    14,
    13,
    14,
    18,
    17,
    19,
    142,
    20,
    19,
    20,
    23,
    28,
    27,
    21,
    21,
    23,
    22,
    22,
    41,
    21,
    20,
    22,
    23,
    23,
    24,
    19,
    21,
    27,
    23,
    24,
    23,
    27,
    25,
    144,
    24,
    19,
    24,
    144,
    24,
    27,
    30,
    25,
    24,
    30,
    26,
    30,
    27,
    27,
    28,
    26,
    36,
    38,
    97,
    26,
    34,
    30,
    29,
    30,
    34,
    30,
    29,
    25,
    25,
    29,
    145,
    31,
    145,
    29,
    31,
    29,
    35,
    29,
    34,
    35,
    32,
    34,
    26,
    33,
    35,
    34,
    34,
    32,
    33,
    33,
    38,
    35,
    35,
    36,
    31,
    36,
    35,
    38,
    37,
    36,
    97,
    37,
    146,
    36,
    31,
    36,
    146,
    28,
    16,
    43,
    38,
    40,
    39,
    39,
    97,
    38,
    40,
    38,
    33,
    21,
    41,
    42,
    41,
    4,
    42,
    3,
    42,
    4,
    42,
    28,
    21,
    28,
    42,
    16,
    3,
    16,
    42,
    26,
    28,
    43,
    17,
    43,
    16,
    43,
    32,
    26,
    32,
    43,
    18,
    17,
    18,
    43,
    33,
    32,
    44,
    32,
    18,
    44,
    13,
    44,
    18,
    44,
    40,
    33,
    13,
    12,
    44,
    40,
    44,
    12,
    39,
    40,
    45,
    40,
    12,
    45,
    48,
    31,
    146,
    11,
    45,
    12,
    25,
    47,
    144,
    46,
    25,
    145,
    47,
    19,
    144,
    19,
    143,
    142,
    31,
    46,
    145,
    60,
    59,
    52,
    49,
    53,
    55,
    50,
    49,
    51,
    51,
    49,
    55,
    52,
    55,
    53,
    53,
    75,
    52,
    54,
    55,
    59,
    52,
    59,
    55,
    55,
    54,
    51,
    54,
    59,
    62,
    56,
    54,
    62,
    57,
    54,
    56,
    54,
    57,
    51,
    58,
    62,
    59,
    59,
    60,
    58,
    68,
    71,
    63,
    61,
    62,
    65,
    58,
    65,
    62,
    62,
    61,
    56,
    61,
    65,
    69,
    63,
    61,
    69,
    64,
    61,
    63,
    61,
    64,
    56,
    65,
    67,
    66,
    66,
    69,
    65,
    67,
    65,
    58,
    68,
    69,
    73,
    69,
    68,
    63,
    66,
    73,
    69,
    68,
    73,
    120,
    70,
    68,
    120,
    71,
    68,
    70,
    72,
    120,
    73,
    73,
    74,
    72,
    74,
    73,
    66,
    75,
    77,
    78,
    52,
    75,
    78,
    76,
    78,
    77,
    77,
    143,
    76,
    76,
    80,
    78,
    60,
    78,
    80,
    78,
    60,
    52,
    46,
    83,
    79,
    58,
    60,
    81,
    60,
    80,
    81,
    79,
    81,
    80,
    80,
    47,
    79,
    47,
    80,
    76,
    81,
    67,
    58,
    67,
    81,
    83,
    79,
    83,
    81,
    66,
    67,
    84,
    67,
    83,
    84,
    82,
    84,
    83,
    83,
    46,
    82,
    84,
    74,
    66,
    82,
    86,
    84,
    74,
    84,
    86,
    74,
    86,
    136,
    72,
    74,
    136,
    85,
    136,
    86,
    86,
    48,
    85,
    48,
    86,
    82,
    25,
    46,
    79,
    79,
    47,
    25,
    82,
    46,
    31,
    19,
    47,
    76,
    76,
    143,
    19,
    31,
    48,
    82,
    37,
    48,
    146,
    85,
    48,
    37,
    10,
    87,
    11,
    87,
    10,
    147,
    92,
    95,
    149,
    88,
    89,
    90,
    89,
    148,
    91,
    90,
    89,
    91,
    91,
    92,
    90,
    92,
    149,
    90,
    93,
    87,
    94,
    87,
    93,
    11,
    94,
    87,
    95,
    87,
    147,
    95,
    95,
    92,
    94,
    96,
    92,
    91,
    92,
    96,
    94,
    39,
    101,
    97,
    97,
    98,
    37,
    98,
    97,
    101,
    99,
    98,
    103,
    99,
    150,
    98,
    37,
    98,
    150,
    98,
    101,
    103,
    100,
    103,
    101,
    101,
    102,
    100,
    102,
    101,
    39,
    100,
    107,
    103,
    103,
    104,
    99,
    104,
    103,
    107,
    105,
    104,
    109,
    105,
    151,
    104,
    99,
    104,
    151,
    104,
    107,
    109,
    106,
    109,
    107,
    107,
    108,
    106,
    108,
    107,
    100,
    109,
    110,
    105,
    106,
    152,
    109,
    110,
    109,
    152,
    105,
    110,
    153,
    111,
    152,
    106,
    11,
    93,
    45,
    102,
    45,
    93,
    45,
    102,
    39,
    102,
    93,
    112,
    100,
    102,
    112,
    94,
    112,
    93,
    112,
    108,
    100,
    108,
    112,
    96,
    94,
    96,
    112,
    106,
    108,
    113,
    108,
    96,
    113,
    91,
    113,
    96,
    91,
    148,
    113,
    113,
    111,
    106,
    111,
    113,
    148,
    114,
    116,
    99,
    99,
    115,
    114,
    115,
    99,
    151,
    99,
    116,
    150,
    72,
    124,
    120,
    116,
    37,
    150,
    37,
    116,
    85,
    117,
    105,
    153,
    105,
    115,
    151,
    105,
    117,
    118,
    118,
    115,
    105,
    119,
    120,
    124,
    120,
    119,
    70,
    119,
    124,
    127,
    119,
    121,
    70,
    121,
    119,
    122,
    122,
    119,
    127,
    123,
    124,
    72,
    124,
    123,
    125,
    125,
    127,
    124,
    126,
    127,
    131,
    127,
    126,
    122,
    125,
    131,
    127,
    126,
    131,
    134,
    128,
    126,
    129,
    129,
    126,
    134,
    126,
    128,
    122,
    136,
    123,
    72,
    130,
    134,
    131,
    131,
    132,
    130,
    132,
    131,
    125,
    133,
    134,
    155,
    134,
    133,
    129,
    130,
    155,
    134,
    133,
    156,
    129,
    135,
    155,
    130,
    123,
    136,
    137,
    85,
    137,
    136,
    139,
    115,
    118,
    123,
    137,
    138,
    125,
    123,
    138,
    114,
    138,
    137,
    137,
    116,
    114,
    116,
    137,
    85,
    114,
    139,
    138,
    132,
    138,
    139,
    138,
    132,
    125,
    132,
    139,
    140,
    130,
    132,
    140,
    115,
    139,
    114,
    118,
    140,
    139,
    135,
    140,
    154,
    118,
    154,
    140,
    140,
    135,
    130,
    117,
    154,
    118,
};

// 0x07024CD4
static const PaintingData *const hmc_seg7_painting_texture_maps_07024CD4[] = {
    hmc_seg7_pool_texture_map_070242F0,
};

UNUSED static const u64 hmc_unused_0 = 0;

// 0x07024CE0 - 0x070254E0
ALIGNED8 static const u8 hmc_seg7_texture_07024CE0[] = {
#include "levels/hmc/7.rgba16.inc.c"
};

// 0x070254E0 - 0x07025518
static const Gfx hmc_seg7_painting_dl_070254E0[] = {
    gsDPPipeSync(),
    gsSPLight(&hmc_seg7_lights_070241D0.l, 1),
    gsSPLight(&hmc_seg7_lights_070241D0.a, 2),
    gsSPVertex(hmc_seg7_vertex_07024228, 4, 0),
    gsSP2Triangles(0, 1, 2, 0x0, 0, 2, 3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07025518 - 0x07025594
const u8 *const hmc_seg7_painting_textures_07025518[] = {
    hmc_seg7_texture_07024CE0,
};

// 0x0702551C (PaintingData)
struct Painting cotmc_painting = {
    /* id */ 0x000E,
    /* Image Count */ 0x01,
    /* Texture Type */ PAINTING_ENV_MAP,
    /* Floor Status */ 0x00,
    0x00,
    0x00 /* which of the painting's nearby special floors Mario's on */,
    /* Ripple Status */ 0x00,
    /* Rotation */ 270.0f,
    0.0f,
    /* Position */ 2989.055908f,
    -4485.120117f,
    5135.359863f,
    /*                         curr   passive     entry */
    /* Ripple Magnitude */ 0.0f,
    10.0f,
    30.0f,
    /* Ripple Decay */ 1.0f,
    1.0f,
    0.98f,
    /* Ripple Rate */ 0.0f,
    0.05f,
    0.05f,
    /* Ripple Dispersion */ 0.0f,
    15.0f,
    15.0f,
    /* Curr Ripple Timer */ 0.0f,
    /* Curr Ripple x, y */ 0.0f,
    0.0f,
    /* Normal DList */ hmc_seg7_painting_dl_070254E0,
    /* Texture Maps */ hmc_seg7_painting_texture_maps_07024CD4,
    /* Textures */ hmc_seg7_painting_textures_07025518,
    /* Texture w, h */ 32,
    32,
    /* Ripple DList */ hmc_seg7_painting_dl_070242D0,
    /* Ripple Trigger */ RIPPLE_TRIGGER_CONTINUOUS,
    /* Alpha */ 0xFF,
    /* Mario Below */ 0x00,
    0x00,
    0x00, /* Whether or not Mario is below the painting */
    /* Size */ 723.968018f,
};
