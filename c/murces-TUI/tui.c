#include <ncurses.h>
#include <prc/prc_window.h>
#include <prc/prc_winpool.h>

#include "tui.h"

#include <stdint.h>
#include <string.h>

int _mm_init_windows(
	struct prc_window *desc_win, struct prc_window *content_win,
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

	content_win->parent = desc_win;
	if (memset(&content_win->wbord, 0, sizeof(struct prc_border_desc)) == NULL)
	{
		eputs("Error: Failed to initialize border.\n");
		return -1;
	}

	content_win->wpad.left = 2;
	content_win->wpad.right = 2;
	content_win->wpad.top = 5;
	content_win->wpad.bottom = 1;
	content_win->wpad.yes = TRUE;

	content_win->walign = PRC_ALIGN_NONE;

	ret = prc_create_window(desc_win, ctx);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to create window.\n");
		return ret;
	}

	ret = prc_create_derwin(content_win, content_win->parent, ctx);
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

	return 0;
}

int _mmdw_insert_text(struct prc_window *win,
	char *s, int left, int right, int top)
{
	if (s == NULL)
		return -1;

	unsigned long ogsize = strlen(s);

	long bufsize = win->width - right - left;
	if(right - left < 0)
		return -1;

	unsigned long curptr = 0;
	
	for (int i = 0; curptr < ogsize; ++i)
	{
		if (mvwaddnstr(win->win, top + i, left, s + curptr, bufsize) == ERR)
			return -1;
		curptr += bufsize;
	}

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
		goto cleanup;
	}

	if (noecho() != OK)
	{
		ret = -1;
		goto cleanup;
	}

	ret = _mm_init_windows(desc_win, content_win, ctx);
	if (ret == -1)
		goto cleanup;

	refresh();

	/* prefix: 'dw' - inside 'desc_win' */
	char *dw_desc = "MurCes is a Minecraft server configuration"
	" tool. Press 'Q' to quit. All navigations are bound to the ARROW KEYS.";

	_mmdw_insert_text(desc_win,
		dw_desc, content_win->wpad.left, content_win->wpad.right, 2);

	wnoutrefresh(content_win->win);
	wnoutrefresh(desc_win->win);

	doupdate();

	chtype c = 0;
	while((c = wgetch(content_win->win)))
	{
		if (c == 'q')
			break;
		timeout(10);
	}

	cleanup:
		prc_destroy_window(content_win, ctx);
		prc_destroy_window(desc_win, ctx);

	return ret;
}