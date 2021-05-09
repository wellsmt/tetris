#include <ncurses.h>

void ncurses_setup()
{
    initscr(); /* initialize the curses library */
    start_color();
    cbreak(); /* take input chars one at a time, no wait for \n */
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);
    keypad(stdscr, TRUE); /* enable keyboard mapping */
}

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR)
    {
        ungetch(ch);
        ch = getch();

        return ch;
    }
    else
    {
        return 0;
    }
}