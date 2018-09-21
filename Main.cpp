#include <iostream>
#include <string>
#include "Commands.h"

using namespace std;

int main()
{
	int i = 0;
	string inputString;
	do 
	{
		getline(cin, inputString);
		commands(inputString);
		//cout << " " << inputString << endl;
	} while (!cin.eof());
	return 0;
}