
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
	
	bool TimeInterval::equals(const TimeInterval&time) const
	{
		if(getMilliseconds() == time.getMilliseconds())
		{
			return true;
		}
		else if(time.getMilliseconds() == getMilliseconds())
		{
			return true;
		}
		return false;
	}
	
	bool TimeInterval::operator==(const TimeInterval&time) const
	{
		return equals(time);
	}
	
	bool TimeInterval::operator!=(const TimeInterval&time) const
	{
		return !equals(time);
	}
	
	bool TimeInterval::operator<(const TimeInterval&time) const
	{
		if(getMilliseconds() < time.getMilliseconds())
		{
			return true;
		}
		return false;
	}
	
	bool TimeInterval::operator<=(const TimeInterval&time) const
	{
		if(getMilliseconds() <= time.getMilliseconds())
		{
			return true;
		}
		return false;
	}
	
	bool TimeInterval::operator>(const TimeInterval&time) const
	{
		if(getMilliseconds() > time.getMilliseconds())
		{
			return true;
		}
		return false;
	}
	
	bool TimeInterval::operator>=(const TimeInterval&time) const
	{
		if(getMilliseconds() >= time.getMilliseconds())
		{
			return true;
		}
		return false;
	}
	
	TimeInterval TimeInterval::operator+(const TimeInterval&time) const
	{
		return TimeInterval(getMilliseconds() + time.getMilliseconds());
	}
	
	TimeInterval TimeInterval::operator-(const TimeInterval&time) const
	{
		return TimeInterval(getMilliseconds() - time.getMilliseconds());
	}
	
	TimeInterval& TimeInterval::operator+=(const TimeInterval&time)
	{
		milliseconds += time.getMilliseconds();
		return *this;
	}
	
	TimeInterval& TimeInterval::operator-=(const TimeInterval&time)
	{
		milliseconds -= time.getMilliseconds();
		return *this;
	}
	
	void TimeInterval::update() const
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

	long long TimeInterval::getMilliseconds() const
	{
		if(running)
		{
			update();
		}
		return milliseconds;
	}
	
	String TimeInterval::toString() const
	{
		return (String)"" + milliseconds;
	}
}