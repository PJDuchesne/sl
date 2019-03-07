/*========================================
 *    sl.c: SL version 5.03
 *        Copyright 1993,1998,2014-2015
 *                  Toyoda Masashi
 *                  (mtoyoda@acm.org)
 *        This version modified on 2019/03/06 by Paul Duchesne
 *========================================
 */

#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "sl.h"

// Prototypes
int my_mvaddstr(int y, int x, char *str);
int add_neo(int x);

int main(int argc, char *argv[])
{
    initscr();
    signal(SIGINT, SIG_IGN);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    int x;

    for (x = COLS - 1; ; --x) {
        if (add_neo(x) == ERR) break;
        getch();
        refresh();
        usleep(40000);
    }

    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();

    return 0;
}

/* Implementation */

int my_mvaddstr(int y, int x, char *str)
{
    for ( ; x < 0; ++x, ++str)
        if (*str == '\0') return ERR;
    for ( ; *str != '\0'; ++str, ++x)
        if (mvaddch(y, x, *str) == ERR) return ERR;
    return OK;
}

int add_neo(int x)
{
    static char *neo1x[NEO1XHEIGHT + 1]
        = {NEO1XSTR1, NEO1XSTR2, NEO1XSTR3, NEO1XSTR4, NEO1XSTR5, NEO1XSTR6, NEO1XSTR7, NEO1XSTR8,
            NEO1XSTR9, NEO1XSTR10, NEO1XSTR11, NEO1XSTR12, NEO1XSTR13, NEO1XSTR14, NEO1XSTR15,
            NEO1XSTR16, NEO1XSTR17, NEO1XSTR18, NEO1XDEL};

    static char *neo1xtrail = NEO1XTRAIL;

    int y, i = 0;

    if (x < -NEO1XLENGTH) return ERR; // Donezo!

    y = LINES / 2 - 7; // Draw somewhere near the middle of the screen

    // Sketch stuff
    for (i = 0; i <= NEO1XHEIGHT - 1; ++i) {
        my_mvaddstr(y + i, x, neo1x[i]);
    }
    my_mvaddstr(y + NEO1XHEIGHT - 1, x + 38, neo1xtrail);

    return OK; // Not Donezo!
}
