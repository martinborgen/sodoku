// Sodoku class that provides data storage and access methods suitable for
// sodoku-solvers

// Martin Borgén
// August 2024

#include "sodoku.hpp"
#include <cmath>
#include <vector>

Sodoku::Sodoku() : Sodoku::Sodoku(9, 3) {}

Sodoku::Sodoku(int side_len, int box_len) {
    this->side_length = side_len;
    this->box_side_length = box_len;
    this->solved_count = 0;
    this->sodoku.assign(this->side_length,
                        std::vector<int>(this->side_length, 0));
    this->row_contains_vec.assign(this->side_length,
                                  std::vector<bool>(side_len + 1, false));
    this->col_contains_vec.assign(this->side_length,
                                  std::vector<bool>(side_len + 1, false));
    this->initial_values.assign(this->side_length,
                                std::vector<bool>(side_len, false));
    this->box_contains_vec.assign(
        this->side_length / this->box_side_length,
        std::vector<std::vector<bool>>(
            this->side_length / this->box_side_length,
            std::vector<bool>(this->side_length + 1, false)));
}

Sodoku& Sodoku::operator=(std::vector<std::vector<int>>& initial) {
    this->solved_count = 0;
    this->initial_values.assign(this->side_length,
                                std::vector<bool>(this->side_length, false));

    this->sodoku.assign(this->side_length,
                        std::vector<int>(this->side_length, 0));

    for (int i = 0; i < initial.size(); i++) {
        if (i >= this->side_length) {
            break;
        }
        for (int j = 0; j < initial[i].size(); j++) {
            if (j >= this->side_length || initial[i][j] == 0 ||
                initial[i][j] > this->side_length) {
                continue;
            }

            this->sodoku[i][j] = initial[i][j];
        }
    }

    this->row_contains_vec.assign(
        this->side_length, std::vector<bool>(this->side_length + 1, false));
    this->col_contains_vec.assign(
        this->side_length, std::vector<bool>(this->side_length + 1, false));
    this->box_contains_vec.assign(
        this->side_length / this->box_side_length,
        std::vector<std::vector<bool>>(
            this->side_length / this->box_side_length,
            std::vector<bool>(this->side_length + 1, false)));

    this->establish_initial_contains();
    this->establish_initial_values();
    return *this;
}

Sodoku::~Sodoku() {}

int Sodoku::get_box_side_len() {
    return this->box_side_length;
}

int Sodoku::get_side_len() {
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
    if (this->is_initial(row, col) || val > this->side_length) {
        return;
    }

    int old_val = this->get_cell(row, col);
    if (val > 0) {
        this->solved_count++;
        this->row_contains_vec[row][val] = true;
        this->col_contains_vec[col][val] = true;
        this->box_contains_vec[row / this->box_side_length]
                              [col / this->box_side_length][val] = true;
    } else {
        this->solved_count--;
    }
    this->row_contains_vec[row][old_val] = false;
    this->col_contains_vec[col][old_val] = false;
    this->box_contains_vec[row / this->box_side_length]
                          [col / this->box_side_length][old_val] = false;
    this->sodoku[row][col] = val;
}

std::vector<int> Sodoku::get_nums_in_box(int row, int col) {
    std::vector<int> out;
    out.reserve(this->side_length);
    for (int i = 0; i < this->box_side_length; i++) {
        for (int j = 0; j < this->box_side_length; j++) {
            out.push_back(this->sodoku[row * this->box_side_length + i]
                                      [col * this->box_side_length + j]);
        }
    }
    return out;
}

void Sodoku::establish_initial_contains(void) {
    for (int i = 0; i < this->side_length; i++) {
        for (int j = 0; j < this->side_length; j++) {
            int curr = this->get_cell(i, j);
            this->row_contains_vec[i][curr] = true;
            this->col_contains_vec[j][curr] = true;
            this->box_contains_vec[i / this->box_side_length]
                                  [j / box_side_length][curr] = true;
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
    return this->row_contains_vec[row][val];
}

bool Sodoku::col_contains(int col, int val) {
    return this->col_contains_vec[col][val];
}

// row and col are box indices, typically 0-2 in a normal sodoku
bool Sodoku::box_contains(int row, int col, int val) {
    return this->box_contains_vec[row][col][val];
}

int Sodoku::get_solved_count(void) {
    return this->solved_count;
}

bool Sodoku::verify_nums(std::vector<int> nums) {
    std::vector<int> buckets(nums.size() + 1, 0);

    for (int i = 0; i < nums.size(); i++) {
        buckets[nums[i]]++;
    }

    if (buckets[0] > 0) {
        return false;
    }

    for (int i = 1; i < buckets.size(); i++) {
        if (buckets[i] != 1) {
            return false;
        }
    }
    return true;
}

bool Sodoku::verify_solution(void) {
    // buckets will be used to count the numbers in rows, columns and boxes.
    for (int row = 0; row < this->side_length; row++) {
        if (!this->verify_nums(this->get_row(row))) {
            return false;
        }
    }

    // check the columns
    for (int col = 0; col < this->side_length; col++) {
        if (!this->verify_nums(this->get_col(col))) {
            return false;
        }
    }

    // check the boxes
    for (int count = 0; count < this->side_length; count++) {
        int i = count / this->box_side_length;
        int j = count % this->box_side_length;
        if (!this->verify_nums(this->get_nums_in_box(i, j))) {
            return false;
        }
    }
    return true;
}