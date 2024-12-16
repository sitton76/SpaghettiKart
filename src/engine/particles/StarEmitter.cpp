

#include "StarEmitter.h"

extern "C" {
#include "render_objects.h"
#include "common_data.h"
#include "code_80057C60.h"
}

void StarEmitter::Tick() {

}

void StarEmitter::Draw(s32 cameraId) { // func_80054BE8
    s32 var_s0;
    s32 temp_a0;
    Camera* camera;

    camera = &camera1[cameraId];
    gSPDisplayList(gDisplayListHead++, (Gfx*)D_0D007AE0);
    load_texture_block_ia8_nomirror(D_8018D488, 0x00000020, 0x00000020);
    func_8004B35C(0x000000FF, 0x000000FF, 0, 0x000000FF);
    D_80183E80[0] = 0;
    for (var_s0 = 0; var_s0 < gObjectParticle3_SIZE; var_s0++) {
        temp_a0 = gObjectParticle3[var_s0];
        if ((temp_a0 != -1) && (gObjectList[temp_a0].state >= 2)) {
            func_80054AFC(temp_a0, camera->pos);
        }
    }
}
