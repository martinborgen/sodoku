#include "sodoku.hpp"

Sodoku::Sodoku(int side, int box_size)
{
    this->side_length = side;
    this->box_size = box_size;
}

Sodoku::~Sodoku()
{
}

int Sodoku::get_box()
{
    return this->box_size;
}

int Sodoku::get_len()
{
    return this->side_length;
}