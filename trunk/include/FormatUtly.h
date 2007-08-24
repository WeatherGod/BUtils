#ifndef _FORMATUTLY_H
#define _FORMATUTLY_H

//  these functions are to assist in formatting output to a LINUX terminal screen
//  see the manpage on console_codes for info

#include <string>

string Bold(const string &TheLine);
string Dim(const string &TheLine);
string Underline(const string &TheLine);
string Blink(const string &TheLine);

#endif
