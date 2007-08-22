#ifndef _CMDLINEUTLY_C
#define _CMDLINEUTLY_C

using namespace std;

#include <vector>
#include <string>

#include "CmdLineUtly.h"

vector <string> ProcessFlatCommandLine(int ArgumentCount, char *ArgLine[])
//	ProcessFlatCommandLine takes the commandline variables and breaks the strings down straight into a string vector
//	no interpreatation is done as to what values belong to what options since each string is treated blindly.

//	Usage:  SomeDeclaredVector = ProcessFlatCommandLine(argc, argv);

//	Input:  a count for the number of strings the command line was broken into by the operating system. Must be greater than 0.
//		a pointer to an array of character pointers, this would be supplied by the operating system to the main(int, char *[]) function.

//	Ouput:	a vector of strings populated by the strings found in ArgLine, without the first word, which should have been the Program name
{
	if (ArgumentCount <= 0)
	{
		return(vector<string>(0));
	}

	vector <string> CmdLineStrings(ArgumentCount - 1, "");	
	// string vector of size one less than the size of ArgLine filled with nothing

	for (int ArgIndex = 0; ArgIndex < CmdLineStrings.size(); ArgIndex++)
	{
		CmdLineStrings[ArgIndex] = ArgLine[ArgIndex + 1];
	}

	return(CmdLineStrings);
}

#endif
