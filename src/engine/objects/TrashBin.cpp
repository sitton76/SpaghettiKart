#include "TrashBin.h"
#include "World.h"

extern "C" {
#include "code_800029B0.h"
#include "render_objects.h"
#include "update_objects.h"
#include "assets/banshee_boardwalk_data.h"
#include "assets/common_data.h"
#include "math_util.h"
#include "math_util_2.h"
#include "code_80086E70.h"
#include "code_80057C60.h"
#include "audio/external.h"
}

#define DEGREES_FLOAT_TO_SHORT(Degrees) ((s16)((Degrees) * (0x8000 / 180.0f)))

OTrashBin::OTrashBin(const FVector& pos, const FRotation& rotation, f32 scale) {
    _pos = pos;
    _rot = rotation;
    _scale = scale;

    // if (gIsMirrorMode != 0) {
    //     gObjectList[objectIndex].pos[0] = 1765.0f;
    //     gObjectList[objectIndex].pos[2] = 195.0f;
    //     gObjectList[objectIndex].orientation[1] = (s16) rotation.y;
    // } else {
    //     gObjectList[objectIndex].pos[0] = -1765.0f;
    //     gObjectList[objectIndex].pos[2] = 70.0f;
    // }

}

void OTrashBin::Tick() {
    s32 objectIndex = indexObjectList1[1];
    OTrashBin::func_8007E00C(objectIndex);
    if (gModeSelection != TIME_TRIALS) {
        func_8007DDC0(objectIndex);
    }
}

void OTrashBin::Draw(s32 cameraId) {
    s32 objectIndex;
    Object* object;

    objectIndex = indexObjectList1[1];
    func_8008A364(objectIndex, cameraId, 0x5555U, 0x00000320);
    if (is_obj_flag_status_active(objectIndex, VISIBLE) != 0) {
        object = &gObjectList[objectIndex];
        if (object->state >= 2) {
            func_80043220(object->pos, object->orientation, object->sizeScaling, object->model);
        }
    }
}

void OTrashBin::init_bb_trash_bin(s32 objectIndex) {
    gObjectList[objectIndex].sizeScaling = _scale;
    gObjectList[objectIndex].model = (Gfx*)d_course_banshee_boardwalk_dl_trash_bin;
    gObjectList[objectIndex].unk_04C = 0;
    gObjectList[objectIndex].unk_084[7] = 0;
    set_obj_orientation(objectIndex, 0U, 0U, 0U);
    gObjectList[objectIndex].orientation[0] = DEGREES_FLOAT_TO_SHORT(_rot.pitch);
    gObjectList[objectIndex].orientation[1] = DEGREES_FLOAT_TO_SHORT(_rot.yaw);
    gObjectList[objectIndex].orientation[2] = DEGREES_FLOAT_TO_SHORT(_rot.roll);
    gObjectList[objectIndex].pos[0] = _pos.x;
    gObjectList[objectIndex].pos[1] = _pos.y;
    gObjectList[objectIndex].pos[2] = _pos.z;
    set_obj_velocity(objectIndex, 0.0f, 0.0f, 0.0f);
    gObjectList[objectIndex].type = 0;
    object_next_state(objectIndex);
}

#undef DEGREES_FLOAT_TO_SHORT

void OTrashBin::func_8007E00C(s32 objectIndex) {
    switch (gObjectList[objectIndex].state) {
        case 1:
            init_bb_trash_bin(objectIndex);
            break;
        case 3:
            D_8018CFB0 = 1;
            object_next_state(objectIndex);
            break;
        case 4:
            set_and_run_timer_object(objectIndex, 0x000000D2);
            if (D_80165594 == 0) {
                if (gCCSelection < CC_150) {
                    func_8007D714(1);
                    func_8007D714(1);
                } else {
                    func_8007D714(1);
                    func_8007D714(1);
                    func_8007D714(1);
                    func_8007D714(1);
                }
            }
            func_80073CB0(objectIndex, &gObjectList[objectIndex].primAlpha, -0x00002000, 0, 0x00000400, 0, -1);
            gObjectList[objectIndex].orientation[2] = gObjectList[objectIndex].primAlpha;
            if (gObjectList[objectIndex].unk_084[7] == 0) {
                func_800C98B8(gObjectList[objectIndex].pos, gObjectList[objectIndex].velocity,
                              SOUND_ARG_LOAD(0x19, 0x01, 0x90, 0x4E));
                gObjectList[objectIndex].unk_084[7] = 0x0014;
            } else {
                gObjectList[objectIndex].unk_084[7]--;
            }
            break;
        case 5:
            gObjectList[objectIndex].orientation[2] = func_800417B4(gObjectList[objectIndex].orientation[2], 0U);
            if (gObjectList[objectIndex].orientation[2] == 0) {
                object_next_state(objectIndex);
            }
            break;
        case 6:
            gObjectList[objectIndex].orientation[2] = 0;
            gObjectList[objectIndex].unk_084[7] = 0;
            object_next_state(objectIndex);
            D_8018CFB0 = 0;
            break;
        case 0:
        case 2:
        default:
            break;
    }
}
