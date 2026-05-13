#include "prc/prc_context.h"
#include "tui.h"

#include <assert.h>
#include <limits.h>

// _Static_assert(CHAR_BIT <= 8, "Incompatible device.");

int main(void)
{
	eputs("w");

	struct tui_info info = {0};
	int ret = 0;

	if (prc_get_context(&info.ctx) != FN_SUCCESS)
	{
		ret = -1;
		goto kill_em;
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