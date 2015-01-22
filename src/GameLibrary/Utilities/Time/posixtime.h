
#pragma once

#include <stdint.h>
#include <ctime>
#include <time.h>
#ifdef _WIN32
#include <winsock.h>
#else
#include <sys/time.h>
#endif

#if defined(_WIN32)
typedef int suseconds_t;
struct timezone
{
	int tz_minuteswest; /* Minutes west of GMT.  */
	int tz_dsttime; /* Nonzero if DST is ever in effect.  */
};

struct timeval;
#endif

#if defined(_WIN32) || defined(__APPLE__)
struct timeval64
{
	int64_t tv_sec;
	int32_t tv_usec;
};
#endif

#if defined(_WIN32)
int gettimeofday(struct timeval*tv, struct timezone*tz);
int gettimeofday64(struct timeval64*tv, struct timezone*tz);
#elif defined(__APPLE__)
int gettimeofday64(struct timeval64*tv, struct timezone*tz);
#endif