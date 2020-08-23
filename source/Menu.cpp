#include "Menu.h"
#include "nds/arm9/background.h"
#include "nds/arm9/sprite.h"

#include "main_menu.h"

Menu::Menu()
{
	bg_ = bgInitSub(3, BgType_Text8bpp, BgSize_B16_256x256, 2, 2);
	dmaCopy(main_menuTiles, bgGetGfxPtr(bg_), main_menuTilesLen);
	dmaCopy(main_menuMap, bgGetMapPtr(bg_), main_menuMapLen);
	dmaCopy(main_menuPal, BG_PALETTE_SUB, main_menuPalLen);

	cursor_ = new Cursor(16, 128, 0, &oamSub);
	cursor_position_ = CURSOR_POSITIONS::PLAY;
	cursor_h_off_ = 128;
}

Menu::~Menu()
{
	delete cursor_;
}

void Menu::process_input(int keys)
{
	if (keys & KEY_LEFT)
	{
		if (cursor_position_ == CURSOR_POSITIONS::EXIT) {
			move_cursor_left();
			cursor_position_ = CURSOR_POSITIONS::PLAY;
		}
	}
	else if (keys & KEY_RIGHT)
	{
		if (cursor_position_ == CURSOR_POSITIONS::PLAY)
		{
			move_cursor_right();
			cursor_position_ = CURSOR_POSITIONS::EXIT;
		}
	}
	else if (keys & KEY_A)
	{
		exit = true;
	}

	update();
}

void Menu::update()
{
	cursor_->update();
}

void Menu::move_cursor_left()
{
	cursor_->move(cursor_->get_x() - 128, cursor_->get_y());
}

void Menu::move_cursor_right()
{
	cursor_->move(cursor_->get_x() + 128, cursor_->get_y());
}