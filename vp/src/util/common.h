#pragma once

#include <stdexcept>

#define likely(x)       __builtin_expect((x),1)
#define unlikely(x)     __builtin_expect((x),0)

#define UNUSED(x) (void)(x)

inline void ensure(bool cond) {
    if (!cond)
        throw std::runtime_error("runtime assertion failed");
}

inline void ensure(bool cond, const std::string &reason) {
    if (!cond)
        throw std::runtime_error(reason);
}


/* Allow to provide a custom function name for a SystemC thread to avoid duplicate name warning in case the same
 * SystemC module is instantiated multiple times. */
#define SC_NAMED_THREAD(func,name)                                            \
    declare_thread_process( func ## _handle,                                  \
                            name,                                             \
                            SC_CURRENT_USER_MODULE,                           \
                            func )
