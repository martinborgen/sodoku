// Sodoku solver program project
// Martin Borgén 
// 2024-08-14

#include <iostream>
#include "sodoku.hpp"

void brute_force_solve(Sodoku& sodoku);
void print_sodoku(Sodoku& s);

int main() {
    // Vector to be sent to the sodoku class
    std::vector<std::vector<int>> sodoku = {{0,5,0, 8,0,0, 0,0,0},
                                            {0,0,7, 6,0,3, 0,0,0},
                                            {2,0,0, 0,0,0, 9,0,0},
                                            {0,0,2, 9,0,0, 0,3,5},
                                            {0,0,0, 3,5,0, 4,0,0},
                                            {3,6,0, 0,8,4, 0,0,7},
                                            {5,0,0, 1,0,0, 0,4,6},
                                            {7,0,4, 0,6,2, 0,0,0},
                                            {1,0,0, 4,9,0, 0,8,0}};
    
    // Creating empty sodoku, then examining behaviour
    Sodoku s(9, 3);
    print_sodoku(s);
    s.set_cell(0, 0, 9);
    print_sodoku(s);
    s = sodoku;

    print_sodoku(s);
    
    // Verificating the print of sodoku
    for (int i = 0; i < s.get_side_len(); i++) {
        for (int j = 0; j < s.get_side_len(); j++) {
            std::cout << s.get_cell(i, j);
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    // Verification of column access
    std::vector<int> col_test;
    col_test = s.get_col(2);

    for (int i = 0; i < s.get_side_len(); i++) {
        std::cout << col_test[i] << "\n";
    }

    // Verification of box access
    std::cout << "\n";
    std::vector<int> box_test;
    box_test = s.get_nums_in_box(1, 1);
    for (int i = 0; i < s.get_box_side_len() * s.get_box_side_len(); i++) {
        std::cout << box_test[i];
    }
    std::cout << "\n";

    // verification of boolean contains function
    if (s.row_contains(0, 8)) {
        std::cout << "row 0 contains 8\n";
    } else {
        std::cout << "Error row_contains\n";
    }
    if (!s.row_contains(2, 5)) {
        std::cout << "row 2 does not contain 5\n";
    } else {
        std::cout << "Error col_contains\n";
    }
    if (s.box_contains(1, 1, 9)) {
        std::cout << "Box (1, 1) contains 9\n";
    } else {
        std::cout << "Error box contains\n";
    }
    if (!s.box_contains(1, 1, 7)) {
        std::cout << "Box (1, 1) does not contain 7\n";
    } else {
        std::cout << "ERROR box contains\n";
    }

    // Initial values check
    if (s.is_initial(0, 1)) {
        std::cout << "Square 0, 1 is initial\n";
    } else {
        std::cout << "ERROR in is_initial!\n";
    }

    if (!s.is_initial(0, 0)) {
        std::cout << "Square 0, 0 is not initial\n";
    } else {
        std::cout << "ERROR in is_initial!\n";
    }

    // Verification of solved count
    if (s.get_solved_count() == 31) {
        std::cout << "Solved is 31\n";
    } else {
        std::cout << "Error in solved count";
    }

    brute_force_solve(s);

    std::cout << "\n verificiation original is unchanged:\n";

    for (int i = 0; i < sodoku.size(); i++) {
        for (int j = 0; j < sodoku[0].size(); j++) {
            std::cout << sodoku[i][j];
        }
        std::cout << "\n";
    }

    return 0;
}

void brute_force_solve(Sodoku& sodoku) {

    int i = 0; 
    int j = 0;
    int maxit = 1000000;
    int it = 0;
    while (it < maxit && sodoku.get_solved_count() < sodoku.get_side_len() * sodoku.get_side_len()) {
        print_sodoku(sodoku);
        if (sodoku.is_initial(i, j)) {
            if (j < sodoku.get_side_len() - 1) {
                j++;
            } else if (i < sodoku.get_side_len() - 1) {
                j = 0;
                i++;
            } else {
                std::cout << "Brute solve failed\n"; 
                return;
            }
            continue;
        }
        
        int current = sodoku.get_cell(i, j);
        int prospective = current + 1;

        while (prospective <= sodoku.get_side_len() && (
                sodoku.row_contains(i, prospective) ||
                sodoku.col_contains(j, prospective) ||
                sodoku.box_contains(i / sodoku.get_box_side_len(), 
                                    j / sodoku.get_box_side_len(), prospective))) {
            prospective++;
        }

        if (prospective <= sodoku.get_side_len()) {
            // set cell and increment
            sodoku.set_cell(i, j, prospective);
            if (j < sodoku.get_side_len() - 1) {
                j++;
            } else if (i < sodoku.get_side_len() - 1) {
                j = 0;
                i++;
            } else {
                // means sucessful solve
                std::cout << "\nSOLVED\n";
                print_sodoku(sodoku);
            }
        } else {
            // Means going backwards
            sodoku.set_cell(i, j, 0);
            if (j > 0) {
                j--;
            } else if (i > 0) {
                j = sodoku.get_side_len() - 1;
                i--;
            }

            while (i >= 0 &&
                   j >= 0 &&
                   sodoku.is_initial(i, j)) {

                if (j > 0) {
                    j--;
                } else if (i > 0) {
                    j = sodoku.get_side_len() - 1;
                    i--;
                }
            }

            if (i == 0 && j == 0 && sodoku.get_cell(i, j) > sodoku.get_side_len()) {
                std::cout << "Brute solve failed\n"; 
                return;
            }
        }
        // it++;
    }
    if (it == maxit) {
        std::cout << "hit maxit\n";
    } else {
        std::cout << "SOLVED!\n";
        print_sodoku(sodoku);
    }
}

void print_sodoku(Sodoku& s) {
    for (int i = 0; i < s.get_side_len(); i++) {
        for (int j = 0; j < s.get_side_len(); j++) {
            std::cout << s.get_cell(i, j);
            if (j % 3 == 2) {
                std::cout << " ";
            }
        }
        if (i % 3 == 2) {
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}