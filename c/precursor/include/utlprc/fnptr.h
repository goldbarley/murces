#ifndef UTLPRC_FNPTR_H
#define UTLPRC_FNPTR_H

#define MAKE_FNPTR(t, f, ...) \
    t (*f)(__VA_ARGS__)

#endif /* UTLPRC_FNPTR_H */