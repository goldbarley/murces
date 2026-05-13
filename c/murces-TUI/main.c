#include <prc/prc_context.h>

#include "tui.h"

#include <assert.h>
#include <limits.h>

_Static_assert(CHAR_BIT <= 8, "Incompatible device.");

int main(void)
{
	struct tui_info info = {0};
	int ret = 0;

	if (prc_get_context(&info.ctx) != FN_SUCCESS)
	{
		ret = -1;
		goto kill_em;
	}

	if (info.ctx.term_has_color)
	{
		start_color();

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
	
	if (main_menu(&info) != 0)
	{
		ret = -1;
		goto kill_em;
	}

	kill_em:
		prc_destroy_context(&info.ctx);
		prc_kill_mother();

	return ret;
}