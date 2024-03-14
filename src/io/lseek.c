// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
	off_t result = syscall(__NR_lseek, fd, offset, whence);

    if (result < 0) {
        errno = -result;
        return -1; // Return -1 to indicate an error.
    }

    return result;
}
