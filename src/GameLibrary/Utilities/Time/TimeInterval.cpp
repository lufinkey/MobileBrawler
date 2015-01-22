
#include "TimeInterval.h"
#include "posixtime.h"
#include <time.h>

#ifndef _WIN32
	#include <sys/time.h>
#endif

namespace GameLibrary
{
	long long TimeInterval_getCurrentMilliseconds()
	{
		struct timeval64 tv;
		gettimeofday64(&tv, nullptr);
		return (long long)(((long long)tv.tv_sec*1000) + ((long long)tv.tv_usec/1000));
	}

	TimeInterval::TimeInterval()
	{
		lastmillis = 0;
		milliseconds = 0;
		running = false;
	}

	TimeInterval::TimeInterval(const TimeInterval&time)
	{
		lastmillis = time.lastmillis;
		milliseconds = time.milliseconds;
		running = time.running;
	}

	TimeInterval::TimeInterval(long long millis)
	{
		lastmillis = 0;
		milliseconds = millis;
		running = false;
	}

	TimeInterval::~TimeInterval()
	{
		//
	}

	TimeInterval& TimeInterval::operator=(const TimeInterval&time)
	{
		lastmillis = time.lastmillis;
		milliseconds = time.milliseconds;
		running = time.running;

		return *this;
	}

	void TimeInterval::update()
	{
		long long currentmillis = TimeInterval_getCurrentMilliseconds();
		milliseconds += (currentmillis - lastmillis);
		lastmillis = currentmillis;
	}

	void TimeInterval::start()
	{
		if(!running)
		{
			lastmillis = TimeInterval_getCurrentMilliseconds();
			running = true;
		}
	}

	void TimeInterval::stop()
	{
		if(running)
		{
			running = false;
			update();
		}
	}

	void TimeInterval::reset()
	{
		milliseconds = 0;
		lastmillis = TimeInterval_getCurrentMilliseconds();
	}

	long long TimeInterval::getMilliseconds()
	{
		if(running)
		{
			update();
		}
		return milliseconds;
	}

	long long TimeInterval::getMilliseconds() const
	{
		return milliseconds;
	}
}