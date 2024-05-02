// 0x06006EA0
static const s16 swoop_seg6_animvalue_06006EA0[] = {
    0x0000, 0x0030, 0x0005, 0x3FFF, 0x13F6, 0x13CD, 0x1356, 0x1298, 0x119C, 0x1068, 0x0F04, 0x0D77,
    0x0BC9, 0x0A01, 0x0826, 0x0640, 0x0457, 0x0271, 0x0096, 0xFECF, 0xFD21, 0xFB94, 0xFA30, 0xF8FC,
    0xF800, 0xF742, 0xF6CB, 0xF6A2, 0xF6C5, 0xF72A, 0xF7CC, 0xF8A5, 0xF9AF, 0xFAE4, 0xFC3E, 0xFDB8,
    0xFF4D, 0x00F4, 0x02AB, 0x046A, 0x062D, 0x07EC, 0x09A3, 0x0B4B, 0x0CDF, 0x0E5A, 0x0FB4, 0x10E9,
    0x11F3, 0x12CC, 0x136E, 0x13D3, 0x13F6, 0x13F6, 0x7FFB, 0x7FFB, 0x7FFB, 0x7FFB, 0x7FFB, 0x7FFB,
    0x7FFB, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFE, 0x7FFE, 0x7FFE,
    0x7FFE, 0x7FFE, 0x7FFE, 0x7FFE, 0x7FFE, 0x8001, 0x7FFE, 0x7FFE, 0x7FFE, 0x7FFE, 0x7FFE, 0x7FFE,
    0x7FFE, 0x7FFE, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC,
    0x7FFB, 0x7FFB, 0x7FFB, 0x7FFB, 0x7FFB, 0x7FFB, 0x7FFB, 0x7FFB, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD,
    0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC,
    0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC,
    0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFC, 0x7FFD,
    0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x7FFD, 0x9328, 0x92FE,
    0x9287, 0x91CA, 0x90CD, 0x8F99, 0x8E35, 0x8CA8, 0x8AFA, 0x8932, 0x8757, 0x8572, 0x8388, 0x81A2,
    0x7FC5, 0x7DFD, 0x7C4E, 0x7AC2, 0x795D, 0x7829, 0x772D, 0x766F, 0x75F8, 0x75CF, 0x75F2, 0x7657,
    0x76F9, 0x77D2, 0x78DC, 0x7A11, 0x7B6C, 0x7CE6, 0x7E7A, 0x8025, 0x81DC, 0x839C, 0x855E, 0x871D,
    0x88D4, 0x8A7D, 0x8C11, 0x8D8B, 0x8EE6, 0x901B, 0x9124, 0x91FD, 0x929F, 0x9305, 0x9328, 0x9328,
    0x5FA3, 0x3FFF, 0xE05C, 0xA05D, 0xC001, 0xE05C, 0xFF27, 0xFF27, 0x3F48, 0x0000,
};

// 0x0600704C
static const u16 swoop_seg6_animindex_0600704C[] = {
    0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0000, 0x0001, 0x0003, 0x0001,
    0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x00D4, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x00D3, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x00D2, 0x0001, 0x00CF, 0x0001,
    0x00D0, 0x0001, 0x00D1, 0x0001, 0x0000, 0x0001, 0x0000, 0x0032, 0x0004, 0x0001, 0x00CC,
    0x0001, 0x00CD, 0x0001, 0x00CE, 0x0032, 0x0036, 0x0032, 0x0068, 0x0032, 0x009A,
};

// 0x060070B8
static const struct Animation swoop_seg6_anim_060070B8 = {
    0,
    0,
    0,
    0,
    0x32,
    ANIMINDEX_NUMPARTS(swoop_seg6_animindex_0600704C),
    swoop_seg6_animvalue_06006EA0,
    swoop_seg6_animindex_0600704C,
    0,
};
