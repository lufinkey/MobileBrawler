
#include "GameLibrary/Utilities/String.h"
#include "GameLibrary/Utilities/ArrayList.h"
#include "GameLibrary/Utilities/Math.h"
#include <iostream> //just for now since I haven't finished the Console class

using namespace GameLibrary;

int main(int argc, char *argv[])
{
	//Test math function
	std::cout << Math::sin(5.0f) << std::endl;

	//int ArrayList test
	ArrayList<int> arr;
	arr.add(4);
	arr.add(1);
	arr.add(5);

	//printing int ArrayList size
	std::cout << "arr.size() = " << arr.size() << std::endl;

	//printing int ArrayList
	for(unsigned int i=0; i<arr.size(); i++)
	{
		std::cout << arr.get(i) << ", ";
	}
	std::cout << std::endl; //new line

	//String ArrayList test
	ArrayList<String> arr2;
	arr2.add("hello");
	arr2.add("pasdf");
	arr2.add("wfads");
	arr2.add("tasdf");
	
	//printing String ArrayList size
	std::cout << "arr2.size() = " << arr2.size() << std::endl;

	//printing String ArrayList
	for(unsigned int i=0; i<arr2.size(); i++)
	{
		//ArrayList contents can be gotten using either the get function or the [] operator
		std::cout << arr2[i] << ", ";
	}
	std::cout << std::endl; //new line

	system("PAUSE"); //"press any key to continue..." prompt, just so we can see the output
}
