// 0x0E000A18
const GeoLayout jrb_geo_000A18[] = {
    GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2),
    GEO_OPEN_NODE(),
    GEO_ZBUFFER(0),
    GEO_OPEN_NODE(),
    GEO_NODE_ORTHO(100),
    GEO_OPEN_NODE(),
    GEO_BACKGROUND(BACKGROUND_ABOVE_CLOUDS, geo_skybox_main),
    GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_ZBUFFER(1),
    GEO_OPEN_NODE(),
    GEO_CAMERA_FRUSTUM_WITH_FUNC(45, 100, 25000, geo_camera_fov),
    GEO_OPEN_NODE(),
    GEO_CAMERA(16, 0, 2000, 6000, 0, 0, 0, geo_camera_main),
    GEO_OPEN_NODE(),
    GEO_DISPLAY_LIST(LAYER_ALPHA, jrb_seg7_dl_07002FD0),
    GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_07004940),
    GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_07004C78),
    GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_070058C8),
    GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_070069B0),
    GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_07007570),
    GEO_DISPLAY_LIST(LAYER_ALPHA, jrb_seg7_dl_07007718),
    GEO_ASM(0, geo_movtex_pause_control),
    GEO_ASM(0x1201, geo_movtex_draw_water_regions),
    GEO_ASM(0x1205, geo_movtex_draw_water_regions),
    GEO_RENDER_OBJ(),
    GEO_ASM(14, geo_envfx_main),
    GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_ZBUFFER(0),
    GEO_OPEN_NODE(),
    GEO_ASM(0, geo_cannon_circle_base),
    GEO_CLOSE_NODE(),
    GEO_CLOSE_NODE(),
    GEO_END(),
};
