
#pragma once

namespace GameLibrary
{
	class Math
	{
	public:
		//Trig
		static double sin(double radians);
		static double cos(double radians);
		static double tan(double radians);
		static double asin(double x);
		static double acos(double x);
		static double atan(double x);
		static double atan2(double x, double y);

		//Logarithmic
		static double log(double arg); //natural log
		static double log(double base, double arg);
		static double log10(double arg);

		//Power
		static double pow(double base, double exponent);
		static double sqrt(double arg);

		//Rounding and remainders
		static double ceil(double arg);
		static double floor(double arg);
		static double round(double arg);

		//Others
		static double abs(double arg);
	};
}








