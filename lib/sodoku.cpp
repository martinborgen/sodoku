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
    this->row_contains_arr.reserve(side_length);
    this->col_contains_arr.reserve(side_length);
    this->initial_values.reserve(side_length);
    for (int i = 0; i < side_length; i++) {
        this->sodoku[i].reserve(side_length);
        this->row_contains_arr[i].assign(side_length + 1, false); // + 1 is so that index corresponds to values 1-9
        this->col_contains_arr[i].assign(side_length + 1, false);
        this->initial_values[i].assign(side_length, false);
    }

    this->box_contains_arr.reserve(side_length / box_size);
    for (int i = 0; i < box_size; i++) {
        this->box_contains_arr[i].reserve(side_length / box_size);
        for (int j = 0; j < box_size; j++) {
            this->box_contains_arr[i][j].assign(side_length + 1, false);
            int a = 0;
        }
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

    this->establish_initial_contains();
    this->establish_initial_values();
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

void Sodoku::set_cell(int row, int col, int val) {
    this->sodoku[row][col] = val;
}

std::vector<int> Sodoku::get_nums_in_box(int row, int col) {
    std::vector<int> out;
    out.reserve(this->side_length);
    for (int i = 0; i < this->box_size; i++) {
        for (int j = 0; j < this->box_size; j++) {
            out.push_back(this->sodoku[row * this->box_size + i][col * this->box_size + j]);
        }
    }
    return out;
}

void Sodoku::establish_initial_contains(void) {
    for (int i = 0; i < this->side_length; i++) {
        for (int j = 0; j < this->side_length; j++) {
            int curr = this->get_cell(i, j);
            this->row_contains_arr[i][curr] = true;
            this->col_contains_arr[j][curr] = true;
            this->box_contains_arr[i / this->box_size][j / box_size][curr] = true;
        }
    }
}


void Sodoku::establish_initial_values(void) {
    for (int i = 0; i < this->side_length; i++) {
        for (int j = 0; j < this->side_length; j++) {
            if (this->get_cell(i, j) > 0) {
                this->initial_values[i][j] = true;
            }
        }
    }
}

bool Sodoku::is_initial(int row, int col) {
    return this->initial_values[row][col];
}

bool Sodoku::row_contains(int row, int val) {
    return this->row_contains_arr[row][val];
}

bool Sodoku::col_contains(int col, int val) {
    return this->col_contains_arr[col][val];
}

// row and col are box indices, typically 0-2 in a normal sodoku
bool Sodoku::box_contains(int row, int col, int val) {
    return this->box_contains_arr[row][col][val];
}