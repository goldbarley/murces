#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
int main() {
  initscr();
  const int height = LINES;
  const int width = COLS;

  if (has_colors() == FALSE || can_change_color() == FALSE) {
    endwin();
    printf("Error: Terminal does not support custom color definitions.\n");
    return 1;
  }

  start_color();
  cbreak();
  noecho();

  init_color(COLOR_YELLOW, 588, 294, 0);
  init_pair(1, COLOR_GREEN, COLOR_YELLOW);

  WINDOW *welcome = newwin(10, 30, height / 2 - 5, width / 2 - 15);

  wbkgd(welcome, COLOR_PAIR(1));
  wclear(welcome);

  box(welcome, 0, 0);
  mvwprintw(welcome, 1, 1,
            "  Welcome to MurCes\n    Please Press \n   Enter To Continue\n");

  refresh();
  wrefresh(welcome);
  getch();
  werase(welcome);

  WINDOW *warning = newwin(10, 30, height / 2 - 5, width / 2 - 15);
  init_pair(2, COLOR_RED, COLOR_BLACK);

  wbkgd(warning, COLOR_PAIR(2));
  box(warning, 1, 1);
  mvwprintw(warning, 1, 1, "DO NOT RESIZE THE WINDOW\n DURRING OPERATION");
  wrefresh(warning);
  usleep(5000000);
  delwin(warning);
  box(welcome, 0, 0);
  mvwprintw(welcome, 1, 1, "TODO MENU");
  refresh();
  wrefresh(welcome);
  getch();
  delwin(welcome);
  endwin();

  return 0;
}
