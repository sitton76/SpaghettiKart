#pragma once

#include <libultraship.h>

extern "C" {
    #include "camera.h"
    #include "objects.h"
}

class OObject {
public:
    uint8_t uuid[16];
    Object o;

    virtual ~OObject() = default;

    explicit OObject();

    virtual void Tick();
    virtual void Draw(s32 cameraId);
    virtual void Collision();
    virtual void Expire();
    virtual void Destroy();
};
