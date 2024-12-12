#pragma once

#include <libultraship.h>
#include <vector>

extern "C" {
#include "macros.h"
#include "main.h"
#include "vehicles.h"
#include "waypoints.h"
#include "common_structs.h"
#include "objects.h"
#include "course_offsets.h"
#include "some_data.h"
}


class OCrab {
public:
    enum Behaviour : uint16_t {
    };

public:
    f32 Diameter = 0.0f; // Waddle in a circle around the spawn point at this diameter.
    uint16_t MirrorModeAngleOffset;

    explicit OCrab(s32 i, Vec3f pos);

    void Tick();
    void Draw(s32 objectIndex, s32 cameraId);
    void DrawModel(s32 cameraId);

    void init_ktb_crab(s32 objectIndex);
    void func_80082B34(s32 objectIndex);
    void func_80082C30(s32 objectIndex);
    void func_80082E18(s32 objectIndex);

private:

    s32 _idx;
};
