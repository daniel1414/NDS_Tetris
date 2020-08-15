#ifndef _TETRIS_TILE_H_
#define _TETRIS_TILE_H_

#include <nds.h>
#include "Square.h"

#include <memory>
#include <vector>
#include <map>

enum class TILE_TYPE {
	TILE_I,
	TILE_J,
	TILE_L,
	TILE_O,
	TILE_S,
	TILE_T,
	TILE_Z
};

class TetrisTile {
	s8 x_; // top left coords
	u8 y_;
	TILE_TYPE tile_type_;
	std::vector<std::unique_ptr<Square>>squares_;
	bool falling_;

public:
	TetrisTile(s8 x, u8 y, TILE_TYPE tile_type);
	void update();

	void move(bool right);
	void rotate(bool right);
	void fall();
	void fly();
	void fall_square(u8 y);
	/* return true if deleted every square */
	bool erase_row(u8 y);
	inline bool is_falling() const { return falling_; }
	inline void stop() { falling_ = false; }
	inline TILE_TYPE get_type() const { return tile_type_; }
	std::vector<std::pair<int, int>> get_square_positions() const;
	/* virtual destructor */
	virtual ~TetrisTile();
};

#endif /* _TETRIS_TILE_H_ */