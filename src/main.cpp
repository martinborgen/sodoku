// Sodoku solver program project
// Martin Borgén 
// 2024-08-14

#include <iostream>
#include "sodoku.hpp"

int main() {
    Sodoku s(9, 3);
    

    for (int i = 0; i < s.get_side_len(); i++) {
        for (int j = 0; j < s.get_side_len(); j++) {
            std::cout << s.get_cell(i, j);
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    std::vector<int> res;
    res = s.get_col(2);

    for (int i = 0; i < s.get_side_len(); i++) {
        std::cout << res[i] << "\n";
    }
    return 0;
}