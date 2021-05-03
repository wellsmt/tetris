#include <chrono>
#include <iostream>
#include <ncurses.h>
#include <thread>
#include <vector>
#include "time.h"
#include "board.h"
#include "rotate.h"
#include "tetromino.h"
#include "does_piece_fit.h"

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR)
    {
        ungetch(ch);
        return 1;
    }
    else
    {
        return 0;
    }
}

void draw(Board board);
void draw_piece(const int piece, const int rotation, const int x, const int y);

using namespace std::literals::chrono_literals;

int main()
{
    srand (time(NULL));

    initscr(); /* initialize the curses library */
    start_color();
    cbreak(); /* take input chars one at a time, no wait for \n */
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
    keypad(stdscr, TRUE); /* enable keyboard mapping */

    Tetromino tetromino;
    Board board(12, 18);
    board.init();

    bool bGameOver = false;
    bool bKey[4];
    int nCurrentPiece = rand() % 7;
    int nCurrentRotation = 0;
    int nCurrentX = board.width() / 2;
    int nCurrentY = 0;
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
        if (kbhit())
        {
            ch = getch();
        }
        else
        {
            ch = 0;
        }
        bKey[0] = (ch == 261); // R
        bKey[1] = (ch == 260); // L
        bKey[2] = (ch == 258); // D
        bKey[3] = (ch == 122); // z
        // GAME LOGIC
        nCurrentX += (bKey[0] && DoesPieceFit(board, nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
        nCurrentX -= (bKey[1] && DoesPieceFit(board, nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
        nCurrentY += (bKey[2] && DoesPieceFit(board, nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;
        if (bKey[3])
        {
            nCurrentRotation += (!bRotateHold && bKey[3] && DoesPieceFit(board, nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
            bRotateHold = true;
        }
        else
        {
            bRotateHold = false;
        }

        if(bForceDown)
        {
            if(DoesPieceFit(board, nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
            {
                nCurrentY++;
            } else {
                // Lock the current piece in the field
                board.lock(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);

                for(int py=0;py < 4;py++)
                {
                    if(nCurrentY + py < board.height() - 1)
                    {
                        bool bLine = true;
                        for(int px = 1;px < board.width()-1;px++)
                        {
                            bLine &= (board.field()[(nCurrentY + py) * board.width() + px]) != 0;
                        }

                        if(bLine)
                        {
                            for(int px = 1;px < board.width() - 1;px++)
                                board.field()[(nCurrentY + py) * board.width() + px] = 8;

                            vLines.push_back(nCurrentY + py);
                        }
                    }
                }

                // have we created any full horizontal lines

                // choose the next piece
                nCurrentX = board.width() / 2;
                nCurrentY = 0;
                nCurrentRotation = 0;
                nCurrentPiece = rand() % 7;

                // if piece does not fit end game
                bGameOver = !DoesPieceFit(board, nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
            }
            nSpeedCounter = 0;
        }
        // RENDER OUTPUT

        draw(board);

        draw_piece(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);

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
                        board.field()[py * board.width() + px] = board.field()[(py - 1) * board.width() + px];
                    }
                    board.field()[px] = 0;
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
            mvaddch(y + 2, x + 2, L" ABCDEFG=#"[board.field()[y * board.width() + x]]);
        }
    }
}

void draw_piece(const int piece, const int rotation, const int x, const int y)
{
    Tetromino tetromino;
// Draw Current Piece
        for (int px = 0; px < 4; px++)
        {
            for (int py = 0; py < 4; py++)
            {
                if (tetromino.get(piece)[Rotate(px, py, rotation)] == L'X')
                    mvaddch(py + 2 + y, px + 2 + x, piece + 65);
            }
        }
}
