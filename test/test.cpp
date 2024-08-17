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

void verify_column_access() {
    Sodoku s(9, 3);
    s = _sodoku_vector;

    std::vector<int> col_test;
    col_test = s.get_col(2);

    for (int i = 0; i < s.get_side_len(); i++) {
        std::vector<int> col;
        col.reserve(9);
        for (int j = 0; j < s.get_side_len(); j++) {
            col.push_back(s.get_cell(i, j));
        }
        TEST_CHECK(s.get_col(i) == col);
    }
}

void verify_box_access() {
    Sodoku s(9, 3);
    s = _sodoku_vector;
    int box_len = 3;


    for (int count = 0; count < s.get_side_len(); count++) {
        int i = count % box_len;
        int j = count / box_len;
        std::vector<int> box;
        box.reserve(s.get_side_len());
        for (int box_i = 0; box_i < box_len; box_i++) {
            for (int box_j = 0; box_j < box_len; box_j++) {
                box.push_back(_sodoku_vector[i + box_i][j + box_j]);
            }
        }
        TEST_CHECK(box == s.get_nums_in_box(i, j));
    }
}

TEST_LIST = {
    {"initialize sodoku", initialize_sodoku},
    {"verify col access", verify_column_access},
    {"verify box access", verify_box_access},
    {NULL, NULL}
};

    // // Verification of box access
    // std::cout << "\n";
    // std::vector<int> box_test;
    // box_test = s.get_nums_in_box(1, 1);
    // for (int i = 0; i < s.get_box_side_len() * s.get_box_side_len(); i++) {
    //     std::cout << box_test[i];
    // }
    // std::cout << "\n";

    // // verification of boolean contains function
    // if (s.row_contains(0, 8)) {
    //     std::cout << "row 0 contains 8\n";
    // } else {
    //     std::cout << "Error row_contains\n";
    // }
    // if (!s.row_contains(2, 5)) {
    //     std::cout << "row 2 does not contain 5\n";
    // } else {
    //     std::cout << "Error col_contains\n";
    // }
    // if (s.box_contains(1, 1, 9)) {
    //     std::cout << "Box (1, 1) contains 9\n";
    // } else {
    //     std::cout << "Error box contains\n";
    // }
    // if (!s.box_contains(1, 1, 7)) {
    //     std::cout << "Box (1, 1) does not contain 7\n";
    // } else {
    //     std::cout << "ERROR box contains\n";
    // }

    // // Initial values check
    // if (s.is_initial(0, 1)) {
    //     std::cout << "Square 0, 1 is initial\n";
    // } else {
    //     std::cout << "ERROR in is_initial!\n";
    // }

    // if (!s.is_initial(0, 0)) {
    //     std::cout << "Square 0, 0 is not initial\n";
    // } else {
    //     std::cout << "ERROR in is_initial!\n";
    // }

    // // Verification of solved count
    // if (s.get_solved_count() == 31) {
    //     std::cout << "Solved is 31\n";
    // } else {
    //     std::cout << "Error in solved count";
    // }


    // std::cout << "\n verificiation original is unchanged:\n";

    // for (int i = 0; i < sodoku.size(); i++) {
    //     for (int j = 0; j < sodoku[0].size(); j++) {
    //         std::cout << sodoku[i][j];
    //     }
    //     std::cout << "\n";
    // }

    // return 0;