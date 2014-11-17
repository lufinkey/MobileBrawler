
#include "Math.h"
#include <cmath>

namespace GameLibrary
{
	const double Math::PI = 3.141592654;

	//Trig
	double Math::sin(double radians){ return std::sin(radians); }
	float Math::sin(float radians){ return std::sin(radians); }
	long double Math::sin(long double radians){ return std::sin(radians); }
	double Math::cos(double radians){ return std::cos(radians); }
	float Math::cos(float radians){ return std::cos(radians); }
	long double Math::cos(long double radians){ return std::cos(radians); }
	double Math::tan(double radians){ return std::tan(radians); }
	float Math::tan(float radians){ return std::tan(radians); }
	long double Math::tan(long double radians){ return std::tan(radians); }
	double Math::asin(double x){ return std::asin(x); }
	float Math::asin(float x){ return std::asin(x); }
	long double Math::asin(long double x){ return std::asin(x); }
	double Math::acos(double x){ return std::acos(x); }
	float Math::acos(float x){ return std::acos(x); }
	long double Math::acos(long double x){ return std::acos(x); }
	double Math::atan(double x){ return std::atan(x); }
	float Math::atan(float x){ return std::atan(x); }
	long double Math::atan(long double x){ return std::atan(x); }
	double Math::atan2(double x, double y){ return std::atan2(x, y); }
	float Math::atan2(float x, float y){ return std::atan2(x, y); }
	long double Math::atan2(long double x, long double y){ return std::atan2(x, y); }

	//Logarithmic
	double Math::log(double arg){ return std::log(arg); }
	float Math::log(float arg){ return std::log(arg); }
	long double Math::log(long double arg){ return std::log(arg); }
	double Math::log(double base, double arg){ return std::log(arg) / std::log(base); }
	float Math::log(float base, float arg){ return std::log(arg) / std::log(base); }
	long double Math::log(long double base, long double arg){ return std::log(arg) / std::log(base); }
	double Math::log10(double arg){ return std::log10(arg); }
	float Math::log10(float arg){ return std::log10(arg); }
	long double Math::log10(long double arg){ return std::log10(arg); }

	//Powers
	double Math::pow(double base, double exponent){ return std::pow(base, exponent); }
	float Math::pow(float base, float exponent){ return std::pow(base, exponent); }
	long double Math::pow(long double base, long double exponent){ return std::pow(base, exponent); }
	double Math::sqrt(double arg){ return std::sqrt(arg); }
	float Math::sqrt(float arg){ return std::sqrt(arg); }
	long double Math::sqrt(long double arg){ return std::sqrt(arg); }

	//Rounding and remainders
	double Math::ceil(double arg){ return std::ceil(arg); }
	float Math::ceil(float arg){ return std::ceil(arg); }
	long double Math::ceil(long double arg){ return std::ceil(arg); }
	double Math::floor(double arg){ return std::floor(arg); }
	float Math::floor(float arg){ return std::floor(arg); }
	long double Math::floor(long double arg){ return std::floor(arg); }
	double Math::round(double arg){ return std::round(arg); }
	float Math::round(float arg){ return std::round(arg); }
	long double Math::round(long double arg){ return std::round(arg); }

	//Others
	double Math::abs(double arg){ return std::abs(arg); }
	float Math::abs(float arg){ return std::abs(arg); }
	long double Math::abs(long double arg){ return std::abs(arg); }
	int Math::abs(int arg){ return std::abs(arg); }

}

