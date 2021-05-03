#ifndef _BOARD_H_
#define _BOARD_H_

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
    
    int width();

    int height();

    unsigned char* field();

    void init();
};

#endif
