#ifndef PRC_TYPES_H
#define PRC_TYPES_H

#undef FALSE
#define FALSE (0)

#undef TRUE
#define TRUE (1)

#undef UINT32_MAX
#define UINT32_MAX (4294967295U)

typedef enum fnresult
{
    FN_SUCCESS,
    FN_FAILURE,
    FN_INVALID_ARGUMENT,
    FN_NO_ARGS,
    FN_OUT_OF_MEMORY
} fnresult_t;

enum prc_align
{
    PRC_ALIGN_NONE          = 0x000000FF,
    PRC_ALIGN_LEFT          = 0x00000001,
    PRC_ALIGN_RIGHT         = 0x00000002,
    PRC_ALIGN_TOP           = 0x00000004,
    PRC_ALIGN_BOTTOM        = 0x00000008,
    PRC_ALIGN_CENTRE        = 0x00000000,
    PRC_ALIGN_TOPLEFT       = 0x00000005,
    PRC_ALIGN_TOPRIGHT      = 0x00000006,
    PRC_ALIGN_BOTTOMLEFT    = 0x00000009,
    PRC_ALIGN_BOTTOMRIGHT   = 0x0000000A
};

enum prc_event_type
{
    PRC_EVENT_KEY_EMPTY,
    PRC_EVENT_KEY_PRESS,
    PRC_EVENT_BUTTON_PRESS
};

#endif /* PRC_TYPES_H */