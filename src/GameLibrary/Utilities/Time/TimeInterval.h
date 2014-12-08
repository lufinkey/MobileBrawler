
#pragma once

namespace GameLibrary
{
	class TimeInterval
	{
	private:
		long long milliseconds;
		long long lastmillis;
		bool running;

		void update();

	public:
		TimeInterval();
		TimeInterval(const TimeInterval&);
		TimeInterval(long long milliseconds);
		~TimeInterval();

		void start();
		void stop();
		void reset();

		long long getMilliseconds();
		long long getMilliseconds() const;
	};
}