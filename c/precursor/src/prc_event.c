#include "prc/prc_event.h"
#include "utlprc/types.h"

struct _prc_event_buffer
{
    struct prc_generic_event buffer[PRC_MAX_EVENT_COUNT];
    uint16_t head;
    uint16_t tail;
    uint8_t init;
};

static struct _prc_event_buffer _event_buffer;

void prc_init_evt_buffer(void)
{
    if (_event_buffer.init)
        return;

    _event_buffer.head = 0;
    _event_buffer.tail = 0;
    _event_buffer.init = TRUE;
}

fnresult_t prc_use_event(void)
{
    if (_event_buffer.head == _event_buffer.tail)
        return FN_NO_ARGS;
    
    _event_buffer.tail = (_event_buffer.tail + 1) & (PRC_MAX_EVENT_COUNT - 1);
    return FN_SUCCESS;
}

fnresult_t _prc_get_evt_buffer_status(void)
{
    if (((_event_buffer.head + 1) & (PRC_MAX_EVENT_COUNT - 1))
        == _event_buffer.tail)
        return FN_OUT_OF_MEMORY;
    
    if (_event_buffer.head == _event_buffer.tail)
        return FN_NO_ARGS;

    return FN_SUCCESS;
}

fnresult_t _prc_allocto_evt_buffer(enum prc_event_type type, uint16_t detail)
{
    if (((_event_buffer.head + 1) & (PRC_MAX_EVENT_COUNT - 1))
        == _event_buffer.tail)
        return FN_OUT_OF_MEMORY;

    _event_buffer.buffer[_event_buffer.head].type = type;
    _event_buffer.buffer[_event_buffer.head].detail = detail;
    _event_buffer.head = (_event_buffer.head + 1) & (PRC_MAX_EVENT_COUNT - 1);

    return FN_SUCCESS;
}

fnresult_t _prc_fill_evt_buffer(struct prc_window *window)
{

    int32_t c;
    while ((c = wgetch(window->win)) != ERR)
    {
        if (_prc_allocto_evt_buffer(PRC_EVENT_KEY_PRESS, c)
            != FN_SUCCESS)
            break;
    }

    return FN_SUCCESS;
}

fnresult_t prc_wait_for_event(struct prc_window *window)
{
    if (window == NULL)
        return FN_FAILURE;

    int32_t keydtl  = wgetch(window->win);
    if (keydtl == ERR)
        return FN_FAILURE;

    if (_prc_allocto_evt_buffer(PRC_EVENT_KEY_PRESS, keydtl)
        != FN_SUCCESS)
        return FN_FAILURE;

    return FN_SUCCESS;
}

fnresult_t prc_poll_for_event(struct prc_window *window)
{
    if (window == NULL)
        return FN_FAILURE;

    return _prc_fill_evt_buffer(window);
}

fnresult_t prc_get_first_event(struct prc_generic_event *evt)
{
    if (evt == NULL)
        return FN_INVALID_ARGUMENT;

    if (_event_buffer.head == _event_buffer.tail)
        return FN_NO_ARGS;

    *evt = _event_buffer.buffer[_event_buffer.tail];

    return FN_SUCCESS;
}

fnresult_t prc_get_last_event(struct prc_generic_event *evt)
{
    if (evt == NULL)
        return FN_INVALID_ARGUMENT;

    *evt = _event_buffer.buffer[
        (_event_buffer.head - 1) & (PRC_MAX_EVENT_COUNT - 1)];

    return FN_SUCCESS;
}