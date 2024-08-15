// Sodoku solver program project
// Martin Borgén 
// 2024-08-14

#include <iostream>
#include "sodoku.hpp"

void brute_force_solve(Sodoku sodoku);

int main() {
    // Just testing of sodoku class atm
    Sodoku s(9, 3);
    
    // Verificating the print of dummy hardcoded sodoku
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

    return 0;
}

void brute_force_solve(Sodoku sodoku) {

    int i = 0; 
    int j = 0;
    while (i < sodoku.get_side_len()) {
        while (j < sodoku.get_side_len()) {
            int current = sodoku.get_cell(i, j);
            
            if (current > 0) {
                j++;
                continue;
            }

            int prospective = 1;
            while (prospective <= sodoku.get_side_len() &&
                   sodoku.row_contains(i, prospective) &&
                   sodoku.col_contains(j, prospective) &&
                   sodoku.box_contains(i / sodoku.get_box_side_len(), 
                                       j / sodoku.get_box_side_len(), prospective)) {
                prospective++;
            }

            if (prospective > sodoku.get_side_len()) {
                if (j > 0) {
                    j--;
                } else {

                }

                // sodoku.set_cell(i, j)
            }

            j++;
        }
        i++;
    }
}