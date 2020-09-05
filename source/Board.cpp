#include "Board.h"
#include <nds/arm9/background.h>

#include <algorithm>
#include <map>

#include "board_bg_up.h"
#include "board_bg_down.h"

std::random_device Board::rd;
std::mt19937 Board::mt(Board::rd());
std::uniform_int_distribution<int> Board::dist_tile(0, 7);

Board::Board()
{
	bg_ = bgInit(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);
	bg_sub_ = bgInitSub(3, BgType_Text8bpp, BgSize_T_256x256, 0, 1);

	dmaCopy(board_bg_downTiles, bgGetGfxPtr(bg_), board_bg_downTilesLen);
	dmaCopy(board_bg_downMap, bgGetMapPtr(bg_), board_bg_downMapLen);
	dmaCopy(board_bg_downPal, BG_PALETTE, board_bg_downPalLen);

	dmaCopy(board_bg_upTiles, bgGetGfxPtr(bg_sub_), board_bg_upTilesLen);
	dmaCopy(board_bg_upMap, bgGetMapPtr(bg_sub_), board_bg_upMapLen);
	dmaCopy(board_bg_upPal, BG_PALETTE_SUB, board_bg_upPalLen);

	new_future_tile();
	new_tile();
}

Board::~Board()
{
	bgHide(bg_);
	bgHide(bg_sub_);
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
		if (!can_move_down()) {
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

void Board::move_down_cur_tile()
{
	if (!can_move_down()) {
		tetris_tiles_.back()->stop();
		erase_rows_if_needed();
		new_tile();
		if (check_overlap()) { // he's dead
			game_over();
		}
	}
}

/* private functions */
bool Board::can_move_down() const
{
	bool can_move_down = true;
	tetris_tiles_.back()->move_down(SQUARE_SIZE);
	/* ckeck if tiles are below */
	if (check_overlap()) 
	{
		can_move_down = false;
	}
	/* check if ground is below */
	std::vector<std::pair<u16, u16>> new_positions;
	tetris_tiles_.back()->get_square_positions(new_positions);

	for (auto& pos : new_positions)
	{
		if (pos.second >= BOARD_HEIGHT_PX) 
		{
			can_move_down = false;
		}
	}
	if (!can_move_down) {
		tetris_tiles_.back()->move_up(SQUARE_SIZE);
	}
	tetris_tiles_.back()->update();
	return can_move_down;
}

bool Board::can_rotate(bool right) const
{
	bool can_rotate = true;
	/* rotate and check, if there are two blocks in the same position in that area */
	tetris_tiles_.back()->rotate(right);
	
	if (check_overlap()) 
	{
		can_rotate = false;
	}
	/* check if after rotation the tile exceeds the board */
	std::vector<std::pair<u16, u16>> new_positions;
	tetris_tiles_.back()->get_square_positions(new_positions);

	for (auto& p : new_positions) 
	{
		if (p.first < BOARD_BORDER_LEFT_PX || p.first >= BOARD_BORDER_RIGHT_PX) 
		{
			can_rotate = false;
		}
	}

	if (!can_rotate)
	{
		tetris_tiles_.back()->rotate(!right);
	}
	
	tetris_tiles_.back()->update();
	return can_rotate;
}
bool Board::can_move(bool right) const
{
	/* logid similar to can_rotate() */
	bool can_move = true;
	tetris_tiles_.back()->move_to_side(right, SQUARE_SIZE);

	if (check_overlap()) 
	{
		can_move = false;
	}

	std::vector<std::pair<u16, u16>> new_positions;
	tetris_tiles_.back()->get_square_positions(new_positions);

	for (auto& p : new_positions) 
	{
		if (p.first < BOARD_BORDER_LEFT_PX || p.first >= BOARD_BORDER_RIGHT_PX) 
		{
			can_move = false;
		}
	}

	if (!can_move) 
	{
		tetris_tiles_.back()->move_to_side(!right, SQUARE_SIZE);
	}

	tetris_tiles_.back()->update();
	return can_move;
}

/* checks overlap with the last tile and all previous tiles */
bool Board::check_overlap() const
{
	std::vector<std::pair<u16, u16>> new_positions;
	tetris_tiles_.back()->get_square_positions(new_positions);

	for (unsigned int i = 0; i < tetris_tiles_.size() - 1; i++) 
	{
		std::vector<std::pair<u16, u16>> other_tile_positions;
		tetris_tiles_[i]->get_square_positions(other_tile_positions);

		for (unsigned int j = 0; j < other_tile_positions.size(); j++)
		{
			for (unsigned int k = 0; k < new_positions.size(); k++) 
			{
				if ((other_tile_positions[j].first == new_positions[k].first) && (other_tile_positions[j].second == new_positions[k].second)) 
				{
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
	int y = BOARD_HEIGHT - 1;

	while(y >= 0)
	{
		int square_count = 0;
		for (const auto& t : tetris_tiles_)
		{
			std::vector<std::pair<u16, u16>> pos;
			t->get_square_positions(pos);
			for (const auto& p : pos)
			{
				if (p.second == y * SQUARE_SIZE) 
				{
					square_count++;
				}
			}
		}

		if (square_count == 10) 
		{
			rows_erased++;
			unsigned int t = 0;

			while (t < tetris_tiles_.size())
			{
				bool erased_all = tetris_tiles_[t]->erase_row(y * SQUARE_SIZE);
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
					t->move_down_squares(z * SQUARE_SIZE, SQUARE_SIZE);
					t->update();
				}
			}
			y++;
		}
		y--;
	}

	return rows_erased;
}

void Board::new_future_tile()
{
	TILE_TYPE new_tile_type;
	u16 new_x = BOARD_NEW_TILE_RECT_PX;
	u16 new_y = BOARD_NEW_TILE_RECT_PY;
	switch (dist_tile(mt)) {
	case 0:
		new_tile_type = TILE_TYPE::TILE_I;
		new_x = BOARD_NEW_TILE_RECT_PX;
		new_y = BOARD_NEW_TILE_RECT_PY;
		break;
	case 1:
		new_tile_type = TILE_TYPE::TILE_J;
		new_x = BOARD_NEW_TILE_RECT_PX + 8;
		new_y = BOARD_NEW_TILE_RECT_PY + 8;
		break;
	case 2:
		new_tile_type = TILE_TYPE::TILE_L;
		new_x = BOARD_NEW_TILE_RECT_PX - 8;
		new_y = BOARD_NEW_TILE_RECT_PY + 8;
		break;
	case 3:
		new_tile_type = TILE_TYPE::TILE_O;
		new_x = BOARD_NEW_TILE_RECT_PX - 8;
		new_y = BOARD_NEW_TILE_RECT_PY;
		break;
	case 4:
		new_tile_type = TILE_TYPE::TILE_S;
		new_x = BOARD_NEW_TILE_RECT_PX;
		new_y = BOARD_NEW_TILE_RECT_PY;
		break;
	case 5:
		new_tile_type = TILE_TYPE::TILE_T;
		new_x = BOARD_NEW_TILE_RECT_PX;
		new_y = BOARD_NEW_TILE_RECT_PY;
		break;
	case 6:
		new_tile_type = TILE_TYPE::TILE_Z;
		new_x = BOARD_NEW_TILE_RECT_PX;
		new_y = BOARD_NEW_TILE_RECT_PY;
		break;
	default:
		new_tile_type = TILE_TYPE::TILE_I;
		new_x = BOARD_NEW_TILE_RECT_PX;
		new_y = BOARD_NEW_TILE_RECT_PY;
		break;
	}
	future_tile_ = std::make_unique<TetrisTile>(new_x, new_y, new_tile_type);
}

void Board::new_tile()
{
	future_tile_->move(BOARD_BORDER_LEFT_PX + 3 * SQUARE_SIZE, 0);
	tetris_tiles_.push_back(std::move(future_tile_));
	new_future_tile();
	update();
}

void Board::update()
{
	for(auto& t : tetris_tiles_)
	{
		t->update();
	}
}


void Board::game_over()
{
	tetris_tiles_.clear();
	alive = false;
}