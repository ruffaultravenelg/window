// window.c

#if defined(_WIN32) || defined(_WIN64)
#include "window_windows.c"
#elif defined(__linux__)
#error "This platform is not supported yet."
#endif
