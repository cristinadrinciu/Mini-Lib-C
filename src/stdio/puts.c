#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int puts(const char *str)
{
    int n = strlen(str);
    int result = syscall(__NR_write, 1, str, n);
    if(result < 0) {
        errno = -result;
		return -1;
    }
    // put the terminator
    char new_line = '\n';
    result = syscall(__NR_write, 1, &new_line, 1);
    if(result < 0) {
        errno = -result;
		return -1;
    }
    return result;
}