#include <libultraship.h>
#include <libultra/gbi.h>
#include "engine/vehicles/OThwomp.h"
#include <vector>

#include "port/Game.h"

extern "C" {
#include "macros.h"
#include "main.h"
#include "actors.h"
#include "math_util.h"
#include "sounds.h"
#include "update_objects.h"
#include "render_player.h"
#include "external.h"
#include "bomb_kart.h"
#include "collision.h"
#include "code_80086E70.h"
#include "render_objects.h"
#include "code_80057C60.h"
#include "defines.h"
#include "code_80005FD0.h"
#include "math_util_2.h"
#include "collision.h"
#include "assets/bowsers_castle_data.h"
#include "ceremony_and_credits.h"
#include "objects.h"
#include "update_objects.h"
#include "render_objects.h"
extern s8 gPlayerCount;
}

OThwomp::OThwomp(s32 i, f32 x, f32 z, s16 direction, f32 scale, s16 behaviour, s16 primAlpha) {
    if (i >= 32) {
        printf("MAX THWOMPS REACHED (32), skipping\n");
        return;
    }
    _idx = i;
    _faceDirection = direction;
    State = (States)behaviour;
    s32 objectId = indexObjectList1[i];
    init_object(objectId, 0);
    gObjectList[objectId].origin_pos[0] = x * xOrientation;
    gObjectList[objectId].origin_pos[2] = z;
    gObjectList[objectId].unk_0D5 = behaviour;
    gObjectList[objectId].primAlpha = primAlpha;

    if (scale == 0) {
        scale = 1;
    }

    gObjectList[objectId].sizeScaling = scale;
}

void OThwomp::Tick() { // func_80081210
    Player* player;
    s32 objectIndex;
    s32 var_s2_3;
    s32 var_s4;

    D_80165834[0] += 0x100;
    D_80165834[1] += 0x200;
    objectIndex = indexObjectList1[_idx];
    func_800722CC(objectIndex, 0x00000010);
    func_8008A4CC(objectIndex);

    OThwomp::func_8007F8D8();

    objectIndex = indexObjectList1[_idx];
    if (gObjectList[objectIndex].state != 0) {
        switch (State) {
            case STATIONARY:
                OThwomp::StationaryBehaviour(objectIndex);
                break;
            case MOVE_AND_ROTATE:
                OThwomp::MoveAndRotateBehaviour(objectIndex);
                break;
            case MOVE_FAR:
                OThwomp::MoveFarBehaviour(objectIndex);
                break;
            case STATIONARY_FAST:
                OThwomp::StationaryFastBehaviour(objectIndex);
                break;
            case JAILED:
                OThwomp::JailedBehaviour(objectIndex);
                break;
            case SLIDE:
                OThwomp::SlidingBehaviour(objectIndex);
                break;
        }
    }

    player = gPlayerOne;
    for (var_s4 = 0; var_s4 < NUM_PLAYERS; var_s4++, player++) {
        player->tyres[FRONT_LEFT].unk_14 &= ~3;
        player->unk_046 &= ~0x0006;

        objectIndex = indexObjectList1[_idx];
        if (!(player->effects & BOO_EFFECT)) {
            func_80080B28(objectIndex, var_s4);
        }
        if (is_obj_flag_status_active(objectIndex, 0x00020000) != 0) {
            func_80080A14(objectIndex, player);
        }
        if (is_obj_flag_status_active(objectIndex, 0x00010000) != 0) {
            func_80080A4C(objectIndex, var_s4);
        }

    }
    func_8007542C(3);

    objectIndex = indexObjectList1[_idx];
    if (func_80072320(objectIndex, 0x00000020) == 0) {
        return;
    }

    func_800722CC(objectIndex, 0x00000020);
    func_80080FEC(objectIndex);

    for (var_s4 = 0; var_s4 < gObjectParticle2_SIZE; var_s4++) {
        objectIndex = gObjectParticle2[var_s4];
        if (objectIndex == DELETED_OBJECT_ID) {
            return;
        }
        if (gObjectList[objectIndex].state == 0) {
            return;
        }
        func_800810F4(objectIndex);
        if (gObjectList[objectIndex].state != 0) {
            return;
        }
        delete_object_wrapper(&gObjectParticle2[var_s4]);
    }
}

void OThwomp::func_8007F8D8() {
    Player* player;
    s32 objectIndex;
    s32 var_s0;
    s32 someIndex;
    s32 var_s4;
    Object* object;

    player = gPlayerOne;
    var_s4 = 1;

    objectIndex = indexObjectList1[_idx];
    object = &gObjectList[objectIndex];
    if (object->unk_0D5 == 3) {
        var_s0 = 0;
        if ((object->state >= 2) && (func_80072354(objectIndex, 8) != 0)) {
            var_s0 = 1;
        }
        var_s4 *= var_s0;
    }

    if (var_s4 != 0) {
        for (var_s0 = 0; var_s0 < 4; var_s0++, player++) {
            if ((player->type & PLAYER_EXISTS) && !(player->type & PLAYER_KART_AI)) {
                if (OThwomp::func_8007F75C(var_s0) != 0) {
                    break;
                }
            }
        }
    }
}

s32 OThwomp::func_8007F75C(s32 playerId) {
    s32 someIndex;
    s32 objectIndex;
    s32 temp_s7;
    s32 var_s6;
    s32 waypoint;

    waypoint = gNearestWaypointByPlayerId[playerId];
    var_s6 = 0;
    if ((waypoint >= 0xAA) && (waypoint < 0xB5)) {
        temp_s7 = random_int(0x0032U) + 0x32;
        objectIndex = indexObjectList1[_idx];
        if (gObjectList[objectIndex].unk_0D5 == 3) {
            var_s6 = 1;
            func_8007F660(objectIndex, playerId, temp_s7);
        }

    } else if ((waypoint >= 0xD7) && (waypoint < 0xE2)) {
        objectIndex = indexObjectList1[_idx];
        if (gObjectList[objectIndex].unk_0D5 == 3) {
            var_s6 = 1;
            func_8007F6C4(objectIndex, playerId);
        }
    }
    return var_s6;
}

Lights1 thwompLight = gdSPDefLights1(85, 85, 85, 255, 255, 255, -66, 82, -55);

void OThwomp::Draw(s32 cameraId) {
    s32 objectIndex = 0;
    s32 i;
    UNUSED s32 stackPadding0;
    s16 minusone, plusone;
    Camera* camera;
    Object* object;
    // Lights1 *thwompLightl = (Lights1 *) LOAD_ASSET(thwompLight);

    camera = &camera1[cameraId];
    if (cameraId == PLAYER_ONE) {
        objectIndex = indexObjectList1[_idx];
        set_object_flag_status_false(objectIndex, 0x00070000);
        func_800722CC(objectIndex, 0x00000110);
    }

    func_800534A4(objectIndex);

    objectIndex = indexObjectList1[_idx];
    minusone = gObjectList[objectIndex].unk_0DF - 1;
    plusone = gObjectList[objectIndex].unk_0DF + 1;

    //! @todo Fix this quick hack fix to allow thwomps to render in custom courses
    OThwomp::DrawModel(objectIndex);
    if (GetCourse() != GetBowsersCastle()) {
    } else {
        if (gGamestate != CREDITS_SEQUENCE) {
            if ((D_8018CF68[cameraId] >= minusone) && (plusone >= D_8018CF68[cameraId]) &&
                (is_object_visible_on_camera(objectIndex, camera, 0x8000) != 0)) {
                OThwomp::DrawModel(objectIndex);
            }
        } else { // CREDITS_SEQUENCE
            OThwomp::DrawModel(objectIndex);
        }
    }

    gSPDisplayList(gDisplayListHead++, (Gfx*)D_0D0079C8);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gSPNumLights(gDisplayListHead++, 1);
    gSPLight(gDisplayListHead++, &thwompLight.l[0], LIGHT_1);
    gSPLight(gDisplayListHead++, &thwompLight.a, LIGHT_2);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BOTH);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADE | G_LIGHTING | G_SHADING_SMOOTH);
    load_texture_block_rgba16_mirror((u8*)d_course_bowsers_castle_thwomp_side, 0x00000020, 0x00000020);
    for (i = 0; i < gObjectParticle3_SIZE; i++) {
        objectIndex = gObjectParticle3[i];
        if (objectIndex != NULL_OBJECT_ID) {
            object = &gObjectList[objectIndex];
            if ((object->state > 0) && (State == MOVE_FAR) && (gMatrixHudCount <= MTX_HUD_POOL_SIZE_MAX)) {
                rsp_set_matrix_transformation(object->pos, object->orientation, object->sizeScaling);
                gSPVertex(gDisplayListHead++, (uintptr_t)D_0D005C00, 3, 0);
                gSPDisplayList(gDisplayListHead++, (Gfx*)D_0D006930);
            }
        }
    }
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPTexture(gDisplayListHead++, 0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF);
    gSPDisplayList(gDisplayListHead++, (Gfx*)D_0D007AE0);
    load_texture_block_ia8_nomirror(D_8018D490, 0x00000020, 0x00000020);
    func_8004B3C8(0);
    D_80183E80[0] = 0;
    D_80183E80[2] = 0x8000;
    for (i = 0; i < gObjectParticle2_SIZE; i++) {
        objectIndex = gObjectParticle2[i];
        if (objectIndex != NULL_OBJECT_ID) {
            object = &gObjectList[objectIndex];
            if ((object->state >= 2) && (State == MOVE_AND_ROTATE) && (gMatrixHudCount <= MTX_HUD_POOL_SIZE_MAX)) {
                func_8004B138(0x000000FF, 0x000000FF, 0x000000FF, (s32) object->primAlpha);
                D_80183E80[1] = func_800418AC(object->pos[0], object->pos[2], camera->pos);
                func_800431B0(object->pos, D_80183E80, object->sizeScaling, (Vtx*)D_0D005AE0);
            }
        }
    }
}

void OThwomp::DrawModel(s32 objectIndex) {
    if ((gObjectList[objectIndex].state >= 2) && (func_80072354(objectIndex, 0x00000040) != 0)) {
        func_8004A7AC(objectIndex, 1.75f);
        rsp_set_matrix_transformation(gObjectList[objectIndex].pos, gObjectList[objectIndex].orientation,
                                      gObjectList[objectIndex].sizeScaling);
        func_800534E8(objectIndex);
        gSPDisplayList(gDisplayListHead++, (Gfx*)D_0D007828);
        gDPSetTextureLUT(gDisplayListHead++, G_TT_RGBA16);
        gDPLoadTLUT_pal256(gDisplayListHead++, d_course_bowsers_castle_thwomp_tlut);
        rsp_load_texture_mask((u8*)gObjectList[objectIndex].activeTexture, 0x00000010, 0x00000040, 4);
        gSPDisplayList(gDisplayListHead++, gObjectList[objectIndex].model);
    }
}

void OThwomp::StationaryBehaviour(s32 objectIndex) { // func_8007ED6C
    UNUSED s32 stackPadding[4];
    switch (gObjectList[objectIndex].state) {
        case 0:
            break;
        case 1:
            OThwomp::func_8007EC30(objectIndex);
            break;
        case 2:
            set_and_run_timer_object(objectIndex, 0x0000003C);
            break;
        case 3:
            func_80072568(objectIndex, 0x00000032);
            break;
        case 4:
            if (func_8007E59C(objectIndex) != 0) {
                func_800725E8(objectIndex, 0x0000012C, 2);
            } else {
                func_800726CC(objectIndex, 2);
            }
            break;
    }
    func_8007E63C(objectIndex);
    object_calculate_new_pos_offset(objectIndex);
    gObjectList[objectIndex].direction_angle[1] = gObjectList[objectIndex].orientation[1];
    func_80073514(objectIndex);
}

// Stationary
void OThwomp::func_8007EC30(s32 objectIndex) {
    Object* object;

    object = &gObjectList[objectIndex];
    object->surfaceHeight = 0.0f;
    object->origin_pos[1] = 0.0f;
    set_obj_origin_offset(objectIndex, 0.0f, 0.0f, 0.0f);
    if (gIsMirrorMode != 0) {
        set_obj_direction_angle(objectIndex, 0U, -_faceDirection, 0U);
        set_obj_orientation(objectIndex, 0U, -_faceDirection, 0U);
    } else {
        set_obj_direction_angle(objectIndex, 0U, _faceDirection, 0U);
        set_obj_orientation(objectIndex, 0U, _faceDirection, 0U);
    }
    init_texture_object(objectIndex, (uint8_t*) d_course_bowsers_castle_thwomp_tlut, (const char**) d_course_bowsers_castle_thwomp_faces,
                        0x10U, (u16) 0x00000040);
    object->model = (Gfx*)d_course_bowsers_castle_dl_thwomp;
    object->boundingBoxSize = 0x000C;
    object->unk_01C[1] = 30.0f;
    set_object_flag_status_true(objectIndex, 0x05000220);
    object->type = 0;
    object->unk_0DF = 6;
    func_800724DC(objectIndex);
    object_next_state(objectIndex);
}

void OThwomp::MoveAndRotateBehaviour(s32 objectIndex) { // func_8007F5A8

    switch (gObjectList[objectIndex].state) { /* irregular */
        case 0:
            break;
        case 1:
            OThwomp::func_8007EE5C(objectIndex);
            break;
        case 3:
            func_80072568(objectIndex, 0x00000032);
            break;
        case 4:
            func_80086FD4(objectIndex);
            object_next_state(objectIndex);
            break;
    }
    func_8007E63C(objectIndex);
    func_8007F544(objectIndex);
    object_calculate_new_pos_offset(objectIndex);
    func_80073514(objectIndex);
}

// MoveAndRotateBehaviour
void OThwomp::func_8007EE5C(s32 objectIndex) {
    Object* object;

    init_texture_object(objectIndex, (u8*)d_course_bowsers_castle_thwomp_tlut, (const char**) d_course_bowsers_castle_thwomp_faces,
                        0x10U, (u16) 0x00000040);
    object = &gObjectList[objectIndex];
    object->model = (Gfx*)d_course_bowsers_castle_dl_thwomp;
    object->boundingBoxSize = 0x000C;
    set_object_flag_status_true(objectIndex, 0x04000220);
    object->type = 0;
    object->unk_0DF = 6;
    func_80086E70(objectIndex);
    object->surfaceHeight = 0.0f;
    object->origin_pos[1] = 0.0f;
    set_obj_origin_offset(objectIndex, 0.0f, 20.0f, 0.0f);
    object->unk_01C[1] = 20.0f;
    if (gIsMirrorMode != 0) {
        set_obj_direction_angle(objectIndex, 0U, -_faceDirection, 0U);
        set_obj_orientation(objectIndex, 0U, -_faceDirection, 0U);
    } else {
        set_obj_direction_angle(objectIndex, 0U, _faceDirection, 0U);
        set_obj_orientation(objectIndex, 0U, _faceDirection, 0U);
    }
    object->unk_0AE = 1;
    if (object->primAlpha == 0) {
        object->unk_0DD = 1;
    } else {
        object->unk_0DD = 2;
    }
    object_next_state(objectIndex);
}

void OThwomp::MoveFarBehaviour(s32 objectIndex) { // func_8007FFC0
    switch (gObjectList[objectIndex].state) {
        case 0:
            break;
        case 1:
            OThwomp::func_8007FA08(objectIndex);
            break;
        case 3:
            func_80072568(objectIndex, 0x00000032);
            break;
        case 4:
            object_next_state(objectIndex);
            func_80086FD4(objectIndex);
            break;
    }
    func_8007E63C(objectIndex);
    func_8007FF5C(objectIndex);
    object_calculate_new_pos_offset(objectIndex);
    func_80073514(objectIndex);
}

// MoveFarBehaviour
void OThwomp::func_8007FA08(s32 objectIndex) {
    Object* object;

    init_texture_object(objectIndex, (u8*)d_course_bowsers_castle_thwomp_tlut, (const char**) d_course_bowsers_castle_thwomp_faces,
                        0x10U, (u16) 0x00000040);
    object = &gObjectList[objectIndex];
    object->model = (Gfx*)d_course_bowsers_castle_dl_thwomp;
    object->boundingBoxSize = 0x000C;
    set_object_flag_status_true(objectIndex, 0x04000220);
    object->type = 0;
    object->surfaceHeight = 0.0f;
    object->origin_pos[1] = 0.0f;
    set_obj_origin_offset(objectIndex, 0.0f, 0.0f, 0.0f);
    set_obj_direction_angle(objectIndex, 0U, 0U, 0U);
    if (gIsMirrorMode != 0) {
        set_obj_orientation(objectIndex, 0U, 0xC000U, 0U);
    } else {
        set_obj_orientation(objectIndex, 0U, 0x4000U, 0U);
    }
    object->velocity[0] = 0.0f;
    object->direction_angle[1] = object->orientation[1];
    object->unk_0DD = 1;
    object->unk_0DF = 8;
    object->offset[1] = 15.0f;
    object->unk_01C[1] = 15.0f;
    object_next_state(objectIndex);
}

void OThwomp::StationaryFastBehaviour(s32 objectIndex) { // func_800801FC
    Object* object;

    object = &gObjectList[objectIndex];
    switch (object->state) {
        case 0:
            break;
        case 1:
            OThwomp::func_80080078(objectIndex);
            break;
        case 2:
            set_and_run_timer_object(objectIndex, object->timer);
            break;
        case 3:
            func_80072568(objectIndex, 0x00000032);
            break;
        case 4:
            object->timer = 0x0000003C;
            func_800726CC(objectIndex, 2);
            break;
    }
    func_8007E63C(objectIndex);
    object_calculate_new_pos_offset(objectIndex);
    func_80073514(objectIndex);
}

// StationaryFastBehaviour
void OThwomp::func_80080078(s32 objectIndex) { // func_80080078
    Object* object;

    init_texture_object(objectIndex, (u8*)d_course_bowsers_castle_thwomp_tlut, (const char**) d_course_bowsers_castle_thwomp_faces,
                        0x10U, (u16) 0x00000040);
    object = &gObjectList[objectIndex];
    object->model = (Gfx*)d_course_bowsers_castle_dl_thwomp;
    object->boundingBoxSize = 0x000C;
    set_object_flag_status_true(objectIndex, 0x04000220);
    object->type = 2;
    object->unk_0DF = 8;
    set_obj_direction_angle(objectIndex, 0U, 0U, 0U);
    object->surfaceHeight = 0.0f;
    object->origin_pos[1] = 0.0f;
    set_obj_origin_offset(objectIndex, 0.0f, 0.0f, 0.0f);
    object->unk_01C[1] = 30.0f;
    if (gIsMirrorMode != 0) {
        set_obj_orientation(objectIndex, 0U, -_faceDirection, 0U);
    } else {
        set_obj_orientation(objectIndex, 0U, _faceDirection, 0U);
    }
    switch (object->primAlpha) { /* irregular */
        case 0:
            object->timer = 2;
            break;
        case 1:
            object->timer = 0x0000003C;
            break;
        case 2:
            object->timer = 0x00000078;
            break;
        case 3:
            object->timer = 0x000000B4;
            break;
    }
    func_800724DC(objectIndex);
    object_next_state(objectIndex);
}

void OThwomp::JailedBehaviour(s32 objectIndex) { // func_80080408
    switch (gObjectList[objectIndex].state) {
        case 0:
            break;
        case 1:
            OThwomp::func_800802C0(objectIndex);
            break;
        case 2:
            func_8008A6DC(objectIndex, 100.0f);
            if (is_obj_flag_status_active(objectIndex, VISIBLE) != 0) {
                func_800C98B8(gObjectList[objectIndex].pos, gObjectList[objectIndex].velocity,
                              SOUND_ARG_LOAD(0x19, 0x01, 0x80, 0x45));
                object_next_state(objectIndex);
            }
            break;
        case 3:
            if (func_800730BC(objectIndex, 3, 5, 1, 6, 6) != 0) {
                gObjectList[objectIndex].textureListIndex = 0;
            }
            break;
        case 4:
            if (set_and_run_timer_object(objectIndex, 0x0000012C) != 0) {
                func_800726CC(objectIndex, 2);
            }
            break;
    }
    object_calculate_new_pos_offset(objectIndex);
    func_80073514(objectIndex);
}

// JailedBehaviour
void OThwomp::func_800802C0(s32 objectIndex) {
    Object* object;

    object = &gObjectList[objectIndex];
    object->unk_0D8 = 0;
    init_texture_object(objectIndex, (u8*)d_course_bowsers_castle_thwomp_tlut, (const char**) d_course_bowsers_castle_thwomp_faces,
                        0x10U, (u16) 0x00000040);
    object->model = (Gfx*)d_course_bowsers_castle_dl_thwomp;
    object->textureListIndex = 0;
    object->boundingBoxSize = 0x000C;
    //object->sizeScaling = 1.5f;
    set_object_flag_status_true(objectIndex, 0x05000220);
    object->type = 1;
    object->unk_0DF = 6;
    set_obj_origin_offset(objectIndex, 0.0f, 0.0f, 0.0f);
    set_obj_direction_angle(objectIndex, 0U, 0U, 0U);
    object->surfaceHeight = 0.0f;
    object->origin_pos[1] = 0.0f;
    object->offset[1] = 10.0f;
    object->unk_01C[1] = 10.0f;
    if (gIsMirrorMode != 0) {
        set_obj_orientation(objectIndex, 0U, 0x4000U, 0U);
    } else {
        set_obj_orientation(objectIndex, 0U, 0xC000U, 0U);
    }
    object->offset[0] = 0.0f;
    object->offset[2] = 0.0f;
    func_800724DC(objectIndex);
    object_next_state(objectIndex);
}

void OThwomp::SlidingBehaviour(s32 objectIndex) { // func_800808CC
    switch (gObjectList[objectIndex].state) { /* irregular */
        case 0:
            break;
        case 1:
            OThwomp::func_80080524(objectIndex);
            break;
        case 2:
            func_800730BC(objectIndex, 3, 5, 1, 6, -1);
            break;
    }
    if (gObjectList[objectIndex].state >= 2) {
        func_8007E63C(objectIndex);
        func_8008085C(objectIndex);
        func_80073514(objectIndex);
        if (gGamestate != 9) {
            if ((D_8018D40C == 0) && (gObjectList[objectIndex].state == 2)) {
                func_800C98B8(gObjectList[objectIndex].pos, gObjectList[objectIndex].velocity,
                              SOUND_ARG_LOAD(0x19, 0x03, 0x60, 0x45));
            }
        } else if ((gCutsceneShotTimer < 0xBF) && (((s16) gCutsceneShotTimer % 88) == 0x0000001E)) {
            func_800C98B8(gObjectList[objectIndex].pos, gObjectList[objectIndex].velocity,
                          SOUND_ARG_LOAD(0x19, 0x03, 0x60, 0x45));
        }
    }
}

// SlidingBehaviour
void OThwomp::func_80080524(s32 objectIndex) {
    Object* object;

    init_texture_object(objectIndex, (u8*)d_course_bowsers_castle_thwomp_tlut, (const char**) d_course_bowsers_castle_thwomp_faces,
                        0x10U, (u16) 0x00000040);
    object = &gObjectList[objectIndex];
    object->model = (Gfx*)d_course_bowsers_castle_dl_thwomp;
    object->boundingBoxSize = 0x000C;
    object->textureListIndex = 0;
    set_object_flag_status_true(objectIndex, 0x04000220);
    object->type = 0;
    object->unk_0DF = 0x0A;
    func_80086E70(objectIndex);
    set_obj_origin_offset(objectIndex, 0.0f, 0.0f, 0.0f);
    object->surfaceHeight = 70.0f;
    object->origin_pos[1] = 70.0f;
    object->unk_01C[1] = 0.0f;
    set_obj_direction_angle(objectIndex, 0U, 0U, 0U);
    if ((gIsMirrorMode != 0) || (gGamestate == CREDITS_SEQUENCE)) {
        set_obj_orientation(objectIndex, 0U, -_faceDirection, 0U);
    } else {
        set_obj_orientation(objectIndex, 0U, _faceDirection, 0U);
    }
    switch (object->primAlpha) { /* irregular */
        case 0:
            object->unk_0DD = 2;
            object->velocity[2] = -1.0f;
            break;
        case 1:
            object->unk_0DD = 2;
            object->velocity[2] = -1.5f;
            break;
    }
    func_800722A4(objectIndex, 0x00000080);
    object_next_state(objectIndex);
}
