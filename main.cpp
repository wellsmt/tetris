#include <chrono>
#include <iostream>
#include <ncurses.h>
#include <thread>
#include "win.h"
#include "create_box.h"

std::wstring tetromino[7];

int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;

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

int Rotate(int px, int py, int r)
{
    switch (r % 4)
    {
    case 0:
        return py * 4 + px; // 0
    case 1:
        return 12 + py - (px * 4); // 90
    case 2:
        return 15 - (py * 4) - px; // 180
    case 3:
        return 3 - py + (px * 4); // 270
    }
    return 0;
}

bool DoesPieceFit(const int nTetromino, const int nRotation, const int nPosX, const int nPosY)
{
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            // Get index
            int pi = Rotate(px, py, nRotation);
            // Get index into field
            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            if (nPosX + px >= 0 && nPosX + px <= nFieldWidth)
            {
                if (nPosY + py >= 0 && nPosY + py <= nFieldHeight)
                {
                    if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
                        return false;
                }
            }
        }
    }
    return true;
}
void createAssests(std::wstring tetromino[7]);
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void DrawField(unsigned char *pField);

using namespace std::literals::chrono_literals;

int main()
{
    createAssests(tetromino);

    pField = new unsigned char[nFieldWidth * nFieldHeight];
    for (int x = 0; x < nFieldWidth; x++)
    {
        for (int y = 0; y < nFieldHeight; y++)
        {
            pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
        }
    }

    initscr(); /* initialize the curses library */
    start_color();
    cbreak(); /* take input chars one at a time, no wait for \n */
    noecho();
    nodelay(stdscr, TRUE);

    keypad(stdscr, TRUE); /* enable keyboard mapping */
    int startx = (LINES - nFieldHeight) / 2;
    int starty = (COLS - nFieldWidth) / 2;

    bool bGameOver = false;
    bool bKey[4];
    int nCurrentPiece = 0;
    int nCurrentRotation = 0;
    int nCurrentX = nFieldWidth / 2;
    int nCurrentY = 0;
    int ch = 0;
    bool bRotateHold = false;

    while (!bGameOver)
    {
        // GAME TIMING
        std::this_thread::sleep_for(50ms);
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
        nCurrentX += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
        nCurrentX -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
        nCurrentY += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;
        if (bKey[3])
        {
            nCurrentRotation += (!bRotateHold && bKey[3] && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
            bRotateHold = true;
        }
        else
        {
            bRotateHold = false;
        }
        // RENDER OUTPUT

        DrawField(pField);

        // Draw Current Piece
        for (int px = 0; px < 4; px++)
        {
            for (int py = 0; py < 4; py++)
            {
                if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
                    mvaddch(py + 2 + nCurrentY, px + 2 + nCurrentX, nCurrentPiece + 65);
            }
        }

        refresh();
    }

    endwin();
    return 0;
}

void DrawField(unsigned char *pField)
{
    for (int x = 0; x < nFieldWidth; x++)
    {
        for (int y = 0; y < nFieldHeight; y++)
        {
            mvaddch(y + 2, x + 2, L" ABCDEFG=#"[pField[y * nFieldWidth + x]]);
        }
    }
}

void createAssests(std::wstring tetromino[7])
{
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");

    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L"..X.");
    tetromino[4].append(L"....");

    tetromino[5].append(L"....");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");

    tetromino[6].append(L"....");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L".X..");
    tetromino[6].append(L".X..");
};