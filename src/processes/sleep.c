#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

unsigned int sleep(unsigned int seconds)
{
    // use nanosleep
    struct timespec req, rem;
    req.tv_sec = seconds;
    req.tv_nsec = 0; // no nanoseconds given
    while(nanosleep(&req, &rem) == -1)
        if (errno == EINTR)
                // sleep was interrupted by a signal
                req = rem;
    return 0; // default sleep return value
}
