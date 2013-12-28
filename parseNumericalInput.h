#ifndef PARSENUMERICALINPUT_H
#define PARSENUMERICALINPUT_H

// Enter Two Ints class header.
// The purpose of this class - implement the interface 
// to enter two integer values from keyboard

#include <iostream>
#include <string>
#include <vector>

class parseNumericalInput
{
private:
	std::vector<int> values;
    std::string delimiters;
    bool isSubstringNumerical
		(
			const std::string&,
			const std::string::size_type&, 
			const std::string::size_type&
		) const; 
    
public:
	// default delimiters are spaces or tabs
	parseNumericalInput(const std::string& delimiters = " \t");
    std::istream& parseNonNegativeNumbers(std::istream&, int);
    const std::vector<int> getValues() const;
};

#endif