
#pragma once

#include "../Time/TimeInterval.h"

namespace GameLibrary
{
	typedef void(*ValueEaseCallback)(void*);

	template<typename T>
	class ValueEase
	{
	private:
		T*value;
		T goal;
		
		TimeInterval duration;
		TimeInterval previousTime;
		TimeInterval timer;
		long double progress;

		bool easing;

		ValueEaseCallback completion;
		
	public:
		ValueEase() : ValueEase(nullptr)
		{
			//
		}
		
		ValueEase(T*value)
		{
			ValueEase::value = value;
			goal = *value;
			progress = 1;
			completion = nullptr;
			easing = false;
			timer.start();
		}

		void setValue(T*value)
		{
			ValueEase::value = value;
		}
		
		void setGoal(const T&goal, const TimeInterval&duration)
		{
			progress = nullptr;
			ValueEase::goal = goal;
			ValueEase::duration = duration;
		}

		const T& getValue() const
		{
			return value;
		}
		
		const T& getGoal() const
		{
			return goal;
		}

		void update()
		{
			if(easing && value!=nullptr)
			{
				TimeInterval elapsedTime = time - previousTime;
				long double elapsedMillis = (long double)elapsedTime.getMilliseconds();
				long double durationMillis = (long double)duration.getMilliseconds();
				if(durationMillis == 0)
				{
					progress = 1.0;
					*value = goal;
					easing = false;
					if(completion != nullptr)
					{
						completion(this);
					}
				}
				else
				{
					long double easeProgress = elapsedMillis/durationMillis;
					long double totalProgress = easeProgress + progress;
					if(totalProgress >= 1.0)
					{
						progress = 1.0;
						*value = goal;
						easing = false;
						if(completion != nullptr)
						{
							completion(this);
						}
					}
					else
					{
						long double portionRatio = easeProgress/(1.0 - progress);
						*value = (T)(((long double)(goal-*value))*portionRatio);
						progress = totalProgress;
					}
				}
			}
		}

		void pause()
		{
			timer.stop();
		}

		void resume()
		{
			timer.start();
		}
	};
}
