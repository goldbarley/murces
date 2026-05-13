#include <prc/prc_window.h>
#include <prc/prc_winpool.h>

#include "tui.h"

#include <stdint.h>
#include <string.h>

static struct menu_items _menu_items0 = {
	.items = {
		/* Start/Stop server*/
		'S' | A_UNDERLINE, 't', 'a', 'r', 't', '/',
		'S' | A_UNDERLINE, 't', 'o', 'p',
		' ', 's', 'e', 'r', 'v', 'e', 'r',
		0,
		/* Configure server */
		'C' | A_UNDERLINE, 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'e',
		' ', 's', 'e', 'r', 'v', 'e', 'r',
		0,
		/* Install server */
		'I' | A_UNDERLINE, 'n', 's', 't', 'a', 'l', 'l',
		' ', 's', 'e', 'r', 'v', 'e', 'r',
		0,
		/* Migrate player */
		'M' | A_UNDERLINE, 'i', 'g', 'r', 'a', 't', 'e',
		' ', 'p', 'l', 'a', 'y', 'e', 'r',
		0,
		/* Create backup */
		'C', 'r', 'e', 'a', 't', 'e',
		' ', 'b' | A_UNDERLINE, 'a', 'c', 'k', 'u', 'p',
		0,
		/* Browse mods */
		'B', 'r', 'o', 'w' | A_UNDERLINE, 's', 'e',
		' ', 'm', 'o', 'd', 's',
		0,
		/* Delete mods */
		'D' | A_UNDERLINE, 'e', 'l', 'e', 't', 'e',
		' ', 'm', 'o', 'd', 's',
		0
	},
	.strterms = {17, 34, 49, 64, 78, 90, 102},
	.nitems = 7,
	.selected = 0
};

int _mm_init_windows(
	struct prc_window *desc_win, struct prc_window *content_win,
	struct prc_window *log_win,
	struct prc_context *ctx)
{
	int ret = 0;

	if (memset(&desc_win->wbord, 0, sizeof(struct prc_border_desc)) == NULL)
	{
		eputs("Error: Failed to initialize window border.\n");
		return -1;
	}

	desc_win->wpad.left = 5;
	desc_win->wpad.right = 5;
	desc_win->wpad.top = 2;
	desc_win->wpad.bottom = 1;
	desc_win->wpad.yes = TRUE;

	desc_win->walign = PRC_ALIGN_NONE;

	desc_win->title = MAIN_MENU_DESC_WNAME;
	desc_win->talign = PRC_ALIGN_TOP;

	ret = prc_create_window(desc_win, ctx);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to create window.\n");
		return ret;
	}

	content_win->parent = desc_win;
	if (memset(&content_win->wbord, 0, sizeof(struct prc_border_desc)) == NULL)
	{
		eputs("Error: Failed to initialize border.\n");
		return -1;
	}

	content_win->wpad.left = 2;
	content_win->wpad.right = 60;
	content_win->wpad.top = 5;
	content_win->wpad.bottom = 1;
	content_win->wpad.yes = TRUE;

	content_win->walign = PRC_ALIGN_NONE;

	ret = prc_create_derwin(content_win, content_win->parent, ctx);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to create derived window.\n");
		return ret;
	}

	log_win->parent = desc_win;
	if (memset(&log_win->wbord, 0, sizeof(struct prc_border_desc)) == NULL)
	{
		eputs("Error: Failed to initialize border.\n");
		return -1;
	}
	log_win->wpad.left = content_win->wpad.left + content_win->width;
	log_win->wpad.right = 2;
	log_win->wpad.top = 5;
	log_win->wpad.bottom = 1;
	log_win->wpad.yes = TRUE;

	ret = prc_create_derwin(log_win, log_win->parent, ctx);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to create derived window.\n");
		return ret;
	}

	ret = prc_draw_window_border(desc_win);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to draw window border.\n");
		return ret;
	}

	ret = prc_window_title(desc_win, 0, 0, ctx);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to write window title.\n");
		return ret;
	}

	ret = prc_draw_window_border(content_win);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to draw window border.\n");
		return ret;
	}

	ret = prc_draw_window_border(log_win);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to draw window border.\n");
		return ret;
	}

	return 0;
}

unsigned int _mm_get_menu_idx_21(unsigned int i,
	unsigned int j)
{
	return i * MAX_MENU_ITEM_COUNT + j;
}

int _mm_print_menu_item(struct prc_window *win, unsigned int y,
	unsigned int x, struct menu_items *items,
	unsigned int n, int idx)
{
	if (win == NULL || items == NULL || idx < 0)
		return -1;
	if (!idx)
		return mvwaddchnstr(win->win, y, x,
			items->items, n);

	return mvwaddchnstr(win->win, y, x,
		items->items + items->strterms[idx - 1] + 1, n);
}

int _mm_insert_text(struct prc_window *win,
	char *s, int left, int right, int top)
{
	if (win == NULL || s == NULL)
		return -1;

	unsigned int ogsize = strlen(s);

	int bufsize = win->width - right - left;
	if(bufsize < 0)
		return -1;
	else if ((unsigned int) bufsize >= ogsize)
	{
		if (mvwaddstr(win->win, top, left, s) == ERR)
			return -1;
		return 0;
	}

	unsigned int curptr = 0;
	for (int i = 0; curptr < ogsize; ++i)
	{
		mvwaddnstr(win->win, top + i, left, s + curptr, bufsize);
		curptr += bufsize;
	}

	return 0;
}

int _mm_insert_menu_text(struct prc_window *win,
	struct menu_items *items, 
	int left, int right, int top)
{
	if (win == NULL || items == NULL)
		return -1;

	for (unsigned int idx = 0, y = 0; idx < items->nitems; ++idx, y += 2)
	{
		unsigned int ogsize = 0;
		if (!idx)
			ogsize = items->strterms[idx];
		else
			ogsize = items->strterms[idx] - items->strterms[idx - 1] - 1;

		int bufsize = win->width - right - left;
		if(bufsize < 0)
			return -1;
		else if ((unsigned int) bufsize >= ogsize)
		{
			eputs("CP\n");
			_mm_print_menu_item(win, top + y, left, items, ogsize, idx);
			continue;
		}

		unsigned int curptr = 0;
		if (!idx)
			curptr = 0;
		else
			curptr = items->strterms[idx - 1] + 1;
		
		for (int i = 0; curptr < ogsize; ++i)
		{
			_mm_print_menu_item(win, top + i, left,
				items + curptr, bufsize, idx);
			curptr += bufsize;
		}
	}

	return 0;
}

int _mm_restore_text0(struct prc_window *desc_win,
	struct prc_window *content_win)
{
	char *dw_desc = "MurCes is a Minecraft server configuration"
	" tool. Press <Q> to quit. All navigations are bound to <LEFT>, <RIGHT>,"
	" <UP>, and <DOWN> keys.";

	if (_mm_insert_text(desc_win,
		dw_desc, 4, 4, 2) != 0)
		return -1;

	if (_mm_insert_menu_text(content_win, &_menu_items0,
		5, 5, 2) != 0)
		return -1;
	eputs("CP1\n");

	return 0;
}

int main_menu(struct tui_info *info)
{
	struct prc_context *ctx = &info->ctx;
	int ret = 0;

	struct prc_window *desc_win = prc_get_freeaddr();
	if (desc_win == NULL)
	{
		eputs("Error: No memory in window pool.\n");
		return -1;
	}

	struct prc_window *content_win = prc_get_freeaddr();
	if (content_win == NULL)
	{
		eputs("Error: No memory in window pool.\n");
		ret = -1;
	}

	struct prc_window *log_win = prc_get_freeaddr();
	if (log_win == NULL)
	{
		eputs("Error: No memory in window pool.\n");
		ret = -1;
		goto cleanup;
	}
	else if (content_win == NULL)
		goto cleanup;

	if (noecho() != OK)
	{
		ret = -1;
		goto cleanup;
	}

	ret = _mm_init_windows(desc_win, content_win, log_win, ctx);
	if (ret == -1)
		goto cleanup;

	_mm_insert_text(log_win,
		"VERY VERY BIG BIG LONG LONG TEXT TO TEST THE HOW LONG A MESSAGE IT CAN WRAP! I AM NOT GOING TO ADD LOGIC TO CHECK FOR WORDS AND SPACES TO WRAP WORDS PROPERLY SINCE IT IS TO GODDAMN COMPLICATED!",
		4, 4, 2);

	wnoutrefresh(stdscr);

	_mm_restore_text0(desc_win, content_win);

	wnoutrefresh(log_win->win);
	wnoutrefresh(content_win->win);
	wnoutrefresh(desc_win->win);

	doupdate();

	chtype c = 0;
	while((c = wgetch(content_win->win)))
	{
		if (c == 'q')
			break;
		if (c == KEY_RESIZE)
		{
			prc_resize_context(ctx);

            prc_resize_window(desc_win, ctx);
			prc_resize_window(content_win, ctx);
			prc_resize_window(log_win, ctx);

            clearok(stdscr, TRUE);

			_mm_restore_text0(desc_win, content_win);
            
            wnoutrefresh(stdscr);

			wnoutrefresh(log_win->win);
			wnoutrefresh(content_win->win);
			wnoutrefresh(desc_win->win);

			doupdate();
		}

		timeout(10);
	}

	cleanup:
		prc_destroy_window(log_win, ctx);
		prc_destroy_window(content_win, ctx);
		prc_destroy_window(desc_win, ctx);

	return ret;
}