#ifndef PRC_WINPOOL_H
#define PRC_WINPOOL_H

#include "prc/prc_window.h"

#define PRC_MARK_USED(m, i) \
    ((m) &= ~(1U << (i)))

#define PRC_MARK_FREE(m, i) \
    ((m) |= (1U << (i)))

#if defined(__GNUC__) || defined(__clang__)
#define CTZ(u) __builtin_ctz(u)
#elif defined(_MSC_VER)
#include <intrin.h>
/* Not implemented. */
#define CTZ(u) _msvc_ctz(u)
#define CTZ64(u) _msvc_ctz64(u)
#else
#define CTZ(u)
#define CTZ64(u)
#endif /* defined(__GNUC__) || defined(__clang__) elif defined(_MCS_VER) */

#define PRC_MAX_WINDOW_COUNT (32U)

#define anakin_skywalker(p) (prc_kill_all_children(p))

struct prc_window *prc_get_freeaddr(void);

void prc_dalfrom_winpool(
    struct prc_window *window
);

void prc_kill_all_children(
    struct prc_window *parent
);

fnresult_t prc_get_active_windows(
    struct prc_window **actwins,
    uint32_t *          count
);

#endif /* PRC_WINSTACK_H */