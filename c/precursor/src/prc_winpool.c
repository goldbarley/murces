#include "prc/prc_winpool.h"
#include "prc/prc_context.h"
#include "utlprc/math.h"
#include "utlprc/types.h"

#include <string.h>

struct _prc_winpool
{
    struct prc_window windows[PRC_MAX_WINDOW_COUNT];
    uint32_t freemask;
    uint8_t nact;
    uint8_t init;
};

static struct _prc_winpool _window_pool;

fnresult_t _prc_init_winpool(void)
{
    if (_window_pool.init)
        return FN_SUCCESS;

    if (memset(_window_pool.windows, 0,
        PRC_MAX_WINDOW_COUNT * sizeof(struct prc_window)) == NULL)
        return FN_FAILURE;
    
    _window_pool.freemask = UINT32_MAX;
    _window_pool.nact = 0;

    _window_pool.init = TRUE;

    return FN_SUCCESS;
}

struct prc_window *prc_get_freeaddr(void)
{
    _prc_init_winpool();

    uint32_t fm = _window_pool.freemask;

    if (fm == 0)
        return NULL;

    uint32_t fidx = CTZ(fm);
    PRC_MARK_USED(fm, fidx);

    _window_pool.freemask = fm;
    ++_window_pool.nact;

    return &_window_pool.windows[fidx];
}

void prc_dalfrom_winpool(struct prc_window *window)
{
    if (!_window_pool.init || window == NULL)
        return;

    uint8_t widx = window - _window_pool.windows;

    if (widx >= PRC_MAX_WINDOW_COUNT)
        return;

    if (!(_window_pool.freemask & (1U << widx))) 
    {
        if (window->win != NULL)
            delwin(window->win);
        PRC_MARK_FREE(_window_pool.freemask, widx);
        memset(window, 0, sizeof(struct prc_window));
        --_window_pool.nact;
    }
}

fnresult_t prc_get_children(struct prc_window *parent, uint32_t *family)
{
    if (!_window_pool.init || parent == NULL || family == NULL)
        return FN_INVALID_ARGUMENT;

    uint32_t fmly = 0;
    uint32_t am = ~(_window_pool.freemask);
    uint32_t aidx;

    const struct prc_window *mother = prc_get_mother();

    while (am != 0)
    {
        aidx = CTZ(am);
        struct prc_window *w = &_window_pool.windows[aidx];
        if (w->parent == parent)
            PRC_SETBIT_1(fmly, aidx);
        PRC_SETBIT_0(am, aidx);
    }

    uint8_t has_child = FALSE;
    do
    {
        has_child = FALSE;
        am =  ~(_window_pool.freemask | fmly);
        while (am != 0)
        {
            aidx = CTZ(am);
            struct prc_window *w = &_window_pool.windows[aidx];

            uint32_t pidx = w->parent - _window_pool.windows;
            if (pidx >= PRC_MAX_WINDOW_COUNT)   
            {
                PRC_SETBIT_0(am, aidx);
                continue;
            }

            if (w->parent != mother && (fmly & (1U << pidx)))
            {
                PRC_SETBIT_1(fmly, aidx);
                has_child = TRUE;
            }
            PRC_SETBIT_0(am, aidx);
        }
    } while (has_child);

    *family = fmly;

    return FN_SUCCESS;
}

void prc_kill_all_children(struct prc_window *parent)
{
    if (!_window_pool.init || parent == NULL)
        return;

    uint32_t hitlist = 0;
    if (prc_get_children(parent, &hitlist) != FN_SUCCESS)
        return;

    struct prc_window *mother = prc_get_mother();

    while (hitlist != 0)
    {
        uint32_t kidx = CTZ(hitlist);
        struct prc_window *w = &_window_pool.windows[kidx];
        if (w->derived)
            prc_dalfrom_winpool(w);
        else if (w->parent == parent)
            w->parent = mother;

        PRC_SETBIT_0(hitlist, kidx);
    }
}

fnresult_t prc_get_active_windows(struct prc_window **actwins, uint32_t *count)
{
    if (count == NULL)
        return FN_INVALID_ARGUMENT;
    

    if (actwins == NULL)
    {
        *count = _window_pool.nact;
        return FN_SUCCESS;
    }

    uint32_t am = ~_window_pool.freemask;
    uint32_t aidx = 0;
    uint32_t cnt = 0;

    for (; am != 0; ++cnt)
    {
        aidx = CTZ(am);
        actwins[cnt] = &_window_pool.windows[aidx];
        PRC_MARK_USED(am, aidx);
    }

    *count = cnt;

    return FN_SUCCESS;
}