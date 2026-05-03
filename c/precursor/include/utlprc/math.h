#ifndef PRC_MATH_H
#define PRC_MATH_H

#define PRC_SETBIT_0(m, i) \
    ((m) &= ~(1U << (i)))

#define PRC_SETBIT_1(m, i) \
    ((m) |= (1U << (i)))

#define PRC_TOGGLEBIT(m, i) \
    ((m) ^= (1U << (i)))

#endif /* PRC_MATH_H */