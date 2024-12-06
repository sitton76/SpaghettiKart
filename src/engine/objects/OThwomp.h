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
class OThwomp {
private:
    enum States : uint16_t {
        DISABLED,
        STATIONARY,
        MOVE_AND_ROTATE,
        MOVE_FAR, // Requires enough space to work
        STATIONARY_FAST,
        SLIDE, // Moves sideways left / right
        JAILED // Has no collision
    };

public:
    States State = States::DISABLED;

    explicit OThwomp(s32 i, s16 x, s16 z, s16 direction, f32 scale, s16 behaviour, s16 primAlpha, u16 boundingBoxSize);

    void Tick();
    void func_80080B28(s32 objectIndex, s32 playerId);
    void Draw(s32 playerId);
    void DrawModel(s32);
    s32 func_8007F75C(s32 playerId);
    void func_8007F8D8();

    void StationaryBehaviour(s32 objectIndex);
    void func_8007EC30(s32 objectIndex);

    void MoveAndRotateBehaviour(s32 objectIndex);
    void func_8007EE5C(s32 objectIndex);

    void MoveFarBehaviour(s32 objectIndex);
    void func_8007FA08(s32 objectIndex);

    void StationaryFastBehaviour(s32 objectIndex);
    void func_80080078(s32 objectIndex);

    void JailedBehaviour(s32 objectIndex);
    void func_800802C0(s32 objectIndex);

    void SlidingBehaviour(s32 objectIndex);
    void func_80080524(s32 objectIndex);
private:
    s32 _idx;
    s16 _faceDirection;
    //! @todo Write this better. This effects the squish size and the bounding box size.
    // We should probably return to the programmer the pointer to the actor so they can do thwomp->squishSize = value.
    u16 _boundingBoxSize;


};
