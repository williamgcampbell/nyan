#include "nyan.h"

#include <curses.h>
#include <ncurses.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int draw (int y, int x, char *str) {
  for ( ; x < 0; ++x, ++str) {
    if (*str == '\0')  return ERR;
  }
  for ( ; *str != '\0'; ++str, ++x) {
    if (mvaddch(y, x, *str) == ERR)  return ERR;
  }
  return OK;
}

int fill_rainbox_buffer(int y, int x, char* buffer) {
  int i;
  char possible_chars[2];

  switch (y % 2) {
  case 0:
    possible_chars[0] = '-';
    possible_chars[1] = '_';
    break;
  case 1:
    possible_chars[0] = '_';
    possible_chars[1] = '-';
    break;
  default:
    return ERR;
  }

  for (i = 0; i < x; i++) {
    buffer[i] = possible_chars[i % 2];
  }
  buffer[x] = '\0';
  return OK;
}
int draw_rainbow (int y, int x, int color) {
  int i;
  static char buffer[512];
  if (has_colors() == TRUE) {
    start_color();
    init_pair(color, color, COLOR_BLACK);
    attron(COLOR_PAIR(color));
    fill_rainbox_buffer(y, x, buffer);
    draw(y, 0, buffer);
    attroff(COLOR_PAIR(color));
  } else {
    draw(y, x, buffer);
  }
  return OK;
}

int add_cat (int x) {
  static char *catr[CATPATTERNS][CATHEIGHT + 1] =
	{{CAT1, CAT2, CAT3, FEET1},
	 {CAT1, CAT2, CAT3, FEET2}};

  static int colors[CATHEIGHT] =
    {COLOR_RED, COLOR_BLUE, COLOR_YELLOW, COLOR_GREEN};

  if (x < - CATLENGTH)  return ERR;
  if (x > COLS) return ERR;
  int y = LINES / 2;

  int i, pattern, rpattern;
  for (i = 0; i < CATHEIGHT; ++i) {
    pattern = (CATLENGTH + x) % CATPATTERNS;
    if (x >= 0) {
      draw_rainbow(y + i, x, colors[i]);
    }
    draw(y + i, x, catr[pattern][i]);
  }
  return OK;
}

int main(int argc, char *argv[]) {
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
