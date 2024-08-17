#include "acutest.h"
#include "sodoku.hpp"
#include <vector>
#include <iostream>

std::vector<std::vector<int>> _sodoku_vector = {{0,5,0, 8,0,0, 0,0,0},
                                                {0,0,7, 6,0,3, 0,0,0},
                                                {2,0,0, 0,0,0, 9,0,0},
                                                {0,0,2, 9,0,0, 0,3,5},
                                                {0,0,0, 3,5,0, 4,0,0},
                                                {3,6,0, 0,8,4, 0,0,7},
                                                {5,0,0, 1,0,0, 0,4,6},
                                                {7,0,4, 0,6,2, 0,0,0},
                                                {1,0,0, 4,9,0, 0,8,0}};
void initialize_sodoku() {
    // Creating empty sodoku, then examining behaviour
    Sodoku s(9, 3); 

    for (int i = 0; i < 9; i++) {
        TEST_CHECK(s.get_row(i) == std::vector<int>(9, 0));
    }

    s.set_cell(0, 0, 9);

    TEST_CHECK(s.get_cell(0, 0) == 9);

    s = _sodoku_vector;
    
    for (int i = 0; i < s.get_side_len(); i++) {
        TEST_CHECK(s.get_row(i) == _sodoku_vector[i]);
    }
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
                box.push_back(_sodoku_vector[i * box_len + box_i][j * box_len + box_j]);
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


TEST_LIST = {
    {"initialize sodoku", initialize_sodoku},
    {"verify original vector is unchanged", verify_original_vector_is_unchanged},
    {"verify col access", verify_column_access},
    {"verify box access", verify_box_access},
    {"veryf boolean contains", verify_boolean_contains},
    {"initial values check", initial_values_check},
    {"verify solved count", verify_solved_count},
    {NULL, NULL}
};

