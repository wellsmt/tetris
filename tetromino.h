#ifndef _TETROMINO_H_
#define _TETROMINO_H_

#include <iostream>

class Tetromino {
private:
    std::wstring _shape[7];

public:
    Tetromino();

    std::wstring get(const size_t index);
};

#endif