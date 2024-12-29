#include <libultraship.h>
#include <libultra/gbi.h>
#include "Seagull.h"
#include "engine/Actor.h"
#include <vector>

#include "port/Game.h"

extern "C" {
#include "macros.h"
#include "main.h"
#include "defines.h"
#include "camera.h"
#include "update_objects.h"
#include "render_objects.h"
#include "actors.h"
#include "code_80057C60.h"
#include "code_80086E70.h"
#include "math_util.h"
#include "math_util_2.h"
#include "code_80005FD0.h"
#include "some_data.h"
#include "ceremony_and_credits.h"
extern SplineData D_800E6034;
extern SplineData D_800E60F0;
extern SplineData D_800E61B4;
extern SplineData D_800E6280;
}

SplineData* D_800E633C[] = { &D_800E6034, &D_800E60F0, &D_800E61B4, &D_800E6280 };

OSeagull::OSeagull(s32 i, Vec3f pos) {
    size_t objectId;
    _idx = i;

    s16 randZ;
    s16 randX;
    s16 randY;
    randX = random_int(200) + -100.0;
    randY = random_int(20);
    randZ = random_int(200) + -100.0;

    SpawnPos[0] = pos[0] + randX;
    SpawnPos[1] = pos[1] + randY;
    SpawnPos[2] = pos[2] + randZ;

    //for (i = 0; i < NUM_SEAGULLS; i++) {


    //objectId = indexObjectList2[i];
    //init_object(objectId, 0);


    //set_obj_origin_pos(objectId, pos[0], pos[1], pos[2]);
        //if (i < (NUM_SEAGULLS / 2)) {
    //gObjectList[objectId].unk_0D5 = 0;
        //} else {
        //    gObjectList[objectId].unk_0D5 = 1;
        //}
    //}
}

bool OSeagull::IsMod() { return true; }

void OSeagull::Tick() {
    Object* object;
    UNUSED s32* var_s4;
    s32 temp_s0;

    //for (var_s3 = 0; var_s3 < NUM_SEAGULLS; var_s3++) {
        //temp_s0 = indexObjectList2[_idx];

        //object = &gObjectList[temp_s0];
        if (_state == 0) {
            return;
        }

        OSeagull::func_80082714(temp_s0, _idx);
        OSeagull::func_8008275C(temp_s0);
        if (_toggle) {
            _toggle = false;
            if (D_80165A90 != 0) {
                D_80165A90 = 0;
                D_80183E40[0] = 0.0f;
                D_80183E40[1] = 0.0f;
                D_80183E40[2] = 0.0f;
                if (gGamestate != CREDITS_SEQUENCE) {
                    func_800C98B8(Pos, D_80183E40, SOUND_ARG_LOAD(0x19, 0x01, 0x70, 0x43));
                } else {
                    //temp_s0 = indexObjectList2[1];
                    //! @todo confirm this is equivallent to indexObjectList2[1];
                    if (_idx == 1) {
                        if (gCutsceneShotTimer <= 150) {
                            //object = &gObjectList[temp_s0];
                            func_800C98B8(Pos, D_80183E40, SOUND_ARG_LOAD(0x19, 0x01, 0x70, 0x43));
                        }
                    }
                }
            }
        }
    //}
    if (D_80165900 != 0) {
        D_80165900 -= 1;
    } else {
        if (gGamestate != CREDITS_SEQUENCE) {
            D_80165900 = 60;
        } else {
            D_80165900 = 15;
        }
        if ((D_80165908 != 0) && (D_80165A90 == 0)) {
            D_80165A90 = 1;
        }
    }
    D_80165908 = 0;
}

void OSeagull::Draw(Camera* camera) { // render_object_seagulls
    s32 var_s1;
    //for (i = 0; i < NUM_SEAGULLS; i++) {
        var_s1 = indexObjectList2[_idx];
        //! @todo: Quick hack to let seagull work in actor system. Should be cameraId not camera->playerId
        //if (func_8008A364(var_s1, camera->playerId, 0x5555U, 0x000005DC) < 0x9C401 && CVarGetInteger("gNoCulling", 0) == 0) {
            D_80165908 = 1;
            _toggle = true;
        //}
        //if (is_obj_flag_status_active(var_s1, VISIBLE) != 0) {
            OSeagull::func_800552BC(var_s1);
        //}
    //}
}

void OSeagull::func_800552BC(s32 objectIndex) {
    if (gObjectList[objectIndex].state >= 2) {
        rsp_set_matrix_transformation(gObjectList[objectIndex].pos, gObjectList[objectIndex].direction_angle,
                                      gObjectList[objectIndex].sizeScaling);
        gSPDisplayList(gDisplayListHead++, (Gfx*)D_0D0077D0);
        if (gIsGamePaused == 0) {
            gObjectList[objectIndex].unk_0A2 = render_animated_model((Armature*) gObjectList[objectIndex].model,
                                                                     (Animation**) gObjectList[objectIndex].vertex, 0,
                                                                     gObjectList[objectIndex].unk_0A2);
        } else {
            render_animated_model((Armature*) gObjectList[objectIndex].model,
                                  (Animation**) gObjectList[objectIndex].vertex, 0, gObjectList[objectIndex].unk_0A2);
        }
    }
}

void OSeagull::func_8008275C(s32 objectIndex) {
    UNUSED s32 stackPadding;
    switch (gObjectList[objectIndex].unk_0DD) {
        case 1:
            func_8008B78C(objectIndex);
            object_calculate_new_pos_offset(objectIndex);
            break;
        case 2:
            func_8008B78C(objectIndex);
            vec3f_copy(gObjectList[objectIndex].unk_01C, gObjectList[objectIndex].pos);
            func_8000D940(SpawnPos, (s16*) &gObjectList[objectIndex].unk_0C6,
                          gObjectList[objectIndex].unk_034, 0.0f, 0);
            Offset[0] *= 2.0;
            Offset[1] *= 2.5;
            Offset[2] *= 2.0;
            object_calculate_new_pos_offset(objectIndex);
            gObjectList[objectIndex].direction_angle[1] =
                get_angle_between_two_vectors(gObjectList[objectIndex].unk_01C, gObjectList[objectIndex].pos);
            break;
    }
    func_800873F4(objectIndex);
}

void OSeagull::func_8008241C(s32 objectIndex, s32 arg1) {
    UNUSED s16 stackPadding0;

    gObjectList[objectIndex].unk_0D8 = 1;
    gObjectList[objectIndex].model = (Gfx*) d_course_koopa_troopa_beach_unk4;
    gObjectList[objectIndex].vertex = (Vtx*) d_course_koopa_troopa_beach_unk_data5;
    gObjectList[objectIndex].sizeScaling = 0.2f;
    gObjectList[objectIndex].unk_0DD = 1;
    // if (gGamestate == CREDITS_SEQUENCE) {
    //     set_obj_origin_pos(objectIndex, randX + -360.0, randY + 60.0, randZ + -1300.0);
    // } else if (gObjectList[objectIndex].unk_0D5 != 0) {
    //     set_obj_origin_pos(objectIndex, (randX + 328.0) * xOrientation, randY + 20.0, randZ + 2541.0);
    // } else {
    //     set_obj_origin_pos(objectIndex, (randX + -985.0) * xOrientation, randY + 15.0, randZ + 1200.0);
    // }
    set_obj_direction_angle(objectIndex, 0U, 0U, 0U);
    gObjectList[objectIndex].unk_034 = 1.0f;
    func_80086EF0(objectIndex);
    //gObjectList[objectIndex].spline = D_800E633C[arg1 % 4];
    spline = D_800E633C[arg1 % 4];
    //set_object_flag(objectIndex, 0x800);
    //object_next_state(objectIndex);
    _status |= 0x800;
    _timer = 0;
    _status &= ~0x2000;
    _state++;
}


void OSeagull::func_80082714(s32 objectIndex, s32 arg1) {
    switch (gObjectList[objectIndex].state) {
        case 1:
            OSeagull::func_8008241C(objectIndex, arg1);
            break;
        case 0:
        default:
            break;
    }
}