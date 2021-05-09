#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "time.h"
#include "board.h"
#include "rotate.h"
#include "tetromino.h"
#include <ncurses.h>
#include "ncurses_setup.h"

void draw(Board board);
void draw_piece(Tetromino tetromino);

using namespace std::literals::chrono_literals;

int main()
{
    srand (time(NULL));

    ncurses_setup();
   
    Board board(12, 18);
    board.init();

    Tetromino tetromino;
    tetromino.next(board);

    bool bGameOver = false;
    bool bKey[4];

    int ch = 0;
    bool bRotateHold = false;
    int nSpeed = 20;
    int nSpeedCounter = 0;
    bool bForceDown = false;

    std::vector<int> vLines;

    while (!bGameOver)
    {
        // GAME TIMING
        std::this_thread::sleep_for(50ms);
        nSpeedCounter++;
        bForceDown = (nSpeedCounter == nSpeed);
        // INPUT
        ch = kbhit();
        
        bKey[0] = (ch == 261); // R
        bKey[1] = (ch == 260); // L
        bKey[2] = (ch == 258); // D
        bKey[3] = (ch == 122); // z

        // GAME LOGIC

        if(bKey[0] && tetromino.right().fit(board))
        {
            tetromino = tetromino.right();
        }
        if(bKey[1] && tetromino.left().fit(board))
        {
            tetromino = tetromino.left();
        }
        if(bKey[2] && tetromino.down().fit(board))
        {
            tetromino = tetromino.down();
        }
        
        if (bKey[3])
        {
            if(!bRotateHold && bKey[3] && tetromino.rotate().fit(board))
            {
                tetromino = tetromino.rotate();
            }
            bRotateHold = true;
        }
        else
        {
            bRotateHold = false;
        }

        if(bForceDown)
        {
            if(tetromino.down().fit(board))
            {
                tetromino = tetromino.down();
            } else {
                // Lock the current piece in the field
                board.lock(tetromino);

                for(int py=0;py < 4;py++)
                {
                    if(tetromino.posy() + py < board.height() - 1)
                    {
                        bool bLine = true;
                        for(int px = 1;px < board.width()-1;px++)
                        {
                            bLine &= board(tetromino.posy() + py, px) != 0;
                        }

                        if(bLine)
                        {
                            for(int px = 1;px < board.width() - 1;px++)
                                board(tetromino.posy() + py, px) = 8;

                            vLines.push_back(tetromino.posy() + py);
                        }
                    }
                }

                // choose the next piece
                tetromino.next(board);

                // if piece does not fit end game
                bGameOver = !tetromino.fit(board);
            }
            nSpeedCounter = 0;
        }
        // RENDER OUTPUT

        draw(board);

        draw_piece(tetromino);

        if(!vLines.empty())
        {
            draw(board);
            std::this_thread::sleep_for(400ms);

            for(auto &v : vLines)
            {
                for(int px = 1;px < board.width() - 1;px++)
                {
                    for(int py = v;py > 0;py--)
                    {
                        board(py, px) = board(py - 1, px);
                    }
                    board(0, px) = 0;
                }
            }
            vLines.clear();
        }

        refresh();
    }

    endwin();
    return 0;
}

void draw(Board board)
{
    for (int x = 0; x < board.width(); x++)
    {
        for (int y = 0; y < board.height(); y++)
        {
            mvaddch(y + 2, x + 2, L" ABCDEFG=#"[board(y, x)]);
        }
    }
}

void draw_piece(Tetromino tetromino)
{
// Draw Current Piece
        for (int px = 0; px < 4; px++)
        {
            for (int py = 0; py < 4; py++)
            {
                if (tetromino.current()[Rotate(px, py, tetromino.rotation())] == L'X')
                    mvaddch(py + 2 + tetromino.posy(), px + 2 + tetromino.posx(), tetromino.index() + 65);
            }
        }
}
