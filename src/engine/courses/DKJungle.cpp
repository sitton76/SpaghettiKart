#include <libultraship.h>
#include <libultra/gbi.h>
#include <vector>
#include <memory>

#include "DKJungle.h"
#include "World.h"
#include "engine/actors/Finishline.h"
#include "engine/objects/BombKart.h"
#include "assets/dks_jungle_parkway_data.h"

#include "engine/vehicles/Boat.h"
#include "engine/vehicles/Utils.h"

extern "C" {
    #include "main.h"
    #include "common_structs.h"
    #include "camera.h"
    #include "course_offsets.h"
    #include "code_800029B0.h"
    #include "render_courses.h"
    #include "code_8006E9C0.h"
    #include "code_80057C60.h"
    #include "defines.h"
    #include "math_util.h"
    #include "external.h"
    #include "code_80005FD0.h"
    #include "spawn_players.h"
    #include "render_objects.h"
    #include "assets/common_data.h"
    #include "save.h"
    #include "replays.h"
    #include "actors.h"
    #include "collision.h"
    #include "code_8003DC40.h"
    #include "memory.h"
    #include "sounds.h"
    #include "course.h"
    extern const char *d_course_dks_jungle_parkway_unknown_dl_list[];
    extern s16 currentScreenSection;
}

const course_texture dks_jungle_parkway_textures[] = {
    { gTexture648508, 0x01FE, 0x1000, 0x0 },
    { gTexture6684F8, 0x010D, 0x0800, 0x0 },
    { gTextureWoodBridgeSlats, 0x0DAB, 0x1000, 0x0 },
    { gTexture654460, 0x0B12, 0x1000, 0x0 },
    { gTexture654F74, 0x0A24, 0x1000, 0x0 },
    { gTexture655998, 0x059F, 0x0800, 0x0 },
    { gTexture655F38, 0x0BB9, 0x1000, 0x0 },
    { gTexture656AF4, 0x0AD3, 0x1000, 0x0 },
    { gTexture6575C8, 0x0DA7, 0x1000, 0x0 },
    { gTexture658370, 0x0DBA, 0x1000, 0x0 },
    { gTexture65912C, 0x0DBC, 0x1000, 0x0 },
    { gTexture659EE8, 0x0EF5, 0x1000, 0x0 },
    { gTexture65ADE0, 0x0D5A, 0x1000, 0x0 },
    { gTexture65BB3C, 0x0D9E, 0x1000, 0x0 },
    { gTexture65C8DC, 0x0CF5, 0x1000, 0x0 },
    { gTexture65D5D4, 0x0D18, 0x1000, 0x0 },
    { gTexture65E2EC, 0x02B0, 0x0800, 0x0 },
    { gTexture65EAEC, 0x034A, 0x0800, 0x0 },
    { gTexture65E59C, 0x054F, 0x1000, 0x0 },
    { gTexture65EE38, 0x0CDE, 0x1000, 0x0 },
    { gTexture65FB18, 0x03EE, 0x0800, 0x0 },
    { gTextureSignPinkArrow, 0x0198, 0x0800, 0x0 },
    { gTextureWaves0, 0x04D0, 0x0800, 0x0 },
    { gTexture683844, 0x0655, 0x0800, 0x0 },
    { 0x00000000, 0x0000, 0x0000, 0x0 },
};

DKJungle::DKJungle() {
    this->vtx = d_course_dks_jungle_parkway_vertex;
    this->gfx = d_course_dks_jungle_parkway_packed_dls;
    this->gfxSize = 4997;
    Props.textures = dks_jungle_parkway_textures;
    Props.Minimap.Texture = minimap_dks_jungle_parkway;
    Props.Minimap.Width = ResourceGetTexWidthByName(Props.Minimap.Texture);
    Props.Minimap.Height = ResourceGetTexHeightByName(Props.Minimap.Texture);
    Props.Minimap.Pos[0].X = 255;
    Props.Minimap.Pos[0].Y = 170;
    Props.Minimap.PlayerX = 29;
    Props.Minimap.PlayerY = 47;
    Props.Minimap.PlayerScaleFactor = 0.0155f;
    Props.Minimap.FinishlineX = 0;
    Props.Minimap.FinishlineY = 0;
    ResizeMinimap(&Props.Minimap);

    Props.SetText(Props.Name, "d.k.'s jungle parkway", sizeof(Props.Name));
    Props.SetText(Props.DebugName, "jungle", sizeof(Props.DebugName));
    Props.SetText(Props.CourseLength, "893m", sizeof(Props.CourseLength));

    Props.AIBehaviour = D_0D0093C0;
    Props.AIMaximumSeparation = 40.0f;
    Props.AIMinimumSeparation = 0.1f;
    Props.AISteeringSensitivity = 53;

    Props.NearPersp = 9.0f;
    Props.FarPersp = 4500.0f;

    Props.PathSizes = {0x370, 1, 1, 1, 0x1F4, 0, 0, 0, 0, 0, 0};

    Props.CurveTargetSpeed[0] = 4.1666665f;
    Props.CurveTargetSpeed[1] = 5.5833334f;
    Props.CurveTargetSpeed[2] = 6.1666665f;
    Props.CurveTargetSpeed[3] = 6.75f;

    Props.NormalTargetSpeed[0] = 3.75f;
    Props.NormalTargetSpeed[1] = 5.1666665f;
    Props.NormalTargetSpeed[2] = 5.75f;
    Props.NormalTargetSpeed[3] = 6.3333334f;

    Props.D_0D0096B8[0] = 3.3333332f;
    Props.D_0D0096B8[1] = 3.9166667f;
    Props.D_0D0096B8[2] = 4.5f;
    Props.D_0D0096B8[3] = 5.0833334f;

    Props.OffTrackTargetSpeed[0] = 3.75f;
    Props.OffTrackTargetSpeed[1] = 5.1666665f;
    Props.OffTrackTargetSpeed[2] = 5.75f;
    Props.OffTrackTargetSpeed[3] = 6.3333334f;

    Props.PathTable[0] = (TrackPathPoint*)LOAD_ASSET_RAW(d_course_dks_jungle_parkway_unknown_waypoints);
    Props.PathTable[1] = NULL;
    Props.PathTable[2] = NULL;
    Props.PathTable[3] = NULL;

    Props.PathTable2[0] = (TrackPathPoint*)LOAD_ASSET_RAW(d_course_dks_jungle_parkway_track_waypoints);
    Props.PathTable2[1] = NULL;
    Props.PathTable2[2] = NULL;
    Props.PathTable2[3] = NULL;

    Props.Clouds = NULL; // no clouds
    Props.CloudList = NULL;

    Props.Skybox.TopRight = {255, 174, 0};
    Props.Skybox.BottomRight = {255, 229, 124};
    Props.Skybox.BottomLeft = {255, 229, 124};
    Props.Skybox.TopLeft = {255, 174, 0};
    Props.Skybox.FloorTopRight = {22, 145, 22};
    Props.Skybox.FloorBottomRight = {0, 0, 0};
    Props.Skybox.FloorBottomLeft = {0, 0, 0};
    Props.Skybox.FloorTopLeft = {22, 145, 22};
    Props.Sequence = MusicSeq::MUSIC_SEQ_DK_JUNGLE;

    Props.WaterLevel = -475.0f;
    for (size_t i = 0; i < 104; i++) {
        replace_segmented_textures_with_o2r_textures((Gfx*) d_course_dks_jungle_parkway_unknown_dl_list[i], Props.textures);
    }
}

void DKJungle::Load() {
    Course::Load();

    parse_course_displaylists((TrackSections*)LOAD_ASSET_RAW(d_course_dks_jungle_parkway_addr));
    func_80295C6C();
    // d_course_dks_jungle_parkway_packed_dl_3FA8
    find_vtx_and_set_colours(segmented_gfx_to_virtual((void*)0x07003FA8), 120, 255, 255, 255);
}

f32 DKJungle::GetWaterLevel(FVector pos, Collision* collision) {
    int32_t temp_v1 = get_track_section_id(collision->meshIndexZX) & 0xFF;

    if (temp_v1 == 0xFF) {
        if ((get_surface_type(collision->meshIndexZX) & 0xFF) == CAVE) {
            return -475.0f;
        }
        if (pos.x > -478.0f) {
            return -33.9f;
        }
        if (pos.x < -838.0f) {
            return -475.0f;
        }
        if (pos.z > -436.0f) {
            return -475.0f;
        }
        if (pos.z < -993.0f) {
            return -33.9f;
        }
        if (pos.z < pos.x) {
            return -475.0f;
        }

        return -33.9f;
    }
    if (temp_v1 >= 0x14) {
        return -475.0f;
    }
    return -33.9f;
}

void DKJungle::LoadTextures() {
    dma_textures(gTextureDksJungleParkwayKiwanoFruit1, 0x0000032FU, 0x00000400U); // 0x03009000
    dma_textures(gTextureDksJungleParkwayKiwanoFruit2, 0x00000369U, 0x00000400U); // 0x03009800
    dma_textures(gTextureDksJungleParkwayKiwanoFruit3, 0x00000364U, 0x00000400U); // 0x0300A000
}

void DKJungle::BeginPlay() {
    spawn_all_item_boxes((struct ActorSpawnData*)LOAD_ASSET_RAW(d_course_dks_jungle_parkway_item_box_spawns));

    init_kiwano_fruit();
    func_80298D10();
    if (gGamestate != CREDITS_SEQUENCE) {

        generate_ferry_path();

        // The original game only ran vehicle logic every second frame.
        // Thus the speed gets divided by two to set speed to match properly
        gWorldInstance.AddActor(new ABoat((0.6666666f)/4, 0));

        if (gModeSelection == VERSUS) {
            FVector pos = { 0, 0, 0 };

            gWorldInstance.AddObject(new OBombKart(pos, &gTrackPaths[0][50], 50, 3, 0.8333333f));
            gWorldInstance.AddObject(new OBombKart(pos, &gTrackPaths[0][100], 100, 1, 0.8333333f));
            gWorldInstance.AddObject(new OBombKart(pos, &gTrackPaths[0][150], 150, 3, 0.8333333f));
            gWorldInstance.AddObject(new OBombKart(pos, &gTrackPaths[0][190], 190, 1, 0.8333333f));
            gWorldInstance.AddObject(new OBombKart(pos, &gTrackPaths[0][250], 250, 3, 0.8333333f));
            gWorldInstance.AddObject(new OBombKart(pos, &gTrackPaths[0][0], 0, 0, 0.8333333f));
            gWorldInstance.AddObject(new OBombKart(pos, &gTrackPaths[0][0], 0, 0, 0.8333333f));
        }
    }
}

void DKJungle::InitCourseObjects() {
    for (size_t i = 0; i < NUM_TORCHES; i++) {
        init_smoke_particles(i);
        // wtf?
        if (D_8018CF10) {}
    }
}

void DKJungle::UpdateCourseObjects() {
    update_ferries_smoke_particle();
}

void DKJungle::RenderCourseObjects(s32 cameraId) {
    if (gGamestate != CREDITS_SEQUENCE) {
        render_object_paddle_boat_smoke_particles(cameraId);
    }
}

void DKJungle::SomeSounds() {
    vec3f_set(D_8015F738, -790.0f, -255.0f, -447.0f);
    func_800C9D80(D_8015F738, D_802B91C8, 0x51028001);
}

void DKJungle::WhatDoesThisDo(Player* player, int8_t playerId) {
    if ((((s16) gNearestPathPointByPlayerId[playerId] >= 0) &&
            ((s16) gNearestPathPointByPlayerId[playerId] < 0x65)) ||
        (((s16) gNearestPathPointByPlayerId[playerId] >= 0x14A) &&
            ((s16) gNearestPathPointByPlayerId[playerId] < 0x21F))) {
        if (D_80165300[playerId] != 2) {
            func_800C8F80(playerId, 0x0170802D);
        }
        D_80165300[playerId] = 2;
    } else {
        if (((s16) gNearestPathPointByPlayerId[playerId] >= 0x288) &&
            ((s16) gNearestPathPointByPlayerId[playerId] < 0x305)) {
            if (D_80165300[playerId] != 1) {
                func_800CA288(playerId, 0x55);
            }
            D_80165300[playerId] = 1;
        } else {
            if (D_80165300[playerId] != 0) {
                if (D_80165300[playerId] == 1) {
                    func_800CA2B8(playerId);
                }
                if (D_80165300[playerId] == 2) {
                    func_800C9018(playerId, SOUND_ARG_LOAD(0x01, 0x70, 0x80, 0x2D));
                }
                D_80165300[playerId] = 0;
            }
        }
    }
}

void DKJungle::WhatDoesThisDoAI(Player* player, int8_t playerId) {
    if (((s16) gNearestPathPointByPlayerId[playerId] >= 0x288) &&
        ((s16) gNearestPathPointByPlayerId[playerId] < 0x305)) {
        if (D_80165300[playerId] != 1) {
            func_800CA2E4(playerId, 0x55);
        }
        D_80165300[playerId] = 1;
    } else {
        if (D_80165300[playerId] != 0) {
            func_800CA30C(playerId);
            D_80165300[playerId] = 0;
        }
    }
}

void DKJungle::Render(struct UnkStruct_800DC5EC* arg0) {
    set_track_light_direction(D_800DC610, D_802B87D4, 0, 1);
    set_track_light_direction(&D_800DC610[1], D_802B87D4, D_802B87D0, 1);

    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK | G_LIGHTING);

    if (func_80290C20(arg0->camera) == 1) {
        gSPTexture(gDisplayListHead++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        // d_course_dks_jungle_parkway_packed_dl_92D8
        gSPDisplayList(gDisplayListHead++, (segmented_gfx_to_virtual((void*)0x070092D8)));
    }

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    render_course_segments(d_course_dks_jungle_parkway_unknown_dl_list, arg0);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void DKJungle::RenderCredits() {
    gSPDisplayList(gDisplayListHead++, (Gfx*)(d_course_dks_jungle_parkway_dl_13C30));
}

void DKJungle::SomeCollisionThing(Player *player, Vec3f arg1, Vec3f arg2, Vec3f arg3, f32* arg4, f32* arg5, f32* arg6, f32* arg7) {
    func_8003F138(player, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

void DKJungle::Waypoints(Player* player, int8_t playerId) {
    s16 waypoint = gNearestPathPointByPlayerId[playerId];
    if ((waypoint >= 0xB9) && (waypoint < 0x119)) {
        player->nearestPathPointId = 0xB9U;
    } else {
        player->nearestPathPointId = gNearestPathPointByPlayerId[playerId];
        if (player->nearestPathPointId < 0) {
            player->nearestPathPointId = gPathCountByPathIndex[0] + player->nearestPathPointId;
        }
    }
}

void DKJungle::ScrollingTextures() {
    D_802B87BC += 2;
    if (D_802B87BC > 255) {
        D_802B87BC = 0;
    }
    // d_course_dks_jungle_parkway_packed_dl_3DD0
    find_and_set_tile_size((uintptr_t) segmented_gfx_to_virtual((void*)0x07003DD0), 0, D_802B87BC);
    // d_course_dks_jungle_parkway_packed_dl_3E40
    find_and_set_tile_size((uintptr_t) segmented_gfx_to_virtual((void*)0x07003E40), 0, D_802B87BC);
    // d_course_dks_jungle_parkway_packed_dl_3EB0
    find_and_set_tile_size((uintptr_t) segmented_gfx_to_virtual((void*)0x07003EB0), 0, D_802B87BC);
    // d_course_dks_jungle_parkway_packed_dl_3F30
    find_and_set_tile_size((uintptr_t) segmented_gfx_to_virtual((void*)0x07003F30), 0, D_802B87BC);
    // d_course_dks_jungle_parkway_packed_dl_36A8
    find_and_set_tile_size((uintptr_t) segmented_gfx_to_virtual((void*)0x070036A8), 0, D_802B87BC);
    D_802B87C4 -= 20;
    if (D_802B87C4 < 0) {
        D_802B87C4 = 0xFF;
    }
    // d_course_dks_jungle_parkway_packed_dl_9880
    find_and_set_tile_size((uintptr_t) segmented_gfx_to_virtual((void*)0x07009880), 0, D_802B87C4);
    evaluate_collision_players_palm_trees();
}

void DKJungle::DrawWater(struct UnkStruct_800DC5EC* screen, uint16_t pathCounter, uint16_t cameraRot, uint16_t playerDirection) {
    Mat4 matrix;
    gDPPipeSync(gDisplayListHead++);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetBlendMask(gDisplayListHead++, 0xFF);
    gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
    gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);

    mtxf_identity(matrix);
    render_set_position(matrix, 0);

    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);

    if (pathCounter < 17) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
        // d_course_dks_jungle_parkway_packed_dl_3E40
        gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003E40));
        // d_course_dks_jungle_parkway_packed_dl_3EB0
        gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003EB0));
        if ((pathCounter >= 6) && (pathCounter < 13)) {
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            // d_course_dks_jungle_parkway_packed_dl_3DD0
            gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003DD0));
        }
    } else if ((pathCounter == 21) || (pathCounter == 22)) {
        if (playerDirection == 3) {
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
            // d_course_dks_jungle_parkway_packed_dl_36A8
            gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x070036A8));
        }
        if ((playerDirection == 1) || (playerDirection == 0)) {
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
            // d_course_dks_jungle_parkway_packed_dl_36A8
            gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x070036A8));
        } else {
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            // d_course_dks_jungle_parkway_packed_dl_3F30
            gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003F30));
            // d_course_dks_jungle_parkway_packed_dl_36A8
            gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x070036A8));
        }
    } else if (pathCounter == 24) {
        if ((playerDirection == 0) || (playerDirection == 3)) {
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
            // d_course_dks_jungle_parkway_packed_dl_36A8
            gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x070036A8));
        }
    } else if (pathCounter == 23) {
        if (playerDirection == 3) {
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
            // d_course_dks_jungle_parkway_packed_dl_36A8
            gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x070036A8));
        } else if (playerDirection == 0) {
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
            // d_course_dks_jungle_parkway_packed_dl_36A8
            gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x070036A8));
        }
    }
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    switch (pathCounter) {
        case 5:
            if (playerDirection != 3) {
                // d_course_dks_jungle_parkway_packed_dl_3DD0
                gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003DD0));
            }
            break;
        case 17:
            switch (playerDirection) {
                case 0:
                    // d_course_dks_jungle_parkway_packed_dl_3E40
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003E40));
                    // d_course_dks_jungle_parkway_packed_dl_3EB0
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003EB0));
                    break;
                case 1:
                    // d_course_dks_jungle_parkway_packed_dl_3DD0
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003DD0));
                    // d_course_dks_jungle_parkway_packed_dl_3E40
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003E40));
                    // d_course_dks_jungle_parkway_packed_dl_3EB0
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003EB0));
                    break;
                case 2:
                    // d_course_dks_jungle_parkway_packed_dl_
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003E40));
                    // d_course_dks_jungle_parkway_packed_dl_3EB0
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003EB0));
                    // d_course_dks_jungle_parkway_packed_dl_3F30
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003F30));
                    break;
                case 3:
                    // d_course_dks_jungle_parkway_packed_dl_3EB0
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003EB0));
                    // d_course_dks_jungle_parkway_packed_dl_3F30
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003F30));
                    break;
            }
            break;
        case 18:
            switch (playerDirection) {
                case 0:
                    // d_course_dks_jungle_parkway_packed_dl_3E40
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003E40));
                    // d_course_dks_jungle_parkway_packed_dl_3EB0
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003EB0));
                    break;
                case 1:
                    // d_course_dks_jungle_parkway_packed_dl_3DD0
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003DD0));
                    // d_course_dks_jungle_parkway_packed_dl_3E40
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003E40));
                    // d_course_dks_jungle_parkway_packed_dl_3EB0
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003EB0));
                    break;
                case 2:
                    // d_course_dks_jungle_parkway_packed_dl_3E40
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003E40));
                    // d_course_dks_jungle_parkway_packed_dl_3EB0
                    gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003EB0));
                    break;
            }
            break;
        case 21:
            if ((playerDirection == 0) || (playerDirection == 1)) {
                // d_course_dks_jungle_parkway_packed_dl_3E40
                gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003E40));
                // d_course_dks_jungle_parkway_packed_dl_3EB0
                gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003EB0));
                // d_course_dks_jungle_parkway_packed_dl_3F30
                gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003F30));
            } else {
                // d_course_dks_jungle_parkway_packed_dl_3EB0
                gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003EB0));
            }
            break;
        case 22:
            if (playerDirection == 0) {
                // d_course_dks_jungle_parkway_packed_dl_3F30
                gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003F30));
            }
            break;
        case 23:
            if (playerDirection != 1) {
                // d_course_dks_jungle_parkway_packed_dl_3F30
                gSPDisplayList(gDisplayListHead++, segmented_gfx_to_virtual((void*)0x07003F30));
            }
            break;
    }
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 1, 1, G_OFF);
    gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
    gDPPipeSync(gDisplayListHead++);
}

void DKJungle::CreditsSpawnActors() {
    // d_course_dks_jungle_parkway_packed_dl_3FA8
    find_vtx_and_set_colours(segmented_gfx_to_virtual((void*)0x07003FA8), 0x78, 0xFF, 0xFF, 0xFF);
}

void DKJungle::Destroy() { }
