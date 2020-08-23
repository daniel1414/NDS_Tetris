#pragma once

#include "nds.h"

class Cursor
{
public:
	Cursor(u8 px, u8 py, u8 id, OamState* oam);
	~Cursor();
	void move(u8 px, u8 py);
	void update();

	inline u8 get_x() const { return x_; }
	inline u8 get_y() const { return y_; }

private:
	u8 x_;
	u8 y_;
	u16* gfx_;
	u8 id_;
	OamState* oam_;
};