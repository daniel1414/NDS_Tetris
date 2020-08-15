#include "Square.h"
#include <nds/arm9/sprite.h>

#include <algorithm>

std::vector<int> Square::ids_in_use_sub_;
std::vector<int> Square::ids_in_use_main_;

/* private functions */
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

void Square::update()
{
	oamSet(oam_, id_, 48 + x_ * 16, (oam_ == &oamMain) * (-192) + y_ * 16, 0, 0, SpriteSize_16x16, SpriteColorFormat_256Color, gfx_, -1, false, false, false, false, false);
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
	if (y_ < 12 && oam_ != &oamSub) {
		change_oam(&oamSub);
	}
	else if (y_ > 11 && oam_ != &oamMain) {
		change_oam(&oamMain);
	}
}

/* public functions */
Square::Square(u8 x, u8 y, const unsigned int* tiles_ptr, const u32 tiles_len, const unsigned short* pal_ptr, const u32 pal_len, const u8 pal_offset) :
	x_(x), y_(y), id_(0), oam_(&oamSub), tiles_ptr_(tiles_ptr), tiles_len_(tiles_len), pal_ptr_(pal_ptr), pal_len_(pal_len), pal_offset_(pal_offset)
{
	init();
}

void Square::move(u8 x, u8 y)
{
	x_ = x;
	y_ = y;
	change_oam_if_needed();
}
void Square::move_up()
{
	y_ -= 1;
	change_oam_if_needed();
}
void Square::move_down()
{
	y_ += 1;
	change_oam_if_needed();
}

void Square::move_right()
{
	x_ += 1;
}
void Square::move_left()
{
	x_ -= 1;
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