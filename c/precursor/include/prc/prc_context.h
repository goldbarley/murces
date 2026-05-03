#ifndef PRC_CONTEXT_H
#define PRC_CONTEXT_H

#include <ncurses.h>

#include "utlprc/types.h"

#include <stdint.h>
#include <stdbool.h>

struct prc_context
{
    struct prc_window * cwin;
    struct prc_window * fwin;
    struct prc_window * pwin;
    bool                term_change_color;
    uint32_t            term_y;
    uint32_t            term_x;
    bool                term_has_color;
};

fnresult_t prc_get_context(
    struct prc_context *ctx
);

fnresult_t prc_change_context_focus(
    struct prc_window * window,
    struct prc_context *ctx
);

fnresult_t prc_chto_previous_focus(
    struct prc_context *ctx
);

fnresult_t prc_resize_context(
    struct prc_context *ctx
);

fnresult_t prc_chto_focus_mother(
    struct prc_context *ctx
);

void prc_destroy_context(
    struct prc_context *ctx
);

struct prc_window *prc_get_mother(void);

fnresult_t prc_get_grandmother(
    struct prc_window *grandmother
);

void prc_kill_mother(void);

// MAKE_FNPTR(fnresult_t, prc_resize_context, struct prc_context *)

#endif /* PRC_CONTEXT_H */