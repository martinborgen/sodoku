#include "sodoku.hpp"
#include <vector>

// A sodoku for testing:
// 0,5,0, 8,0,0, 0,0,0 
// 0,0,7, 6,0,3, 0,0,0
// 2,0,0, 0,0,0, 9,0,0
// 0,0,2, 9,0,0, 0,3,5
// 0,0,0, 3,5,0, 4,0,0
// 3,6,0, 0,8,4, 0,0,7
// 5,0,0, 1,0,0, 0,4,6
// 7,0,4, 0,6,2, 0,0,0
// 1,0,0, 4,9,0, 0,8,0

// SOLUTION:
// 6 5 3 8 1 9 2 7 4
// 4 9 7 6 2 3 8 5 1
// 2 1 8 7 4 5 9 6 3
// 8 4 2 9 7 1 6 3 5
// 9 7 1 3 5 6 4 2 8
// 3 6 5 2 8 4 1 9 7
// 5 2 9 1 3 8 7 4 6
// 7 8 4 5 6 2 3 1 9
// 1 3 6 4 9 7 5 8 2

Sodoku::Sodoku(int side_length, int box_size)
{
    this->side_length = side_length;
    this->box_size = box_size;
    this->sodoku.reserve(side_length);
    for (int i = 0; i < side_length; i++) {
        this->sodoku[i].reserve(side_length);

    }

    // Hardcoding a sodoku for testing purposes now. 
    sodoku[0] = {0,5,0, 8,0,0, 0,0,0};
    sodoku[1] = {0,0,7, 6,0,3, 0,0,0};
    sodoku[2] = {2,0,0, 0,0,0, 9,0,0};
    sodoku[3] = {0,0,2, 9,0,0, 0,3,5};
    sodoku[4] = {0,0,0, 3,5,0, 4,0,0};
    sodoku[5] = {3,6,0, 0,8,4, 0,0,7};
    sodoku[6] = {5,0,0, 1,0,0, 0,4,6};
    sodoku[7] = {7,0,4, 0,6,2, 0,0,0};
    sodoku[8] = {1,0,0, 4,9,0, 0,8,0};
}

Sodoku::~Sodoku()
{
}

int Sodoku::get_box_side_len()
{
    return this->box_size;
}

int Sodoku::get_side_len()
{
    return this->side_length;
}

std::vector<int> Sodoku::get_row(int row) {
    return this->sodoku[row];
}

std::vector<int> Sodoku::get_col(int col) {
    std::vector<int> out;
    out.reserve(this->side_length);
    for (int i = 0; i < this->side_length; i++) {
        out.push_back(this->sodoku[i][col]);
    }
    return out;
}

int Sodoku::get_cell(int row, int col) {
    return this->sodoku[row][col];
}