
#pragma once

#include "../String.h"
#include "../Dictionary.h"
#include "../../Exception/Utilities/Time/IllegalDateTimeFormatException.h"

namespace GameLibrary
{
	class DateTime
	{
	private:
		/* UTC offset in seconds (00000-43200) */
		long utc_offset;

		/* microsecond (000000-999999) */
		int usec;

		/* second (00-61) (generally 00-59. the extra 2 seconds are for leap seconds) */
		int sec;

		/* minute (00-59) */
		int min;

		/* hour (00-23) */
		int hour;

		/* day of the month (01-31) */
		int mday;

		/* month (01-12) */
		int mon;

		/* year (0000-9999) */
		int year;

		/* day of the week (sunday=1) (1-7) */
		int wday;

		/* day of the year (001-366) */
		int yday;

	public:
		/* Constructs a DateTime object with the current date and time */
		DateTime();
		/* DateTime copy constructor */
		DateTime(const DateTime&);
		DateTime(const time_t&);

		//DateTime is immutable for now
		//DateTime(const String&datestring, const String&format=String("%Y-%m-%d %H:%M:%S %z"));
		//DateTime(int year, int mon, int day);
		//DateTime(int year, int mon, int day, int hour, int min, int sec, int usec);

		/* DateTime destructor */
		~DateTime();
		
		int getMicrosecond() const;
		int getSecond() const;
		int getMinute() const;
		int getHour() const;
		int getDayOfMonth() const;
		int getDayOfWeek() const;
		int getDayOfYear() const;
		int getMonth() const;
		int getYear() const;
		/* returns UTC offset in seconds (00000-43200) */
		long getOffsetUTC() const;

		String toString(const String&format=String("%Y-%m-%d %H:%M:%S %z")) const;
		time_t toTimeType() const;
		
		/*void setMicrosecond(int usec);
		void setSecond(int sec);
		void setMinute(int min);
		void setHour(int hour);
		void setDayOfMonth(int mday);
		void setDayOfWeek(int wday);
		void setDayOfYear(int yday);
		void setMonth(int mon);
		void setYear(int year);
		void setOffsetUTC(long utc_offset);*/ //DateTime is immutable for now
	};
}
