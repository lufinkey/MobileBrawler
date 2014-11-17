
#pragma once

namespace GameLibrary
{
	class Math
	{
	public:
		//Trig
		static double sin(double radians);
		static float sin(float radians);
		static long float sin(long float radians);
		static double cos(double radians);
		static float cos(float radians);
		static long float cos(long float radians);
		static double tan(double radians);
		static float tan(float radians);
		static long float tan(long float radians);
		static double asin(double x);
		static float asin(float x);
		static long float asin(long float x);
		static double acos(double x);
		static float acos(float x);
		static long float acos(long float x);
		static double atan(double x);
		static float atan(float x);
		static long float atan(long float x);
		static double atan2(double x, double y);
		static float atan2(float x, float y);
		static long float atan2(long float x, long float y);

		//Logarithmic
		static double log(double arg); //natural log
		static float log(float arg); //natural log
		static long float log(double float arg); //natural log
		static double log(double base, double arg);
		static float log(float base, float arg);
		static long float log(long float base, long float arg);
		static double log10(double arg);
		static float log10(float arg);
		static long float log10(long float arg);

		//Power
		static double pow(double base, double exponent);
		static float pow(float base, float exponent);
		static long float pow(long float base, long float exponent);
		static double sqrt(double arg);
		static float sqrt(float arg);
		static long float sqrt(long float arg);

		//Rounding and remainders
		static double ceil(double arg);
		static float ceil(float arg);
		static long float ceil(long float arg);
		static double floor(double arg);
		static float floor(float arg);
		static long float floor(long float arg);
		static double round(double arg);
		static float round(float arg);
		static long float round(long float arg);

		//Others
		static double abs(double arg);
		static float abs(float arg);
		static long float abs(long float arg);
		static int abs(int arg);
	};
}








