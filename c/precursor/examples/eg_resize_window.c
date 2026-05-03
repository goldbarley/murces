#include "prc/prc_context.h"
#include "prc/prc_window.h"
#include "prc/prc_event.h"
#include "prc/prc_winpool.h"
#include "utlprc/types.h"

#include <ncurses.h>
#include <signal.h>
#include <string.h>

static uint8_t _prc_sigwinch = FALSE;

static void _eg_signal_handler(int signal)
{
    (void) signal;
    _prc_sigwinch = TRUE;
}

fnresult_t eg_resize_window(void)
{
    fnresult_t res = FN_SUCCESS;

    struct prc_window *window = prc_get_freeaddr();
    struct prc_context ctx;

    prc_get_context(&ctx);
    signal(SIGWINCH, _eg_signal_handler);
    noecho();
    raw();

    window->wpad.left = 10;
    window->wpad.right = 10;
    window->wpad.top = 5;
    window->wpad.bottom = 5;

    window->walign = PRC_ALIGN_NONE;

    window->title = "Example: Resizing windows";
    window->talign = PRC_ALIGN_TOP;

    res = prc_create_window(window, &ctx);
    if (res != FN_SUCCESS)
    {
        fputs("Error: Failed to create window.", stderr);
        return res;
    }

    res = prc_draw_window_border(window);
    if (res != FN_SUCCESS)
        goto cleanup;

    res = prc_window_title(window, 0, 0, &ctx);
    if (res != FN_SUCCESS)
        goto cleanup;

    if (memset(&window->wbord, 0, sizeof(struct prc_border_desc)) == NULL)
    {
        res = FN_FAILURE;
        goto cleanup;
    }

    refresh();
    wrefresh(window->win);

    prc_init_evt_buffer();
    // struct prc_generic_event levt = {0};
    struct prc_generic_event fevt = {0};
    
    uint16_t wy = 1;
    uint16_t wx = 1;

    if (nodelay(window->win, TRUE) != OK)
    {
        res = FN_FAILURE;
        goto cleanup;
    }


    // while (TRUE)
    // {
    //     uint8_t c = wgetch(window->win);
    //     if (c == 'q' || c == 'Q')
    //     {
    //         res = FN_SUCCESS;
    //         goto cleanup;
    //     }
    //     mvwaddch(window->win, wy, wx++, c);
    //     wtimeout(window->win, 10);
    // }

    while (TRUE)
    {
        if (_prc_sigwinch) 
        {
            _prc_sigwinch = FALSE;
            
            prc_resize_context(&ctx);
            prc_resize_window(window, &ctx);
            
            prc_draw_window_border(window);
            prc_window_title(window, 0, 0, &ctx);
            
            if (wy >= window->height - 1) wy = window->height - 2;
            if (wx >= window->width - 1) wx = window->width - 2;

            clearok(stdscr, TRUE);
            refresh();
            wrefresh(window->win);
        }

        res = prc_poll_for_event(ctx.cwin);
        if (res != FN_SUCCESS)
        {
            goto cleanup;
            break;
        }

        while (prc_get_first_event(&fevt) == FN_SUCCESS)
        {
            if (fevt.detail == 'q' || fevt.detail == 'Q')
            {
                prc_use_event();
                res = FN_SUCCESS;
                goto cleanup;
            }

            if (fevt.detail == '\n' || fevt.detail == '\r' ||
                fevt.detail == 10 || fevt.detail == 13)
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

            res = prc_use_event();
            if (res != FN_SUCCESS)
                goto cleanup;
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