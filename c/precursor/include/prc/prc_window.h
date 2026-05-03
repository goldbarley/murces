#ifndef PRC_WINDOW_H
#define PRC_WINDOW_H

#include <ncurses.h>

#include "prc/prc_context.h"
#include "utlprc/types.h"

#include <stdint.h>

struct prc_border_desc
{
    uint8_t ls;
    uint8_t rs;
    uint8_t ts;
    uint8_t bs;
    uint8_t tl;
    uint8_t tr;
    uint8_t bl;
    uint8_t br;
};

struct prc_pad_desc
{
    uint16_t left;
    uint16_t right;
    uint16_t top;
    uint16_t bottom;
    uint16_t yes;
};

struct prc_window
{
    WINDOW *                win;
    struct prc_window *     parent;
    char *                  title;
    enum prc_align          talign;
    enum prc_align          walign;
    struct prc_pad_desc     wpad;
    struct prc_border_desc  wbord;
    uint16_t                height;
    uint16_t                width;
    uint16_t                y;
    uint16_t                x;
    uint8_t                 derived;
};

fnresult_t prc_create_window(
    struct prc_window *     window,
    struct prc_context *    ctx
);

fnresult_t prc_create_focused_derwin(
    struct prc_window *     window,
    struct prc_context *    ctx
);

fnresult_t prc_create_derwin(
    struct prc_window *     window,
    struct prc_window *     parent,
    struct prc_context *    ctx
);

void prc_destroy_window(
    struct prc_window * window,
    struct prc_context *ctx
);

fnresult_t prc_draw_window_border(
    struct prc_window *window
);

fnresult_t prc_window_title(
    struct prc_window *             window,
    const uint16_t                  y,
    const uint16_t                  x,
    struct prc_context *restrict    ctx
);

fnresult_t prc_get_talginyx(
    struct prc_window *restrict     window,
    uint32_t                        tl,
    enum prc_align                  align,
    uint16_t *                      y,
    uint16_t *                      x
);

fnresult_t prc_get_walginyx(
    struct prc_window *             basewin,
    uint16_t                        height,
    uint16_t                        width,
    enum prc_align                  align,
    uint16_t *                      y,
    uint16_t *                      x
);

fnresult_t prc_get_padded_wdesc(
    struct prc_window *             window,
    struct prc_window *             basewin,
    struct prc_pad_desc *           pad
);

fnresult_t prc_align_window(
    struct prc_window *             window,
    struct prc_window *             basewin,
    struct prc_context *restrict    ctx,
    enum prc_align                  align,
    struct prc_pad_desc *           pad
);

fnresult_t prc_resize_window(
    struct prc_window *window,
    struct prc_context *restrict ctx
);

#endif /* PRC_WINDOW_H */