
#include <cstdint>

#ifndef _SODOKU_CLASS_HEADER_H
#define _SODOKU_CLASS_HEADER_H

class Sodoku
{
private:
    int side_length;
    int box_size;
public:
    Sodoku(int side, int box_size);
    ~Sodoku();
    int get_len();
    int get_box();
};

#endif // _SODOKU_CLASS_HEADER_H