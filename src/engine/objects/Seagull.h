#pragma once

#include <libultraship.h>
#include <vector>
#include "engine/Actor.h"

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


class OSeagull : public AActor {
public:
    enum Behaviour : uint16_t {
    };

public:
    explicit OSeagull(s32 i, Vec3f pos);

    virtual void Tick() override;
    virtual void Draw(Camera*) override;

    void func_8008275C(s32 objectIndex);
    void func_8008241C(s32 objectIndex, s32 arg1);
    void func_80082714(s32 objectIndex, s32 arg1);
    virtual bool IsMod() override;
    Vec3f Offset;
    Vec3f SpawnPos;
private:
    s32 _idx;
    s32 _state;
    s32 _timer;
    s32 _status;
    bool _toggle;

    SplineData *spline;
};
