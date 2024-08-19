// Sodoku solver program project
// Martin Borgén
// 2024-08-14

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include "sodoku.hpp"

void brute_force_solve(Sodoku& sodoku);
void print_sodoku(Sodoku& s);
std::vector<std::vector<int>> read_sodoku_from_file(std::string filename);
std::vector<std::vector<int>> read_sodoku_from_file(std::string filename,
                                                    int side_size);

int main(int argc, char* argv[]) {
    // Vector to be sent to the sodoku class
    std::vector<std::vector<int>> sodoku;
    if (argc > 1) {
        sodoku = read_sodoku_from_file(std::string(argv[1]));
    } else {
        // This is temporary. Probably should print intented usage.
        std::cout << "Intended usage: sodoku_solver <filename to a txt>";
        // sodoku =
        //     read_sodoku_from_file(std::string("../sample_sodokus/test1.txt"));
    }

    Sodoku s(sodoku.size(), sqrt(sodoku.size()));
    s = sodoku;
    print_sodoku(s);

    brute_force_solve(s);

    if (s.verify_solution()) {
        std::cout << "Solution verified\n";
    } else {
        std::cout << "Solution false\n";
    }
    return 0;
}

void brute_force_solve(Sodoku& sodoku) {
    int i = 0;
    int j = 0;
    int maxit = 1000000;
    int it = 0;
    while (it < maxit && sodoku.get_solved_count() <
                             sodoku.get_side_len() * sodoku.get_side_len()) {
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

        while (
            prospective <= sodoku.get_side_len() &&
            (sodoku.row_contains(i, prospective) ||
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

            while (i >= 0 && j >= 0 && sodoku.is_initial(i, j)) {
                if (j > 0) {
                    j--;
                } else if (i > 0) {
                    j = sodoku.get_side_len() - 1;
                    i--;
                }
            }

            if (i == 0 && j == 0 &&
                sodoku.get_cell(i, j) > sodoku.get_side_len()) {
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
            if (j % s.get_box_side_len() == s.get_box_side_len() - 1) {
                std::cout << " ";
            }
        }
        if (i % s.get_box_side_len() == s.get_box_side_len() - 1) {
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::vector<std::vector<int>> read_sodoku_from_file(std::string filename) {
    return read_sodoku_from_file(filename, 9);
}

std::vector<std::vector<int>> read_sodoku_from_file(std::string filename,
                                                    int side_size) {
    std::ifstream input_file(filename);
    std::vector<std::vector<int>> output = std::vector<std::vector<int>>(
        side_size, std::vector<int>(side_size, 0));

    if (!input_file.is_open()) {
        // Error. Throw exception?
        return output;
    }

    std::string line;
    std::vector<std::string> nums;
    int i = 0;
    while (getline(input_file, line)) {
        std::istringstream iline(line);
        std::string num;
        int j = 0;
        while (getline(iline, num, ',')) {
            sscanf(num.c_str(), "%d", &output[i][j]);
            j++;
        }
        i++;
    }
    return output;
}