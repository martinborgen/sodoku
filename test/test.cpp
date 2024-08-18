#include <iostream>
#include <vector>
#include "acutest.h"
#include "sodoku.hpp"

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

// clang-format off
std::vector<std::vector<int>> _sodoku_vector = {{0,5,0, 8,0,0, 0,0,0},
                                                {0,0,7, 6,0,3, 0,0,0},
                                                {2,0,0, 0,0,0, 9,0,0},
                                                {0,0,2, 9,0,0, 0,3,5},
                                                {0,0,0, 3,5,0, 4,0,0},
                                                {3,6,0, 0,8,4, 0,0,7},
                                                {5,0,0, 1,0,0, 0,4,6},
                                                {7,0,4, 0,6,2, 0,0,0},
                                                {1,0,0, 4,9,0, 0,8,0}};
// clang-format on

void initialize_sodoku() {
    Sodoku s(9, 3);

    for (int i = 0; i < 9; i++) {
        TEST_CHECK(s.get_row(i) == std::vector<int>(9, 0));
    }
}

void verify_initial_cell_status() {
    Sodoku s(9, 3);
    s = _sodoku_vector;

    TEST_CHECK(s.is_initial(0, 0) == false);
    TEST_CHECK(s.is_initial(0, 1) == true);
}

void verify_set_cell() {
    Sodoku s(9, 3);
    s.set_cell(0, 0, 9);
    TEST_CHECK(s.get_cell(0, 0) == 9);

    s.set_cell(0, 1, 11);
    TEST_CHECK(s.get_cell(0, 1) == 0);
    TEST_MSG("Expected: %d", 0);
    TEST_MSG("Produced: %d", s.get_cell(0, 1));

    Sodoku s2(9, 3);
    s2 = _sodoku_vector;

    int expecetd = s2.get_cell(0, 1);
    s2.set_cell(0, 1, 9);
    int produced = s2.get_cell(0, 1);
    TEST_CHECK(produced == expecetd);
    TEST_MSG("Expected: %d, as cell is initial", expecetd);
    TEST_MSG("Produced: %d", produced);
}

void verify_assignment_operator() {
    Sodoku s(9, 3);
    s = _sodoku_vector;

    for (int i = 0; i < s.get_side_len(); i++) {
        TEST_CHECK(s.get_row(i) == _sodoku_vector[i]);
        TEST_MSG("Row vectors does not match");
    }

    Sodoku s2(4, 2);
    s2 = _sodoku_vector;
    TEST_CHECK(s2.get_row(0).size() == 4);
    TEST_CHECK(s2.get_col(0).size() == 4);
}

void verify_original_vector_is_unchanged() {
    Sodoku s(9, 3);
    s = _sodoku_vector;

    s.set_cell(0, 0, 4);
    TEST_CHECK(_sodoku_vector[0][0] == 0);
}

void verify_column_access() {
    Sodoku s(9, 3);
    s = _sodoku_vector;

    for (int col = 0; col < s.get_side_len(); col++) {
        std::vector<int> column;
        column.reserve(9);
        for (int row = 0; row < s.get_side_len(); row++) {
            column.push_back(s.get_cell(row, col));
        }
        TEST_CHECK(s.get_col(col) == column);
    }
}

void verify_box_access() {
    Sodoku s(9, 3);
    s = _sodoku_vector;
    int box_len = 3;

    for (int count = 0; count < s.get_side_len(); count++) {
        int i = count / box_len;
        int j = count % box_len;
        std::vector<int> box;
        box.reserve(s.get_side_len());
        for (int box_i = 0; box_i < box_len; box_i++) {
            for (int box_j = 0; box_j < box_len; box_j++) {
                box.push_back(
                    _sodoku_vector[i * box_len + box_i][j * box_len + box_j]);
            }
        }
        TEST_CHECK(box == s.get_nums_in_box(i, j));
    }
}

void verify_boolean_contains() {
    Sodoku s(9, 3);
    s = _sodoku_vector;

    TEST_CHECK(s.row_contains(0, 8) == true);
    TEST_CHECK(s.row_contains(2, 5) == false);
    TEST_CHECK(s.box_contains(1, 1, 9) == true);
    TEST_CHECK(s.box_contains(1, 1, 7) == false);
}

void initial_values_check() {
    Sodoku s(9, 3);
    s = _sodoku_vector;

    TEST_CHECK(s.is_initial(0, 1) == true);
    TEST_CHECK(s.is_initial(0, 0) == false);
}

void verify_solved_count() {
    Sodoku s(9, 3);
    s = _sodoku_vector;

    int expected = 31;
    int produced = s.get_solved_count();
    TEST_CHECK(produced == expected);
    TEST_MSG("Expected: %d", expected);
    TEST_MSG("Produced: %d", produced);
}

void verify_solution_checker() {
    Sodoku s(9, 3);
    // clang-format off
    std::vector<std::vector<int>> v = {{6, 5, 3, 8, 1, 9, 2, 7, 4},
                                       {4, 9, 7, 6, 2, 3, 8, 5, 1},
                                       {2, 1, 8, 7, 4, 5, 9, 6, 3},
                                       {8, 4, 2, 9, 7, 1, 6, 3, 5},
                                       {9, 7, 1, 3, 5, 6, 4, 2, 8},
                                       {3, 6, 5, 2, 8, 4, 1, 9, 7},
                                       {5, 2, 9, 1, 3, 8, 7, 4, 6},
                                       {7, 8, 4, 5, 6, 2, 3, 1, 9},
                                       {1, 3, 6, 4, 9, 7, 5, 8, 0}};
    // clang-format on'
    s = v;
    s.set_cell(8, 8, 2);
    TEST_CHECK(s.verify_solution() == true);
    s.set_cell(8, 8, 1);
    TEST_CHECK(s.verify_solution() == false);
    s.set_cell(8, 8, 0);
    TEST_CHECK(s.verify_solution() == false);
}

TEST_LIST = {{"initialize sodoku", initialize_sodoku},
             {"verify original vector is unchanged",
              verify_original_vector_is_unchanged},
             {"verify cell's initial status", verify_initial_cell_status},
             {"verify set cell", verify_set_cell},
             {"verify assignment operator", verify_assignment_operator},
             {"verify col access", verify_column_access},
             {"verify box access", verify_box_access},
             {"veryf boolean contains", verify_boolean_contains},
             {"initial values check", initial_values_check},
             {"verify solved count", verify_solved_count},
             {"verify solution checker", verify_solution_checker},
             {NULL, NULL}};
