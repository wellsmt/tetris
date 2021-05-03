#include "rotate.h"
#include "board.h"
#include "tetromino.h"

bool DoesPieceFit(Board board, const int nTetromino, const int nRotation, const int nPosX, const int nPosY)
{
    Tetromino tetromino;
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            // Get index
            int pi = Rotate(px, py, nRotation);
            // Get index into field
            int fi = (nPosY + py) * board.width() + (nPosX + px);

            if (nPosX + px >= 0 && nPosX + px <= board.width())
            {
                if (nPosY + py >= 0 && nPosY + py <= board.height())
                {
                    if (tetromino.get(nTetromino)[pi] == L'X' && board.field()[fi] != 0)
                        return false;
                }
            }
        }
    }
    return true;
}