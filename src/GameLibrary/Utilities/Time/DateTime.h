
#include "../String.h"

#pragma once

namespace GameLibrary
{
	class DateTime
	{
	private:
		int usec;
		int sec;
		int min;
		int hour;
		int mday;
		int wday;
		int mon;
		int yday;
		int year;
		int utc_minoff;
		int utc_houroff;
		
	public:
		DateTime(); //new datetime object with current time
		DateTime(const DateTime&);
		DateTime(const String&datestring, const String&format=String("%Y-%m-%d %H:%M:%S %z"));
		DateTime(int year, int mon, int day);
		DateTime(int year, int mon, int day, int hour, int min, int sec, int usec);
		~DateTime();
		
		int getMicroseconds();
		int getSeconds();
		int getMinutes();
		int getHour();
		int getDayOfMonth();
		int getDayOfWeek();
		int getDayOfYear();
		int getMonth();
		int getYear();
		int getMinuteOffsetUTC();
		int getHourOffsetUTC();

		String getDayOfWeekString();
		String getMonthString();

		String toString(const String&format=String("%Y-%m-%d %H:%M:%S %z"));
		
		void setMicroseconds(int usec);
		void setSeconds(int sec);
		void setMinutes(int min);
		void setHour(int hour);
		void setDayOfMonth(int mday);
		void setDayOfWeek(int wday);
		void setDayOfYear(int yday);
		void setMonth(int mon);
		void setYear(int year);
	};
}
