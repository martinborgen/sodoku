// Sodoku solver program project
// Martin Borgén 
// 2024-08-14

#include <iostream>
#include "sodoku.hpp"

int main() {
    Sodoku s(81, 3);
    printf("Hello World hehe!\nThis sodoku has a total of %d squares with boxes of %d squares", s.get_len(), s.get_box());
    return 0;
}