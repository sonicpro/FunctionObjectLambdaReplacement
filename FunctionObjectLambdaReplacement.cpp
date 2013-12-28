// FunctionObjectLambdsReplacement - paraphrase of "Lambda Expresions in C++" MSDN example.
// Read three numbers one by one and prints where each of them even or odd.

#include "parseNumericalInput.h"
#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::domain_error;
using std::endl;
using std::for_each;
using std::getchar;
using std::istream;
using std::vector;

int main()
{
	if(!cin)
		cin.clear();

	if(cin.rdbuf()->in_avail() > 0)
		cin.ignore(cin.rdbuf()->in_avail());

	cout << "Enter three numbers one by one pressing 'Enter' key after each of the numbers" << endl;
	
	vector<int> vec = vector<int>(3);

	for(int i = 0; i != 3; ++i)
	{
		bool inputResult = false;
		parseNumericalInput parser = parseNumericalInput();
		while(!inputResult)
		{
			try
			{
				const istream& tempInput = parser.parseNonNegativeNumbers(cin, 1);
				inputResult = !(tempInput.fail() || tempInput.eof());
			}
			catch(domain_error e)
			{
				cout << e.what() << endl;
				continue;
			}
		}

		vec[i] = parser.getValues()[0];
	}

	// The lambda syntax tells that it doesn't capture variables from the enclosed scope, have one int parameter and doesn't return a value.
	for_each(vec.begin(), vec.end(), [](int n) { cout << (n % 2 == 0 ? "even" : "odd") << endl; });
	cout << "Press 'Enter' key to exit";
	getchar();
}
