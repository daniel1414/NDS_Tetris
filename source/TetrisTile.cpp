#include "TetrisTile.h"

#include <algorithm>

#include "i_square.h"
#include "o_square.h"
#include "j_square.h"
#include "l_square.h"
#include "s_square.h"
#include "z_square.h"
#include "t_square.h"


TetrisTile::TetrisTile(s8 x, u8 y, TILE_TYPE tile_type) :
	x_(x), y_(y), tile_type_(tile_type), falling_(true)
{
	/* initialize the squares */
	switch (tile_type) {
	case TILE_TYPE::TILE_I:
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_,     i_squareTiles, i_squareTilesLen, i_squarePal, i_squarePalLen, 0));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 1, i_squareTiles, i_squareTilesLen, i_squarePal, i_squarePalLen, 0));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 2, i_squareTiles, i_squareTilesLen, i_squarePal, i_squarePalLen, 0));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 3, i_squareTiles, i_squareTilesLen, i_squarePal, i_squarePalLen, 0));
		break;
	case TILE_TYPE::TILE_O:
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 1, o_squareTiles, o_squareTilesLen, o_squarePal, o_squarePalLen, 8));
		squares_.push_back(std::make_unique<Square>(x_ + 2, y_ + 1, o_squareTiles, o_squareTilesLen, o_squarePal, o_squarePalLen, 8));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 2, o_squareTiles, o_squareTilesLen, o_squarePal, o_squarePalLen, 8));
		squares_.push_back(std::make_unique<Square>(x_ + 2, y_ + 2, o_squareTiles, o_squareTilesLen, o_squarePal, o_squarePalLen, 8));
		break;
	case TILE_TYPE::TILE_J:
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_,     j_squareTiles, j_squareTilesLen, j_squarePal, j_squarePalLen, 16));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 1, j_squareTiles, j_squareTilesLen, j_squarePal, j_squarePalLen, 16));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 2, j_squareTiles, j_squareTilesLen, j_squarePal, j_squarePalLen, 16));
		squares_.push_back(std::make_unique<Square>(x_, y_ + 2,     j_squareTiles, j_squareTilesLen, j_squarePal, j_squarePalLen, 16));
		break;
	case TILE_TYPE::TILE_L:
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_,     l_squareTiles, l_squareTilesLen, l_squarePal, l_squarePalLen, 24));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 1, l_squareTiles, l_squareTilesLen, l_squarePal, l_squarePalLen, 24));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 2, l_squareTiles, l_squareTilesLen, l_squarePal, l_squarePalLen, 24));
		squares_.push_back(std::make_unique<Square>(x_ + 2, y_ + 2, l_squareTiles, l_squareTilesLen, l_squarePal, l_squarePalLen, 24));
		break;
	case TILE_TYPE::TILE_S:
		squares_.push_back(std::make_unique<Square>(x_ + 2, y_ + 1, s_squareTiles, s_squareTilesLen, s_squarePal, s_squarePalLen, 32));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 1, s_squareTiles, s_squareTilesLen, s_squarePal, s_squarePalLen, 32));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 2, s_squareTiles, s_squareTilesLen, s_squarePal, s_squarePalLen, 32));
		squares_.push_back(std::make_unique<Square>(x_, y_ + 2,     s_squareTiles, s_squareTilesLen, s_squarePal, s_squarePalLen, 32));
		break;
	case TILE_TYPE::TILE_T:
		squares_.push_back(std::make_unique<Square>(x_, y_ + 1,     t_squareTiles, t_squareTilesLen, t_squarePal, t_squarePalLen, 40));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 1, t_squareTiles, t_squareTilesLen, t_squarePal, t_squarePalLen, 40));
		squares_.push_back(std::make_unique<Square>(x_ + 2, y_ + 1, t_squareTiles, t_squareTilesLen, t_squarePal, t_squarePalLen, 40));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 2, t_squareTiles, t_squareTilesLen, t_squarePal, t_squarePalLen, 40));
		break;
	case TILE_TYPE::TILE_Z:
		squares_.push_back(std::make_unique<Square>(x_, y_ + 1,     z_squareTiles, z_squareTilesLen, z_squarePal, z_squarePalLen, 48));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 1, z_squareTiles, z_squareTilesLen, z_squarePal, z_squarePalLen, 48));
		squares_.push_back(std::make_unique<Square>(x_ + 1, y_ + 2, z_squareTiles, z_squareTilesLen, z_squarePal, z_squarePalLen, 48));
		squares_.push_back(std::make_unique<Square>(x_ + 2, y_ + 2, z_squareTiles, z_squareTilesLen, z_squarePal, z_squarePalLen, 48));
		break;
	}
	update();
}
void TetrisTile::update()
{
	for (auto& s : squares_)
	{
		s->update();
	}
}

void TetrisTile::move(bool right)
{
	if (right)
	{
		// make sure none of the squares is at right bound
		bool can_move = true;
		for (auto& s : squares_)
		{
			if (s->get_x() == 9)
				can_move = false;
		}
		if (can_move)
		{
			x_ += 1;
			for (auto& s : squares_)
				s->move_right();
		}
	}
	else {
		// make sure none of the squares is at left bound
		bool can_move = true;
		for (auto& s : squares_)
		{
			if (s->get_x() == 0)
				can_move = false;
		}
		if (can_move)
		{
			x_ -= 1;
			for (auto& s : squares_)
				s->move_left();
		}
	}
}

void TetrisTile::rotate(bool right)
{
	u8 x_p;
	u8 y_p;
	for (auto& s : squares_)
	{
		const u8 x = s->get_x();
		const u8 y = s->get_y();
		u8 x_norm = x - x_;
		u8 y_norm = y - y_;

		switch (tile_type_) {
		case TILE_TYPE::TILE_I:
		case TILE_TYPE::TILE_O:
			if (right) {
				x_p = 3 - y_norm + x_;
				y_p = x_norm + y_;
			}
			else {
				x_p = y_norm + x_;
				y_p = 3 - x_norm + y_;
			}
			break;
		case TILE_TYPE::TILE_J:
		case TILE_TYPE::TILE_L:
		case TILE_TYPE::TILE_S:
		case TILE_TYPE::TILE_T:
		case TILE_TYPE::TILE_Z:
			if (right) {
				x_p = 2 - y_norm + x_;
				y_p = x_norm + y_;
			}
			else {
				x_p = y_norm + x_;
				y_p = 2 - x_norm + y_;
			}
			break;
		default:
			x_p = 0;
			y_p = 0;
		}
		s->move(x_p, y_p);
	}
}

void TetrisTile::fall()
{
	y_ += 1;
	for (unsigned int i = 0; i < squares_.size(); i++) {
		squares_[i]->move_down();
	}
}
void TetrisTile::fly()
{
	y_ -= 1;
	for (unsigned int i = 0; i < squares_.size(); i++) {
		squares_[i]->move_up();
	}
}
void TetrisTile::fall_square(u8 y)
{
	/* individual square can fall only when whole Tile isn't falling anymore */
	if (!falling_)
	{
		for (auto& s : squares_)
		{
			if (s->get_y() == y) {
				s->move_down();
			}
		}
	}
}

bool TetrisTile::erase_row(u8 y)
{
	unsigned int i = 0;
	while(i < squares_.size())
	{
		if (squares_[i]->get_y() == y) {
			squares_.erase(squares_.begin() + i);
			i--;
		}
		i++;
	}
	if (squares_.empty()) {
		return true;
	}
	else {
		return false;
	}
}
std::vector<std::pair<int, int>> TetrisTile::get_square_positions() const
{
	std::vector<std::pair<int, int>> positions;
	for (const auto& s : squares_)
	{
		positions.push_back(std::make_pair<int, int>(s->get_x(), s->get_y()));
	}
	return positions;
}
TetrisTile::~TetrisTile()
{

}