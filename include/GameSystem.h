#pragma once
#include "Board.h"
#include "Menu.h"

enum class GAME_STATE
{
	MENU,
	GAMEPLAY,
	EXIT
};

class GameSystem
{
public:
	GameSystem();
	void run();

private:
	void hardware_init();
	void init_menu();
	void deinit_menu();
	void init_board();
	void deinit_board();

	Board* board_;
	Menu* menu_;
	GAME_STATE game_state_;
	bool running_ = true;

	static void timer_callback();

	static bool waiting_tim_0;
	static u16 waiting_ticks_0;
};