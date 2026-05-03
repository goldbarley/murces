#include "prc/prc_event.h"
#include "prc/prc_winpool.h"

#include <signal.h>
#include <string.h>

static uint8_t _prc_sigwinch = FALSE;

static void _eg_signal_handler(int signal)
{
    (void) signal;
    _prc_sigwinch = TRUE;
}

fnresult_t eg_text_box(void)
{
struct prc_window *window = prc_get_freeaddr();
    struct prc_context ctx;

    prc_get_context(&ctx);
    signal(SIGWINCH, _eg_signal_handler);
    noecho();
    raw();

    if (prc_create_window(window, &ctx) != FN_SUCCESS)
    {
        printf("Error: Failed to create window.");
        return FN_FAILURE;
    }
    prc_window_title(window, 0, 0, &ctx);

    if (memset(&window->wbord, 0, sizeof(struct prc_border_desc)) == NULL)
        return FN_FAILURE;
    
    window->wpad.left = 10;
    window->wpad.right = 10;
    window->wpad.top = 5;
    window->wpad.bottom = 5;

    window->walign = PRC_ALIGN_NONE;

    refresh();

    prc_init_evt_buffer();
    // struct prc_generic_event levt = {0};
    struct prc_generic_event fevt = {0};
    
    fnresult_t res = FN_SUCCESS;
    uint16_t wy = 1;
    uint16_t wx = 1;

    if (nodelay(window->win, TRUE) != OK)
        return FN_FAILURE;

    while (TRUE)
    {
        if (_prc_sigwinch) {
            _prc_sigwinch = FALSE;
            
            resizeterm(0, 0); 
            prc_resize_context(&ctx);
            prc_resize_window(window, &ctx);
            
            prc_window_title(window, 0, 0, &ctx);
            
            if (wy >= window->height - 1) wy = window->height - 2;
            if (wx >= window->width - 1) wx = window->width - 2;

            clearok(stdscr, TRUE);
            refresh();
            wrefresh(window->win);
        }

        if (prc_poll_for_event(window) != FN_SUCCESS)
        {
            res = FN_FAILURE;
            break;
        }

        while (prc_get_first_event(&fevt) == FN_SUCCESS)
        {
            if (fevt.detail == 'q' || fevt.detail == 'Q')
            {
                res = FN_SUCCESS;
                goto cleanup;
            }

            if (fevt.detail == '\n' || fevt.detail == '\r' || fevt.detail == 10 || fevt.detail == 13)
            {
                wx = 1;
                wy++;
            }
            else 
            {
                if (wx >= window->width - 1)
                {
                    wx = 1;
                    wy++;
                }

                if (wy >= window->height - 1) 
                    break;

                mvwaddch(window->win, wy, wx++, fevt.detail);
            }

            prc_use_event();
        }

        wrefresh(window->win);
        wtimeout(window->win, 10);
    }

    cleanup:
        prc_destroy_window(window, &ctx);
        prc_destroy_context(&ctx);
        prc_kill_mother();

    return res;
}