// 0x05005EB8
static const s16 blargg_seg5_animvalue_05005EB8[] = {
    0x0000, 0x0016, 0xFFFC, 0xFFB9, 0xFF61, 0xFF08, 0xFEC0, 0xFE9F, 0xFEAC, 0xFED8, 0xFF16, 0xFF59,
    0xFF95, 0xFFBB, 0xFFD4, 0xFFED, 0x0005, 0x001C, 0x0031, 0x0042, 0x004D, 0x0052, 0x004E, 0x0042,
    0x002B, 0xFFED, 0xFF79, 0xFEEE, 0xFE68, 0xFE02, 0xFDD9, 0xFDDF, 0xFDF3, 0xFE13, 0xFE3C, 0xFE6C,
    0xFEA1, 0xFED9, 0xFF13, 0xFF4C, 0xFF81, 0xFFB2, 0xFFDB, 0xFFFB, 0x000F, 0x0016, 0x3FFF, 0x8785,
    0x8785, 0x8785, 0x8785, 0x8785, 0x8785, 0x8785, 0x8A1E, 0x909B, 0x990A, 0xA17A, 0xA7F7, 0xAA8F,
    0xAA75, 0xAA2A, 0xA9B1, 0xA90E, 0xA843, 0xA753, 0xA643, 0xA516, 0xA3CE, 0xA26F, 0xA0FC, 0x9F79,
    0x9DE9, 0x9C4F, 0x9AAE, 0x990A, 0x9766, 0x95C6, 0x942C, 0x929B, 0x9118, 0x8FA6, 0x8E47, 0x8CFF,
    0x8BD1, 0x8AC1, 0x89D2, 0x8907, 0x8863, 0x87EA, 0x879F, 0x8785, 0x804C, 0x0BCD, 0x0D29, 0x106F,
    0x1461, 0x17C8, 0x1967, 0x1806, 0x1248, 0x08E6, 0xFDBD, 0xF2AB, 0xE990, 0xE448, 0xE1F8, 0xE072,
    0xDFA4, 0xDF79, 0xDFDD, 0xE0BB, 0xE1FF, 0xE394, 0xE567, 0xE762, 0xE972, 0xEE5F, 0xF6AA, 0xFED8,
    0x036F, 0x04F7, 0x064D, 0x0774, 0x086F, 0x0941, 0x09EF, 0x0A7C, 0x0AEA, 0x0B3F, 0x0B7C, 0x0BA6,
    0x0BC1, 0x0BCE, 0x0BD3, 0x0BD2, 0x0BCE, 0x0BCD, 0x76C1, 0x76C1, 0x76C1, 0x76C1, 0x76C1, 0x76C1,
    0x76C1, 0x7543, 0x7181, 0x6C93, 0x678D, 0x6385, 0x6191, 0x613B, 0x614D, 0x61BA, 0x627B, 0x6384,
    0x64CA, 0x6645, 0x67E8, 0x69AB, 0x6B83, 0x6D65, 0x7027, 0x7426, 0x78A4, 0x7CE5, 0x802E, 0x81BB,
    0x81FB, 0x81DE, 0x8172, 0x80C4, 0x7FDE, 0x7ED2, 0x7DAC, 0x7C77, 0x7B41, 0x7A17, 0x7907, 0x781C,
    0x7764, 0x76EC, 0x76C1, 0x0000,
};

// 0x05006028
static const u16 blargg_seg5_animindex_05006028[] = {
    0x0001, 0x0000, 0x002D, 0x0001, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x002E, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x002D, 0x008A, 0x0001, 0x0000, 0x0001, 0x0000, 0x002D, 0x005D,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x005C, 0x0001, 0x0000, 0x0001, 0x0000, 0x002D, 0x002F,
};

// 0x05006070
static const struct Animation blargg_seg5_anim_05006070 = {
    0,
    0,
    0,
    0,
    0x2D,
    ANIMINDEX_NUMPARTS(blargg_seg5_animindex_05006028),
    blargg_seg5_animvalue_05005EB8,
    blargg_seg5_animindex_05006028,
    0,
};
