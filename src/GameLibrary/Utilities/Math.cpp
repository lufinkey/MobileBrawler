
#include "Math.h"
#include <cmath>

namespace GameLibrary
{
	//Trig
	double Math::sin(double radians){ return std::sin(radians); }
	double Math::sin(float radians){ return std::sin(radians); }
	double Math::sin(long float radians){ return std::sin(radians); }
	double Math::cos(double radians){ return std::cos(radians); }
	double Math::cos(float radians){ return std::cos(radians); }
	double Math::cos(long float radians){ return std::cos(radians); }
	double Math::tan(double radians){ return std::tan(radians); }
	double Math::tan(float radians){ return std::tan(radians); }
	double Math::tan(long float radians){ return std::tan(radians); }
	double Math::asin(double x){ return std::asin(x); }
	double Math::asin(float x){ return std::asin(x); }
	double Math::asin(long float x){ return std::asin(x); }
	double Math::acos(double x){ return std::acos(x); }
	double Math::acos(float x){ return std::acos(x); }
	double Math::acos(long float x){ return std::acos(x); }
	double Math::atan(double x){ return std::atan(x); }
	double Math::atan(float x){ return std::atan(x); }
	double Math::atan(long float x){ return std::atan(x); }
	double Math::atan2(double x, double y){ return std::atan2(x, y); }
	double Math::atan2(float x, float y){ return std::atan2(x, y); }
	double Math::atan2(long float x, long float y){ return std::atan2(x, y); }

	//Logarithmic
	double Math::log(double arg){ return std::log(arg); }
	double Math::log(float arg){ return std::log(arg); }
	double Math::log(long float arg){ return std::log(arg); }
	double Math::log(double base, double arg){ return std::log(arg) / std::log(base); }
	double Math::log(float base, float arg){ return std::log(arg) / std::log(base); }
	double Math::log(long float base, long float arg){ return std::log(arg) / std::log(base); }
	double Math::log10(double arg){ return std::log10(arg); }
	double Math::log10(float arg){ return std::log10(arg); }
	double Math::log10(long float arg){ return std::log10(arg); }

	//Powers
	double Math::pow(double base, double exponent){ return std::pow(base, exponent); }
	double Math::pow(float base, float exponent){ return std::pow(base, exponent); }
	double Math::pow(long float base, long float exponent){ return std::pow(base, exponent); }
	double Math::sqrt(double arg){ return std::sqrt(arg); }
	double Math::sqrt(float arg){ return std::sqrt(arg); }
	double Math::sqrt(long float arg){ return std::sqrt(arg); }

	//Rounding and remainders
	double Math::ceil(double arg){ return std::ceil(arg); }
	double Math::ceil(float arg){ return std::ceil(arg); }
	double Math::ceil(long float arg){ return std::ceil(arg); }
	double Math::floor(double arg){ return std::floor(arg); }
	double Math::floor(float arg){ return std::floor(arg); }
	double Math::floor(long float arg){ return std::floor(arg); }
	double Math::round(double arg){ return std::round(arg); }
	double Math::round(float arg){ return std::round(arg); }
	double Math::round(long float arg){ return std::round(arg); }

	//Others
	double Math::abs(double arg){ return std::abs(arg); }
	double Math::abs(float arg){ return std::abs(arg); }
	double Math::abs(long float arg){ return std::abs(arg); }
	double Math::abs(int arg){ return std::abs(arg); }

}

