// parseNumericalInput class definitions

#include "parseNumericalInput.h"
#include <cctype>
#include <stdexcept>

using std::cout;
using std::domain_error;
using std::endl;
using std::getline;
using std::istream;
using std::isdigit;
using std::string;
using std::vector;

parseNumericalInput::parseNumericalInput (const string& delimiters):
	delimiters(delimiters)
{
}  
// returns whether substring numerical or not
bool parseNumericalInput::isSubstringNumerical
	(
		const string& buffer,
		const string::size_type& begIdx, 
		const string::size_type& endIdx
	) const
{
	for(string::size_type i = begIdx; i < endIdx; ++i)
	{
		if(!isdigit(buffer.at(i)))
			return false;
	}
	return true;
}
istream& parseNumericalInput::parseNonNegativeNumbers(istream& in, int numbersCount)
{
	// if an input stream is in bad state, do nothing
	if(in)
	{
		string buffer;
		while(getline(in, buffer))
		{
			// if an empty string entered, show the message to start a next attempt
			if(buffer.empty() || buffer.find_first_not_of(delimiters) == string::npos)
			{
				cout << "Please enter the data requested" << endl;
				continue;
			}
			else
			{
				std::string::size_type begIdx;
				std::string::size_type endIdx = 0;
				// loop invariant: number of numbers parsed is i
				for(int i = 0; i < numbersCount; ++i)
				{
					// the beginning of the next number search:
					begIdx = buffer.find_first_not_of(delimiters, endIdx);
					endIdx = buffer.find_first_of(delimiters, begIdx);
					if(endIdx == string::npos)
						endIdx = buffer.length();
					if(begIdx == string::npos)
					{
						char buf[12];
						_itoa_s(numbersCount, buf, 12, 10);
						string message("Number of values entered is lower than " + static_cast<string>(buf));
						throw domain_error(message);
					}
					if(!isSubstringNumerical(buffer, begIdx, endIdx))
						throw domain_error("Entered value is not numerical");
					values.push_back
						(
							atoi(buffer.substr(begIdx, endIdx - begIdx).c_str())
						);
				}
			}
			return in;
		}
		// if the input stream got a bad state for some reason (end of file, etc.)
		// return it in a bad state to indicate a bad input
		return in;
	}
	else
		return in;
}
const vector<int> parseNumericalInput::getValues() const
{
	return values;
}
