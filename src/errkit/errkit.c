#include "errkit.h"

static bool g_verbose = false;

void set_verbose(const bool state) {
    g_verbose = state;
}

bool is_verbose(void) {
    return g_verbose;
}
