#ifndef PRC_EVENT_H
#define PRC_EVENT_H

#include "prc/prc_window.h"
#include "utlprc/types.h"

#include <stdint.h>

#define PRC_MAX_EVENT_COUNT (32U)

struct prc_generic_event
{
    enum prc_event_type type;
    uint32_t detail;
};

typedef struct prc_generic_event prc_key_press_event_t;
typedef struct prc_generic_event prc_button_press_event_t;

void prc_init_evt_buffer(void);

fnresult_t prc_wait_for_event(
    struct prc_window *window
);

fnresult_t prc_poll_for_event(
    struct prc_window *window
);

fnresult_t prc_get_first_event(
    struct prc_generic_event *evt
);

fnresult_t prc_get_last_event(
    struct prc_generic_event *evt
);

fnresult_t prc_use_event(void);

#endif /* PRC_EVENT_H */