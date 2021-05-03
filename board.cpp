#include "board.h"

int Board::width()
{
    return this->_width;
}

int Board::height()
{
    return this->_height;
}

unsigned char* Board::field()
{
    return this->pField;
}

void Board::init()
{
    for (int x = 0; x < this->_width; x++)
    {
        for (int y = 0; y < this->_height; y++)
        {
            pField[y * this->_width + x] = (x == 0 || x == this->_width - 1 || y == this->_height - 1) ? 9 : 0;
        }
    }
}
