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
    
    Sodoku s(9, 3);
    s = sodoku;
    print_sodoku(s);

    brute_force_solve(s);

    return 0;
}

void brute_force_solve(Sodoku& sodoku) {

    int i = 0; 
    int j = 0;
    int maxit = 1000000;
    int it = 0;
    while (it < maxit && sodoku.get_solved_count() < sodoku.get_side_len() * sodoku.get_side_len()) {
        // print_sodoku(sodoku);
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
        it++;
    }
    if (it == maxit) {
        std::cout << "hit maxit\n";
    } else {
        std::cout << "\nSOLVED!\nIterations: " << it << "\n";
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