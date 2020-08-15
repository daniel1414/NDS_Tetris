#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <nds.h>
#include <vector>

class Square {
private:
	u8 x_;
	u8 y_;
	u8 id_;
	OamState* oam_;

	const unsigned int* tiles_ptr_;
	const u32 tiles_len_;
	const unsigned short* pal_ptr_;
	const u32 pal_len_;
	const u8 pal_offset_;
	
	u16* gfx_;

	static std::vector<int> ids_in_use_sub_;
	static std::vector<int> ids_in_use_main_;

	void init();
	void change_oam(OamState* oam);
	void change_oam_if_needed();
public:
	Square(u8 x, u8 y, const unsigned int* tiles_ptr, const u32 tiles_len, const unsigned short* pal_ptr, const u32 pal_len, const u8 pal_offset);
	void move(u8 x, u8 y);
	void move_up();
	void move_down();
	void move_right();
	void move_left();
	void update();
	inline u8 get_x() const { return x_; }
	inline u8 get_y() const { return y_; }

	~Square();
};

#endif /* _SQUARE_H_ */