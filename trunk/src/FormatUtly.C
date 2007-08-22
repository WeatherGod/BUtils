#ifndef _FORMATUTLY_C
#define _FORMATUTLY_C

using namespace std;

//  these functions are to assist in formatting output to a LINUX terminal screen
//  see the manpage on console_codes for info

#include <string>
#include "FormatUtly.h"

string Bold(const string &TheLine)
{
	return("\033[1m" + TheLine + "\033[22m");
}

string Dim(const string &TheLine)
{
	return("\033[2m" + TheLine + "\033[22m");
}

string Underline(const string &TheLine)
{
	return("\033[4m" + TheLine + "\033[24m");
}

string Blink(const string &TheLine)
{
	return("\033[5m" + TheLine + "\033[25m");
}


#endif
