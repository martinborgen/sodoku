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
    return 0;
}

void brute_force_solve(Sodoku sodoku) {

    int i = 0; 
    int j = 0;
    while (j < sodoku.get_side_len() && i < sodoku.get_side_len()) {
        std::vector curr_row = sodoku.get_row(i);
        std::vector curr_col = sodoku.get_col(j);
        std::vector curr_box = sodoku.get_nums_in_box(i / sodoku.get_box_side_len(), j / sodoku.get_box_side_len());
    }
}