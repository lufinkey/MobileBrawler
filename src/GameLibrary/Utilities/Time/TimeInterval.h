
#pragma once

#include "../String.h"

namespace GameLibrary
{
	class TimeInterval
	{
	public:
		TimeInterval();
		TimeInterval(const TimeInterval&);
		explicit TimeInterval(long long milliseconds);
		~TimeInterval();
		
		TimeInterval& operator=(const TimeInterval&);
		
		bool equals(const TimeInterval&) const;
		bool operator==(const TimeInterval&) const;
		bool operator!=(const TimeInterval&) const;
		
		bool operator<(const TimeInterval&) const;
		bool operator<=(const TimeInterval&) const;
		bool operator>(const TimeInterval&) const;
		bool operator>=(const TimeInterval&) const;

		TimeInterval operator+(const TimeInterval&) const;
		TimeInterval operator-(const TimeInterval&) const;

		TimeInterval& operator+=(const TimeInterval&);
		TimeInterval& operator-=(const TimeInterval&);
		
		void start();
		void stop();
		void reset();
		
		long long getMilliseconds() const;
		
		String toString() const;
		
	private:
		mutable long long milliseconds;
		mutable long long lastmillis;
		bool running;
		
		void update() const;
	};
}