#include "TetrisTile.h"

#include <algorithm>

#include "i_square.h"
#include "o_square.h"
#include "j_square.h"
#include "l_square.h"
#include "s_square.h"
#include "z_square.h"
#include "t_square.h"


TetrisTile::TetrisTile(u16 px, u16 py, TILE_TYPE tile_type) :
    px_(px), py_(py), tile_type_(tile_type), falling_(true)
{
    std::vector<std::pair<u16, u16>> square_offsets;
    get_suqare_offsets(square_offsets, tile_type_);
    /* initialize the squares */
    switch (tile_type) {
    case TILE_TYPE::TILE_I:
        for(unsigned int i = 0; i < square_offsets.size(); i++)
        {
            squares_.push_back(std::make_unique<Square>(px_ + square_offsets[i].first, py_ + square_offsets[i].second, i_squareTiles, i_squareTilesLen, i_squarePal, i_squarePalLen, 0));
        }
        break;
    case TILE_TYPE::TILE_O:
        for(unsigned int i = 0; i < square_offsets.size(); i++)
        {
            squares_.push_back(std::make_unique<Square>(px_ + square_offsets[i].first, py_ + square_offsets[i].second, o_squareTiles, o_squareTilesLen, o_squarePal, o_squarePalLen, 8));
        }
        break;
    case TILE_TYPE::TILE_J:
        for(unsigned int i = 0; i < square_offsets.size(); i++)
        {
            squares_.push_back(std::make_unique<Square>(px_ + square_offsets[i].first, py_ + square_offsets[i].second, j_squareTiles, j_squareTilesLen, j_squarePal, j_squarePalLen, 16));
        }
        break;
    case TILE_TYPE::TILE_L:
        for(unsigned int i = 0; i < square_offsets.size(); i++)
        {
            squares_.push_back(std::make_unique<Square>(px_ + square_offsets[i].first, py_ + square_offsets[i].second, l_squareTiles, l_squareTilesLen, l_squarePal, l_squarePalLen, 24));
        }
        break;
    case TILE_TYPE::TILE_S:
        for(unsigned int i = 0; i < square_offsets.size(); i++)
        {
            squares_.push_back(std::make_unique<Square>(px_ + square_offsets[i].first, py_ + square_offsets[i].second, s_squareTiles, s_squareTilesLen, s_squarePal, s_squarePalLen, 32));
        }
        break;
    case TILE_TYPE::TILE_T:
        for(unsigned int i = 0; i < square_offsets.size(); i++)
        {
            squares_.push_back(std::make_unique<Square>(px_ + square_offsets[i].first, py_ + square_offsets[i].second, t_squareTiles, t_squareTilesLen, t_squarePal, t_squarePalLen, 40));
        }
        break;
    case TILE_TYPE::TILE_Z:
        for(unsigned int i = 0; i < square_offsets.size(); i++)
        {
            squares_.push_back(std::make_unique<Square>(px_ + square_offsets[i].first, py_ + square_offsets[i].second, z_squareTiles, z_squareTilesLen, z_squarePal, z_squarePalLen, 48));
        }
        break;
    }
    update();
}

TetrisTile::~TetrisTile()
{

}

void TetrisTile::move_to_side(bool right, u16 poffset)
{
    if (right)
    {
        px_ += poffset;
        for (auto& s : squares_)
        {
            s->move_right(poffset);
        }
    }
    else {
        px_ -= poffset;
        for (auto& s : squares_)
        {
            s->move_left(poffset);
        }
    }
}

/* -------------------- needs to be updated -------------------- */
void TetrisTile::rotate(bool right)
{
    u16 fut_px;
    u16 fut_py;

    for (auto& s : squares_)
    {
        const u16 cur_px = s->get_px();
        const u16 cur_py = s->get_py();
        u16 x_norm = (cur_px - px_) / SQUARE_SIZE; // 0 - 3
        u16 y_norm = (cur_py - py_) / SQUARE_SIZE; // 0 - 3

        switch (tile_type_) {
        case TILE_TYPE::TILE_I:
        case TILE_TYPE::TILE_O:
            if (right)
            {
                //fut_px = 3 - py_norm + x_;
                //fut_py = px_norm + y_;				
                fut_px = (3 - y_norm) * SQUARE_SIZE + px_;
                fut_py = x_norm * SQUARE_SIZE + py_;
            }
            else 
            {
                //x_p = y_norm + x_;
                //y_p = 3 - x_norm + y_;
                fut_px = y_norm * SQUARE_SIZE + px_;
                fut_py = (3 - x_norm) * SQUARE_SIZE + py_;
            }
            break;
        case TILE_TYPE::TILE_J:
        case TILE_TYPE::TILE_L:
        case TILE_TYPE::TILE_S:
        case TILE_TYPE::TILE_T:
        case TILE_TYPE::TILE_Z:
            if (right) {
                //x_p = 2 - y_norm + x_;
                //y_p = x_norm + y_;
                fut_px = (2 - y_norm) * SQUARE_SIZE + px_;
                fut_py = x_norm * SQUARE_SIZE + py_;
            }
            else {
                //x_p = y_norm + x_;
                //y_p = 2 - x_norm + y_;
                fut_px = y_norm * SQUARE_SIZE + px_;
                fut_py = (2 - x_norm) * SQUARE_SIZE + py_;
            }
            break;
        default:
            fut_px = 0;
            fut_py = 0;
        }
        s->move(fut_px, fut_py);
    }
}

void TetrisTile::move(u16 px, u16 py)
{
    px_ = px;
    py_ = py;
    std::vector<std::pair<u16, u16>> square_offsets;
    get_suqare_offsets(square_offsets, tile_type_);
    for(unsigned int i = 0; i < squares_.size(); i++)
    {
        squares_[i]->move(px_ + square_offsets[i].first, py_ + square_offsets[i].second);
    }
    update();
}

void TetrisTile::move_down(u16 poffset)
{
    py_ += poffset;
    for (auto& s : squares_)
    {
        s->move_down(poffset);
    }
}

void TetrisTile::move_up(u16 poffset)
{
    py_ -= poffset;
    for (auto& s : squares_)
    {
        s->move_up(poffset);
    }
}

void TetrisTile::move_down_squares(u16 py, u16 poffset)
{
    /* individual square can fall only when whole Tile isn't falling anymore */
    if (!falling_)
    {
        for (auto& s : squares_)
        {
            if (s->get_py() == py) 
            {
                s->move_down(poffset);
            }
        }
    }
}

bool TetrisTile::erase_row(u16 py)
{
    unsigned int i = 0;
    while(i < squares_.size())
    {
        if (squares_[i]->get_py() == py) 
        {
            squares_.erase(squares_.begin() + i);
            i--;
        }
        i++;
    }
    if (squares_.empty()) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}
void TetrisTile::update()
{
    for (auto& s : squares_)
    {
        s->update();
    }
}

void TetrisTile::get_square_positions(std::vector<std::pair<u16, u16>>& output) const
{
    output.clear();
    output.reserve(4);
    for (const auto& s : squares_)
    {
        output.push_back(std::make_pair<u16, u16>(s->get_px(), s->get_py()));
    }
}

void TetrisTile::get_suqare_offsets(std::vector<std::pair<u16, u16>>& output, TILE_TYPE type) const
{
    output.clear();
    output.reserve(4);
    switch(type)
    {
    case TILE_TYPE::TILE_I:
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 0 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 3 * SQUARE_SIZE));
        break;
    case TILE_TYPE::TILE_J:
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 0 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(0 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        break;
    case TILE_TYPE::TILE_L:
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 0 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(2 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        break;
    case TILE_TYPE::TILE_O:
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(2 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(2 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        break;
    case TILE_TYPE::TILE_S:
        output.push_back(std::make_pair<u16, u16>(2 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(0 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        break;
    case TILE_TYPE::TILE_T:
        output.push_back(std::make_pair<u16, u16>(0 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(2 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        break;
    case TILE_TYPE::TILE_Z:
        output.push_back(std::make_pair<u16, u16>(0 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 1 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(1 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        output.push_back(std::make_pair<u16, u16>(2 * SQUARE_SIZE, 2 * SQUARE_SIZE));
        break;
    }
}