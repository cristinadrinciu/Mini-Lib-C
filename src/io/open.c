// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	mode_t mode = 0;
	va_list args; // list of arguments
	va_start(args, flags);
	mode = va_arg(args, mode_t);
	va_end(args);

	int result = syscall(__NR_open, filename, flags, mode);
	if (result < 0) {
        errno = -result;
        return -1;
    }
    return result;
}