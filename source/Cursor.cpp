#include "Cursor.h"

#include "nds/arm9/sprite.h"

#include "menu_cursor.h"

Cursor::Cursor(u8 px, u8 py, u8 id, OamState* oam)
	: x_(px), y_(py), id_(id), oam_(oam)
{
	gfx_ = oamAllocateGfx(oam_, SpriteSize_16x16, SpriteColorFormat_256Color);
	oamSetGfx(oam_, id_, SpriteSize_16x16, SpriteColorFormat_256Color, gfx_);

	dmaCopy(menu_cursorTiles, gfx_, menu_cursorTilesLen);
	dmaCopy(menu_cursorPal, (oam_ == &oamSub) ? SPRITE_PALETTE_SUB : SPRITE_PALETTE, menu_cursorPalLen);
}

Cursor::~Cursor()
{
	oamFreeGfx(oam_, gfx_);
	oamClearSprite(oam_, id_);
}
void Cursor::move(u8 px, u8 py)
{
	x_ = px;
	y_ = py;
}

void Cursor::update()
{
	oamSet(oam_, id_, x_, y_, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, gfx_, -1, false, false, false, false, false);
}