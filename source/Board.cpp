#include "Board.h"
#include <nds/arm9/background.h>

#include <algorithm>
#include <map>

#include "board_bg.h"

std::random_device Board::rd;
std::mt19937 Board::mt(Board::rd());
std::uniform_int_distribution<int> Board::dist_tile(0, 7);

/* private functions */
bool Board::can_fall() const
{
	bool can_fall = true;
	tetris_tiles_.back()->fall();
	/* ckeck if tiles are below */
	if (check_overlap()) {
		can_fall = false;
	}
	/* check if ground is below */
	std::vector<std::pair<int, int>> new_positions = tetris_tiles_.back()->get_square_positions();
	for (auto& pos : new_positions) {
		if (pos.second > 23) {
			can_fall = false;
		}
	}
	if (!can_fall) {
		tetris_tiles_.back()->fly();
	}
	tetris_tiles_.back()->update();
	return can_fall;
}
bool Board::can_rotate(bool right) const
{
	bool can_rotate = true;
	/* rotate and check, if there are two blocks in the same position in that area */
	tetris_tiles_.back()->rotate(right);
	if (check_overlap()) {
		can_rotate = false;
	}
	/* check if after rotation the tile exceeds the board */
	std::vector<std::pair<int, int>> new_positions = tetris_tiles_.back()->get_square_positions();
	for (auto& p : new_positions) {
		if (p.first < 0 || p.first > 9) {
			can_rotate = false;
		}
	}
	if (!can_rotate){
		tetris_tiles_.back()->rotate(!right);
	}
	tetris_tiles_.back()->update();
	return can_rotate;
}
bool Board::can_move(bool right) const
{
	bool can_move = true;
	tetris_tiles_.back()->move(right);
	if (check_overlap()) {
		can_move = false;
	}
	auto new_positions = tetris_tiles_.back()->get_square_positions();
	for (auto& p : new_positions) {
		if (p.first < 0 || p.first > 9) {
			can_move = false;
		}
	}
	if (!can_move) {
		tetris_tiles_.back()->move(!right);
	}
	tetris_tiles_.back()->update();
	return can_move;
}
bool Board::check_overlap() const
{
	std::vector<std::pair<int, int>> new_positions = tetris_tiles_.back()->get_square_positions();
	for (unsigned int i = 0; i < tetris_tiles_.size() - 1; i++) {
		std::vector<std::pair<int, int>> other_tile_positions = tetris_tiles_[i]->get_square_positions();
		for (unsigned int j = 0; j < other_tile_positions.size(); j++) {
			for (unsigned int k = 0; k < new_positions.size(); k++) {
				if ((other_tile_positions[j].first == new_positions[k].first) && (other_tile_positions[j].second == new_positions[k].second)) {
					return true;
				}
			}
		}
	}
	return false;
}
u8 Board::erase_rows_if_needed()
{
	/* iterate through tiles and check if there are 10 squares in a row.
		if yes, erase that row and move all squares above one position down.
		return the nuber of erased rows. */
	u8 rows_erased = 0;
	int y = 23;
	while(y >= 0)
	{
		int square_count = 0;
		for (const auto& t : tetris_tiles_)
		{
			std::vector<std::pair<int, int>> pos = t->get_square_positions();
			for (const auto& p : pos)
			{
				if (p.second == y) {
					square_count++;
				}
			}
		}
		if (square_count == 10) {
			rows_erased++;
			unsigned int t = 0;
			while (t < tetris_tiles_.size())
			{
				bool erased_all = tetris_tiles_[t]->erase_row(y);
				if (erased_all) { // erased some tile rests
					tetris_tiles_.erase(tetris_tiles_.begin() + t);
					t--;
				}
				t++;
			}

			for (int z = y - 1; z >= 0; z--)
			{
				/* move down all the squares above */
				for (auto& t : tetris_tiles_)
				{
					t->fall_square(z);
					t->update();
				}
			}
			y++;
		}
		y--;
	}
	return rows_erased;
}

Board::Board()
{
	bg_ = bgInit(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);
	bg_sub_ = bgInitSub(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);

	dmaCopy(board_bgTiles, bgGetGfxPtr(bg_), board_bgTilesLen);
	dmaCopy(board_bgMap, bgGetMapPtr(bg_), board_bgMapLen);
	dmaCopy(board_bgPal, BG_PALETTE, board_bgPalLen);

	dmaCopy(board_bgTiles, bgGetGfxPtr(bg_sub_), board_bgTilesLen);
	dmaCopy(board_bgMap, bgGetMapPtr(bg_sub_), board_bgMapLen);
	dmaCopy(board_bgPal, BG_PALETTE_SUB, board_bgPalLen);

	new_tile();
}

void Board::process_input(int keys_down, int keys_held)
{
	if (keys_down & KEY_LEFT) {
		can_move(false);
	}
	if (keys_down & KEY_RIGHT) {
		can_move(true);
	}
	if ((keys_down & KEY_DOWN) || (keys_held & KEY_DOWN)) {
		if (!can_fall()) {
			tetris_tiles_.back()->stop();
			u8 score = erase_rows_if_needed();
			new_tile();
		}
	}
	if (keys_down & KEY_A) {
		can_rotate(true);
	}
	if (keys_down & KEY_B) {
		can_rotate(false);
	}
}

void Board::new_tile()
{
	TILE_TYPE new_tile_type;
	switch (dist_tile(mt)) {
	case 0:
		new_tile_type = TILE_TYPE::TILE_I;
		break;
	case 1:
		new_tile_type = TILE_TYPE::TILE_J;
		break;
	case 2:
		new_tile_type = TILE_TYPE::TILE_L;
		break;
	case 3:
		new_tile_type = TILE_TYPE::TILE_O;
		break;
	case 4:
		new_tile_type = TILE_TYPE::TILE_S;
		break;
	case 5:
		new_tile_type = TILE_TYPE::TILE_T;
		break;
	case 6:
		new_tile_type = TILE_TYPE::TILE_Z;
		break;
	default:
		new_tile_type = TILE_TYPE::TILE_I;
		break;
	}
	tetris_tiles_.push_back(std::make_shared<TetrisTile>(3, 0, new_tile_type));
}

void Board::fall_cur_tile()
{
	if (!can_fall()) {
		tetris_tiles_.back()->stop();
		erase_rows_if_needed();
		new_tile();
		if (check_overlap()) { // he's dead
			// new game or sth
		}
	}
}