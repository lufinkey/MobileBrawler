
#include "DateTime.h"
#include "../ArrayList.h"
#include "posixtime.h"
#include "time64/time64.h"

namespace GameLibrary
{
	DateTime::DateTime()
	{
		struct timeval64 tv;
		gettimeofday64(&tv, NULL);
		Time64_T now = (Time64_T)tv.tv_sec;
		struct tm lcl = *localtime64(&now);
		struct tm gmt = *gmtime64(&now);

		if(gmt.tm_hour < lcl.tm_hour && (lcl.tm_hour - 12)>gmt.tm_hour)
		{
			gmt.tm_hour += 24;
		}
		else if(gmt.tm_hour > lcl.tm_hour && (gmt.tm_hour - 12) > lcl.tm_hour)
		{
			gmt.tm_hour -= 24;
		}

		int gmt_hour = lcl.tm_hour - gmt.tm_hour;
		
		if(gmt.tm_min < lcl.tm_min && (lcl.tm_min - 30)>gmt.tm_min)
		{
			gmt.tm_hour += 24;
		}
		else if(gmt.tm_min > lcl.tm_min && (gmt.tm_min - 30) > lcl.tm_min)
		{
			gmt.tm_min -= 24;
		}

		int gmt_min = lcl.tm_min - gmt.tm_min;

		usec = tv.tv_usec;
		sec = lcl.tm_sec;
		min = lcl.tm_min;
		hour = lcl.tm_hour;
		mday = lcl.tm_mday;
		mon = lcl.tm_mon + 1;
		year = lcl.tm_year+1900;
		wday = lcl.tm_wday;
		yday = lcl.tm_yday;
		utc_minoff = gmt_min;
		utc_houroff = gmt_hour;
	}

	DateTime::DateTime(const DateTime&datetime)
	{
		usec = datetime.usec;
		sec = datetime.sec;
		min = datetime.min;
		hour = datetime.hour;
		mday = datetime.mday;
		mon = datetime.mon;
		year = datetime.year;
		wday = datetime.wday;
		yday = datetime.yday;
		utc_minoff = datetime.utc_minoff;
		utc_houroff = datetime.utc_houroff;
	}

	DateTime::DateTime(const String&datestring, const String&format)
	{
		unsigned int dscounter = 0;

		for(unsigned int i=0; i<format.length() && dscounter<datestring.length(); i++)
		{
			char c = format.charAt(i);
			if(c == '%')
			{
				i++;
				if(i < format.length())
				{
					char spec = format.charAt(i);
					switch(spec)
					{
						case 'a': //Abbreviated weekday name * : Thu
						break;

						case 'A': //Full weekday name * : Thursday
						break;

						case 'b': //Abbreviated month name * : Aug
						case 'h': //Abbreviated month name * (same as %b) : Aug
						break;

						case 'B': //Full month name * : August
						break;

						case 'c': //Date and time representation * : Thu Aug 23 14:55:02 2001
						break;

						case 'C': //Year divided by 100 and truncated to integer (00-99) : 20
						break;

						case 'd': //Day of the month, zero-padded (01-31) : 23
						break;

						case 'D': //Short MM/DD/YY date, equivalent to %m/%d/%y : 08/23/01
						break;

						case 'e': //Day of the month, space-padded ( 1-31) : 23
						break;

						case 'f': //Millisecond (000000-999999) : 023841
						break;

						case 'F': //Short YYYY-MM-DD date, equivalent to %Y-%m-%d : 2001-08-23
						break;

						case 'g': //Week-based year, last two digits (00-99) : 01
						break;

						case 'G': //Week-based year : 2001
						break;

						case 'H': //Hour in 24h format (00-23) : 14
						break;

						case 'I': //Hour in 12h format (01-12) : 02
						break;

						case 'j': //Day of the year (001-366) : 235
						break;

						case 'm': //Month as a decimal number (01-12) : 08
						break;

						case 'M': //Minute (00-59) : 55
						break;
						
						case 'n': //New-line character ('\n')
						break;

						case 'p': //AM or PM designation : PM
						break;

						case 'r': //12-hour clock time * : 02:55:02 pm
						break;

						case 'R': //24-hour HH:MM time, equivalent to %H:%M : 14:55
						break;

						case 'S': //Second (00-61) : 02
						break;

						case 't': //Horizontal-tab character ('\t')
						break;

						case 'T': //ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S : 14:55:02
						break;

						case 'u': //ISO 8601 weekday as number with Monday as 1 (1-7) : 4
						break;

						case 'U': //Week number with the first Sunday as the first day of week one (00-53) : 34
						break;

						case 'V': //ISO 8601 week number (00-53) : 34
						break;

						case 'w': //Weekday as decimal number with Sunday as 0 (0-6) : 5
						break;

						case 'W': //Week number with the first monday as the first day of week one (00-53) : 34
						break;

						case 'x': //Date representation * : 08/23/01
						break;

						case 'X': //Time representation * : 14:55:02
						break;

						case 'y': //Year, last two digits (00-99) : 01
						break;

						case 'Y': //Year : 2001
						break;

						case 'z': //ISO 8601 offset from UTC in timezone (1 minute=1, 1 hour=100) : +0100
						//If timezone cannot be termined, no characters
						break;

						case 'Z': //Timezone name or abbreviation * : CDT
						//If timezone cannot be termined, no characters
						break;

						case '%': //A % sign : %
						break;
					}
				}
			}
		}
	}

	/*DateTime(int day, int mon, int year);
	DateTime(int day, int mon, int year, int hour, int min, int sec=0, int usec=0);
	DateTime(int day, int mon, int year, int hour, int min, int sec, int usec, const DateTime&utcOffset);
	~DateTime();
		
	int getMilliseconds();
	int getSeconds();
	int getMinutes();
	int getHour();
	int getDayOfMonth();
	int getDayOfWeek();
	int getDayOfYear();
	int getMonth();
	int getYear();
	bool isDaylightSavingTime();
	DateTime getOffsetUTC();

	String getDayOfWeekString();
	String getMonthString();

	String toString();
		
	void setMilliseconds(int usec);
	void setSeconds(int sec);
	void setMinutes(int min);
	void setHour(int hour);
	void setDayOfMonth(int mday);
	void setDayOfWeek(int wday);
	void setDayOfYear(int yday);
	void setMonth(int mon);
	void setYear(int year);*/
}