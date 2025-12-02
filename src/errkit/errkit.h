#ifndef __ERRKIT_H__
#define __ERRKIT_H__

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "utils/cross_utils.h"
#include "checks/checks.h"

#define NO_ERROR_CODE 0

extern void set_verbose(bool state);
extern bool is_verbose(void);

typedef int ErrorCode;

#define GET_ERROR_CODE() (((__LINE__) << 16) ^ (errno))

#define push_log(force, desc, ...)                                              \
    do {                                                                        \
        static char buf[64] = {0};                                              \
        if (force || is_verbose()) {                                            \
            snprintf(buf, sizeof(buf), "%s:%d", __FILE__, __LINE__);            \
            printf("%-30s" desc, buf, ##__VA_ARGS__);                           \
        }                                                                       \
    } while(0)

#define push_error(err, desc, ...) push_log(true, desc " [err %d]\n", ##__VA_ARGS__, err)

/* Check that the expr is truthy. Else log custom description */
#define CHECK_LOG(expr, desc, ...) do {         \
    if (!(expr)) {                              \
        err = errno;                            \
        push_error(err, desc, ##__VA_ARGS__);   \
        goto cleanup;                           \
    }                                           \
} while(0)

/* Check that the expr is truthy. Else log custom description, and return (used inside cleanup) */
#define CHECK_LOG_RETURN(expr, desc, ...) do {  \
    if (!(expr)) {                              \
        err = errno;                            \
        push_error(err, desc, ##__VA_ARGS__);   \
        return err;                             \
    }                                           \
} while(0)

/* Check that the expr is truthy. Else log the error */
#define CHECK(expr) CHECK_LOG(expr, "CHECK")

#define CHECK_FAIL() CHECK_LOG(false, "CHECK FAIL")

#define CHECK_FAIL_RETURN() CHECK_LOG_RETURN(false, "CHECK FAIL")

#define CHECK_AND_RETHROW(expr) CHECK_LOG((expr) == NO_ERROR_CODE, "\tCheck rethrown from")

#define CHECK_NULL_TERM(char_ptr, max_len) CHECK(strnlen(char_ptr, max_len) < max_len)

#define TRACE(desc, ...) push_log(false, desc, ##__VA_ARGS__)

/* Like TRACE, but always logs to screen - even if not verbose */
#define TRACE_LOG(desc, ...) push_log(true, desc, ##__VA_ARGS__)

#endif // __ERRKIT_H__
