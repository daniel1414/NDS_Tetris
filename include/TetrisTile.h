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

public:
	TetrisTile(u16 px, u16 py, TILE_TYPE tile_type);
	virtual ~TetrisTile();

	void move_to_side(bool right, u16 poffset);
	void rotate(bool right);
	void move(u16 px, u16 py);
	void move_down(u16 poffset);
	void move_up(u16 poffset);
	void move_down_squares(u16 py, u16 poffset); /* move down all squares with matching py */
	bool erase_row(u16 py); /* return true if deleted every square */

	void update();

	void get_square_positions(std::vector<std::pair<u16, u16>>& output) const;

	inline bool is_falling() const { return falling_; }
	inline void stop() { falling_ = false; }
	inline TILE_TYPE get_type() const { return tile_type_; }

private:
	void get_suqare_offsets(std::vector<std::pair<u16, u16>>& output, TILE_TYPE type) const;
	
	u16 px_; // top left coords
	u16 py_;
	TILE_TYPE tile_type_;
	std::vector<std::unique_ptr<Square>>squares_;
	bool falling_;
};

#endif /* _TETRIS_TILE_H_ */