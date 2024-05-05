#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "types.h"
#include <!sm64/src/game/memory.h>

#define GRAPH_RENDER_ACTIVE (1 << 0)
#define GRAPH_RENDER_CHILDREN_FIRST (1 << 1)
#define GRAPH_RENDER_BILLBOARD (1 << 2)
#define GRAPH_RENDER_Z_BUFFER (1 << 3)
#define GRAPH_RENDER_INVISIBLE (1 << 4)
#define GRAPH_RENDER_HAS_ANIMATION (1 << 5)
#define GRAPH_RENDER_CYLBOARD (1 << 6)

// Whether the node type has a function pointer of type GraphNodeFunc
#define GRAPH_NODE_TYPE_FUNCTIONAL 0x100

// Type used for Bowser and an unused geo function in obj_behaviors.c
#define GRAPH_NODE_TYPE_400 0x400

// The discriminant for different types of geo nodes
#define GRAPH_NODE_TYPE_ROOT 0x001
#define GRAPH_NODE_TYPE_ORTHO_PROJECTION 0x002
#define GRAPH_NODE_TYPE_PERSPECTIVE (0x003 | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_MASTER_LIST 0x004
#define GRAPH_NODE_TYPE_START 0x00A
#define GRAPH_NODE_TYPE_LEVEL_OF_DETAIL 0x00B
#define GRAPH_NODE_TYPE_SWITCH_CASE (0x00C | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_CAMERA (0x014 | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_TRANSLATION_ROTATION 0x015
#define GRAPH_NODE_TYPE_TRANSLATION 0x016
#define GRAPH_NODE_TYPE_ROTATION 0x017
#define GRAPH_NODE_TYPE_OBJECT 0x018
#define GRAPH_NODE_TYPE_ANIMATED_PART 0x019
#define GRAPH_NODE_TYPE_BILLBOARD 0x01A
#define GRAPH_NODE_TYPE_DISPLAY_LIST 0x01B
#define GRAPH_NODE_TYPE_SCALE 0x01C
#define GRAPH_NODE_TYPE_SHADOW 0x028
#define GRAPH_NODE_TYPE_OBJECT_PARENT 0x029
#define GRAPH_NODE_TYPE_GENERATED_LIST (0x02A | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_BACKGROUND (0x02C | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_HELD_OBJ (0x02E | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_CULLING_RADIUS 0x02F

// The number of master lists. A master list determines the order and render
// mode with which display lists are drawn.
#define GFX_NUM_MASTER_LISTS 8

// Passed as first argument to a GraphNodeFunc to give information about in
// which context it was called and what it is expected to do.
#define GEO_CONTEXT_CREATE 0      // called when node is created from a geo command
#define GEO_CONTEXT_RENDER 1      // called from rendering_graph_node.c
#define GEO_CONTEXT_AREA_UNLOAD 2 // called when unloading an area
#define GEO_CONTEXT_AREA_LOAD 3   // called when loading an area
#define GEO_CONTEXT_AREA_INIT 4   // called when initializing the 8 areas
#define GEO_CONTEXT_HELD_OBJ 5    // called when processing a GraphNodeHeldObj

// The signature for a function stored in a geo node
// The context argument depends on the callContext:
// - for GEO_CONTEXT_CREATE it is the AllocOnlyPool from which the node was allocated
// - for GEO_CONTEXT_RENDER or GEO_CONTEXT_HELD_OBJ it is the top of the float matrix stack with type
// Mat4
// - for GEO_CONTEXT_AREA_* it is the root geo node
typedef Gfx *(*GraphNodeFunc)(s32 callContext, struct GraphNode *node, void *context);

/** An extension of a graph node that includes a function pointer.
 *  Many graph node types have an update function that gets called
 *  when they are processed.
 */
struct FnGraphNode {
    /*0x00*/ struct GraphNode node;
    /*0x14*/ GraphNodeFunc func;
};
/* Specifies position and dimensions of the viewport. */
struct GraphNodeRoot {
    struct GraphNode node;    // GraphNode containing viewport info
    u8 areaIndex;             // Index of the area
    s8 unk15;                 // Unknown
    s16 x;                    // X position
    s16 y;                    // Y position
    s16 width;                // Width
    s16 height;               // Height
    s16 numViews;             // Number of views
    struct GraphNode **views; // Array of view nodes
};

/* Sets up an orthographic projection. */
struct GraphNodeOrthoProjection {
    struct GraphNode node; // GraphNode containing orthographic projection info
    f32 scale;             // Scaling factor
};

/* Sets up a perspective projection. */
struct GraphNodePerspective {
    struct FnGraphNode fnNode; // GraphNode containing perspective projection info
    f32 fov;                   // Horizontal field of view in degrees
    s16 near;                  // Near clipping plane
    s16 far;                   // Far clipping plane
    f32 prevFov;               // Previous field of view
    f32 prevTimestamp;         // Previous timestamp
};

/* Manages top-level display lists and render modes. */
struct GraphNodeMasterList {
    struct GraphNode node;                                   // GraphNode containing master list info
    struct DisplayListNode *listHeads[GFX_NUM_MASTER_LISTS]; // Array of list heads
    struct DisplayListNode *listTails[GFX_NUM_MASTER_LISTS]; // Array of list tails
};

/* Simply used as a parent to group multiple children. */
struct GraphNodeStart {
    struct GraphNode node; // GraphNode used for grouping children
};

/* Renders children based on z-translation in camera space. */
struct GraphNodeLevelOfDetail {
    struct GraphNode node; // GraphNode containing level of detail info
    s16 minDistance;       // Minimum distance for rendering
    s16 maxDistance;       // Maximum distance for rendering
};

/* Renders one of its children based on selectedCase. */
struct GraphNodeSwitchCase {
    struct FnGraphNode fnNode; // GraphNode containing switch case info
    s16 numCases;              // Number of cases
    s16 selectedCase;          // Selected case
};

/* Specifies camera location and aim. */
struct GraphNodeCamera {
    struct FnGraphNode fnNode; // GraphNode containing camera info
    union {
        s32 mode;              // Camera mode
        struct Camera *camera; // Pointer to camera
    } config;
    Vec3f pos;                   // Position
    Vec3f focus;                 // Focus
    Vec3f prevPos;               // Previous position
    Vec3f prevFocus;             // Previous focus
    u32 prevTimestamp;           // Previous timestamp
    Mat4 *matrixPtr;             // Pointer to look-at matrix
    Mat4 *matrixPtrInterpolated; // Interpolated matrix pointer
    s16 roll;                    // Roll
    s16 rollScreen;              // Screen roll
};

/* Translates and rotates children. */
struct GraphNodeTranslationRotation {
    struct GraphNode node; // GraphNode containing translation and rotation info
    void *displayList;     // Display list
    Vec3s translation;     // Translation
    Vec3s rotation;        // Rotation
};

/* Translates itself and its children. */
struct GraphNodeTranslation {
    struct GraphNode node; // GraphNode containing translation info
    void *displayList;     // Display list
    Vec3s translation;     // Translation
};

/* Rotates itself and its children. */
struct GraphNodeRotation {
    struct GraphNode node; // GraphNode containing rotation info
    void *displayList;     // Display list
    Vec3s rotation;        // Rotation
    Vec3s prevRotation;    // Previous rotation
    u32 prevTimestamp;     // Previous timestamp
};

/* Part that transforms itself and its children based on animation data. */
struct GraphNodeAnimatedPart {
    struct GraphNode node; // GraphNode containing animated part info
    void *displayList;     // Display list
    Vec3s translation;     // Translation
};

/* Draws a display list always facing the camera. */
struct GraphNodeBillboard {
    struct GraphNode node; // GraphNode containing billboard info
    void *displayList;     // Display list
    Vec3s translation;     // Translation
};

/* Draws a display list without transformation. */
struct GraphNodeDisplayList {
    struct GraphNode node; // GraphNode containing display list info
    void *displayList;     // Display list
};

/* Scales itself and its children. */
struct GraphNodeScale {
    struct GraphNode node; // GraphNode containing scale info
    void *displayList;     // Display list
    f32 scale;             // Scale factor
};

/* Draws a shadow under an object. */
struct GraphNodeShadow {
    struct GraphNode node; // GraphNode containing shadow info
    s16 shadowScale;       // Shadow scale
    u8 shadowSolidity;     // Shadow solidity
    u8 shadowType;         // Shadow type
};

/* Contains a group node containing all object nodes. */
struct GraphNodeObjectParent {
    struct GraphNode node;         // GraphNode containing object parent info
    struct GraphNode *sharedChild; // Shared child node
};

/* Draws display lists generated by a function. */
struct GraphNodeGenerated {
    struct FnGraphNode fnNode; // GraphNode containing generated info
    u32 parameter;             // Parameter for function
};

/* Draws a background image or a colored rectangle. */
struct GraphNodeBackground {
    struct FnGraphNode fnNode; // GraphNode containing background info
    s32 unused;                // Unused field
    s32 background;            // Background ID or color
    Vec3f prevCameraPos;       // Previous camera position
    Vec3f prevCameraFocus;     // Previous camera focus
    u32 prevCameraTimestamp;   // Previous camera timestamp
};

/* Renders the object that Mario is holding. */
struct GraphNodeHeldObject {
    struct FnGraphNode fnNode;  // GraphNode containing held object info
    s32 playerIndex;            // Player index
    struct Object *objNode;     // Object node
    Vec3s translation;          // Translation
    Vec3f prevShadowPos;        // Previous shadow position
    u32 prevShadowPosTimestamp; // Previous shadow position timestamp
};

/* Allows an object to specify a different culling radius. */
struct GraphNodeCullingRadius {
    struct GraphNode node; // GraphNode containing culling radius info
    s16 cullingRadius;     // Culling radius
    u8 pad1E[2];           // Padding
};

/** An entry in the master list. It is a linked list of display lists
 *  carrying a transformation matrix.
 */
struct DisplayListNode {
    Mtx *transform;
    void *transformInterpolated;
    void *displayList;
    void *displayListInterpolated;
    struct DisplayListNode *next;
};

extern struct GraphNodeMasterList *gCurGraphNodeMasterList;
extern struct GraphNodePerspective *gCurGraphNodeCamFrustum;
extern struct GraphNodeCamera *gCurGraphNodeCamera;
extern struct GraphNodeHeldObject *gCurGraphNodeHeldObject;
extern u16 gAreaUpdateCounter;

extern struct GraphNode *gCurRootGraphNode;
extern struct GraphNode *gCurGraphNodeList[];

extern s16 gCurGraphNodeIndex;

extern Vec3f gVec3fZero;
extern Vec3s gVec3sZero;
extern Vec3f gVec3fOne;
extern Vec3s gVec3sOne;

void init_scene_graph_node_links(struct GraphNode *graphNode, s32 type);

struct GraphNodeRoot *init_graph_node_root(struct AllocOnlyPool *pool, s16 areaIndex, s16 x, s16 y,
                                           s16 width, s16 height);
struct GraphNodeOrthoProjection *init_graph_node_ortho_projection(struct AllocOnlyPool *pool,
                                                                  f32 scale);
struct GraphNodePerspective *init_graph_node_perspective(struct AllocOnlyPool *pool, f32 fov, s16 near,
                                                         s16 far, GraphNodeFunc nodeFunc);
struct GraphNodeStart *init_graph_node_start(struct AllocOnlyPool *pool,
                                             struct GraphNodeStart *graphNode);
struct GraphNodeMasterList *init_graph_node_master_list(struct AllocOnlyPool *pool, s16 on);
struct GraphNodeLevelOfDetail *init_graph_node_render_range(struct AllocOnlyPool *pool,
                                                            struct GraphNodeLevelOfDetail *graphNode,
                                                            s16 minDistance, s16 maxDistance);
struct GraphNodeSwitchCase *init_graph_node_switch_case(struct AllocOnlyPool *pool, s16 numCases,
                                                        s16 selectedCase, GraphNodeFunc nodeFunc);
struct GraphNodeCamera *init_graph_node_camera(struct AllocOnlyPool *pool, f32 *pos, f32 *focus,
                                               GraphNodeFunc func, s32 mode);
struct GraphNodeTranslationRotation *
init_graph_node_translation_rotation(struct AllocOnlyPool *pool,
                                     struct GraphNodeTranslationRotation *graphNode, s32 drawingLayer,
                                     void *displayList, Vec3s translation, Vec3s rotation);
struct GraphNodeTranslation *init_graph_node_translation(struct AllocOnlyPool *pool,
                                                         struct GraphNodeTranslation *graphNode,
                                                         s32 drawingLayer, void *displayList,
                                                         Vec3s translation);
struct GraphNodeRotation *init_graph_node_rotation(struct AllocOnlyPool *pool, s32 drawingLayer,
                                                   void *displayList, Vec3s rotation);
struct GraphNodeScale *init_graph_node_scale(struct AllocOnlyPool *pool, s32 drawingLayer,
                                             void *displayList, f32 scale);
struct GraphNodeObject *init_graph_node_object(struct AllocOnlyPool *pool,
                                               struct GraphNodeObject *graphNode,
                                               struct GraphNode *sharedChild, Vec3f pos, Vec3s angle,
                                               Vec3f scale);
struct GraphNodeCullingRadius *init_graph_node_culling_radius(struct AllocOnlyPool *pool, s16 radius);
struct GraphNodeAnimatedPart *init_graph_node_animated_part(struct AllocOnlyPool *pool,
                                                            s32 drawingLayer, void *displayList,
                                                            Vec3s translation);
struct GraphNodeBillboard *init_graph_node_billboard(struct AllocOnlyPool *pool, s32 drawingLayer,
                                                     void *displayList, Vec3s translation);
struct GraphNodeDisplayList *init_graph_node_display_list(struct AllocOnlyPool *pool, s32 drawingLayer,
                                                          void *displayList);
struct GraphNodeShadow *init_graph_node_shadow(struct AllocOnlyPool *pool, s16 shadowScale,
                                               u8 shadowSolidity, u8 shadowType);
struct GraphNodeObjectParent *init_graph_node_object_parent(struct AllocOnlyPool *pool,
                                                            struct GraphNode *sharedChild);
struct GraphNodeGenerated *init_graph_node_generated(struct AllocOnlyPool *pool, GraphNodeFunc gfxFunc,
                                                     s32 parameter);
struct GraphNodeBackground *init_graph_node_background(struct AllocOnlyPool *pool, u16 background,
                                                       GraphNodeFunc backgroundFunc);
struct GraphNodeHeldObject *init_graph_node_held_object(struct AllocOnlyPool *pool,
                                                        struct Object *objNode, Vec3s translation,
                                                        GraphNodeFunc nodeFunc, s32 playerIndex);
struct GraphNode *geo_add_child(struct GraphNode *parent, struct GraphNode *childNode);
struct GraphNode *geo_remove_child(struct GraphNode *graphNode);
struct GraphNode *geo_make_first_child(struct GraphNode *newFirstChild);

void geo_call_global_function_nodes_helper(struct GraphNode *graphNode, s32 callContext);
void geo_call_global_function_nodes(struct GraphNode *graphNode, s32 callContext);

void geo_reset_object_node(struct GraphNodeObject *graphNode);
void geo_obj_init(struct GraphNodeObject *graphNode, void *sharedChild, Vec3f pos, Vec3s angle);
void geo_obj_init_spawninfo(struct GraphNodeObject *graphNode, struct SpawnInfo *spawn);
void geo_obj_init_animation(struct GraphNodeObject *graphNode, struct Animation **animPtrAddr);
void geo_obj_init_animation_accel(struct GraphNodeObject *graphNode, struct Animation **animPtrAddr,
                                  u32 animAccel);

s32 retrieve_animation_index(s32 frame, u16 **attributes);

s16 geo_update_animation_frame(struct GraphNodeObject_sub *obj, s32 *accelAssist);
void geo_retreive_animation_translation(struct GraphNodeObject *obj, Vec3f position);

struct GraphNodeRoot *geo_find_root(struct GraphNode *graphNode);

// graph_node_manager
s16 *read_vec3s_to_vec3f(Vec3f, s16 *src);
s16 *read_vec3s(Vec3s dst, s16 *src);
s16 *read_vec3s_angle(Vec3s dst, s16 *src);
void register_scene_graph_node(struct GraphNode *graphNode);

#endif // GRAPH_NODE_H
