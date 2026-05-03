#include <ncurses.h>

#include "prc/prc_window.h"
#include "prc/prc_context.h"
#include "prc/prc_winpool.h"
#include "utlprc/types.h"

#include <string.h>

static inline fnresult_t _prc_get_window_info(
    struct prc_window *     window
)
{
    if (window == NULL)
        return FN_INVALID_ARGUMENT;

    if (window->wpad.yes == FALSE)
    {
        uint32_t res =
            prc_get_walginyx(window->parent, window->height, window->width,
                window->walign, &window->y, &window->x);
        if (res == FN_FAILURE)
            return FN_FAILURE;
    }
    else
    {
        if (prc_get_padded_wdesc(window, window->parent, &window->wpad) != FN_SUCCESS)
            return FN_FAILURE;
    }

    return FN_SUCCESS;
}

fnresult_t prc_draw_window_border(
    struct prc_window *window
)
{
    if (window == NULL)
        return FN_SUCCESS;

    struct prc_border_desc *bord = &window->wbord;

    if (wborder(
        window->win,
        bord->ls, bord->rs,
        bord->ts, bord->bs,
        bord->tl, bord->tr,
        bord->bl, bord->br
    ) != OK)
    {
        delwin(window->win);
        return FN_FAILURE;
    }

    return FN_SUCCESS;
}

fnresult_t prc_create_window(
    struct prc_window *     window,
    struct prc_context *    ctx
)
{
    if (window == NULL || ctx == NULL)
        return FN_INVALID_ARGUMENT;

    window->parent = ctx->cwin;

    if (_prc_get_window_info(window)
        != FN_SUCCESS)  
        return FN_FAILURE;

    window->win = newwin(window->height, window->width, window->y, window->x);
    if (window->win == NULL)
        return FN_FAILURE;

    if (prc_change_context_focus(window, ctx) != FN_SUCCESS)
        return FN_FAILURE;

    return FN_SUCCESS;
}

fnresult_t prc_create_focused_derwin(
    struct prc_window *     window,
    struct prc_context *    ctx
)
{
    if (window == NULL || ctx == NULL)
        return FN_INVALID_ARGUMENT;

    return prc_create_derwin(window, ctx->fwin, ctx);
}

fnresult_t prc_create_derwin(
    struct prc_window *     window,
    struct prc_window *     parent,
    struct prc_context *    ctx
)
{
    if (window == NULL || ctx == NULL)
        return FN_INVALID_ARGUMENT;

    window->parent = parent;
    
    window->win =
        derwin(window->parent->win, 
            window->height, window->width, window->y, window->x);
    
    if (prc_change_context_focus(window, ctx) != FN_SUCCESS)
            return FN_FAILURE;

    return FN_SUCCESS;
}

void prc_destroy_window(
    struct prc_window * window,
    struct prc_context *ctx
)
{
    if (window == NULL)
        return;

    if (window->win == stdscr)
        return;

    prc_kill_all_children(window);

    if (ctx == NULL)
        return;

    if (ctx->fwin == window)
        ctx->fwin = NULL;

    if (ctx->pwin == window)
        ctx->pwin = NULL;

    prc_dalfrom_winpool(window);
}

fnresult_t prc_window_title(
    struct prc_window *             window,
    const uint16_t                  y,
    const uint16_t                  x,
    struct prc_context *restrict    ctx
)
{
    if (window == NULL)
        return FN_INVALID_ARGUMENT;

    if (window->title == NULL)
        return FN_INVALID_ARGUMENT;

    const char *title = window->title;
    const enum prc_align align = window->talign;

    uint16_t ty;
    uint16_t tx;

    if (prc_get_talginyx(window, strlen(title), align, &ty, &tx)
        == FN_NO_ARGS)
    {
        mvwaddstr(window->win, y, x, title);
        return FN_SUCCESS;
    }

    mvwaddstr(window->win, ty, tx, title);

    prc_change_context_focus(window, ctx);

    return FN_SUCCESS;
}

fnresult_t prc_get_talginyx(
    struct prc_window *restrict     window,
    uint32_t                        tl,
    enum prc_align                  align,
    uint16_t *                      y,
    uint16_t *                      x
)
{
    if (window == NULL || y == NULL || x == NULL)
        return FN_INVALID_ARGUMENT;

    uint32_t wmy;
    uint32_t wmx;
    getmaxyx(window->win, wmy, wmx);

    uint32_t my = wmy - 1;

    if (align == PRC_ALIGN_NONE)
        return FN_NO_ARGS;

    if (align & PRC_ALIGN_TOP)
        *y = 0;
    else if (align & PRC_ALIGN_BOTTOM)
        *y = my;
    else
        *y = wmy >> 1;

    if (align & PRC_ALIGN_LEFT)
        *x = 0;
    else if (align & PRC_ALIGN_RIGHT)
        *x = wmx - tl;
    else
        *x = (wmx - tl) >> 1;

    return FN_SUCCESS;
}

fnresult_t prc_get_walginyx(
    struct prc_window *             basewin,
    uint16_t                        height,
    uint16_t                        width,
    enum prc_align                  align,
    uint16_t *                      y,
    uint16_t *                      x
)
{
    if (basewin == NULL || y == NULL || x == NULL)
        return FN_INVALID_ARGUMENT;

    uint32_t bmy;
    uint32_t bmx;
    getmaxyx(basewin->win, bmy, bmx);

    if (width > bmx || height > bmy)
        return FN_FAILURE;

    if (align == PRC_ALIGN_NONE)
        return FN_NO_ARGS;

    if (align & PRC_ALIGN_TOP)
        *y = 0;
    else if (align & PRC_ALIGN_BOTTOM)
        *y = bmy - height;
    else
        *y = (bmy - height) >> 1;

    if (align & PRC_ALIGN_LEFT)
        *x = 0;
    else if (align & PRC_ALIGN_RIGHT)
        *x = bmx - width;
    else
        *x = (bmx - width) >> 1;

    return FN_SUCCESS;
}

fnresult_t prc_get_padded_wdesc(
    struct prc_window *             window,
    struct prc_window *             basewin,
    struct prc_pad_desc *           pad
)
{
    if (window == NULL || basewin == NULL || pad == NULL)
        return FN_INVALID_ARGUMENT;

    const WINDOW *fwin = basewin->win;
    const uint32_t pl = pad->left;
    const uint32_t pr = pad->right;
    const uint32_t pt = pad->top;
    const uint32_t pb = pad->bottom;
    uint32_t wh;
    uint32_t ww;

    getmaxyx(fwin, wh, ww);
    if (ww < (pl + pr) || wh < (pt + pb))
        return FN_FAILURE;

    window->x = (uint32_t) getbegx(fwin) + pl;
    ww -= pl + pr;

    window->y = (uint32_t) getbegy(fwin) + pt;
    wh -= pt + pb;

    window->height = wh;
    window->width = ww; 
    
    return FN_SUCCESS;
}

fnresult_t prc_align_window(
    struct prc_window *             window,
    struct prc_window *             basewin,
    struct prc_context *restrict    ctx,
    enum prc_align                  align,
    struct prc_pad_desc *           pad
)
{
    if (basewin == NULL || window == NULL)
        return FN_FAILURE;

    if (window == NULL)
        return FN_INVALID_ARGUMENT;

    if (pad->yes == FALSE)
    {
        uint32_t res =
            prc_get_walginyx(basewin, window->height, window->width,
                align, &window->y, &window->x);

        if (res == FN_FAILURE)
            return FN_FAILURE;
    }
    else
    {
        if (prc_get_padded_wdesc(window, basewin, &window->wpad) != FN_SUCCESS)
            return FN_FAILURE;
    }

    if (mvwin(window->win, window->y, window->x) != OK)
        return FN_FAILURE;

    return prc_change_context_focus(window, ctx);
}

fnresult_t prc_resize_window(
    struct prc_window *window,
    struct prc_context *restrict ctx
)
{
    if (window == NULL || ctx == NULL || window->win == stdscr)
        return FN_INVALID_ARGUMENT;

    if (_prc_get_window_info(window) != FN_SUCCESS)
        return FN_FAILURE;

    if (wresize(window->win, window->height, window->width) != OK)
        return FN_FAILURE;

    if (mvwin(window->win, window->y, window->x) != OK)
        return FN_FAILURE;

    werase(window->win);
    prc_draw_window_border(window);
    prc_window_title(window, 0, 0, ctx);

    return FN_SUCCESS;
}