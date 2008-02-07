#ifndef _FORMATUTLY_H
#define _FORMATUTLY_H

/*! \defgroup FormatUtly Formatting Utility
 *  \brief Assist in formatting output to a linux terminal screen
 *
 *  See the manpage on 'console_codes' for information
 *
 *  @{
*/

/*! \file FormatUtly.h
 *
*/
#include <string>

string Bold(const string &TheLine);
string Dim(const string &TheLine);
string Underline(const string &TheLine);
string Blink(const string &TheLine);

/*! @} */	// end of FormatUtly group

#endif
