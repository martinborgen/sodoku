// Sodoku class that provides data storage and access methods suitable for
// sodoku-solvers

// Martin Borgén
// August 2024

#include <cstdint>
#include <vector>

#ifndef _SODOKU_CLASS_HEADER_H
#define _SODOKU_CLASS_HEADER_H

class Sodoku {
   private:
    int side_length;
    int box_size;
    int solved_count;
    std::vector<std::vector<int>> sodoku;
    std::vector<std::vector<bool>> row_contains_arr;
    std::vector<std::vector<bool>> col_contains_arr;
    std::vector<std::vector<std::vector<bool>>> box_contains_arr;
    std::vector<std::vector<bool>> initial_values;
    void establish_initial_contains(void);
    void establish_initial_values(void);
    bool verify_nums(std::vector<int> nums);

   public:
    // creates an emtpy sodoku. A typical sodoku has side len 9 and box len 3
    Sodoku(int side_len, int box_len);
    ~Sodoku();

    // (re) assigns the sodoku to have the clues provided by the initial
    // -vector. initial bust be of dimensions that the sodoku was created for.
    Sodoku& operator=(std::vector<std::vector<int>>& initial);

    // returns the length of one side of the sodoku
    int get_side_len();

    // returns the length of the sub-boxes of the sodoku
    int get_box_side_len();

    // returns the row of the sodoku
    std::vector<int> get_row(int row);

    // returns the column of the sodoku
    std::vector<int> get_col(int col);

    // returns the value of a cell in the sodoku
    int get_cell(int row, int col);

    // sets a cell in the sodoku to val. If cell is initial, then cell is not
    // changed.
    void set_cell(int row, int col, int val);

    // Returns the number of filled cells. Includes the initial clues. Does not
    // guarantee that the solution is correct.
    int get_solved_count(void);

    // Return the numbers in the box
    // row and col are indexed 0-2 for a typical 9x9 sodoku
    std::vector<int> get_nums_in_box(int row, int col);

    // Returns if the row contains val
    bool row_contains(int row, int val);

    // Returns if the column contains val
    bool col_contains(int col, int val);

    // Returns if the box contains val. row and col are box indices, typically
    // 0-2 in a normal sodoku
    bool box_contains(int row, int col, int val);

    // Returns if a cell is an initial clue or not.
    bool is_initial(int row, int col);

    // Returns whether the solution is legal or not.
    bool verify_solution();
};

#endif  // _SODOKU_CLASS_HEADER_H