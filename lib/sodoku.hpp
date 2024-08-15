#include <vector>
#include <cstdint>

#ifndef _SODOKU_CLASS_HEADER_H
#define _SODOKU_CLASS_HEADER_H

class Sodoku
{
private:
    int side_length;
    int box_size;
    std::vector<std::vector<int>> sodoku;
    std::vector<std::vector<bool>> row_contains_arr;
    std::vector<std::vector<bool>> col_contains_arr;
    std::vector<std::vector<std::vector<bool>>> box_contains_arr;
    void establish_initial_contains(void);
public:
    Sodoku(int side_length, int box_size);
    ~Sodoku();
    int get_side_len();
    int get_box_side_len();
    std::vector<int> get_row(int row);
    std::vector<int> get_col(int col);
    int get_cell(int row, int col);
    std::vector<int> get_nums_in_box(int row, int col);

    bool row_contains(int row, int val);
    bool col_contains(int col, int val);

    // row and col are box indices, typically 0-2 in a normal sodoku
    bool box_contains(int row, int col, int val);
};

#endif // _SODOKU_CLASS_HEADER_H