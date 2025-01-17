// 0x0500166C
static const s16 clam_shell_seg5_animvalue_0500166C[] = {
    0x0000, 0x3FFF, 0x7E13, 0x7DFA, 0x7DB2, 0x7D3C, 0x7C99, 0x7BCC, 0x7AD5, 0x79B7, 0x7874,
    0x770C, 0x7582, 0x73D8, 0x720E, 0x7027, 0x6E24, 0x6C08, 0x69D3, 0x6787, 0x6527, 0x62B3,
    0x602E, 0x5D98, 0x5AF5, 0x5845, 0x558A, 0x52C6, 0x4FFA, 0x4D28, 0x4A52, 0x477A, 0x44A1,
    0x41C9, 0x3EF3, 0x3C21, 0x3955, 0x3691, 0x33D6, 0x3126, 0x2E83, 0x2BED, 0x2968, 0x26F4,
    0x2494, 0x2248, 0x2013, 0x1DF7, 0x1BF4, 0x1A0D, 0x1843, 0x1699, 0x150F, 0x13A7, 0x1264,
    0x1146, 0x104F, 0x0F82, 0x0EDF, 0x0E69, 0x0E21, 0x0E08, 0x8001, 0x8001, 0x8001, 0x0000,
};

// 0x050016F0
static const u16 clam_shell_seg5_animindex_050016F0[] = {
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0001,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0040, 0x0001, 0x003E,
    0x0001, 0x003F, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x003C, 0x0002,
};

// 0x0500172C
static const struct Animation clam_shell_seg5_anim_0500172C = {
    1,
    0,
    0,
    0,
    0x3C,
    ANIMINDEX_NUMPARTS(clam_shell_seg5_animindex_050016F0),
    clam_shell_seg5_animvalue_0500166C,
    clam_shell_seg5_animindex_050016F0,
    0,
};
