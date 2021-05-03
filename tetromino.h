#ifndef _TETROMINO_H_
#define _TETROMINO_H_

#include <iostream>

class Board;

class Tetromino {
private:
    std::wstring _shape[7];
    int _nTetromino;
    int _nRotation;
    int _nPosX;
    int _nPosY;

public:
    Tetromino();

    int index();
    int rotation();
    int posx();
    int posy();

    Tetromino down();

    Tetromino right();

    Tetromino left();

    Tetromino rotate();

    std::wstring current();

    std::wstring get(const size_t index);

    bool fit(Board board);

    void next(Board board);
};

#endif