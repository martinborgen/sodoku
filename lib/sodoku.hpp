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
public:
    Sodoku(int side_length, int box_size);
    ~Sodoku();
    int get_side_len();
    int get_box_side_len();
    std::vector<int> get_row(int row);
    std::vector<int> get_col(int col);
    int get_cell(int row, int col);
    std::vector<int> get_nums_in_box(int row, int col);
};

#endif // _SODOKU_CLASS_HEADER_H