#ifndef _BOARD_H_
#define _BOARD_H_

#include <nds.h>

#include <vector>
#include <memory>
#include <random>

#include "TetrisTile.h"

class Board {
	int bg_;
	int bg_sub_;

	std::vector<std::shared_ptr<TetrisTile>> tetris_tiles_;

	bool can_fall() const;
	bool can_rotate(bool right) const;
	bool can_move(bool right) const;
	bool check_overlap() const;
	u8 erase_rows_if_needed();
	void new_tile();
	void game_over();
public:
	Board();
	~Board();
	void process_input(int keys_down, int keys_held);
	void fall_cur_tile();

	bool alive = true;
	static std::random_device rd;
	static std::mt19937 mt;
	static std::uniform_int_distribution<int> dist_tile;
};

#endif /* _BOARD_H_ */