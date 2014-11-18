
#pragma once

namespace GameLibrary
{
	class Math
	{
	public:
		static const double PI;

		//Trig
		static double sin(double radians);
		static float sin(float radians);
		static long double sin(long double radians);
		static double cos(double radians);
		static float cos(float radians);
		static long double cos(long double radians);
		static double tan(double radians);
		static float tan(float radians);
		static long double tan(long double radians);
		static double asin(double sin);
		static float asin(float sin);
		static long double asin(long double sin);
		static double acos(double cos);
		static float acos(float cos);
		static long double acos(long double cos);
		static double atan(double tan);
		static float atan(float tan);
		static long double atan(long double tan);
		static double atan2(double x, double y);
		static float atan2(float x, float y);
		static long double atan2(long double x, long double y);

		//Logarithmic
		static double log(double arg); //natural log
		static float log(float arg); //natural log
		static long double log(long double arg); //natural log
		static double log(double base, double arg);
		static float log(float base, float arg);
		static long double log(long double base, long double arg);
		static double log10(double arg);
		static float log10(float arg);
		static long double log10(long double arg);

		//Power
		static double pow(double base, double exponent);
		static float pow(float base, float exponent);
		static long double pow(long double base, long double exponent);
		static double sqrt(double arg);
		static float sqrt(float arg);
		static long double sqrt(long double arg);

		//Rounding and remainders
		static double ceil(double arg);
		static float ceil(float arg);
		static long double ceil(long double arg);
		static double floor(double arg);
		static float floor(float arg);
		static long double floor(long double arg);
		static double round(double arg);
		static float round(float arg);
		static long double round(long double arg);

		//Absolute Value
		static double abs(double arg);
		static float abs(float arg);
		static long double abs(long double arg);
		static int abs(int arg);

		//Angle Conversions
		static double degtorad(double deg);
		static float degtorad(float deg);
		static long double degtorad(long double deg);
		static double radtodeg(double rad);
		static float radtodeg(float rad);
		static long double radtodeg(long double rad);
	};
}








