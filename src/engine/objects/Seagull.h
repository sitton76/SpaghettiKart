#pragma once

#include <libultraship.h>
#include <vector>
#include "Object.h"

#include "engine/World.h"

extern "C" {
#include "macros.h"
#include "main.h"
#include "vehicles.h"
#include "waypoints.h"
#include "common_structs.h"
#include "objects.h"
#include "camera.h"
}


class OSeagull : public OObject {
public:
    explicit OSeagull(Vec3f pos);

    ~OSeagull() {
        _count--;
    }

    static size_t GetCount() {
        return _count;
    }

    virtual void Tick() override;
    virtual void Draw(s32 cameraId) override;

    void func_800552BC(s32 objectIndex);

    void func_8008275C(s32 objectIndex);
    void func_8008241C(s32 objectIndex, s32 arg1);
    void func_80082714(s32 objectIndex, s32 arg1);
private:
    Vec3f _pos;
    static size_t _count;
    s32 _idx;
    bool _toggle;

    SplineData *spline;
};
