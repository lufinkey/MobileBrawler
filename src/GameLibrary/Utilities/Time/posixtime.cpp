
#include "posixtime.h"

#ifdef _WIN32
	#include <Windows.h>
	#define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
	#define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

#ifdef _WIN32
int gettimeofday(struct timeval*tv, struct timezone*tz)
{
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	static int tzflag;

	if (tv != NULL)
	{
		GetSystemTimeAsFileTime(&ft);
		
		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;
		
		/*converting file time to unix epoch*/
		tmpres -= DELTA_EPOCH_IN_MICROSECS; 
		tmpres /= 10;  /*convert into microseconds*/
		tv->tv_sec = (long)(tmpres / 1000000UL);
		tv->tv_usec = (long)(tmpres % 1000000UL);
	}

	if (tz != NULL)
	{
		if (!tzflag)
		{
			_tzset();
			tzflag++;
		}
		long timezoneseconds = 0;
		_get_timezone(&timezoneseconds);
		tz->tz_minuteswest = (int)(timezoneseconds / 60);
		int dsthours = 0;
		_get_daylight(&dsthours);
		tz->tz_dsttime = dsthours;
	}

	return 0;
}

int gettimeofday64(struct timeval64*tv, struct timezone*tz)
{
	static int tzflag;

	if (tv != NULL)
	{
		// Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
		static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

		SYSTEMTIME  system_time;
		FILETIME    file_time;
		uint64_t    time;

		GetSystemTime(&system_time);
		SystemTimeToFileTime(&system_time, &file_time);
		time =  ((uint64_t)file_time.dwLowDateTime);
		time += ((uint64_t)file_time.dwHighDateTime) << 32;

		tv->tv_sec  = (long long) ((time - EPOCH) / 10000000L);
		tv->tv_usec = (long) (system_time.wMilliseconds * 1000);
	}

	if (tz != NULL)
	{
		if (!tzflag)
		{
			_tzset();
			tzflag++;
		}
		long timezoneseconds = 0;
		_get_timezone(&timezoneseconds);
		tz->tz_minuteswest = (int)(timezoneseconds / 60);
		int dsthours = 0;
		_get_daylight(&dsthours);
		tz->tz_dsttime = dsthours;
	}

	return 0;
}
#endif
