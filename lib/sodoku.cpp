#include "sodoku.hpp"
#include <vector>
#include <cmath>

Sodoku::Sodoku(int side_len, int box_len)
{
    this->side_length = side_len;
    this->box_size = box_len;
    this->solved_count = 0;
    this->sodoku.assign(this->side_length, std::vector<int>(this->side_length, 0));
    this->row_contains_arr.assign(this->side_length, std::vector<bool>(side_len + 1, false));
    this->col_contains_arr.assign(this->side_length, std::vector<bool>(side_len + 1, false));
    this->initial_values.assign(this->side_length, std::vector<bool>(side_len, false));
    this->box_contains_arr.assign(this->side_length / this->box_size, 
        std::vector<std::vector<bool>>(this->side_length / this->box_size, 
        std::vector<bool>(this->side_length + 1, false)));
}

Sodoku& Sodoku::operator=(std::vector<std::vector<int>>& initial)
{
    this->side_length = initial.size();
    this->box_size = std::sqrt(this->side_length);
    this->solved_count = 0;
    this->sodoku = initial;
    this->row_contains_arr.assign(this->side_length, std::vector<bool>(this->side_length + 1, false));
    this->col_contains_arr.assign(this->side_length, std::vector<bool>(this->side_length + 1, false));
    this->initial_values.assign(this->side_length, std::vector<bool>(this->side_length, false));
    this->box_contains_arr.assign(this->side_length / this->box_size, 
        std::vector<std::vector<bool>>(this->side_length / this->box_size, 
        std::vector<bool>(this->side_length + 1, false)));

    this->establish_initial_contains();
    this->establish_initial_values();
    return *this;
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
    if (this->is_initial(row, col)) {
        return;
    }
    
    int old_val = this->get_cell(row, col);
    if (val > 0) {
        this->solved_count++;
        this->row_contains_arr[row][val] = true;
        this->col_contains_arr[col][val] = true;
        this->box_contains_arr[row / this->box_size][col / this->box_size][val] = true;
    } else {
        this->solved_count--;
    }
    this->row_contains_arr[row][old_val] = false;
    this->col_contains_arr[col][old_val] = false;
    this->box_contains_arr[row / this->box_size][col / this->box_size][old_val] = false;
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
                this->solved_count++;
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

int Sodoku::get_solved_count(void) {
    return this->solved_count;
}