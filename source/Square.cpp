/* -------------------- includes -------------------- */
#include "Square.h"
#include <nds/arm9/sprite.h>

#include <algorithm>

/* -------------------- static members -------------------- */
std::vector<int> Square::ids_in_use_sub_;
std::vector<int> Square::ids_in_use_main_;

/* -------------------- public functions -------------------- */
Square::Square(u16 px, u16 py, const unsigned int* tiles_ptr, const u32 tiles_len, const unsigned short* pal_ptr, const u32 pal_len, const u8 pal_offset) :
	px_(px), py_(py), id_(0), oam_(&oamSub), tiles_ptr_(tiles_ptr), tiles_len_(tiles_len), pal_ptr_(pal_ptr), pal_len_(pal_len), pal_offset_(pal_offset)
{
	init();
}

Square::~Square()
{
	oamFreeGfx(oam_, gfx_);
	oamClearSprite(oam_, id_);
	// delete the id
	if (oam_ == &oamSub) {
		ids_in_use_sub_.erase(std::find(ids_in_use_sub_.begin(), ids_in_use_sub_.end(), id_));
	}
	else {
		ids_in_use_main_.erase(std::find(ids_in_use_main_.begin(), ids_in_use_main_.end(), id_));
	}
}

void Square::move(u16 px, u16 py)
{
	px_ = px;
	py_ = py;
	change_oam_if_needed();
}
void Square::move_up(u16 poffset)
{
	py_ -= poffset;
	change_oam_if_needed();
}
void Square::move_down(u16 poffset)
{
	py_ += poffset;
	change_oam_if_needed();
}

void Square::move_right(u16 poffset)
{
	px_ += poffset;
}
void Square::move_left(u16 poffset)
{
	px_ -= poffset;
}

void Square::update()
{
	oamSet(oam_, id_, px_, (oam_ == &oamMain) * (-192) + py_, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, gfx_, -1, false, false, false, false, false);
}

/* -------------------- private functions -------------------- */
void Square::init()
{
	gfx_ = oamAllocateGfx(oam_, SpriteSize_16x16, SpriteColorFormat_256Color);
	if (oam_ == &oamSub) {
		// get the lowest id possible
		int i = 0;
		while (std::find(ids_in_use_sub_.begin(), ids_in_use_sub_.end(), i) != ids_in_use_sub_.end()) {
			i++;
		}
		id_ = i;
		ids_in_use_sub_.push_back(i);
	}
	else {
		int i = 0;
		while (std::find(ids_in_use_main_.begin(), ids_in_use_main_.end(), i) != ids_in_use_main_.end()) {
			i++;
		}
		id_ = i;
		ids_in_use_main_.push_back(i);
	}
	oamSetGfx(oam_, id_, SpriteSize_16x16, SpriteColorFormat_256Color, gfx_);
	dmaCopy(pal_ptr_, (oam_ == &oamMain) ? (SPRITE_PALETTE + pal_offset_) : (SPRITE_PALETTE_SUB + pal_offset_), pal_len_);
	dmaCopy(tiles_ptr_, gfx_, tiles_len_);
	u8* p = (u8*)gfx_; 
	for (int i = 0; i < 16 * 16; i++)
	{
		*(p++) += pal_offset_;
	}
	update();
}

void Square::change_oam(OamState* oam)
{
	oamFreeGfx(oam_, gfx_);
	oamClearSprite(oam_, id_);
	// delete the id
	if (oam_ == &oamSub) {
		ids_in_use_sub_.erase(std::find(ids_in_use_sub_.begin(), ids_in_use_sub_.end(), id_));
	}
	else {
		ids_in_use_main_.erase(std::find(ids_in_use_main_.begin(), ids_in_use_main_.end(), id_));
	}
	oam_ = oam;
	init();
}

void Square::change_oam_if_needed()
{
	if (py_ < 192 && oam_ != &oamSub) {
		change_oam(&oamSub);
	}
	else if (py_ > 191 && oam_ != &oamMain) {
		change_oam(&oamMain);
	}
}
