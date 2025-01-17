// 0x0C0001BC
const GeoLayout enemy_lakitu_geo[] = {
    GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x96, 100),
    GEO_OPEN_NODE(),
    GEO_SCALE(0x00, 16384),
    GEO_OPEN_NODE(),
    GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 63, -62, lakitu_enemy_seg5_dl_050138B0),
    GEO_OPEN_NODE(),
    GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, lakitu_enemy_seg5_dl_05012910),
    GEO_OPEN_NODE(),
    GEO_ANIMATED_PART(LAYER_OPAQUE, 132, 0, 0, lakitu_enemy_seg5_dl_05013160),
    GEO_OPEN_NODE(),
    GEO_SWITCH_CASE(2, geo_switch_anim_state),
    GEO_OPEN_NODE(),
    GEO_DISPLAY_LIST(LAYER_ALPHA, lakitu_enemy_seg5_dl_05013350),
    GEO_DISPLAY_LIST(LAYER_ALPHA, lakitu_enemy_seg5_dl_05013378),
    GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_ANIMATED_PART(LAYER_OPAQUE, 87, 18, 72, NULL),
    GEO_OPEN_NODE(),
    GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, lakitu_enemy_seg5_dl_050136A0),
    GEO_CLOSE_NODE(),
    GEO_ANIMATED_PART(LAYER_OPAQUE, 87, 18, -72, NULL),
    GEO_OPEN_NODE(),
    GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, lakitu_enemy_seg5_dl_050134A8),
    GEO_ASM(0, geo_update_projectile_pos_from_parent),
    GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
    GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_END(),
};
