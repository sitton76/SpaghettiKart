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
}

//! @todo Make shadow size bigger if thwomp is scaled up
//! @todo make adjustable properties for squishSize and boundingBoxSize

    /**
 * Thwomp GameObject
 * 
 * The game automatically places the actor on the ground so you do not need to provide a Y coordinate value.
 * 
 * @arg direction the rotational direction the thwomp is facing.
 * @arg behaviour the behaviour of the thwomp, uses values 1-6.
 * @arg primAlpha unknown
 * @arg boundingBoxSize optional. The size of the bounding box for the thwomp. Default value is 12
 */
class OPenguin {
public:
    enum PenguinType : uint32_t {
        CHICK,
        ADULT,
        CREDITS,
        EMPEROR
    };

    enum Behaviour : uint16_t {
        DISABLED,
        STRUT, // Emperor penguin
        CIRCLE, // Waddle in a circle
        SLIDE3,
        SLIDE4,
        UNK, // unused
        SLIDE6,
    };

public:
    f32 Diameter = 0.0f; // Waddle in a circle around the spawn point at this diameter.
    uint16_t MirrorModeAngleOffset;

    explicit OPenguin(s32 i, Vec3f pos, u16 direction, PenguinType type, Behaviour behaviour);

    void Tick();
    void Draw(s32 playerId);
private:
    void Behaviours(s32 objectIndex, s32 arg1);
    void EmperorPenguin(s32 objectIndex);
    void InitEmperorPenguin(s32 objectIndex);
    void OtherPenguin(s32 objectIndex);
    void InitOtherPenguin(s32 objectIndex);

    s32 _idx;
    PenguinType _type;
    Behaviour _bhv;


};
