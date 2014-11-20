
#include <stdint.h>
#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#pragma once

#ifdef _WIN32
typedef int suseconds_t;
struct timezone
{
	int tz_minuteswest; /* Minutes west of GMT.  */
	int tz_dsttime; /* Nonzero if DST is ever in effect.  */
};

struct timeval;
struct timeval64
{
	int64_t tv_sec;
	int32_t tv_usec;
};

int gettimeofday(struct timeval*tv, struct timezone*tz);
int gettimeofday64(struct timeval64*tv, struct timezone*tz);
#endif