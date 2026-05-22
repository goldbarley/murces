#include <prc/prc_winpool.h>
#include <prc/prc_window.h>

#include "tui.h"

#include <string.h>

static struct tui_layout3__
{
	struct prc_context *ctx;
	struct prc_window *modloader_win;
	struct prc_window *version_win;
	unsigned char init;
} tui_layout3__ = {0};

int m3_init_windows(struct tui_info *info)
{
	if (tui_layout3__.init)
		return 0;

	struct prc_context *ctx = &info->ctx;
	int ret = 0;

	struct prc_window *modloader_win = tui_layout3__.modloader_win;
	struct prc_window *version_win = tui_layout3__.version_win;

	if (memset(&modloader_win->wbord, 0, sizeof(struct prc_border_desc))
		== NULL)
	{
		eputs("Error: Failed to initialize window border.");
		return -1;
	}

	unsigned int width_occup = mtstdlogwin->width + mtstdlogwin->wpad.right;
	// unsigned int width_remain = mtstdbigwin->width - width_occup;

	modloader_win->wpad.left = mtstdlogwin->wpad.right;
	modloader_win->wpad.right = mtstdlogwin->wpad.left;
	modloader_win->wpad.top = mtstdlogwin->wpad.top;
	modloader_win->wpad.bottom = mtstdlogwin->wpad.bottom;
	modloader_win->wpad.yes = TRUE;

	modloader_win->walign = PRC_ALIGN_NONE;

	ret = prc_create_derwin(modloader_win, mtstdbigwin, ctx);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to create derived window.");
		return ret;
	}

	if (memset(&version_win->wbord, 0, sizeof(struct prc_border_desc))
		== NULL)
	{
		eputs("Error: Failed to initialize window border.");
		return -1;
	}	

	version_win->wpad.left = width_occup;
	version_win->wpad.right = width_occup;
	version_win->wpad.top = mtstdlogwin->wpad.top;
	version_win->wpad.bottom = mtstdlogwin->wpad.bottom;
	version_win->wpad.yes = TRUE;

	ret = prc_create_derwin(version_win, mtstdbigwin, ctx);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to create derived window.");
		return ret;
	}

	tui_layout3__.init = TRUE;

	return ret;
}

void m3_destroy_layout3(void)
{
	if (!tui_layout3__.init)
		return;
	
	prc_destroy_window(tui_layout3__.modloader_win, tui_layout3__.ctx);	
	prc_destroy_window(tui_layout3__.version_win, tui_layout3__.ctx);
}

int m3_draw_layout3(void)
{
	struct prc_context *ctx = tui_layout3__.ctx;
	int ret = 0;

	struct prc_window *modloader_win = tui_layout3__.modloader_win;
	struct prc_window *version_win = tui_layout3__.version_win;

	ret = prc_draw_window_border(mtstdbigwin);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to draw window border.");
		return ret;
	}
	
	mtstdbigwin->talign = PRC_ALIGN_TOP;
	ret = prc_window_title(mtstdbigwin, 0, 0, ctx);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to write window title.");
		return ret;
	}

	ret = prc_draw_window_border(modloader_win);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to draw window border.");
		return ret;
	}

	ret = prc_draw_window_border(version_win);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to draw window border.");
		return ret;
	}

	ret = prc_draw_window_border(mtstdlogwin);
	if (ret != FN_SUCCESS)
	{
		eputs("Error: Failed to draw window border.");
		return ret;
	}

	return ret;
}

int menu3(struct tui_info *info)
{
	if (!tui_layout3__.init)
	{
		struct prc_context *ctx = &info->ctx;
		int ret = 0;

		struct prc_window *modloader_win = prc_get_freeaddr();
		if (modloader_win == NULL)
		{
			eputs("Error: No memory in window pool.");
			return -1;
		}

		struct prc_window *version_win = prc_get_freeaddr();
		if (version_win == NULL)
		{
			eputs("Error: No memory in window pool.");
			prc_destroy_window(modloader_win, ctx);
			return -1;
		}
		tui_layout3__.modloader_win = modloader_win;
		tui_layout3__.version_win = version_win;
		tui_layout3__.ctx = &info->ctx;

		ret = m3_init_windows(info);
		if (ret != 0)
		{
			eputs("Failed to initialize layout.");
			return -1;
		}
	}

	if (m3_draw_layout3() != 0)
	{
		eputs("Failed to draw layout.");
		return -1;
	}

	struct prc_window *modloader_win = tui_layout3__.modloader_win;
	struct prc_window *version_win = tui_layout3__.version_win;
	// struct prc_context *ctx = tui_layout3__.ctx;

	wnoutrefresh(mtstdbigwin->win);
	wnoutrefresh(modloader_win->win);
	wnoutrefresh(version_win->win);
	doupdate();

	uint32_t c;
	while((c = getch()))
	{
		if (c == 'q' || c == 'Q')
			return 0;
	}

	return 0;
}