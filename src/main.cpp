
#include <iostream>
using namespace std;


class Math
{
public:
	double sin(double radians);
};

#include <cmath>

double Math::sin(double radians)
{
	return sin(radians);
}





//using namespace GameLibrary;

int main(int argc, char *argv[])
{
	Math Math1;
	cout << Math1.sin(5) << '\n';
	system("pause");
}
