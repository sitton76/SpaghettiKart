#include <libultraship.h>
#include <libultra/gbi.h>
#include "engine/vehicles/OPenguin.h"
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
#include "course_offsets.h"
#include "data/some_data.h"
extern s8 gPlayerCount;
}

OPenguin::OPenguin(s32 i, Vec3f pos, u16 direction, PenguinType type, Behaviour behaviour) {
    if (i >= 32) {
        printf("MAX penguin REACHED (32), skipping\n");
        return;
    }
    _idx = i;
    _type = type;
    _bhv = behaviour;

    s32 objectIndex = indexObjectList1[i];
    init_object(objectIndex, 0);

    Object *object = &gObjectList[objectIndex];
    object->origin_pos[0] = pos[0] * xOrientation;
    object->origin_pos[1] = pos[1];
    object->origin_pos[2] = pos[2];
    object->unk_0C6 = direction;

    switch(type) {
        case PenguinType::CHICK:
            object->surfaceHeight = 5.0f;
            object->sizeScaling = 0.04f;
            object->boundingBoxSize = 4;
            break;
        case PenguinType::ADULT:
            object->surfaceHeight = -80.0f;
            object->sizeScaling = 0.08f;
            object->boundingBoxSize = 4;
            break;
        case PenguinType::CREDITS:
            object->surfaceHeight = -80.0f;
            object->sizeScaling = 0.08f;
            object->sizeScaling = 0.15f;
            break;
        case PenguinType::EMPEROR:
            object->sizeScaling = 0.2f;
            object->boundingBoxSize = 0x000C;
            break;
    }

}

void OPenguin::Tick(void) {
    s32 objectIndex;

    objectIndex = indexObjectList1[_idx];
    if (gObjectList[objectIndex].state != 0) {
        if (_type == PenguinType::EMPEROR) {
            OPenguin::EmperorPenguin(objectIndex);
        } else {
            OPenguin::OtherPenguin(objectIndex);
        }

        OPenguin::Behaviours(objectIndex, _idx);
    }
    if (func_80072320(objectIndex, 1) != 0) {
        func_80089820(objectIndex, 1.75f, 1.5f, 0x1900A046U);
    } else if (func_80072320(objectIndex, 8) != 0) {
        func_80089820(objectIndex, 1.3f, 1.0f, 0x1900A046U);
    } else {
        func_80089820(objectIndex, 1.5f, 1.25f, 0x1900A046U);
    }
    if ((is_obj_flag_status_active(objectIndex, 0x02000000) != 0) &&
        (func_80072354(objectIndex, 0x00000020) != 0)) {
        func_800722A4(objectIndex, 0x00000060);
        set_object_flag_status_false(objectIndex, 0x02000000);
    }
}

void OPenguin::Draw(s32 cameraId) {
    s32 objectIndex;
    s32 temp_s1;
    s32 drawDistance;
    u16 var_s1;
    u32 var_s3;

    if (gPlayerCountSelection1 == 1) {
        var_s3 = 0x0003D090;
    } else if (gPlayerCountSelection1 == 2) {
        var_s3 = 0x00027100;
    } else {
        var_s3 = 0x00015F90;
    }

    objectIndex = indexObjectList1[_idx];
    if (gObjectList[objectIndex].state >= 2) {
        if (gPlayerCountSelection1 == 1) {
            var_s1 = 0x4000;
            if (_idx == 0) {
                drawDistance = 0x000005DC;
            } else if (func_80072320(objectIndex, 8) != 0) {
                drawDistance = 0x00000320;
            } else {
                drawDistance = 0x000003E8;
            }
        } else {
            if (func_80072320(objectIndex, 8) != 0) {
                drawDistance = 0x000001F4;
                var_s1 = 0x4000;
            } else {
                drawDistance = 0x00000258;
                var_s1 = 0x5555;
            }
        }
        temp_s1 = func_8008A364(objectIndex, cameraId, var_s1, drawDistance);
        if (is_obj_flag_status_active(objectIndex, VISIBLE) != 0) {
            func_800557B4(objectIndex, (u32) temp_s1, var_s3);
        }
    }
}

void OPenguin::Behaviours(s32 objectIndex, s32 arg1) {
    Object* object;

    object = &gObjectList[objectIndex];
    switch (_bhv) {
        case 1: // emperor
            func_80085080(objectIndex);
            break;
        case 2:
            func_8008502C(objectIndex, arg1);
            break;
        case 3:
            func_80084D2C(objectIndex, 0);
            break;
        case 4:
            func_80084D2C(objectIndex, 1);
            break;
        case 5:
            func_80084D2C(objectIndex, 2);
            break;
        case 6:
            func_80084D2C(objectIndex, 3);
            break;
    }
    if (func_80072320(objectIndex, 0x00000020) != 0) {
        if (func_80072320(objectIndex, 0x00000040) != 0) {
            func_800722CC(objectIndex, 0x00000040);
            object->unk_084[6] = 0;
            object->unk_084[7] = 0x0096;
        }
        if (object->unk_084[7] == 0) {
            func_800722CC(objectIndex, 0x00000020);
        } else {
            object->unk_084[7]--;
            object->orientation[0] = object->direction_angle[0];
            object->orientation[1] += 0x2000;
            object->orientation[2] = object->direction_angle[2];
        }
    } else {
        object->orientation[0] = object->direction_angle[0];
        object->orientation[1] = object->direction_angle[1];
        object->orientation[2] = object->direction_angle[2];
    }
}

void OPenguin::EmperorPenguin(s32 objectIndex) {
    switch (gObjectList[objectIndex].state) {
        case 0:
            break;
        case 1:
            OPenguin::InitEmperorPenguin(objectIndex);
            break;
        case 2:
            func_80072E54(objectIndex, 0, gObjectList[objectIndex].type, 1, 0, -1);
            break;
    }
}

void OPenguin::InitEmperorPenguin(s32 objectIndex) {
    Object* object;

    object = &gObjectList[objectIndex];
    object->unk_0D8 = 0;
    object->model = (Gfx*) d_course_sherbet_land_unk_data1;
    object->vertex = (Vtx*) d_course_sherbet_land_unk_data11;
    //object->sizeScaling = 0.2f;
    //object->boundingBoxSize = 0x000C;
    object->unk_09C = 1;
    set_obj_direction_angle(objectIndex, 0U, 0U, 0U);
    object->unk_0DD = 1;
    func_80086EF0(objectIndex);
    object->spline = D_800E672C[0];
    set_object_flag_status_true(objectIndex, 0x04000800);
    object->type = get_animation_length(d_course_sherbet_land_unk_data11, 0);
    object_next_state(objectIndex);
}

void OPenguin::OtherPenguin(s32 objectIndex) {
    Object* object;

    object = &gObjectList[objectIndex];
    switch (object->state) {
        case 0:
            break;
        case 1:
            OPenguin::InitOtherPenguin(objectIndex);
            break;
        case 2:
            func_80072E54(objectIndex, 0, (s32) object->type, (s32) object->unk_09C, 0, -1);
            if (func_80072354(objectIndex, 0x00000020) != 0) {
                if (object->unk_084[6] == 0) {
                    object->unk_084[6] = random_int(0x005AU) + 0x5A;
                    func_800722A4(objectIndex, 0x00000080);
                } else {
                    object->unk_084[6]--;
                }
            }
            break;
        case 3:
            func_80072E54(objectIndex, 0, object->type, 1, 0, 0);
            break;
        case 4:
            func_800722CC(objectIndex, 2);
            object_next_state(objectIndex);
            break;
    }
    if (func_80072320(objectIndex, 0x00000020) != 0) {
        if (object->unk_084[6] == 0) {
            func_800722A4(objectIndex, 0x00000080);
            object->unk_084[6] = 0x0010;
        } else {
            object->unk_084[6]--;
        }
    }
    if (func_80072320(objectIndex, 0x00000080) != 0) {
        func_800722CC(objectIndex, 0x00000080);
        if (func_80072320(objectIndex, 0x00000010) != 0) {
            func_800C98B8(object->pos, object->velocity, SOUND_ARG_LOAD(0x19, 0x00, 0x70, 0x49));
        } else {
            func_800C98B8(object->pos, object->velocity, SOUND_ARG_LOAD(0x19, 0x00, 0x70, 0x17));
        }
    }
}

void OPenguin::InitOtherPenguin(s32 objectIndex) {
    Object* object;

    object = &gObjectList[objectIndex];
    object->unk_0D8 = 0;
    object->model = (Gfx*) d_course_sherbet_land_unk_data1;
    object->vertex = (Vtx*) d_course_sherbet_land_unk_data11;
    //object->boundingBoxSize = 4;
    object->unk_09C = 2;
    object->unk_04C = random_int(0x012CU);
    set_object_flag_status_true(objectIndex, 0x04000220);

    switch(_bhv) {
        case Behaviour::CIRCLE:
            object->unk_01C[1] = Diameter;
            object->unk_0C4 = (_idx << 0xF) & 0xFFFF;
            //object->unk_0DD = 2;
            func_800722A4(objectIndex, 8);
            break;
        case Behaviour::SLIDE3:
        case Behaviour::SLIDE4:
        case Behaviour::SLIDE6:
        case Behaviour::STRUT:

            if (gIsMirrorMode) {
                object->unk_0C6 = MirrorModeAngleOffset;
            }

            set_obj_direction_angle(objectIndex, 0U, object->unk_0C6 + 0x8000, 0U);
            func_800722A4(objectIndex, 20);
            break;
    }

    if ((_idx > 0) && (_idx < 9)) {
        if ((_idx == 1) || (_idx == 2)) {
            //object->unk_0C6 = 0x0150;
            //object->unk_01C[1] = 100.0f;
        } else if ((_idx == 3) || (_idx == 4)) {
            //object->unk_0C6 = 0x0100;
            //object->unk_01C[1] = 80.0f;
        } else if ((_idx == 5) || (_idx == 6)) {
            //object->unk_0C6 = 0xFF00;
            //object->unk_01C[1] = 80.0f;
        } else if ((_idx == 7) || (_idx == 8)) {
            //object->unk_0C6 = 0x0150;
            //object->unk_01C[1] = 80.0f;
        }
        //object->unk_0C4 = (_idx << 0xF) & 0xFFFF;
        //object->surfaceHeight = -80.0f;
        //object->sizeScaling = 0.08f;
        //object->unk_0DD = 2;
        //func_800722A4(objectIndex, 8);
    } else if ((_idx > 8) && (_idx < 15)) {
        switch (_idx) {
            case 9:
                if (gGamestate != CREDITS_SEQUENCE) {
                } else {
                    //object->sizeScaling = 0.15f;
                }
                //object->unk_0C6 = 0x9000;
                if (gIsMirrorMode != 0) {
                    //object->unk_0C6 -= 0x4000;
                }
                //object->unk_0DD = 3;
                break;
            case 10:
                //object->unk_0C6 = 0x5000;
                if (gIsMirrorMode != 0) {
                    //object->unk_0C6 += 0x8000;
                }
                //object->unk_0DD = 4;
                break;
            case 11:
                //object->unk_0C6 = 0xC000;
                //object->unk_0DD = 6;
                if (gIsMirrorMode != 0) {
                    //object->unk_0C6 += 0x8000;
                }
                break;
            case 12:
                //object->unk_0C6 = 0x4000;
                //object->unk_0DD = 6;
                if (gIsMirrorMode != 0) {
                    //object->unk_0C6 += 0x8000;
                }
                break;
            case 13:
               // object->unk_0C6 = 0x8000;
                //object->unk_0DD = 6;
                if (gIsMirrorMode != 0) {
                    //object->unk_0C6 -= 0x4000;
                }
                break;
            case 14:
                //object->unk_0C6 = 0x9000;
                //object->unk_0DD = 6;
                if (gIsMirrorMode != 0) {
                    //object->unk_0C6 -= 0x4000;
                }
                break;
            default:
                break;
        }
        //set_obj_direction_angle(objectIndex, 0U, object->unk_0C6 + 0x8000, 0U);
        //object->surfaceHeight = 5.0f;
        //object->sizeScaling = 0.04f;
        //func_800722A4(objectIndex, 0x00000014);
    }
    func_80086EF0(objectIndex);
    object->unk_034 = 0.0f;
    object->type = get_animation_length(d_course_sherbet_land_unk_data11, 0);
    object_next_state(objectIndex);
}
