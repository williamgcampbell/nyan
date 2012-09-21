#include <curses.h>
#include <ncurses.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "nyan.h"

int draw(int y, int x, char *str)
{
    for ( ; x < 0; ++x, ++str)
	if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++str, ++x)
	if (mvaddch(y, x, *str) == ERR)  return ERR;
    return OK;
}

int draw_rainbow(int y, int x, char *str, int color)
{
    if(has_colors() == TRUE) {
        start_color();
        init_pair(color, color, COLOR_BLACK);
        attron(COLOR_PAIR(color));
        draw(y, x, str);
        attroff(COLOR_PAIR(color));
    } else {
        draw(y, x, str);
    }
    return OK;
}

int add_cat(int x) 
{
    static char *catr[CATPATTERNS][CATHEIGHT + 1] =
	{{CAT1, CAT2, CAT3, FEET1},
	 {CAT1, CAT2, CAT3, FEET2}};

    static char *rainbow[2] =
	{RAINBOW1, RAINBOW2};

    static int colors[CATHEIGHT] =
        {COLOR_RED, COLOR_BLUE, COLOR_YELLOW, COLOR_GREEN};

    if (x < - CATLENGTH)  return ERR;
    if (x > COLS+CATLENGTH) return ERR;
    int y = LINES / 2;

    int i;
    for (i = 0; i < CATHEIGHT; ++i) {
	int pattern = (CATLENGTH + x) % CATPATTERNS;
        int rpattern = (CATLENGTH + x) % RAINBOWPATTERNS;
        draw_rainbow(y + i, x, rainbow[rpattern], colors[i]);
        draw(y + i, RAINBOWLENGTH + x, catr[pattern][i]);
    }
    return OK;
}

int main(int argc, char *argv[])
{
    system("afplay nyan.mp3 &");
    int x;
    initscr();
    curs_set(0);
    signal(SIGINT, SIG_IGN);
    noecho();
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    usleep(4000000);
    for (x = - CATLENGTH ; x <= COLS; ++x) {
	if (add_cat(x) == ERR) break;
	refresh();
	usleep(100000);
    }

    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
    system("killall afplay");
}
