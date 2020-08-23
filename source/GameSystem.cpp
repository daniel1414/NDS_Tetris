#include "GameSystem.h"
#include <nds/arm9/sprite.h>
#include <nds/timers.h>
#include <nds/system.h>

bool GameSystem::waiting_tim_0 = false;
u16 GameSystem::waiting_ticks_0 = 20000;

GameSystem::GameSystem()
{
	hardware_init();
	init_menu();
	game_state_ = GAME_STATE::MENU;
}

void GameSystem::hardware_init()
{
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankB(VRAM_B_MAIN_BG_0x06000000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	oamInit(&oamMain, SpriteMapping_1D_128, false);
	oamInit(&oamSub, SpriteMapping_1D_128, false);
	lcdMainOnBottom();
	timerStart(0, ClockDivider_1024, 65535 - waiting_ticks_0, timer_callback);
}

void GameSystem::run()
{
	timerStart(0, ClockDivider_1024, 65535 - waiting_ticks_0, timer_callback);
	int keys_down;
	int keys_held;
	while (running_)
	{
		while (game_state_ == GAME_STATE::MENU)
		{
			scanKeys();
			keys_down = keysDown();

			menu_->process_input(keys_down);

			if (menu_->exit)
			{
				switch (menu_->get_cursor_pos())
				{
				case CURSOR_POSITIONS::EXIT:
					deinit_menu();
					game_state_ = GAME_STATE::EXIT;
					break;
				case CURSOR_POSITIONS::PLAY:
					deinit_menu();
					init_board();
					game_state_ = GAME_STATE::GAMEPLAY;
					break;
				}
			}
			swiWaitForVBlank();
			oamUpdate(&oamSub);
			oamUpdate(&oamMain);
		}
		while (game_state_ == GAME_STATE::GAMEPLAY)
		{
			waiting_tim_0 = true;
			timerStart(0, ClockDivider_1024, 65535 - waiting_ticks_0, timer_callback);
			while (waiting_tim_0)
			{
				scanKeys();
				keys_down = keysDown();
				keys_held = keysHeld();

				board_->process_input(keys_down, keys_held);

				swiWaitForVBlank();
				oamUpdate(&oamSub);
				oamUpdate(&oamMain);
			}
			board_->fall_cur_tile();
			if (!(board_->alive))
			{
				deinit_board();
				init_menu();
				game_state_ = GAME_STATE::MENU;
			}
		}
		if (game_state_ == GAME_STATE::EXIT)
		{
			running_ = false;
		}
	}
}

void GameSystem::init_menu()
{
	menu_ = new Menu();
}
void GameSystem::deinit_menu()
{
	delete menu_;
}

void GameSystem::init_board()
{
	board_ = new Board();
}

void GameSystem::deinit_board()
{
	delete board_;
}

void GameSystem::timer_callback()
{
	waiting_tim_0 = false;
	if (waiting_ticks_0 > 5000) {
		waiting_ticks_0 -= 100;
	}
}