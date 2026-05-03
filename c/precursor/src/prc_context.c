#include <ncurses.h>
#include <menu.h>
#include <string.h>

#include "prc/prc_context.h"
#include "prc/prc_window.h"
#include "utlprc/types.h"

/* Will cause segfault of mother is removed. */
struct _prc_mother_info
{
    struct prc_window mwin;
    bool init;
};

static struct _prc_mother_info GLaDOS = {
    .mwin = {0},
    .init = FALSE
};

static void _prc_init_GLaDOS(void)
{
    if (GLaDOS.init)
        return;

    GLaDOS.mwin.win = initscr();
    getmaxyx(GLaDOS.mwin.win, GLaDOS.mwin.height, GLaDOS.mwin.width);
    GLaDOS.mwin.y = 0;
    GLaDOS.mwin.x = 0;

    GLaDOS.init = true;
}

static void _prc_resize_GLaDOS(void)
{
    getmaxyx(GLaDOS.mwin.win, GLaDOS.mwin.height, GLaDOS.mwin.width);
    GLaDOS.mwin.y = 0;
    GLaDOS.mwin.x = 0;
}

fnresult_t prc_get_context(struct prc_context *ctx)
{
    if (ctx == NULL)
        return FN_FAILURE;

    _prc_init_GLaDOS();

    ctx->cwin = &GLaDOS.mwin;
    ctx->fwin = &GLaDOS.mwin;
    ctx->pwin = NULL;
    ctx->term_y = GLaDOS.mwin.height;
    ctx->term_x = GLaDOS.mwin.width;

    ctx->term_has_color = has_colors();
    ctx->term_change_color = can_change_color();

    return FN_SUCCESS;
}

fnresult_t prc_change_context_focus(
    struct prc_window * window,
    struct prc_context *ctx
)
{
    if (window == NULL || ctx == NULL || window->win == NULL)
        return FN_INVALID_ARGUMENT;

    if (window == ctx->fwin)
        return FN_SUCCESS;

    ctx->pwin = ctx->fwin;
    ctx->fwin = window;

    return FN_SUCCESS;
}

fnresult_t prc_chto_previous_focus(
    struct prc_context *ctx
)
{
    if (ctx == NULL || ctx->pwin == NULL || ctx->fwin == NULL)
        return FN_INVALID_ARGUMENT;

    struct prc_window *tmp = ctx->fwin;
    ctx->fwin = ctx->pwin;
    ctx->pwin = tmp;

    return FN_SUCCESS;
}

fnresult_t prc_resize_context(struct prc_context *ctx)
{
    if (ctx == NULL)
        return FN_INVALID_ARGUMENT;

    _prc_resize_GLaDOS();
        
    ctx->term_y = GLaDOS.mwin.height;
    ctx->term_x = GLaDOS.mwin.width;

    return FN_SUCCESS;
}

__attribute__((__unused__))
static fnresult_t _prc_change_mother(struct prc_window *new_mom)
{
    if (new_mom == NULL)
        return FN_INVALID_ARGUMENT;

    /* Cheap fix. TODO: Change this later for a proper copy. */
    GLaDOS.mwin = *new_mom;

    return FN_SUCCESS;
}

fnresult_t prc_chto_focus_mother(struct prc_context *ctx)
{
    if (ctx == NULL)
        return FN_INVALID_ARGUMENT;

    prc_change_context_focus(&GLaDOS.mwin, ctx);

    return FN_SUCCESS;
}

void prc_destroy_context(struct prc_context *ctx)
{
    if (ctx == NULL)
        return;

    struct prc_window *target[3] = {
        ctx->cwin,
        ctx->fwin,
        ctx->pwin
    };

    if (memset(ctx, 0, sizeof(struct prc_context)) == NULL)
        return;

    for (uint8_t i = 0; i < 3; ++i)
    {
        if (target[i] != NULL && target[i] != &GLaDOS.mwin)
            prc_destroy_window(target[i], NULL);
    }
}

struct prc_window *prc_get_mother(void)
{
    return &GLaDOS.mwin;
}

void prc_kill_mother(void)
{
    endwin();
}