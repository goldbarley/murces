#ifndef MTUI_TUI_H
#define MTUI_TUI_H

#include <prc/prc_context.h>

#include <stdint.h>

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

#define MAX_MENU_ITEM_COUNT (20)
#define MAX_MENU_ITEM_CHAR_COUNT (256)
#define MAX_STR_MENU_ITEMS (256)

enum cpid
{
	CPID_STDSCR = 1,
	CPID_MM_DESC,
	CPID_MM_CONTENT
};

#define CPID_STDSCR (CPID_STDSCR)
#define CPID_MM_DESC (CPID_MM_DESC)
#define CPID_MM_CONTENT (CPID_MM_CONTENT)

enum mc_colors
{
	MC_COLOR_DARK_BLUE = 8,
	MC_COLOR_LIGHT_CYAN,
	MC_COLOR_LIGHT_GREY,
	MC_COLOR_BLACK_BROWN,
	MC_COLOR_VIOLET_BLUE,
	MC_COLOR_LITTLE_BROWN_RED
};

#define MC_COLOR_DARK_BLUE (MC_COLOR_DARK_BLUE)
#define MC_COLOR_LIGHT_CYAN (MC_COLOR_LIGHT_CYAN)
#define MC_COLOR_LIGHT_GREY (MC_COLOR_LIGHT_GREY)
#define MC_COLOR_BLACK_BROWN (MC_COLOR_BLACK_BROWN)
#define MC_COLOR_VIOLET_BLUE (MC_COLOR_VIOLET_BLUE)
#define MC_COLOR_LITTLE_BROWN_RED (MC_COLOR_LITTLE_BROWN_RED)

struct tui_info
{
	struct prc_context ctx;
};

struct menu_items
{
	chtype items[MAX_MENU_ITEM_CHAR_COUNT * MAX_MENU_ITEM_COUNT];
	unsigned long int strterms[MAX_MENU_ITEM_COUNT];
	unsigned int nitems;
	uint64_t selected;
};

struct str_menu_items
{
	char *items[MAX_STR_MENU_ITEMS];
	unsigned int nitems;
	uint64_t selected[(MAX_STR_MENU_ITEMS + 63) >> 6];
};

int mm_insert_text(struct prc_window *win, short pair,
	char *s, int left, int right, int top);

int main_menu(struct tui_info *info);

#endif /* MTUI_TUI_H */