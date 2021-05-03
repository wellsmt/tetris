#include "tetromino.h"

Tetromino::Tetromino()
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

std::wstring Tetromino::get(const size_t index){
    return this->_shape[index];
}
