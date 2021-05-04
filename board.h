#ifndef _BOARD_H_
#define _BOARD_H_

#include <stddef.h>

class Tetromino;

class Board {
private:
    int _width;
    int _height;
    unsigned char *pField;

public:
    Board(const int width = 12, const int height = 18)
        :_width(width), _height(height){
            pField = new unsigned char[this->_width * this->_height];
        }
    
    const int width() const;

    const int height() const;

    unsigned char & operator()(const size_t row, const size_t col);

    unsigned char operator()(const size_t row, const size_t col) const;

    unsigned char* field();

    void init();
    void lock(Tetromino tetromino);
};

#endif
