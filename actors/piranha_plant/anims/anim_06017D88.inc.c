// 0x06017C50
static const s16 piranha_plant_seg6_animvalue_06017C50[] = {
    0x0000, 0x000E, 0x0003, 0x3FFF, 0x84A3, 0x8207, 0x7C46, 0x7688, 0xF5DD, 0xF773, 0xFAEF, 0xFE6B,
    0xFEFF, 0xFF27, 0xFF80, 0xFFD8, 0x81B5, 0x7F83, 0x7AB5, 0x75E7, 0xDEB2, 0xFB9A, 0x6705, 0x1B6D,
    0xF78F, 0x2B07, 0xC05D, 0xE128, 0xC001, 0xE128, 0xC05D, 0x0234, 0x023F, 0x0257, 0x026F, 0x0919,
    0x0917, 0x0910, 0x090A, 0x2370, 0x23A2, 0x2410, 0x247E, 0xE128, 0xC001, 0xE128, 0x00E8, 0x00D0,
    0x009C, 0x0068, 0x09BA, 0x09BB, 0x09BE, 0x09C2, 0x139B, 0x1336, 0x1259, 0x117B, 0x01DD, 0x019A,
    0x0104, 0x006F, 0xF885, 0xF87C, 0xF868, 0xF855, 0xE6C8, 0xE835, 0xEB58, 0xEE7A, 0x3DB1, 0x0000,
};

// 0x06017CE0
static const u16 piranha_plant_seg6_animindex_06017CE0[] = {
    0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0000, 0x0001, 0x0003, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0046, 0x0004, 0x003A, 0x0004, 0x003E, 0x0004, 0x0042,
    0x0004, 0x002E, 0x0004, 0x0032, 0x0004, 0x0036, 0x0004, 0x001F, 0x0004, 0x0023, 0x0004, 0x0027,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x001E, 0x0001, 0x0000, 0x0001, 0x0000, 0x0004, 0x0004,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x001A, 0x0004, 0x0008, 0x0004, 0x000C, 0x0004, 0x0010,
    0x0001, 0x002B, 0x0001, 0x002C, 0x0001, 0x002D, 0x0001, 0x0014, 0x0001, 0x0015, 0x0001, 0x0016,
    0x0001, 0x001B, 0x0001, 0x001C, 0x0001, 0x001D, 0x0001, 0x0017, 0x0001, 0x0018, 0x0001, 0x0019,
};

// 0x06017D88
static const struct Animation piranha_plant_seg6_anim_06017D88 = {
    0,
    0,
    0,
    0,
    0x04,
    ANIMINDEX_NUMPARTS(piranha_plant_seg6_animindex_06017CE0),
    piranha_plant_seg6_animvalue_06017C50,
    piranha_plant_seg6_animindex_06017CE0,
    0,
};
