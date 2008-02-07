#ifndef _STRUTLY_H
#define _STRUTLY_H

/*!
 *  \defgroup StrUtly String Utilities
 *  \brief StrUtly contains a variety of useful string manipulation
 *         functions.
 *
 *  Some of these functions should be deprecated or only used for 
 *  special purposes.  They were originally developed without the
 *  knowledge of various built-in functions.  Now, many of them
 *  are merely wrappers for those functions.
 *
 *  @{
*/

/*! \file StrUtly.h
 *
*/


#include <string>
#include <vector>
#include <cctype>	// for off_t, size_t



/*! \name String to Numeric
 *  For obtaining the numeric value that a string represents
*/
//@{
int StrToInt(const string &);
long int StrToLong(const string &);
double StrToDouble(const string &);
size_t StrToSize_t(const string &);
float StrToFloat(const string &);
off_t StrToOff_t(const string &);

vector <int> StrToInt(const vector <string> &);
vector <long int> StrToLong(const vector <string> &);
vector <double> StrToDouble(const vector <string> &);
vector <size_t> StrToSize_t(const vector <string> &);
vector <float> StrToFloat(const vector <string> &);
vector <off_t> StrToOff_t(const vector <string> &);
//@}




/*! \name Numeric to String
 *  Produce string representation of a numeric value.
*/
//@{
string IntToStr(const int &);
string LongToStr(const long int &);
string DoubleToStr(const double &, const int &SigDigs = 6);
string Size_tToStr(const size_t &);
string FloatToStr(const float &, const int &SigDigs = 6);

vector <string> IntToStr(const vector <int> &);
vector <string> LongToStr(const vector <long int> &);
vector <string> DoubleToStr(const vector <double> &, const int &SigDigs = 6);
vector <string> Size_tToStr(const vector <size_t> &);
vector <string> FloatToStr(const vector <float> &, const int &SigDigs = 6);
//@}


/*! \name Whitespace Strippers
 *  For stripping leading and trailing white spaces from your strings.
*/
//@{
void StripWhiteSpace(string &FatString);
void StripWhiteSpace(vector <string>&);
string RipWhiteSpace(string);
vector <string> RipWhiteSpace(vector <string>);
//@}

/*! \name Delimited List Manipulators
 *  For the purpose of breaking a string into a vector
 *  and joining them back together as one string.
*/
//@{
vector <string> TakeDelimitedList(const string &, const char &);
vector <string> TakeDelimitedList(const string &, const string &);
string GiveDelimitedList(const vector <string> &, const char &);
string GiveDelimitedList(const vector <string> &, const string &);
//@}

/*! \name Miscellanious
 *  Performs basic manipulation of strings
*/
//@{
string StrToUpper(string);
string StrToLower(string);
string FlipString(string);


vector <string> StrToUpper(vector <string>);
vector <string> StrToLower(vector <string>);
vector <string> FlipString(vector <string>);


bool OnlyDigits(const string &WordRep);
bool OnlyAlpha(const string &WordRep);
//@}

/*! @} */	// end group StrUtly
#endif
