#include "tetromino.h"
#include "board.h"
#include "rotate.h"

Tetromino::Tetromino()
    :_nTetromino(0), _nRotation(0), _nPosX(0), _nPosY(0)
{
    this->_shape[0].append(L"..X.");
    this->_shape[0].append(L"..X.");
    this->_shape[0].append(L"..X.");
    this->_shape[0].append(L"..X.");

    this->_shape[1].append(L"..X.");
    this->_shape[1].append(L".XX.");
    this->_shape[1].append(L".X..");
    this->_shape[1].append(L"....");

    this->_shape[2].append(L".X..");
    this->_shape[2].append(L".XX.");
    this->_shape[2].append(L"..X.");
    this->_shape[2].append(L"....");

    this->_shape[3].append(L"....");
    this->_shape[3].append(L".XX.");
    this->_shape[3].append(L".XX.");
    this->_shape[3].append(L"....");

    this->_shape[4].append(L"..X.");
    this->_shape[4].append(L".XX.");
    this->_shape[4].append(L"..X.");
    this->_shape[4].append(L"....");

    this->_shape[5].append(L"....");
    this->_shape[5].append(L".XX.");
    this->_shape[5].append(L"..X.");
    this->_shape[5].append(L"..X.");

    this->_shape[6].append(L"....");
    this->_shape[6].append(L".XX.");
    this->_shape[6].append(L".X..");
    this->_shape[6].append(L".X..");
}

int Tetromino::index()
{
    return this->_nTetromino;
}

int Tetromino::rotation()
{
    return this->_nRotation;
}
int Tetromino::posx()
{
    return this->_nPosX;
}
int Tetromino::posy()
{
    return this->_nPosY;
}

std::wstring Tetromino::get(const size_t index){
    return this->_shape[index];
}

void Tetromino::next(Board board)
{
    this->_nTetromino = rand() % 7;
    this->_nRotation = 0;
    this->_nPosX = board.width() / 2;
    this->_nPosY = 0;
}

bool Tetromino::fit(Board board)
{
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            // Get index
            int pi = Rotate(px, py, this->_nRotation);
            // Get index into field
            int fi = (this->_nPosY + py) * board.width() + (this->_nPosX + px);

            if (this->_nPosX + px >= 0 && this->_nPosX + px <= board.width())
            {
                if (this->_nPosY + py >= 0 && this->_nPosY + py <= board.height())
                {
                    if (this->get(this->_nTetromino)[pi] == L'X' && board.field()[fi] != 0)
                        return false;
                }
            }
        }
    }
    return true;
}

Tetromino Tetromino::down()
{
    Tetromino t = *this;
    t._nPosY++;
    return t;
}

Tetromino Tetromino::right()
{
    Tetromino t = *this;
    t._nPosX++;
    return t;
}

Tetromino Tetromino::left()
{
    Tetromino t = *this;
    t._nPosX--;
    return t;
}

Tetromino Tetromino::rotate()
{
    Tetromino t = *this;
    t._nRotation++;
    return t;
}

std::wstring Tetromino::current()
{
    return this->get(this->index());
}