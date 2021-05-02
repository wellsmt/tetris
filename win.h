#ifndef _WIN_H
#define _WIN_H

#include <ncurses.h>

typedef struct _win_border_struct
{
    chtype ls, rs, ts, bs,
        tl, tr, bl, br;
} WIN_BORDER;
typedef struct _WIN_struct
{

    int startx, starty;
    int height, width;
    WIN_BORDER border;
} WIN;

#endif
