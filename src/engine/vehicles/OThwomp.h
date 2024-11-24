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

/**
 * Used in VS mode
 * 
 * This differs from the other vehicle classes in that it does not get added to the standard actor list
 * So this is sort of its own thing. Draw call in different place too.
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

    explicit OThwomp(s32 i, f32 x, f32 z, s16 direction, f32 scale, s16 behaviour, s16 primAlpha);

    void Tick();
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


};
