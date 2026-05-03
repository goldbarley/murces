#ifndef PRC_EG_H
#define PRC_EG_H

#include "prc/prc_window.h"

/* eg_single_window.c */
fnresult_t eg_single_window(void);

fnresult_t eg_align_window(void);

void eg_destroy_single_window(
    struct prc_window * win,
    struct prc_context *ctx
);

/* eg_derived_window.c */
fnresult_t eg_create_derwin(
    struct prc_window *basewin,
    struct prc_window *dervwin,
    struct prc_context *ctx,
    bool bborder, bool dborder,
    bool balign, bool dalign,
    bool bpad, bool dpad
);

/* eg_input_handling.c */
fnresult_t eg_blocking_events(void);

fnresult_t eg_polling_events(void);

/* eg_text_box.c */
fnresult_t eg_text_box(void);

/* eg_resize_window.c */
fnresult_t eg_resize_window(void);

#endif /* PRC_EG_H */