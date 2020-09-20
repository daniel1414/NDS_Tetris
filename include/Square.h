#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <nds.h>
#include <vector>

#define SQUARE_SIZE 16

class Square {
public:
	Square(u16 px, u16 py, const unsigned int* tiles_ptr, const u32 tiles_len, const unsigned short* pal_ptr, const u32 pal_len, const u8 pal_offset);
	Square(const Square&) = delete;
	Square& operator=(const Square&) = delete;
	~Square();
	
	void move(u16 px, u16 py);
	void move_up(u16 poffset);
	void move_down(u16 poffset);
	void move_right(u16 poffset);
	void move_left(u16 poffset);
	
	void update();
	
	inline u16 get_px() const { return px_; }
	inline u16 get_py() const { return py_; }

private:
	void init();
	void change_oam(OamState* oam);
	void change_oam_if_needed();

	static std::vector<int> ids_in_use_sub_;
	static std::vector<int> ids_in_use_main_;

	u16 px_;
	u16 py_;
	u8 id_;
	OamState* oam_;

	u16* gfx_;
	const unsigned int* tiles_ptr_;
	const u32 tiles_len_;
	const unsigned short* pal_ptr_;
	const u32 pal_len_;
	const u8 pal_offset_;
	
};

#endif /* _SQUARE_H_ */