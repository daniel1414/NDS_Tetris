#ifndef _BOARD_H_
#define _BOARD_H_

#include "TetrisTile.h"

#include <nds.h>

#include <vector>
#include <memory>
#include <random>

#define BOARD_WIDTH				10
#define BOARD_HEIGHT			24
#define BOARD_WIDTH_PX			(BOARD_WIDTH * SQUARE_SIZE)
#define BOARD_HEIGHT_PX			(BOARD_HEIGHT * SQUARE_SIZE)
#define BOARD_BORDER_LEFT_PX	(1 * SQUARE_SIZE)
#define BOARD_BORDER_RIGHT_PX	(BOARD_BORDER_LEFT_PX + BOARD_WIDTH_PX)
#define BOARD_NEW_TILE_RECT_PX 	192
#define BOARD_NEW_TILE_RECT_PY 	16
#define BOARD_SCORE_RECT_PX		192
#define BOARD_SCORE_RECT_PY		272

class Board {
public:
	Board();
	~Board();

	void process_input(int keys_down, int keys_held);
	void move_down_cur_tile();

	bool alive = true;

	static std::random_device rd;
	static std::mt19937 mt;
	static std::uniform_int_distribution<int> dist_tile;

private:
	bool can_move_down() const;
	bool can_rotate(bool right) const;
	bool can_move(bool right) const;
	bool check_overlap() const;
	u8 erase_rows_if_needed();
	void new_future_tile();
	void new_tile();
	void game_over();
	void update();

	int bg_;
	int bg_sub_;
	std::unique_ptr<TetrisTile> future_tile_;
	std::vector<std::shared_ptr<TetrisTile>> tetris_tiles_;
};

#endif /* _BOARD_H_ */