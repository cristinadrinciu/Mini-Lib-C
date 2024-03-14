// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	char *d;

	for (d = destination; *source != '\0'; source++, d++)
		*d = *source;
	// place the NULL terminator
	*d = *source;

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	char *d;
	size_t contor = 0;
	d = destination;

	while(*source != '\0' && contor < (len - 1)) {
		*d = *source;
		contor++;
		source++;
        d++;
	}
	// place the NULL terminator
	*d = *source;
	return destination;
}

char *strcat(char *destination, const char *source)
{
	char *d = destination;

	// copy the initial string first
    while (*d != '\0') {
        d++;
    }
	// concatenate the source
    while (*source != '\0') {
        *d = *source;
        source++;
        d++;
    }
	//place the NULL terminator
    *d = '\0';
    return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	char *d = destination;

	// copy the initial string first
    while (*d != '\0') {
        d++;
    }
	while (*source != '\0' && len > 0) {
        *d = *source;
        source++;
        d++;
		len--;
    }
	//place the NULL terminator
    *d = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while(*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
		str1++;
		str2++;
	}
	int difference = *str1 - *str2;
	if(difference > 0)
		return 1;
	if(difference < 0)
		return -1;
	return 0;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	while(*str1 != '\0' && *str2 != '\0' && len > 0) {
		if(*str1 != *str2) {
			return *str1 - *str2;
		}
		str1++;
		str2++;
		len--;
	}
	if((*str1 == '\0' && *str2 == '\0') || len == 0)
		return 0;
	if(*str1 == '\0')
		return -1;
	return 1;
}

size_t strlen(const char *str)
{
	size_t i = 0;
	const char *d;
	for (d = str; *str != '\0'; str++, d++)
		i++;

	return i;
}

char *strchr(const char *str, int c)
{
	// return a pointer to the first occurance
	const char *pointer = NULL;
	const char *tmp = str;
	while(*tmp != '\0') {
		if(*tmp == c) {
			pointer = tmp;
			break; // exit at first occurance
		}
		tmp++;
	}
	return (char*) pointer;
}

char *strrchr(const char *str, int c)
{
	// return a pointer to the last occurance
	const char *pointer = NULL;
	const char *tmp = str;
	while(*tmp != '\0') {
		if(*tmp == c) {
			pointer = tmp;
			// do not exit
		}
		tmp++;
	}
	return (char*) pointer;
}

char *strstr(const char *haystack, const char *needle)
{
	const char *pointer = NULL;
	const char *tmp1, *tmp2;
	while(*haystack != '\0') {
		// initialise with the given strings
		tmp1 = haystack;
		tmp2 = needle;
		// compare the strings
		while(*tmp2 != '\0') {
			if(*tmp1 != *tmp2)
				break;
			tmp1++;
			tmp2++;
		}
		if(*tmp2 == '\0') {
			// means that in tmp1 is the tmp2(needle)
			pointer = haystack;
			break; // exit the loop
		}
		haystack++;
	}
	return (char*) pointer;
}

char *strrstr(const char *haystack, const char *needle)
{
	const char *pointer = NULL;
	const char *tmp1, *tmp2;
	while(*haystack != '\0') {
		// initialise with the given strings
		tmp1 = haystack;
		tmp2 = needle;
		// compare the strings
		while(*tmp2 != '\0') {
			if(*tmp1 != *tmp2)
				break;
			tmp1++;
			tmp2++;
		}
		if(*tmp2 == '\0') {
			// means that in tmp1 is the tmp2(needle)
			pointer = haystack;
			//do not exit the loop
		}
		haystack++;
	}
	return (char*) pointer;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	char *tmp1 = (char *) destination;
	const char *tmp2 = (const char *) source;
	for(size_t i = 0; i < num; i++)
		tmp1[i] = tmp2[i];
	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	char *tmp1 = (char *) destination;
	const char *tmp2 = (const char *) source;

	if(tmp1 == tmp2) {
		// same address => overlap
		// do nothing
		return destination;
	}

	// treat the overlapping cases
	if(tmp1 < tmp2 && tmp2 - tmp1 < (int) num) {
		// no overlap of the memory
		for(int i = 0; i < (int)num; i++)
			tmp1[i] = tmp2[i];
		return destination;
	} else if(tmp1 > tmp2 && tmp1 - tmp2 < (int) num) {
		/*
			 it may overlap because the destination address is greater
			 then the source address
		*/
		for(int i = (int)num - 1; i >= 0; i--)
			tmp1[i] = tmp2[i];
		return destination;
	}

	// copy as usual the block of memory
	for(int i = 0; i < (int)num; i++)
		tmp1[i] = tmp2[i];
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const char *tmp1 = (const char *) ptr1;
	const char *tmp2 = (const char *) ptr2;
	while(*tmp1 != '\0' && *tmp2 != '\0' && num > 0) {
		if(*tmp1 != *tmp2) {
			return *tmp1 - *tmp2;
		}
		tmp1++;
		tmp2++;
		num--;
	}
	if((*tmp1 == '\0' && *tmp2 == '\0') || num == 0)
		return 0;
	if(*tmp1 == '\0')
		return -1;
	return 1;
}

void *memset(void *source, int value, size_t num)
{
	char *tmp = (char *) source;
	for(int i = 0; i < (int) num; i++)
		tmp[i] = value;
	return source;
}

