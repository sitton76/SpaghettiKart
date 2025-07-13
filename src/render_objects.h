#ifndef RENDER_OBJECTS_H
#define RENDER_OBJECTS_H

#include <common_structs.h>
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void func_80045738(u8*, u8*, s32, s32);
void render_bomb_karts(s32);
void func_800431B0(Vec3f, Vec3su, f32, Vtx*);
void func_80043220(Vec3f, Vec3su, f32, Gfx*);
void func_80043328(Vec3f, Vec3su, f32, Gfx*);
void func_80043288(Vec3f, Vec3su, f32, Gfx*);
void func_80043390(Vec3f, Vec3su, f32, Gfx*);
void func_800433F8(Vec3f, Vec3su, f32, Gfx*);
void func_80043460(Vec3f, Vec3su, f32, Gfx*);
void func_80043500(Vec3f, Vec3su, f32, Gfx*);
void func_800435A0(Vec3f, Vec3su, f32, Gfx*, s32);
void func_80043668(Vec3f, Vec3su, f32, Gfx*);
void func_800436D0(s32, s32, u16, f32, Vtx*);
void func_80043764(s32, s32, u16, f32, Vtx*);
void func_800437F8(s32, s32, u16, f32, Vtx*, s32);
void func_800438C4(s32, s32, u16, f32, Vtx*, s32);
void func_8004398C(s32, s32, u16, f32, Vtx*, s32);
s32 func_80043A54(s32);
void load_texture_block_rgba32_nomirror(u8*, s32, s32);
void load_texture_tile_rgba32_nomirror(u8*, s32, s32);
void load_texture_block_rgba16_mirror(u8*, s32, s32);
void load_texture_block_rgba16_nomirror(u8*, s32, s32, s32);

void load_texture_tile_rgba16_nomirror(u8*, s32, s32);
void load_texture_block_ia16_nomirror(u8*, s32, s32);
void load_texture_tile_ia16_nomirror(u8*, s32, s32);
void load_texture_block_ia8_nomirror(u8*, s32, s32);
void load_texture_tile_ia8_nomirror(u8*, s32, s32);
void load_texture_block_i8_nomirror(u8*, s32, s32);
void func_80044AB8(u8*, s32, s32);
void func_80044BF8(u8*, s32, s32);

void rsp_load_texture(u8*, s32, s32);
void rsp_load_texture_mask(u8*, s32, s32, s32);
void func_80045614(u8*, s32, s32);
void func_80045B2C(Vtx*);
void func_80045B74(Vtx*);
void func_80045BBC(Vec3f, Vec3su, f32, Vtx*);
void func_80045C48(Vec3f, Vec3su, f32, Vtx*);
void func_80045D0C(u8*, Vtx*, s32, s32, s32);
void func_80045E10(u8*, Vtx*, s32, s32, s32);
void func_80045F18(u8*, Vtx*, s32, s32, s32, s32);

void func_800461A4(u8*, Vtx*, s32, s32, s32);
void func_800462A8(u8*, Vtx*, s32, s32, s32);
void func_800463B0(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80046424(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_800464D0(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80046544(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_800465B8(s32, s32, u16, f32, s32, u8*, Vtx*, s32, s32, s32, s32);
void func_80046634(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_800466B0(s32, s32, u16, f32, u8*, Vtx*, s32, s32);
void func_80046720(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80046794(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80046808(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80046874(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_800468E0(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32, s32);
void func_80046954(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80046A00(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32);
void func_80046A68(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80046AD4(s32, s32, u16, f32, u8*);
void func_80046B38(s32, s32, u16, f32, u8*);
void func_80046B9C(Vec3f, Vec3su, f32, u8*);
void func_80046BEC(s32, s32, u16, f32, u8*, Vtx*);
void func_80046C3C(Vec3f, Vec3su, f32, u8*, Vtx*);
void func_80046C78(s32, s32, u16, f32, u8*);
void func_80046CDC(s32, s32, u16, f32, u8*);
void func_80046D40(Vec3f, Vec3su, f32, u8*);
void func_80046D90(s32, s32, u16, f32, u8*);
void func_80046DF4(s32, s32, u16, f32, s32, u8*);
void load_texture_and_tlut(u8*, u8*, s32, s32);
void func_80046F60(u8*, u8*, s32, s32, s32);

void func_80047068(u8*, u8*, Vtx*, s32, s32, s32, s32);
void draw_rectangle_texture_overlap(u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_8004747C(u8*, u8*, Vtx*, s32, s32, s32, s32, s32);
void func_8004768C(u8*, u8*, Vtx*, s32, s32, s32);
void func_8004788C(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047910(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047994(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047A18(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047A9C(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047B20(s32, s32, u16, f32, u8*, u8*, Vtx*, s32, s32, s32);
void func_80047B9C(s32, s32, u16, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047C28(s32, s32, u16, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047CB4(s32, s32, u16, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047D40(s32, s32, u16, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047DCC(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047E48(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047EC4(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047F40(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80047FBC(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);

void func_80048038(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void draw_2d_texture_at(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80048130(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32, s32, s32);
void func_800481B4(Vec3f, Vec3su, f32, u8*, u8*, Vtx*, s32, s32, s32);
void func_80048228(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_800482AC(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80048330(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_800483B4(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80048438(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_800484BC(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_80048540(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_800485C4(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*, s32, s32, s32, s32);
void func_800486B0(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_80048718(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_80048780(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*);
void func_800487DC(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_80048844(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_800488AC(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_80048914(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_8004897C(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_800489E4(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_80048A4C(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_80048AB4(s32, s32, u16, f32, s32, u8*, u8*, Vtx*);
void func_80048B24(s32, s32, u16, f32, s32, u8*, u8*, Vtx*);
void func_80048B94(Vec3f, Vec3su, f32, u8*, u8*, Vtx*);
void func_80048BE8(Vec3f, Vec3su, f32, u8*, u8*, Vtx*);
void func_80048C3C(Vec3f, Vec3su, f32, u8*, u8*, Vtx*);
void func_80048C90(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*);
void func_80048CEC(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*);
void func_80048D48(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*);
void func_80048DA4(Vec3f, Vec3su, f32, s32, u8*, u8*, Vtx*);
void func_80048E00(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_80048E68(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_80048ED0(s32, s32, u16, f32, u8*, u8*, Vtx*);
void func_80048F38(Vec3f, Vec3su, f32, u8*, u8*, Vtx*);
void func_80048F8C(u8*, Vtx*, s32, s32, s32, s32);
void func_80044924(u8*, s32, s32);
void func_80044DA0(u8*, s32, s32);

void func_80049130(u8*, Vtx*, s32, s32, s32, s32);
void func_800492D4(u8*, Vtx*, s32, s32, s32, s32);
void func_80049478(u8*, Vtx*, s32, s32, s32, s32);
void func_800497CC(u8*, Vtx*, s32, s32, s32, s32);
void func_80049B20(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80049B9C(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80049C18(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80049C94(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80049D10(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80049D8C(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_80049E08(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void func_80049E98(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void func_80049F28(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void func_80049FB8(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);

void func_8004A034(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A0B0(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A12C(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A1BC(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A258(s32, s32, u16, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A2F4(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A384(s32, s32, u16, f32, s32, s32, s32, s32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A414(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A488(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A4FC(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A570(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004A5E4(Vec3f, Vec3su, f32, u8*, Vtx*);
void func_8004A630(Collision*, Vec3f, f32);
void func_8004A6EC(s32, f32);
void func_8004A7AC(s32, f32);
void func_8004A9B8(f32);
void func_8004AA10(Vec3f, Vec3su, f32, u8*, Vtx*, s32, s32, s32, s32);
void func_8004AAA0(s32, s32, u16, f32, u8*, Vtx*);
void func_8004AB00(s32, s32, u16, f32, u8*, Vtx*);
void func_8004AB60(s32, s32, u16, f32, u8*, Vtx*);
void func_8004ABC0(s32, s32, u16, f32, u8*, Vtx*);
void func_8004AC20(s32, s32, u16, f32, u8*, Vtx*);
void func_8004AC80(s32, s32, u16, f32, u8*, Vtx*);
void func_8004ACE0(Vec3f, Vec3su, f32, u8*, Vtx*);
void func_8004AD2C(s32, s32, u16, f32, u8*, Vtx*);
void func_8004AD8C(s32, s32, u16, f32, u8*, Vtx*);
void func_8004ADEC(s32, s32, u16, f32, u8*, Vtx*);
void func_8004AE4C(s32, s32, u16, f32, u8*, Vtx*);
void func_8004AEAC(s32, s32, u16, f32, u8*, Vtx*);
void func_8004AF0C(s32, s32, u16, f32, u8*, Vtx*);
void func_8004AF6C(s32, s32, u16, f32, u8*, Vtx*);
void func_8004AFCC(s32, s32, u16, f32, u8*, Vtx*);

void func_8004B02C(void);
void func_8004B05C(u8*);
void func_8004B138(s32, s32, s32, s32);
void func_8004B180(s32, s32, s32, s32);
void set_color_render(s32, s32, s32, s32, s32, s32, s32);
void func_8004B254(s32, s32, s32);
void set_transparency(s32);
void func_8004B310(s32);
void func_8004B35C(s32, s32, s32, s32);
void func_8004B3C8(s32);
void func_8004B414(s32, s32, s32, s32);
void func_8004B480(s32, s32, s32);
void func_8004B4E8(s32, s32, s32, s32);
void func_8004B554(s32);
void func_8004B5A8(s32, s32, s32, s32);
void func_8004B614(s32, s32, s32, s32, s32, s32, s32);
void func_8004B6C4(s32, s32, s32);
void func_8004B72C(s32, s32, s32, s32, s32, s32, s32);
void render_texture_rectangle_wrap(s32, s32, s32, s32, s32);
void func_8004BB34(void);
void func_8004BB3C(s32, s32, s32, s32, f32);
void func_8004BD14(s32, s32, u32, u32, s32, u8*, u8*);

void render_texture_tile_rgba32_block(s16, s16, u8*, u32, u32);

void func_8004C024(s16, s16, s16, u16, u16, u16, u16);
void func_8004C148(s16, s16, s16, u16, u16, u16, u16);
void func_8004C354(void);
void func_8004C35C(void);
void draw_hud_2d_texture(s32, s32, u32, u32, u8*);
void draw_hud_2d_texture_wide(s32, s32, u32, u32, u8*);
void func_8004C450(s32, s32, u32, u32, u8*);
void func_8004C53C(s32, s32, u32, u32, u8*);
void func_8004C628(s32, s32, u32, u32, u8*);
void render_game_logo(s16, s16);
void func_8004C91C(s32, s32, u8*, s32, s32, s32);
void func_8004C9D8(s32, s32, s32, u8*, s32, s32, s32, s32);
void func_8004CA58(s32, s32, f32, u8*, s32, s32);
void draw_hud_2d_texture_8x8(s32, s32, u8*);
void draw_hud_2d_texture_8x16(s32, s32, u8*);
void draw_hud_2d_texture_16x16(s32, s32, u8*);
void draw_hud_2d_texture_32x8(s32, s32, u8*);
void draw_hud_2d_texture_32x16(s32, s32, u8*);
void func_8004CBC0(s32, s32, f32, u8*);
void draw_hud_2d_texture_32x32(s32, s32, u8*);
void func_8004CC24(s32, s32, u8*);
void draw_hud_2d_texture_40x32(s32, s32, u8*);
void func_8004CC84(s32, s32, u8*);
void func_8004CCB4(s32, s32, u8*);
void func_8004CCE4(s32, s32, f32, u8*);
void func_8004CD18(s32, s32, u8*);
void func_8004CF9C(s32, s32, u8*, s32, s32, s32, s32);
void func_8004CFF0(s32, s32, u8*, s32, s32, s32, s32);

void func_800450C8(u8*, s32, s32);
void func_80044F34(u8*, s32, s32);
void func_8004D044(s32, s32, u8*, s32, s32, s32, s32, s32, s32, s32, s32);
void func_8004D0CC(void);
void func_8004D0D4(s32, s32, u8*, s32, s32, s32);
void func_8004D210(s32, s32, u8*, s32, s32, s32, s32, s32, s32, s32, s32);
void func_8004D37C(s32, s32, u8*, s32, s32, s32, s32, s32, s32, s32, s32);
void func_8004D4E8(s32, s32, u8*, s32, s32, s32, s32, s32, s32, s32, s32);
void func_8004DC34(s32, s32, u8*);
void func_8004DC6C(s32, s32, u8*);
void func_8004DCA4(s32, s32, u8*);
void func_8004DCDC(s32, s32, u8*);
void func_8004DD0C(s32, s32, u8*);
void func_8004DD44(s32, s32, u8*);
void func_8004DD74(s32, s32, u8*);
void func_8004DDAC(s32, s32, u8*);
void func_8004DDDC(s32, s32, u8*);
void func_8004DE04(s32, s32, u8*);
void func_8004DE2C(s32, s32, u8*);
void func_8004DE54(s32, s32, u8*);
void func_8004DE84(s32, s32, u8*);
void func_8004DEB4(s32, s32, u8*);
void func_8004DEEC(s32, s32, u8*);
void func_8004DF24(s32, s32, u8*);

void func_8004F6D0(s32);
void func_8004E238(void);
void func_8004E240(s32, s32, u8*, u8*, s32, s32, s32);
void func_8004E2B8(s32, s32, s32, u8*, u8*, s32, s32, s32);
void func_8004E338(s32, s32, u8*, u8*, s32, s32);
void func_8004E3B8(void);
void func_8004E3C0(s32, s32, u8*, u8*, s32, s32, s32, s32);
void func_8004E3F4(s32, s32, s32, u8*, u8*, s32, s32, s32, s32);
void func_8004E430(s32, s32, u8*, u8*);
void func_8004E464(s32, s32, u8*, u8*);
void func_8004E498(s32, s32, u8*, u8*);
void func_8004E4CC(s32, s32, u8*, u8*);
void func_8004E500(s32, s32, u8*, u8*);
void func_8004E534(s32, s32, u8*, u8*);
void func_8004E568(s32, s32, u8*, u8*);
void func_8004E59C(s32, s32, s32, u8*, u8*);
void func_8004E5D8(s32, s32, u8*, u8*);
void func_8004E604(s32, s32, u8*, u8*);
void draw_item_window(s32);
void func_8004E6C4(s32);
void draw_simplified_lap_count(s32);
void func_8004E800(s32);
void func_8004E998(s32);
void func_8004EB30(s32);
void func_8004EB38(s32);
void render_digital_speedometer(s32 playerIdx);
void render_speedometer(s32);
void func_8004EE54(s32);

void func_8004EF9C(s32);
void set_minimap_finishline_position(s32);
void draw_minimap_character(s32, s32, s32);
void func_8004F3E4(s32);
s32 func_8004F674(s32*, s32);
void print_timer(s32, s32, s32);
void func_8004F950(s32, s32, s32, s32);
void print_timer_rainbow(s32, s32, s32);
void render_hud_timer(s32);
void draw_lap_count(s16, s16, s8);
void func_8004FDB4(f32, f32, s16, s16, s16, s32, s32, s32, s32);

void func_80050320(void);
s32 func_80050644(u16, s32*, s32*);
void func_800507D8(u16, s32*, s32*);
void func_800508C0(void);
void func_80050C68(void);
void func_80050E34(s32, s32);

void func_800514BC(void);
void render_object_leaf_particle(s32);
void render_object_snowflakes_particles(void);
void func_800518F8(s32, s16, s16);
void func_800519D4(s32, s16, s16);
void func_80051ABC(s16, s32);
void func_80051C60(s16, s32);
void func_80051EBC(void);
void func_80051EF8(void);
void func_80051F9C(void);

void func_80052044(void);
void func_80052080(void);
void func_800520C0(s32);
void func_8005285C(s32);
void func_800528EC(s32);
void render_ice_block(s32);
void func_80052D70(s32);
void func_80052E30(s32);
void render_object_snowmans_list_2(s32);

void render_object_snowmans_list_1(s32);
void render_object_snowmans(s32);
void translate_thwomp_lights(s32);
void thwomp_lights(s32);
void render_object_thwomps_model(s32);
void render_object_thwomps(s32);

void render_object_train_smoke_particle(s32, s32);
void render_object_trains_smoke_particles(s32);
void render_object_paddle_boat_smoke_particle(s32, s32);
void render_object_paddle_boat_smoke_particles(s32);
void render_object_bowser_flame_particle(s32, s32);
void render_object_bowser_flame(s32);
void func_8005477C(s32, u8, Vec3f);
void render_object_smoke_particles(s32);
void func_80054D00(s32, s32);
void func_80054E10(s32);
void func_80054EB8(s32);
void func_80054F04(s32);

void render_object_moles(s32);
void func_80055228(s32);
void render_object_seagulls(s32);
void render_object_crabs(s32);
void func_800557AC(void);
void func_800557B4(s32, u32, u32);
void func_80055AB8(s32, s32);
void render_object_chain_chomps(s32);
void func_80055EF4(s32, s32);
void func_80055F48(s32);

void func_80056160(s32);
void render_object_neon(s32);
void func_800562E4(s32, s32, s32);
void func_800563DC(s32, s32, s32);
void func_800568A0(s32, s32);
void func_8005669C(s32, s32, s32);
void func_800569F4(s32);
void func_80056A40(s32, s32);
void func_80056A94(s32);
void render_battle_bomb_karts(s32);
void func_80056E24(s32, Vec3f);
void func_80056FCC(s32);

void render_bomb_karts(s32);
void func_8005762C(s32*, s32*, s32, u32);
void func_80057330(void);
void func_80057338(void);
void func_800573BC(void);
void func_800573C4(void);
void func_800573CC(void);
void func_800573D4(void);
void func_800573DC(void);
void func_800573E4(s32, s32, s8);
void debug_wrap_text(s32*, s32*);
void debug_print_string(s32*, s32*, char*);
void debug_print_number(s32*, s32*, s32, u32);
void func_80057708(void);
void load_debug_font(void);
void func_80057778(void);
void debug_print_str2(s32, s32, char*);
void print_str_num(s32, s32, char*, s32);
void func_80057814(s32, s32, char*, u32);
void func_80057858(s32, s32, char*, u32);
void func_800578B0(s32, s32, char*, u32);
void func_80057908(s32, s32, char*, u32);
void func_80057960(s32, s32, char*, u32);
void func_800579B8(s32, s32, char*);
void func_800579F8(s32, s32, char*, u32);
void func_80057A50(s32, s32, char*, u32);
void func_80057AA8(s32, s32, char*, u32);
void func_80057B14(s32, s32, char*, u32);
void func_80057B80(s32, s32, char*, u32);
void func_80057BEC(s32, s32, char*, u32);

extern Lights1 D_800E45C0[];
extern Lights1 D_800E4668;

extern f32 D_801637C4;
extern s32 D_801637E8;
extern f32 D_801637F0;

extern s32 D_80163814;

extern s32 D_801655CC;

extern u16 D_8016579E;

extern Vec3su D_80183E80;

extern f32 D_8018CFEC;
extern f32 D_8018CFF4;
extern s16 gMinimapPlayerX;
extern s16 gMinimapPlayerY;

extern u8* D_8018D4BC;
extern u8* D_8018D4C0;

extern u8* gPortraitTextures[];

#ifdef __cplusplus
}
#endif

#endif
