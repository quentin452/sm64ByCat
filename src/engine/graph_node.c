#include <ultra64.h>
#include "sm64.h"

#include <!sm64/src/game/level_update.h>
#include <!sm64/src/engine/math_util.h>
#include <!sm64/src/game/memory.h>
#include <!sm64/src/engine/graph_node.h>
#include <!sm64/src/game/rendering_graph_node.h>
#include <!sm64/src/game/area.h>
#include <!sm64/src/engine/geo_layout.h>
#include <stdio.h>
Vec3f gVec3fZero = { 0.0f, 0.0f, 0.0f };
Vec3s gVec3sZero = { 0, 0, 0 };
Vec3f gVec3fOne = { 1.0f, 1.0f, 1.0f };
/**
 * Initialize a geo node with a given type. Sets all links such that there
 * are no siblings, parent or children for this node.
 */
void init_scene_graph_node_links(struct GraphNode *graphNode, s32 type) {
    graphNode->type = type;
    graphNode->flags = GRAPH_RENDER_ACTIVE;
    graphNode->prev = graphNode;
    graphNode->next = graphNode;
    graphNode->parent = NULL;
    graphNode->children = NULL;
}
struct GraphNode *init_graph_node(struct AllocOnlyPool *pool, struct GraphNode *graphNode, size_t size,
                                  s32 type, const char *caller) {
    if (!pool) {
        printf("Attention: Le pool de mémoire est NULL lors de l'initialisation du nœud de type %d "
               "dans %s.\n",
               type, caller);
        return NULL;
    }

    graphNode = alloc_only_pool_alloc(pool, size);
    if (!graphNode) {
        printf("Erreur: Impossible d'allouer %zu octets pour le nœud de type %d dans %s.\n", size, type,
               caller);
        return NULL;
    }

    init_scene_graph_node_links(graphNode, type);
    return graphNode;
}

/**
 * Allocated and returns a newly created root node
 */
struct GraphNodeRoot *init_graph_node_root(struct AllocOnlyPool *pool, s16 areaIndex, s16 x, s16 y,
                                           s16 width, s16 height) {
    struct GraphNodeRoot *graphNode = (struct GraphNodeRoot *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeRoot), GRAPH_NODE_TYPE_ROOT, __func__);
    graphNode->areaIndex = areaIndex;
    graphNode->unk15 = 0;
    graphNode->x = x;
    graphNode->y = y;
    graphNode->width = width;
    graphNode->height = height;
    graphNode->views = NULL;
    graphNode->numViews = 0;
    return graphNode;
}

/**
 * Allocates and returns a newly created otrhographic projection node
 */
struct GraphNodeOrthoProjection *init_graph_node_ortho_projection(struct AllocOnlyPool *pool,
                                                                  f32 scale) {
    struct GraphNodeOrthoProjection *graphNode = (struct GraphNodeOrthoProjection *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeOrthoProjection), GRAPH_NODE_TYPE_ORTHO_PROJECTION,
        __func__);
    graphNode->scale = scale;
    return graphNode;
}

/**
 * Allocates and returns a newly created perspective node
 */
struct GraphNodePerspective *init_graph_node_perspective(struct AllocOnlyPool *pool, f32 fov, s16 near,
                                                         s16 far, GraphNodeFunc nodeFunc, s32 unused) {
    struct GraphNodePerspective *graphNode = (struct GraphNodePerspective *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodePerspective), GRAPH_NODE_TYPE_PERSPECTIVE, __func__);
    graphNode->fov = fov;
    graphNode->near = near;
    graphNode->far = far;
    graphNode->fnNode.func = nodeFunc;
    graphNode->unused = unused;
    if (nodeFunc != NULL) {
        nodeFunc(GEO_CONTEXT_CREATE, &graphNode->fnNode.node, pool);
    }
    return graphNode;
}

/**
 * Allocates and returns a newly created start node
 */
struct GraphNodeStart *init_graph_node_start(struct AllocOnlyPool *pool,
                                             struct GraphNodeStart *graphNode) {
    if (pool != NULL) {
        graphNode = alloc_only_pool_alloc(pool, sizeof(struct GraphNodeStart));
    }
    if (graphNode != NULL) {
        init_scene_graph_node_links(&graphNode->node, GRAPH_NODE_TYPE_START);
    }
    return graphNode;
}

/**
 * Allocates and returns a newly created master list node
 */
struct GraphNodeMasterList *init_graph_node_master_list(struct AllocOnlyPool *pool, s16 on) {
    struct GraphNodeMasterList *graphNode = (struct GraphNodeMasterList *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeMasterList), GRAPH_NODE_TYPE_MASTER_LIST, __func__);
    if (on) {
        graphNode->node.flags |= GRAPH_RENDER_Z_BUFFER;
    }
    return graphNode;
}

/**
 * Allocates and returns a newly created render range node
 */
struct GraphNodeLevelOfDetail *init_graph_node_render_range(struct AllocOnlyPool *pool,
                                                            struct GraphNodeLevelOfDetail *graphNode,
                                                            s16 minDistance, s16 maxDistance) {
    graphNode = (struct GraphNodeLevelOfDetail *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeLevelOfDetail), GRAPH_NODE_TYPE_LEVEL_OF_DETAIL, __func__);
    graphNode->minDistance = minDistance;
    graphNode->maxDistance = maxDistance;
    return graphNode;
}

/**
 * Allocates and returns a newly created switch case node
 */
struct GraphNodeSwitchCase *init_graph_node_switch_case(struct AllocOnlyPool *pool, s16 numCases,
                                                        s16 selectedCase, GraphNodeFunc nodeFunc,
                                                        s32 unused) {
    struct GraphNodeSwitchCase *graphNode = (struct GraphNodeSwitchCase *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeSwitchCase), GRAPH_NODE_TYPE_SWITCH_CASE, __func__);
    graphNode->numCases = numCases;
    graphNode->selectedCase = selectedCase;
    graphNode->fnNode.func = nodeFunc;
    graphNode->unused = unused;
    if (nodeFunc != NULL) {
        nodeFunc(GEO_CONTEXT_CREATE, &graphNode->fnNode.node, pool);
    }
    return graphNode;
}

/**
 * Allocates and returns a newly created camera node
 */
struct GraphNodeCamera *init_graph_node_camera(struct AllocOnlyPool *pool, f32 *pos, f32 *focus,
                                               GraphNodeFunc func, s32 mode) {
    struct GraphNodeCamera *graphNode = (struct GraphNodeCamera *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeCamera), GRAPH_NODE_TYPE_CAMERA, __func__);
    vec3f_copy(graphNode->pos, pos);
    vec3f_copy(graphNode->focus, focus);
    graphNode->fnNode.func = func;
    graphNode->config.mode = mode;
    graphNode->roll = 0;
    graphNode->rollScreen = 0;
    if (func != NULL) {
        func(GEO_CONTEXT_CREATE, &graphNode->fnNode.node, pool);
    }
    return graphNode;
}

/**
 * Allocates and returns a newly created translation rotation node
 */
struct GraphNodeTranslationRotation *
init_graph_node_translation_rotation(struct AllocOnlyPool *pool,
                                     struct GraphNodeTranslationRotation *graphNode, s32 drawingLayer,
                                     void *displayList, Vec3s translation, Vec3s rotation) {
    graphNode = (struct GraphNodeTranslationRotation *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeTranslationRotation), GRAPH_NODE_TYPE_TRANSLATION_ROTATION,
        __func__);
    vec3s_copy(graphNode->translation, translation);
    vec3s_copy(graphNode->rotation, rotation);
    graphNode->node.flags = (drawingLayer << 8) | (graphNode->node.flags & 0xFF);
    graphNode->displayList = displayList;
    return graphNode;
}

/**
 * Allocates and returns a newly created translation node
 */
struct GraphNodeTranslation *init_graph_node_translation(struct AllocOnlyPool *pool,
                                                         struct GraphNodeTranslation *graphNode,
                                                         s32 drawingLayer, void *displayList,
                                                         Vec3s translation) {
    graphNode = (struct GraphNodeTranslation *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeTranslation), GRAPH_NODE_TYPE_TRANSLATION, __func__);
    vec3s_copy(graphNode->translation, translation);
    graphNode->node.flags = (drawingLayer << 8) | (graphNode->node.flags & 0xFF);
    graphNode->displayList = displayList;
    return graphNode;
}

/**
 * Allocates and returns a newly created rotation node
 */
struct GraphNodeRotation *init_graph_node_rotation(struct AllocOnlyPool *pool, s32 drawingLayer,
                                                   void *displayList, Vec3s rotation) {
    struct GraphNodeRotation *graphNode = (struct GraphNodeRotation *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeRotation), GRAPH_NODE_TYPE_ROTATION, __func__);
    vec3s_copy(graphNode->rotation, rotation);
    graphNode->node.flags = (drawingLayer << 8) | (graphNode->node.flags & 0xFF);
    graphNode->displayList = displayList;
    return graphNode;
}

/**
 * Allocates and returns a newly created scaling node
 */
struct GraphNodeScale *init_graph_node_scale(struct AllocOnlyPool *pool, s32 drawingLayer,
                                             void *displayList, f32 scale) {
    struct GraphNodeScale *graphNode = (struct GraphNodeScale *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeScale), GRAPH_NODE_TYPE_SCALE, __func__);
    graphNode->node.flags = (drawingLayer << 8) | (graphNode->node.flags & 0xFF);
    graphNode->scale = scale;
    graphNode->displayList = displayList;
    return graphNode;
}

/**
 * Allocates and returns a newly created object node
 */
struct GraphNodeObject *init_graph_node_object(struct AllocOnlyPool *pool,
                                               struct GraphNodeObject *graphNode,
                                               struct GraphNode *sharedChild, Vec3f pos, Vec3s angle,
                                               Vec3f scale) {
    if (pool != NULL) {
        graphNode = alloc_only_pool_alloc(pool, sizeof(struct GraphNodeObject));
    }
    if (graphNode != NULL) {
        init_scene_graph_node_links(&graphNode->node, GRAPH_NODE_TYPE_OBJECT);
        vec3f_copy(graphNode->pos, pos);
        vec3f_copy(graphNode->scale, scale);
        vec3s_copy(graphNode->angle, angle);
        graphNode->sharedChild = sharedChild;
        graphNode->throwMatrix = NULL;
        graphNode->unk38.animID = 0;
        graphNode->unk38.curAnim = NULL;
        graphNode->unk38.animFrame = 0;
        graphNode->unk38.animFrameAccelAssist = 0;
        graphNode->unk38.animAccel = 0x10000;
        graphNode->unk38.animTimer = 0;
        graphNode->node.flags |= GRAPH_RENDER_HAS_ANIMATION;
    }
    return graphNode;
}
/**
 * Allocates and returns a newly created frustum culling radius node
 */
struct GraphNodeCullingRadius *init_graph_node_culling_radius(struct AllocOnlyPool *pool, s16 radius) {
    struct GraphNodeCullingRadius *graphNode = (struct GraphNodeCullingRadius *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeCullingRadius), GRAPH_NODE_TYPE_CULLING_RADIUS, __func__);
    graphNode->cullingRadius = radius;
    return graphNode;
}
/**
 * Allocates and returns a newly created animated part node
 */
struct GraphNodeAnimatedPart *init_graph_node_animated_part(struct AllocOnlyPool *pool,
                                                            s32 drawingLayer, void *displayList,
                                                            Vec3s translation) {
    struct GraphNodeAnimatedPart *graphNode = (struct GraphNodeAnimatedPart *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeAnimatedPart), GRAPH_NODE_TYPE_ANIMATED_PART, __func__);
    vec3s_copy(graphNode->translation, translation);
    graphNode->node.flags = (drawingLayer << 8) | (graphNode->node.flags & 0xFF);
    graphNode->displayList = displayList;
    return graphNode;
}

/**
 * Allocates and returns a newly created billboard node
 */
struct GraphNodeBillboard *init_graph_node_billboard(struct AllocOnlyPool *pool, s32 drawingLayer,
                                                     void *displayList, Vec3s translation) {
    struct GraphNodeBillboard *graphNode = (struct GraphNodeBillboard *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeBillboard), GRAPH_NODE_TYPE_BILLBOARD, __func__);
    vec3s_copy(graphNode->translation, translation);
    graphNode->node.flags = (drawingLayer << 8) | (graphNode->node.flags & 0xFF);
    graphNode->displayList = displayList;
    return graphNode;
}

/**
 * Allocates and returns a newly created displaylist node
 */
struct GraphNodeDisplayList *init_graph_node_display_list(struct AllocOnlyPool *pool, s32 drawingLayer,
                                                          void *displayList) {
    struct GraphNodeDisplayList *graphNode = (struct GraphNodeDisplayList *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeDisplayList), GRAPH_NODE_TYPE_DISPLAY_LIST, __func__);
    graphNode->node.flags = (drawingLayer << 8) | (graphNode->node.flags & 0xFF);
    graphNode->displayList = displayList;
    return graphNode;
}

/**
 * Allocates and returns a newly created shadow node
 */
struct GraphNodeShadow *init_graph_node_shadow(struct AllocOnlyPool *pool, s16 shadowScale,
                                               u8 shadowSolidity, u8 shadowType) {
    struct GraphNodeShadow *graphNode = (struct GraphNodeShadow *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeShadow), GRAPH_NODE_TYPE_SHADOW, __func__);
    graphNode->shadowScale = shadowScale;
    graphNode->shadowSolidity = shadowSolidity;
    graphNode->shadowType = shadowType;
    return graphNode;
}

/**
 * Allocates and returns a newly created object parent node
 */
struct GraphNodeObjectParent *init_graph_node_object_parent(struct AllocOnlyPool *pool,
                                                            struct GraphNode *sharedChild) {
    struct GraphNodeObjectParent *graphNode = (struct GraphNodeObjectParent *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeObjectParent), GRAPH_NODE_TYPE_OBJECT_PARENT, __func__);
    graphNode->sharedChild = sharedChild;
    return graphNode;
}

/**
 * Allocates and returns a newly created generated node
 */
struct GraphNodeGenerated *init_graph_node_generated(struct AllocOnlyPool *pool, GraphNodeFunc gfxFunc,
                                                     s32 parameter) {
    struct GraphNodeGenerated *graphNode = (struct GraphNodeGenerated *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeGenerated), GRAPH_NODE_TYPE_GENERATED_LIST, __func__);
    graphNode->fnNode.func = gfxFunc;
    graphNode->parameter = parameter;

    if (gfxFunc != NULL) {
        gfxFunc(GEO_CONTEXT_CREATE, &graphNode->fnNode.node, pool);
    }
    return graphNode;
}

/**
 * Allocates and returns a newly created background node
 */
struct GraphNodeBackground *init_graph_node_background(struct AllocOnlyPool *pool, u16 background,
                                                       GraphNodeFunc backgroundFunc, s32 zero) {
    struct GraphNodeBackground *graphNode = (struct GraphNodeBackground *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeBackground), GRAPH_NODE_TYPE_BACKGROUND, __func__);
    graphNode->background = (background << 16) | background;
    graphNode->fnNode.func = backgroundFunc;
    graphNode->unused = zero; // always 0, unused
    if (backgroundFunc != NULL) {
        backgroundFunc(GEO_CONTEXT_CREATE, &graphNode->fnNode.node, pool);
    }
    return graphNode;
}

/**
 * Allocates and returns a newly created held object node
 */
struct GraphNodeHeldObject *init_graph_node_held_object(struct AllocOnlyPool *pool,
                                                        struct Object *objNode, Vec3s translation,
                                                        GraphNodeFunc nodeFunc, s32 playerIndex) {
    struct GraphNodeHeldObject *graphNode = (struct GraphNodeHeldObject *) init_graph_node(
        pool, NULL, sizeof(struct GraphNodeHeldObject), GRAPH_NODE_TYPE_HELD_OBJ, __func__);
    vec3s_copy(graphNode->translation, translation);
    graphNode->objNode = objNode;
    graphNode->fnNode.func = nodeFunc;
    graphNode->playerIndex = playerIndex;

    if (nodeFunc != NULL) {
        nodeFunc(GEO_CONTEXT_CREATE, &graphNode->fnNode.node, pool);
    }
    return graphNode;
}

/**
 * Adds 'childNode' to the end of the list children from 'parent'
 */
struct GraphNode *geo_add_child(struct GraphNode *parent, struct GraphNode *childNode) {
    struct GraphNode *parentFirstChild;
    struct GraphNode *parentLastChild;

    if (childNode != NULL) {
        childNode->parent = parent;
        parentFirstChild = parent->children;

        if (parentFirstChild == NULL) {
            parent->children = childNode;
            childNode->prev = childNode;
            childNode->next = childNode;
        } else {
            parentLastChild = parentFirstChild->prev;
            childNode->prev = parentLastChild;
            childNode->next = parentFirstChild;
            parentFirstChild->prev = childNode;
            parentLastChild->next = childNode;
        }
    }

    return childNode;
}

/**
 * Remove a node from the scene graph. It changes the links with its
 * siblings and with its parent, it doesn't deallocate the memory
 * since geo nodes are allocated in a pointer-bumping pool that
 * gets thrown out when changing areas.
 */
struct GraphNode *geo_remove_child(struct GraphNode *graphNode) {
    struct GraphNode *parent = graphNode->parent;

    // Remove link with siblings
    graphNode->prev->next = graphNode->next;
    graphNode->next->prev = graphNode->prev;

    // If this node was the first child, update the parent's first child pointer
    if (parent->children == graphNode) {
        parent->children = (graphNode->next == graphNode) ? NULL : graphNode->next;
    }

    return parent;
}

/**
 * Reorders the given node so it's the first child of its parent.
 * This is called on the Mario object when he is spawned. That's why Mario's
 * object is always drawn before any other objects. (Note that the geo order
 * is independent from processing group order, where Mario is not first.)
 */
struct GraphNode *geo_make_first_child(struct GraphNode *newFirstChild) {
    struct GraphNode *lastSibling;
    struct GraphNode *parent;
    struct GraphNode **firstChild;

    parent = newFirstChild->parent;
    firstChild = &parent->children;

    if (*firstChild != newFirstChild) {
        if ((*firstChild)->prev != newFirstChild) {
            newFirstChild->prev->next = newFirstChild->next;
            newFirstChild->next->prev = newFirstChild->prev;
            lastSibling = (*firstChild)->prev;
            newFirstChild->prev = lastSibling;
            newFirstChild->next = *firstChild;
            (*firstChild)->prev = newFirstChild;
            lastSibling->next = newFirstChild;
        }
        *firstChild = newFirstChild;
    }

    return parent;
}

/**
 * Helper function for geo_call_global_function_nodes that recursively
 * traverses the scene graph and calls the functions of global nodes.
 */
void geo_call_global_function_nodes_helper(struct GraphNode *graphNode, s32 callContext) {
    struct GraphNode **globalPtr;
    struct GraphNode *curNode = graphNode;

    while (curNode) {
        struct FnGraphNode *asFnNode = (struct FnGraphNode *) curNode;

        if (curNode->type & GRAPH_NODE_TYPE_FUNCTIONAL) {
            if (asFnNode->func) {
                asFnNode->func(callContext, curNode, NULL);
            }
        }

        if (curNode->children) {
            switch (curNode->type) {
                case GRAPH_NODE_TYPE_MASTER_LIST:
                    globalPtr = (struct GraphNode **) &gCurGraphNodeMasterList;
                    break;
                case GRAPH_NODE_TYPE_PERSPECTIVE:
                    globalPtr = (struct GraphNode **) &gCurGraphNodeCamFrustum;
                    break;
                case GRAPH_NODE_TYPE_CAMERA:
                    globalPtr = (struct GraphNode **) &gCurGraphNodeCamera;
                    break;
                case GRAPH_NODE_TYPE_OBJECT:
                    globalPtr = (struct GraphNode **) &gCurGraphNodeObject;
                    break;
                default:
                    globalPtr = NULL;
                    break;
            }

            if (globalPtr) {
                *globalPtr = curNode;
            }

            geo_call_global_function_nodes_helper(curNode->children, callContext);

            if (globalPtr) {
                *globalPtr = NULL;
            }
        }

        curNode = curNode->next;
        if (curNode == graphNode) {
            break;
        }
    }
}

/**
 * Call the update functions of geo nodes that are stored in global variables.
 * These variables include gCurGraphNodeMasterList, gCurGraphNodeCamFrustum,
 * gCurGraphNodeCamera and gCurGraphNodeObject.
 * callContext is one of the GEO_CONTEXT_ defines.
 * The graphNode argument should be of type GraphNodeRoot.
 */
void geo_call_global_function_nodes(struct GraphNode *graphNode, s32 callContext) {
    if (graphNode->flags & GRAPH_RENDER_ACTIVE) {
        gCurGraphNodeRoot = (struct GraphNodeRoot *) graphNode;

        if (graphNode->children != NULL) {
            geo_call_global_function_nodes_helper(graphNode->children, callContext);
        }

        gCurGraphNodeRoot = 0;
    }
}

/**
 * When objects are cleared, this is called on all object nodes (loaded or unloaded).
 */
void geo_reset_object_node(struct GraphNodeObject *graphNode) {
    init_graph_node_object(NULL, graphNode, 0, gVec3fZero, gVec3sZero, gVec3fOne);

    geo_add_child(&gObjParentGraphNode, &graphNode->node);
    graphNode->node.flags &= ~GRAPH_RENDER_ACTIVE;
}

/**
 * Initialize an object node using the given parameters
 */
void geo_obj_init(struct GraphNodeObject *graphNode, void *sharedChild, Vec3f pos, Vec3s angle) {
    vec3f_set(graphNode->scale, 1.0f, 1.0f, 1.0f);
    vec3f_copy(graphNode->pos, pos);
    vec3s_copy(graphNode->angle, angle);

    graphNode->sharedChild = sharedChild;
    graphNode->unk4C = 0;
    graphNode->throwMatrix = NULL;
    graphNode->unk38.curAnim = NULL;

    graphNode->node.flags |= GRAPH_RENDER_ACTIVE;
    graphNode->node.flags &= ~GRAPH_RENDER_INVISIBLE;
    graphNode->node.flags |= GRAPH_RENDER_HAS_ANIMATION;
    graphNode->node.flags &= ~GRAPH_RENDER_BILLBOARD;
}

/**
 * Initialize and object node using the given SpawnInfo struct
 */
void geo_obj_init_spawninfo(struct GraphNodeObject *graphNode, struct SpawnInfo *spawn) {
    vec3f_set(graphNode->scale, 1.0f, 1.0f, 1.0f);
    vec3s_copy(graphNode->angle, spawn->startAngle);

    graphNode->pos[0] = (f32) spawn->startPos[0];
    graphNode->pos[1] = (f32) spawn->startPos[1];
    graphNode->pos[2] = (f32) spawn->startPos[2];

    graphNode->unk18 = spawn->areaIndex;
    graphNode->unk19 = spawn->activeAreaIndex;
    graphNode->sharedChild = spawn->unk18;
    graphNode->unk4C = spawn;
    graphNode->throwMatrix = NULL;
    graphNode->unk38.curAnim = 0;

    graphNode->node.flags |= GRAPH_RENDER_ACTIVE;
    graphNode->node.flags &= ~GRAPH_RENDER_INVISIBLE;
    graphNode->node.flags |= GRAPH_RENDER_HAS_ANIMATION;
    graphNode->node.flags &= ~GRAPH_RENDER_BILLBOARD;
}

/**
 * Initialize the animation of an object node
 */
void geo_obj_init_animation(struct GraphNodeObject *graphNode, struct Animation **animPtrAddr) {
    struct Animation **animSegmented = segmented_to_virtual(animPtrAddr);
    struct Animation *anim = segmented_to_virtual(*animSegmented);

    if (graphNode->unk38.curAnim != anim) {
        graphNode->unk38.curAnim = anim;
        graphNode->unk38.animFrame = anim->unk04 + ((anim->flags & ANIM_FLAG_FORWARD) ? 1 : -1);
        graphNode->unk38.animAccel = 0;
        graphNode->unk38.animYTrans = 0;
    }
}

/**
 * Initialize the animation of an object node
 */
void geo_obj_init_animation_accel(struct GraphNodeObject *graphNode, struct Animation **animPtrAddr,
                                  u32 animAccel) {
    struct Animation **animSegmented = segmented_to_virtual(animPtrAddr);
    struct Animation *anim = segmented_to_virtual(*animSegmented);

    if (graphNode->unk38.curAnim != anim) {
        graphNode->unk38.curAnim = anim;
        graphNode->unk38.animYTrans = 0;
        graphNode->unk38.animFrameAccelAssist =
            (anim->unk04 << 16) + ((anim->flags & ANIM_FLAG_FORWARD) ? animAccel : -animAccel);
        graphNode->unk38.animFrame = graphNode->unk38.animFrameAccelAssist >> 16;
    }

    graphNode->unk38.animAccel = animAccel;
}

/**
 * Retrieves an index into animation data based on the attribute pointer
 * An attribute is an x-, y- or z-component of the translation / rotation for a part
 * Each attribute is a pair of s16's, where the first s16 represents the maximum frame
 * and the second s16 the actual index. This index can be used to index in the array
 * with actual animation values.
 */
s32 retrieve_animation_index(s32 frame, u16 **attributes) {
    s32 maxFrame = (*attributes)[0];
    s32 startIndex = (*attributes)[1];
    s32 result;

    if (frame < maxFrame) {
        result = startIndex + frame;
    } else {
        result = startIndex + maxFrame - 1;
    }

    *attributes += 2;

    return result;
}

/**
 * Update the animation frame of an object. The animation flags determine
 * whether it plays forwards or backwards, and whether it stops or loops at
 * the end etc.
 */
s16 geo_update_animation_frame(struct GraphNodeObject_sub *obj, s32 *accelAssist) {
    s32 result;
    struct Animation *anim;

    anim = obj->curAnim;

    if (obj->animTimer == gAreaUpdateCounter || anim->flags & ANIM_FLAG_2) {
        if (accelAssist != NULL) {
            accelAssist[0] = obj->animFrameAccelAssist;
        }

        return obj->animFrame;
    }

    if (anim->flags & ANIM_FLAG_FORWARD) {
        if (obj->animAccel) {
            result = obj->animFrameAccelAssist - obj->animAccel;
        } else {
            result = (obj->animFrame - 1) << 16;
        }

        if (GET_HIGH_S16_OF_32(result) < anim->unk06) {
            if (anim->flags & ANIM_FLAG_NOLOOP) {
                SET_HIGH_S16_OF_32(result, anim->unk06);
            } else {
                SET_HIGH_S16_OF_32(result, anim->unk08 - 1);
            }
        }
    } else {
        if (obj->animAccel != 0) {
            result = obj->animFrameAccelAssist + obj->animAccel;
        } else {
            result = (obj->animFrame + 1) << 16;
        }

        if (GET_HIGH_S16_OF_32(result) >= anim->unk08) {
            if (anim->flags & ANIM_FLAG_NOLOOP) {
                SET_HIGH_S16_OF_32(result, anim->unk08 - 1);
            } else {
                SET_HIGH_S16_OF_32(result, anim->unk06);
            }
        }
    }

    if (accelAssist != 0) {
        accelAssist[0] = result;
    }

    return GET_HIGH_S16_OF_32(result);
}

/**
 * Unused function to retrieve an object's current animation translation
 * Assumes that it has x, y and z data in animations, which isn't always the
 * case since some animation types only have vertical or lateral translation.
 * This might have been used for positioning the shadow under an object, which
 * currently happens in-line in geo_process_shadow where it also accounts for
 * animations without lateral translation.
 */
void geo_retreive_animation_translation(struct GraphNodeObject *obj, Vec3f position) {
    struct Animation *animation = obj->unk38.curAnim;
    u16 *attribute;
    s16 *values;
    s16 frame;

    if (animation != NULL) {
        attribute = segmented_to_virtual((void *) animation->index);
        values = segmented_to_virtual((void *) animation->values);

        frame = obj->unk38.animFrame;
        if (frame < 0) {
            frame = 0;
        }

        s32 index = retrieve_animation_index(frame, &attribute);
        f32 x_translation = (f32) values[index];
        f32 y_translation = (f32) values[index];
        f32 z_translation = (f32) values[index];

        position[0] = x_translation;
        position[1] = y_translation;
        position[2] = z_translation;
    } else {
        vec3f_set(position, 0, 0, 0);
    }
}

/**
 * Unused function to find the root of the geo node tree, which should be a
 * GraphNodeRoot. If it is not for some reason, null is returned.
 */
struct GraphNodeRoot *geo_find_root(struct GraphNode *graphNode) {
    while (graphNode->parent) {
        graphNode = graphNode->parent;
    }
    return (graphNode->type == GRAPH_NODE_TYPE_ROOT) ? (struct GraphNodeRoot *) graphNode : NULL;
}