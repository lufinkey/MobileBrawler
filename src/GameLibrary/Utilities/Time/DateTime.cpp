
#include "DateTime.h"
#include "../ArrayList.h"
#include "../Math.h"
#include "posixtime.h"
#include "time64/time64.h"
#include <ctime>

//TODO important create separate DateTimeParser class and Locale class. DateTime should not remain in this disorganized state.
	//DateTimeParser or Locale should have separate profile or info classes on each DateTime character placeholder
	//note: top level of DateTime class is in an organized state, and is usable, and underlying code is much easier to clean up
	// than headers. Much less refactoring in other classes. There's no rush on this, but it is important.

namespace GameLibrary
{
	#define DATETIME_DAYSPERWEEK 7
	#define DATETIME_DAYSPERNORMALYEAR 365
	#define DATETIME_DAYSPERLEAPYEAR 366
	#define DATETIME_TM_BASEYEAR 1900

//DateTime strings
	#define DATETIME_LIST_MONTHS {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"}
	#define DATETIME_LIST_MONTHS_ABBR {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"}
	#define DATETIME_LIST_WEEKDAYS {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"}
	#define DATETIME_LIST_WEEKDAYS_ABBR {"sun", "mon", "tue", "wed", "thu", "fri", "sat"}
	

// DATEFORMAT ENTITY CONSTANTS


	///Abbreviated weekday name * : Thu
	#define DATEFORMAT_DAYOFWEEK_ABBR_LOCALE 'a'

	///Full weekday name * : Thursday
	#define DATEFORMAT_DAYOFWEEK_FULLNAME_LOCALE 'A'

	///Abbreviated month name * : Aug
	#define DATEFORMAT_MONTH_ABBR_LOCALE 'b'
	#define DATEFORMAT_MONTH_ABBR2_LOCALE 'h'

	///Full month name * : August
	#define DATEFORMAT_MONTH_FULLNAME_LOCALE 'B'

	///Date and time representation * : Thu Aug 23 14:55:02 2001
	#define DATEFORMAT_DATETIME_LOCALE 'c'

	///Year divided by 100 and truncated to integer (00-99) : 20
	#define DATEFORMAT_YEAR_INTOVER100 'C'

	///Day of the month, zero-padded (01-31) : 23
	#define DATEFORMAT_DAYOFMONTH_ZEROPADDED 'd'

	///Day of the month, space-padded ( 1-31) : 23
	#define DATEFORMAT_DAYOFMONTH_SPACEPADDED 'e'

	///Short MM/DD/YY date, equivalent to %m/%d/%y : 08/23/01
	#define DATEFORMAT_DATE_MM_DD_YY 'D'
	///Date representation * : 08/23/01
	#define DATEFORMAT_DATE_LOCALE 'x'

	///Microsecond (000000-999999) : 023841
	#define DATEFORMAT_MICROSECONDS 'f'

	///Short YYYY-MM-DD date, equivalent to %Y-%m-%d : 2001-08-23
	#define DATEFORMAT_DATE_YYYY_MM_DD 'F'

	///Week-based year, last two digits (00-99) : 01
	#define DATEFORMAT_WEEKBASEDYEAR_LAST2DIGITS 'g'

	///Week-based year : 2001
	#define DATEFORMAT_WEEKBASEDYEAR 'G'

	///Hour in 24h format (00-23) : 14
	#define DATEFORMAT_HOUR24 'H'

	///Hour in 12h format (01-12) : 02
	#define DATEFORMAT_HOUR12 'I'

	///Day of the year (001-366) : 235
	#define DATEFORMAT_DAYOFYEAR 'j'

	///Month as a decimal number (01-12) : 08
	#define DATEFORMAT_MONTH 'm'

	///Minute (00-59) : 55
	#define DATEFORMAT_MINUTE 'M'

	///New-line character ('\n')
	#define DATEFORMAT_NEWLINE 'n'

	///AM or PM designation : PM
	#define DATEFORMAT_AMPM 'p'

	///12-hour clock time * : 02:55:02 pm
	#define DATEFORMAT_12HOURTIME_LOCALE 'r'

	///ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S : 14:55:02
	#define DATEFORMAT_TIME_HH_MM_SS 'T'
	///Time representation * : 14:55:02
	#define DATEFORMAT_TIME_LOCALE 'X'

	///24-hour HH:MM time, equivalent to %H:%M : 14:55
	#define DATEFORMAT_HOURMINUTE_REP 'R'

	///Second (00-61) : 02
	#define DATEFORMAT_SECOND 'S'

	///Horizontal-tab character ('\t')
	#define DATEFORMAT_TAB 't'

	///ISO 8601 weekday as number with Monday as 1 (1-7) : 4
	#define DATEFORMAT_DAYOFWEEK_MONDAY1 'u'
	
	///Week number with the first Sunday as the first day of week one (00-53) : 34
	#define DATEFORMAT_WEEKOFYEAR_SUNDAY1 'U'
	
	///ISO 8601 week number (00-53) : 34
	#define DATEFORMAT_WEEKOFYEAR 'V'
	
	///Weekday as decimal number with Sunday as 0 (0-6) : 5
	#define DATEFORMAT_DAYOFWEEK_SUNDAY0 'w'
	
	///Week number with the first monday as the first day of week one (00-53) : 34
	#define DATEFORMAT_WEEKOFYEAR_MONDAY1 'W'
	
	///Year, last two digits (00-99) : 01
	#define DATEFORMAT_YEAR_LAST2DIGITS 'y'
	
	///Year : 2001
	#define DATEFORMAT_YEAR 'Y'
	
	///ISO 8601 offset from UTC in timezone (1 minute=1, 1 hour=100) : +0100
	///If timezone cannot be termined, no characters
	#define DATEFORMAT_UTCOFFSET 'z'
	
	///Timezone name or abbreviation * : CDT
	///If timezone cannot be termined, no characters
	#define DATEFORMAT_TIMEZONE_LOCALE 'Z'
	
	///A % sign : %
	#define DATEFORMAT_PERCENT '%'
	
//DateTime static functions
	
	String DateTime_createNumberString(int num, unsigned int size, char padding)
	{
		String numStr = (String)"" + num;
		while(numStr.length() < size)
		{
			numStr = (String)padding + numStr;
		}
		return numStr;
	}

	struct tm DateTime_to_structtm(const DateTime&datetime)
	{
		struct tm lcl;
		lcl.tm_sec = datetime.getSecond();
		lcl.tm_min = datetime.getMinute();
		lcl.tm_hour = datetime.getHour();
		lcl.tm_mday = datetime.getDayOfMonth();
		lcl.tm_mon = datetime.getMonth() - 1;
		lcl.tm_year = datetime.getYear() - DATETIME_TM_BASEYEAR;
		lcl.tm_wday = datetime.getDayOfWeek() - 1;
		lcl.tm_yday = datetime.getDayOfYear() - 1;
		lcl.tm_isdst = -1;
		return lcl;
	}

	bool DateTime_checkLeapYear(int year)
	{
		if((year % 4)==0 && ((year % 100)!=0 || (year % 400)==0))
		{
			return true;
		}
		return false;
	}
	
//DateTime constructors

	DateTime::DateTime()
	{
		struct timeval64 tv;
		gettimeofday64(&tv, NULL);
		Time64_T now = (Time64_T)tv.tv_sec;
		struct tm lcl = *localtime64(&now);
		struct tm gmt = *gmtime64(&now);

		Time64_T lcl_total = mktime64(&lcl);
		Time64_T gmt_total = mktime64(&gmt);
		Int64 gmt_dif = ((Int64)lcl_total - (Int64)gmt_total);

		usec = tv.tv_usec;
		sec = lcl.tm_sec;
		min = lcl.tm_min;
		hour = lcl.tm_hour;
		mday = lcl.tm_mday;
		mon = lcl.tm_mon + 1;
		year = lcl.tm_year + DATETIME_TM_BASEYEAR;
		wday = lcl.tm_wday + 1;
		yday = lcl.tm_yday + 1;
		utc_offset = (long)gmt_dif;
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
		utc_offset = datetime.utc_offset;
	}

//DateTime destructor

	DateTime::~DateTime()
	{
		//
	}

//DateTime getter functions

	int DateTime::getMicrosecond() const
	{
		return usec;
	}

	int DateTime::getSecond() const
	{
		return sec;
	}

	int DateTime::getMinute() const
	{
		return min;
	}

	int DateTime::getHour() const
	{
		return hour;
	}

	int DateTime::getDayOfMonth() const
	{
		return mday;
	}

	int DateTime::getDayOfWeek() const
	{
		return wday;
	}

	int DateTime::getDayOfYear() const
	{
		return yday;
	}

	int DateTime::getMonth() const
	{
		return mon;
	}

	int DateTime::getYear() const
	{
		return year;
	}

	long DateTime::getOffsetUTC() const
	{
		return utc_offset;
	}

	String DateTime::toString(const String&format) const
	{
		String outputString;
		for(unsigned int i=0; i<format.length(); i++)
		{
			char c = format.charAt(i);
			if(c == '%')
			{
				i++;
				char spec = format.charAt(i);
				switch(spec)
				{
					default:
					outputString += '%';
					outputString += spec;
					break;

					case DATEFORMAT_DAYOFWEEK_ABBR_LOCALE:
					{
						char* weekdayAbbrs[] = DATETIME_LIST_WEEKDAYS_ABBR;
						outputString += weekdayAbbrs[wday-1];
					}
					break;

					case DATEFORMAT_DAYOFWEEK_FULLNAME_LOCALE:
					{
						char* weekdays[] = DATETIME_LIST_WEEKDAYS;
						outputString += weekdays[wday-1];
					}
					break;

					case DATEFORMAT_MONTH_ABBR_LOCALE:
					case DATEFORMAT_MONTH_ABBR2_LOCALE:
					{
						char* monthAbbrs[] = DATETIME_LIST_MONTHS_ABBR;
						outputString += monthAbbrs[mon-1];
					}
					break;

					case DATEFORMAT_MONTH_FULLNAME_LOCALE:
					{
						char* months[] = DATETIME_LIST_MONTHS;
						outputString += months[mon-1];
					}
					break;

					case DATEFORMAT_DATETIME_LOCALE: //Thu Aug 23 14:55:02 2001
					{
						String entityformat = (String)""
											+ '%' + DATEFORMAT_DAYOFWEEK_ABBR_LOCALE + ' '
											+ '%' + DATEFORMAT_MONTH_ABBR_LOCALE + ' '
											+ '%' + DATEFORMAT_DAYOFMONTH_ZEROPADDED + ' '
											+ '%' + DATEFORMAT_HOUR24 + ':'
											+ '%' + DATEFORMAT_MINUTE + ':'
											+ '%' + DATEFORMAT_SECOND + ' '
											+ '%' + DATEFORMAT_YEAR;
						outputString += DateTime::toString(entityformat);
					}
					break;

					case DATEFORMAT_YEAR_INTOVER100:
					{
						String yearStr = DateTime_createNumberString(year, 4, '0');
						outputString += yearStr.substring(0, yearStr.length()-2);
					}
					break;

					case DATEFORMAT_DAYOFMONTH_ZEROPADDED:
					{
						String mdayStr = DateTime_createNumberString(mday, 2, '0');
						outputString += mdayStr;
					}
					break;

					case DATEFORMAT_DAYOFMONTH_SPACEPADDED:
					{
						String mdayStr = DateTime_createNumberString(mday, 2, ' ');
						outputString += mdayStr;
					}
					break;

					case DATEFORMAT_DATE_MM_DD_YY:
					case DATEFORMAT_DATE_LOCALE:
					{
						String entityformat = (String)""
											+ '%' + DATEFORMAT_MONTH + '/'
											+ '%' + DATEFORMAT_DAYOFMONTH_ZEROPADDED + '/'
											+ '%' + DATEFORMAT_YEAR_LAST2DIGITS;
						outputString += DateTime::toString(entityformat);
					}
					break;
					
					case DATEFORMAT_MICROSECONDS:
					{
						String usecStr = DateTime_createNumberString(usec, 6, '0');
						outputString += usecStr;
					}
					break;
							
					case DATEFORMAT_DATE_YYYY_MM_DD:
					{
						String entityformat = (String)""
											+ '%' + DATEFORMAT_YEAR + '-'
											+ '%' + DATEFORMAT_MONTH + '-'
											+ '%' + DATEFORMAT_DAYOFMONTH_ZEROPADDED;
						outputString += DateTime::toString(entityformat);
					}
					break;

					case DATEFORMAT_HOUR24:
					{
						String hour24Str = DateTime_createNumberString(hour, 2, '0');
						outputString += hour24Str;
					}
					break;

					case DATEFORMAT_HOUR12:
					{
						int hour12 = hour;
						if(hour12 > 12)
						{
							hour12 -= 12;
						}
						if(hour12 == 0)
						{
							hour12 = 12;
						}
						String hour12Str = DateTime_createNumberString(hour12, 2, '0');
						outputString += hour12Str;
					}
					break;

					case DATEFORMAT_DAYOFYEAR:
					{
						String ydayStr = DateTime_createNumberString(yday, 3, '0');
						outputString += ydayStr;
					}
					break;

					case DATEFORMAT_MONTH:
					{
						String monStr = DateTime_createNumberString(mon, 2, '0');
						outputString += monStr;
					}
					break;

					case DATEFORMAT_MINUTE:
					{
						String minStr = DateTime_createNumberString(min, 2, '0');
						outputString += minStr;
					}
					break;
					
					case DATEFORMAT_NEWLINE:
					{
						outputString += '\n';
					}
					break;

					case DATEFORMAT_AMPM:
					{
						String ampmStr;
						if(hour < 12)
						{
							ampmStr = "AM";
						}
						else
						{
							ampmStr = "PM";
						}
						outputString += ampmStr;
					}
					break;

					case DATEFORMAT_12HOURTIME_LOCALE: //02:55:02 pm
					{
						String entityformat = (String)""
											+ '%' + DATEFORMAT_HOUR12 + ':'
											+ '%' + DATEFORMAT_MINUTE + ':'
											+ '%' + DATEFORMAT_SECOND + ' '
											+ '%' + DATEFORMAT_AMPM;
						outputString += DateTime::toString(entityformat);
					}
					break;

					case DATEFORMAT_HOURMINUTE_REP:
					{
						String entityformat = (String)""
											+ '%' + DATEFORMAT_HOUR24 + ':'
											+ '%' + DATEFORMAT_MINUTE;
						outputString += DateTime::toString(entityformat);
					}
					break;

					case DATEFORMAT_SECOND:
					{
						String secStr = DateTime_createNumberString(sec, 2, '0');
						outputString += secStr;
					}
					break;

					case DATEFORMAT_TAB:
					{
						outputString += '\t';
					}
					break;

					case DATEFORMAT_TIME_HH_MM_SS: //14:55:02
					case DATEFORMAT_TIME_LOCALE:
					{
						String entityformat = (String)""
											+ '%' + DATEFORMAT_HOUR24 + ':'
											+ '%' + DATEFORMAT_MINUTE + ':'
											+ '%' + DATEFORMAT_SECOND;
						outputString += DateTime::toString(entityformat);
					}
					break;

					case DATEFORMAT_DAYOFWEEK_MONDAY1:
					{
						int wdayMonday1 = wday - 1;
						if(wdayMonday1 == 0)
						{
							wdayMonday1 = DATETIME_DAYSPERWEEK;
						}
						String wdayMonday1Str = DateTime_createNumberString(wdayMonday1, 1, '0');
						outputString += wdayMonday1Str;
					}
					break;

					case DATEFORMAT_WEEKOFYEAR_SUNDAY1:
					{
						/*int firstWday = 0;
						int daysSinceJan1 = yday-1;
						firstWday = wday - ((daysSinceJan1)%7);
						if(firstWday < 1)
						{
							firstWday += 7;
						}
						int wdayOffset = (7-firstWday);
						int weekNum = 0;
						if(daysSinceJan1 > wdayOffset)
						{
							int trueYday = daysSinceJan1 - wdayOffset - 1;
							weekNum = (trueYday/7) + 1;
						}*/
						int weekNum = ((((yday-1) + 7) - (wday-1)) / 7);
						String weekNumStr = DateTime_createNumberString(weekNum, 2, '0');
						outputString += weekNumStr;
					}
					break;

					case DATEFORMAT_WEEKBASEDYEAR:
					case DATEFORMAT_WEEKBASEDYEAR_LAST2DIGITS:
					case DATEFORMAT_WEEKOFYEAR:
					{
						int wyear;
						int tm_yday;
						int tm_wday;
						int w;

						wyear = year;
						tm_yday = yday-1;
						tm_wday = wday-1;

						while (true)
						{
							int  len = 0;
							int  bot = 0;
							int  top = 0;
							
							if(DateTime_checkLeapYear(wyear))
							{
								len = DATETIME_DAYSPERLEAPYEAR;
							}
							else
							{
								len = DATETIME_DAYSPERNORMALYEAR;
							}

							bot = ((tm_yday + 11 - tm_wday) % DATETIME_DAYSPERWEEK) - 3;
							top = bot - (len % DATETIME_DAYSPERWEEK);
							if (top < -3)
							{
								top += DATETIME_DAYSPERWEEK;
							}
							top += len;
							if (tm_yday >= top)
							{
								wyear++;
								w = 1;
								break;
							}
							if (tm_yday >= bot)
							{
								w = 1 + ((tm_yday - bot) / DATETIME_DAYSPERWEEK);
								break;
							}
							wyear--;
							if(DateTime_checkLeapYear(wyear))
							{
								tm_yday += DATETIME_DAYSPERLEAPYEAR;
							}
							else
							{
								tm_yday += DATETIME_DAYSPERNORMALYEAR;
							}
						}

						if (spec == DATEFORMAT_WEEKOFYEAR)
						{
							String weekofyearStr = DateTime_createNumberString(w, 2, '0');
							outputString += weekofyearStr;
						}
						else
						{
							String wyearStr = DateTime_createNumberString(wyear, 4, '0');
							if (spec == DATEFORMAT_WEEKBASEDYEAR_LAST2DIGITS)
							{
								outputString += wyearStr.substring(wyearStr.length()-2, wyearStr.length());
							}
							else //if(spec == DATEFORMAT_WEEKBASEDYEAR)
							{
								outputString += wyearStr;
							}
						}
					}
					break;

					case DATEFORMAT_DAYOFWEEK_SUNDAY0:
					{
						String wdayStr = DateTime_createNumberString(wday-1, 1, '0');
						outputString += wdayStr;
					}
					break;

					case DATEFORMAT_WEEKOFYEAR_MONDAY1:
					{
						int weekNum = 0;
						int tm_wday = wday - 1;
						int tm_yday = yday - 1;
						if(tm_wday == 0)
						{
							weekNum = (((tm_yday + 7) - 6) / 7);
						}
						else
						{
							weekNum = (((tm_yday + 7) - (tm_wday-1)) / 7);
						}
						String weekNumStr = DateTime_createNumberString(weekNum, 2, '0');
						outputString += weekNumStr;
					}
					break;

					case DATEFORMAT_YEAR_LAST2DIGITS:
					{
						String yearStr = DateTime_createNumberString(year, 4, '0');
						outputString += yearStr.substring(yearStr.length()-2, yearStr.length());
					}
					break;

					case DATEFORMAT_YEAR:
					{
						String yearStr = DateTime_createNumberString(year, 4, '0');
						outputString += yearStr;
					}
					break;

					case DATEFORMAT_UTCOFFSET:
					{
						int utc_minoffset = Math::abs(utc_offset/60);
						int utc_min = utc_minoffset%60;
						int utc_hr = utc_minoffset/60;
						String utc_hr_str = DateTime_createNumberString(utc_hr, 2, '0');
						String utc_min_str = DateTime_createNumberString(utc_min, 2, '0');
						char prefix = '+';
						if(utc_offset < 0)
						{
							prefix = '-';
						}
						outputString += (String)"" + prefix + utc_hr_str + utc_min_str;
					}
					break;

					/*case DATEFORMAT_TIMEZONE_LOCALE:
					{
						//TODO figure out how to get the time zone offset abbreviation
					}
					break;*/

					case DATEFORMAT_PERCENT:
					{
						outputString += '%';
					}
					break;
				}
			}
			else
			{
				outputString += c;
			}
		}
		return outputString;
	}
}