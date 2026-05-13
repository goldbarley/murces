#ifndef MTUI_TUI_H
#define MTUI_TUI_H

#include <prc/prc_context.h>

#define MAIN_MENU_DESC_WNAME "MurCes v1.0.0"

#ifndef NDEBUG
#define eputs(s) \
	do \
	{ \
		fputs(s, stderr); \
	} while (0)
#define eprintf(...) \
	do \
	{ \
		fprintf(stderr, __VA_ARGS__); \
	} while (0)
#else
#define eputs(s)
#define eprintf(...)
#endif /* NDEBUG */

struct tui_info
{
	struct prc_context ctx;
};

int main_menu(struct tui_info *info);

#endif /* MTUI_TUI_H */