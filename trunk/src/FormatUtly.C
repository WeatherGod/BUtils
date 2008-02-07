#ifndef _FORMATUTLY_C
#define _FORMATUTLY_C

using namespace std;

/*! \file FormatUtly.C
 *  \ingroup FormatUtly
 *
*/

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
