#pragma once

#include "Cursor.h"

enum class CURSOR_POSITIONS
{
	PLAY,
	EXIT
};

class Menu
{
public:
	Menu();
	~Menu();
	
	void process_input(int keys);
	CURSOR_POSITIONS get_cursor_pos() const { return cursor_position_; }

	bool exit = false;
private:
	void update();
	void move_cursor_left();
	void move_cursor_right();

	int bg_;
	Cursor* cursor_;
	CURSOR_POSITIONS cursor_position_;
	u8 cursor_h_off_;
};