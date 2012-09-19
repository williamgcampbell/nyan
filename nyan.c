#include <curses.h>
#include <ncurses.h>
#include <signal.h>
#include <unistd.h>
#include "nyan.h"

int my_mvaddstr(int y, int x, char *str)
{
    for ( ; x < 0; ++x, ++str)
	if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++str, ++x)
	if (mvaddch(y, x, *str) == ERR)  return ERR;
    return OK;
}

int main(int argc, char *argv[])
{
    int x;
    initscr();
    curs_set(0);
    signal(SIGINT, SIG_IGN);
    noecho();
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    for (x = 0; x <= COLS; ++x) {
	if (add_cat(x) == ERR) break;
	refresh();
	usleep(60000);
    }

    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
}

int add_cat(int x) 
{
    static char *catr[CATPATTERNS][CATHEIGHT + 1] =
	{{CATR1C1, CATR2C1, CATR3C1, CATR4C1, CATDEL},
	 {CATR1C2, CATR2C2, CATR3C2, CATR4C2, CATDEL}};

    if (x < - CATLENGTH)  return ERR;
    if (x > COLS+CATLENGTH) return ERR;
    int y = LINES / 2;

    for (int i = 0; i <= CATHEIGHT; ++i) {
	int pattern = (CATLENGTH + x) % CATPATTERNS;
	my_mvaddstr(y + i, x, catr[pattern][i]);
    }
    return OK;
}
