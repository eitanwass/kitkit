#include <stdio.h>
#include "errkit/errkit.h"

int main(void) {
    printf("verbose before: %d\n", is_verbose());
    set_verbose(true);
    printf("verbose after: %d\n", is_verbose());
    TRACE_LOG("This is a TRACE_LOG test: %s\n", "ok");
    return 0;
}
