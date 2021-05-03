#include "board.h"
#include "tetromino.h"
#include "rotate.h"

int Board::width()
{
    return this->_width;
}

int Board::height()
{
    return this->_height;
}

unsigned char *Board::field()
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

void Board::lock(Tetromino tetromino)
{
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            if (tetromino.current()[Rotate(px, py, tetromino.rotation())] == L'X')
                this->pField[(tetromino.posy() + py) * this->_width + (tetromino.posx() + px)] = tetromino.index() + 1;
        }
    }
}
