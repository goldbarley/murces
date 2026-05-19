#include "tui.h"
#include <../bridge/communciate.h>
#include <../bridge/router.h>
#include <assert.h>
#include <limits.h>
#include <prc/prc_context.h>
#include <pthread.h>
#include <stdio.h>

_Static_assert(CHAR_BIT <= 8, "Incompatible device.");
int threadStarter(void);
pthread_t router;

int main(int argc, char *argv[]) {

  if (argc > 2) {
    switch (argv[1][0]) {
    case 'k':
      if (argc == 3)
        threadStarter();
      break;
    case 's':
      if (argc == 8)
        threadStarter();
      break;
    case 'm':
      if (argc == 9)
        threadStarter();
      break;
    default:
      printf("Messy Parameters, ignoring");
    }
  }

  struct tui_info info = {0};
  int ret = 0;

  if (prc_get_context(&info.ctx) != FN_SUCCESS) {
    ret = -1;
    goto kill_em;
  }

  if (info.ctx.term_has_color) {
    start_color();

    init_color(MC_COLOR_DARK_BLUE, 0, 0, 666);
    init_color(MC_COLOR_LIGHT_CYAN, 329, 992, 996);
    init_color(MC_COLOR_LIGHT_GREY, 666, 666, 666);
    init_color(MC_COLOR_BLACK_BROWN, 250, 120, 40);
    init_color(MC_COLOR_VIOLET_BLUE, 372, 372, 956);
    init_color(MC_COLOR_LITTLE_BROWN_RED, 666, 250, 80);
    init_color(MC_COLOR_DARK_BLUE, 0, 0, 666);
    init_color(MC_COLOR_LIGHT_CYAN, 329, 992, 996);
    init_color(MC_COLOR_LIGHT_GREY, 666, 666, 666);
    init_color(MC_COLOR_BLACK_BROWN, 86, 86, 86);
    init_color(MC_COLOR_VIOLET_BLUE, 372, 372, 956);
    init_color(MC_COLOR_LITTLE_BROWN_RED, 666, 0, 0);

    init_pair(CPID_STDSCR, MC_COLOR_LIGHT_CYAN, MC_COLOR_DARK_BLUE);
    init_pair(CPID_MM_DESC, MC_COLOR_BLACK_BROWN, MC_COLOR_LIGHT_GREY);
    init_pair(CPID_MM_CONTENT, MC_COLOR_BLACK_BROWN, MC_COLOR_LIGHT_GREY);

    // bkgd(COLOR_PAIR(CPID_STDSCR));
  }

  if (main_menu(&info) != 0) {
    ret = -1;
    goto kill_em;
  }

  return ret;
kill_em:
  prc_destroy_context(&info.ctx);
  prc_kill_mother();

  return ret;
}

int threadStarter(void) {
  void *IOP = init_orchestrator(1);

  controlRouter(1);

  if (pthread_create(&router, NULL, initRouter, IOP) != 0)
    return -1;
  return 0;
}
