#ifndef __CHECKS_H__
#define __CHECKS_H__

#include "errkit/errkit.h"

#define CHECK_CMP(expr0, cmp, expr1) do {                                       \
    __typeof__(expr0) _expr0 = (expr0);                                         \
    __typeof__(expr1) _expr1 = (expr1);                                         \
    CHECK_LOG((_expr0) cmp (_expr1), "%ld " #cmp " %ld", (long)(_expr0), (long)(_expr1));    \
} while(0)

/* Check two expressions are equal with indicative error */
#define CHECK_EQ(expr0, expr1) do {                                     \
    __typeof__(expr0) _expr0 = (expr0);                                 \
    __typeof__(expr1) _expr1 = (expr1);                                 \
    CHECK_CMP(expr0, ==, expr1);                                        \
} while(0)

#endif  // __CHECKS_H__
