#pragma once

#include <libultraship.h>
#include <vector>
#include "ParticleEmitter.h"

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

/**
 * Used in the podium ceremony when the trophy appears
 */
class StarEmitter : public ParticleEmitter {
public:
    enum Behaviour : uint16_t {
    };

public:
    f32 Diameter = 0.0f; // Waddle in a circle around the spawn point at this diameter.
    uint16_t MirrorModeAngleOffset;

    explicit StarEmitter(Vec3f pos);

    virtual void Tick() override;
    virtual void Draw(s32 cameraId) override;
    void func_80086700(s32 objectIndex);
    void func_80086940(s32 objectIndex);
    void func_80086C14(s32 objectIndex);
    void func_80086C6C(s32 objectIndex);

private:

    s32 _idx;
};
