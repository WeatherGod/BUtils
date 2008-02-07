#ifndef _STRUTLY_C
#define _STRUTLY_C
using namespace std;

/*! \file StrUtly.C
 *  \ingroup StrUtly
 *
*/


#include <string>
#include <vector>
#include <cctype>	// for off_t, size_t
#include <algorithm>	// for count(), reverse()
#include <cmath>	// for pow(), NAN
#include <cctype>	// for toupper(), tolower(), isspace()
#include <cstdlib>	// for atoi(), atof(), strtoul(), free()
#include <cstdio>	// for asprintf()
#include <errno.h>

#include "StrUtly.h"

/*! \brief Removes any whitespaces from the beginning and the end of a string.
 *
 *  A whitespace is defined by the function isspace().
 *  This function is similar to RipWhiteSpace(string), but will modify the
 *  given string instead of returning a stripped string.
 *
 *  \param FatString	String that will have its leading and trailing whitespaces removed.
 *
 */
void StripWhiteSpace(string &FatString)
{
	if (FatString.empty())
	{
		// no need to do anything, right?
		return;
	}

	string::iterator LastNonSpaceChar(FatString.end() - 1);
	while (LastNonSpaceChar != FatString.begin() && isspace(*LastNonSpaceChar))
	{
		LastNonSpaceChar--;
	}
	
	FatString.erase(LastNonSpaceChar + 1, FatString.end());


	string::iterator FirstNonSpaceChar(FatString.begin());
	while (FirstNonSpaceChar != FatString.end() && isspace(*FirstNonSpaceChar))
        {
                FirstNonSpaceChar++;
        }

	FatString.erase(FatString.begin(), FirstNonSpaceChar);
}



/*! \brief Removes any whitespaces from the beginning and the end of each string in the vector.
 *
 *  A whitespace is defined by the function isspace().
 *  This function is similar to RipWhiteSpace(vector<string>), but will modify the
 *  given vector of strings instead of returning a copy.
 *
 *  \param FatVector    Vector of strings that will have the leading and trailing whitespaces removed
 *                      from each member.
 *
 */
void StripWhiteSpace(vector <string> &FatVector)
{
	for (vector<string>::iterator AFatString = FatVector.begin(); AFatString != FatVector.end(); AFatString++)
	{
		StripWhiteSpace(*AFatString);
	}
}


/*! \brief Removes any whitespaces from the beginning and the end of a string.
 *
 *  A whitespace is defined by the function isspace().
 *  This function is similar to StripWhiteSpace(string&), but will return the
 *  stripped string instead of modifying the given string.
 *
 *  \param FatString    String that will have its leading and trailing whitespaces removed.
 *  \return 		Stripped version of FatString string
 */
string RipWhiteSpace(string FatString)
{
	StripWhiteSpace(FatString);
	return(FatString);
}


/*! \brief Removes any whitespaces from the beginning and the end of each string in the vector.
 *
 *  A whitespace is defined by the function isspace().
 *  This function is similar to RipWhiteSpace(const vector<string>&), but will modify the
 *  given vector of strings instead of returning a copy.
 *
 *  \param FatVector    Vector of strings that will have the leading and trailing whitespaces removed
 *                      from each member.
 *  \return		Copy of the vector with stripped strings.
 *
 */
vector <string> RipWhiteSpace(vector <string> FatVector)
{
	StripWhiteSpace(FatVector);
	return(FatVector);
}

/*! \brief Converts a string into an integer.
 *
 *  \param Temp		String that supposedly contains a string representation of a number.
 *  \return		An integer corresponding to the string representation or 0 on error.
 *  \warning		This function does no error checking and will return a valid number (0)
 *                      on error.
*/
int StrToInt(const string &Temp)
{
	return(atoi(Temp.c_str()));
}

/*! \brief Converts a string into a long integer.
 *
 *  \param Temp         String that supposedly contains a string representation of a number.
 *  \return             A long integer corresponding to the string representation or 0 on error.
 *  \warning            This function does no error checking and will return a valid number (0)
 *                      on error.
*/
long int StrToLong(const string &Temp)
{
	return(atol(Temp.c_str()));
}

/*! \brief Converts a string into a double-percision number.
 *
 *  This is a slightly specialized function.  If the string is
 *  an invalid representation of a number, it will return NAN.
 *  In addition to already supporting representations of NAN or INF,
 *  this function also recognizes MySQL's null (\N) as NAN.
 *  \param Temp         String that supposedly contains a string representation of a number.
 *  \return             A double-percision number corresponding to the string representation 
 *			or NAN on error.
*/
double StrToDouble(const string &Temp)
{
	if (Temp.empty() || Temp == "\\N")
	{
		// this is support for the mySQL's Null.  I will treat them like NaNs.
		return(NAN);
	}

	char* EndPointer;
        const int TempErrno = errno;
        errno = 0;
	const double TempVal = strtod(Temp.c_str(), &EndPointer);

	if (errno == 0)
	{
		errno = TempErrno;
		return(TempVal);
	}
	else
	{
		errno = TempErrno;
		return(NAN);
	}
}

/*! \brief Converts a string into a size_t number.
 *
 *  This is a slightly specialized function.  If the string is
 *  an invalid representation of a number, it will return string::npos.
 *  \param Temp         String that supposedly contains a string representation of a number.
 *  \return             A size_t number corresponding to the string representation or string::npos on error.
 *  \warning            string::npos is a valid number, and it is being used as an error value.
*/
size_t StrToSize_t(const string &Temp)
{
	if (Temp.empty()|| StrToUpper(Temp) == "STRING::NPOS")
	{
		return(string::npos);
	}

	char* EndPointer;
	const int TempErrno = errno;
	errno = 0;
	const size_t TempVar = strtoul(Temp.c_str(), &EndPointer, 10);

	if (errno == 0)
	{
		errno = TempErrno;
		return(TempVar);
	}
	else
	{
		errno = TempErrno;
		return(string::npos);
	}
}

/*! \brief Converts a string into an off_t number.
 *
 *  Note that this function is a functional stub.  It merely
 *  calls StrToInt(const string&).  Maybe it will become explicit later.
 *
 *  \todo Use StrToLong() instead... I think...
 *
 *  \param Temp         String that supposedly contains a string representation of a number.
 *  \return             An off_t number corresponding to the string representation or 0 on error.
 *  \warning            This function does no error checking and will return a valid number (0)
 *                      on error.
*/
off_t StrToOff_t(const string &Temp)
{
	return((off_t) StrToInt(Temp));
}

/*! \brief Converts a string into a single-percision number.
 *
 *  This is a slightly specialized function.  If the string is
 *  an invalid representation of a number, it will return NAN.
 *  In addition to already supporting representations of NAN or INF,
 *  this function also recognizes MySQL's null (\N) as NAN.
 *  \param Temp         String that supposedly contains a string representation of a number.
 *  \return             A single-percision number corresponding to the string representation 
 *                      or NAN on error.
*/
float StrToFloat(const string &Temp)
{
	if (Temp.empty() || Temp == "\\N")
        {
                // this is support for the mySQL's Null.  I will treat them like NaNs.
                return(NAN);
        }

        char* EndPointer;
        const int TempErrno = errno;
        errno = 0;
        const float TempVal = strtof(Temp.c_str(), &EndPointer);

        if (errno == 0)
        {
                errno = TempErrno;
                return(TempVal);
        }
        else
        {
                errno = TempErrno;
                return(NAN);
        }
}

/*! \brief Converts a vector of strings into a vector of integers.
 *
 *  This function merely uses StrToInt(const string&) upon each element of a vector, returning a vector.
 *  \param TempVals     Strings that supposedly contains a string representations of numbers.
 *  \return             A vector of integers corresponding to the string representations.
 *  \warning            This function does no error checking and will return a valid number (0)
 *                      on error.
*/
vector <int> StrToInt(const vector <string> &TempVals)
{
	vector <int> NewVals(TempVals.size());
	vector<string>::const_iterator AStrVal(TempVals.begin());

	for (vector<int>::iterator ANewVal(NewVals.begin()); 
	     ANewVal != NewVals.end();
	     ANewVal++, AStrVal++)
	{
		*ANewVal = StrToInt(*AStrVal);
	}

	return(NewVals);
}

/*! \brief Converts a vector of strings into a vector of long integers.
 *
 *  This function merely uses StrToLong(const string&) upon each element of a vector, returning a vector.
 *  \param TempVals     Strings that supposedly contains a string representations of numbers.
 *  \return             A vector of long integers corresponding to the string representations.
 *  \warning            This function does no error checking and will return a valid number (0)
 *                      on error.
*/
vector <long int> StrToLong(const vector <string> &TempVals)
{
        vector <long int> NewVals(TempVals.size());
        vector<string>::const_iterator AStrVal(TempVals.begin());

        for (vector<long int>::iterator ANewVal(NewVals.begin());
	     ANewVal != NewVals.end();
	     ANewVal++, AStrVal++)
        {
                *ANewVal = StrToLong(*AStrVal);
        }

        return(NewVals);
}

/*! \brief Converts a vector of strings into a vector of double-presision numbers.
 *
 *  This function merely uses StrToDouble(const string&) upon each element of a vector, returning a vector.
 *  \param TempVals     Strings that supposedly contains a string representations of numbers.
 *  \return             A vector of integers corresponding to the string representations.
*/
vector <double> StrToDouble(const vector <string> &TempVals)
{
        vector <double> NewVals(TempVals.size());
        vector<string>::const_iterator AStrVal(TempVals.begin());

        for (vector<double>::iterator ANewVal(NewVals.begin()); 
	     ANewVal != NewVals.end();
	     ANewVal++, AStrVal++)
        {
                *ANewVal = StrToDouble(*AStrVal);
        }

        return(NewVals);
}

/*! \brief Converts a vector of strings into a vector of size_t numbers.
 *
 *  This function merely uses StrToSize_t(const string&) upon each element of a vector, returning a vector.
 *  \param TempVals     Strings that supposedly contains a string representations of numbers.
 *  \return             A vector of integers corresponding to the string representations.
 *  \warning            string::npos is returned for invalid values, however, string::npos
 *                      itself represents a valid value.
*/
vector <size_t> StrToSize_t(const vector <string> &TempVals)
{
        vector <size_t> NewVals(TempVals.size());
        vector<string>::const_iterator AStrVal(TempVals.begin());

        for (vector<size_t>::iterator ANewVal(NewVals.begin()); 
	     ANewVal != NewVals.end();
	     ANewVal++, AStrVal++)
        {
                *ANewVal = StrToSize_t(*AStrVal);
        }

        return(NewVals);
}

/*! \brief Converts a vector of strings into a vector of off_t numbers.
 *
 *  This function merely uses StrToOff_t(const string&) upon each element of a vector, returning a vector.
 *  \param TempVals     Strings that supposedly contains a string representations of numbers.
 *  \return             A vector of off_t corresponding to the string representations.
 *  \warning            This function does no error checking and will return a valid number (0)
 *                      on error.
*/
vector <off_t> StrToOff_t(const vector <string> &TempVals)
{
	vector <off_t> NewVals(TempVals.size());
	vector<string>::const_iterator AStrVal = TempVals.begin();

	for (vector<off_t>::iterator ANewVal = NewVals.begin(); 
	     ANewVal != NewVals.end(); 
	     ANewVal++, AStrVal++)
	{
		*ANewVal = StrToOff_t(*AStrVal);
	}

	return(NewVals);
}

/*! \brief Converts a vector of strings into a vector of single-presision numbers.
 *
 *  This function merely uses StrToFloat(const string&) upon each element of a vector, returning a vector.
 *  \param TempVals     Strings that supposedly contains a string representations of numbers.
 *  \return             A vector of integers corresponding to the string representations.
*/
vector <float> StrToFloat(const vector <string> &TempVals)
{
        vector <float> NewVals(TempVals.size());
        vector<string>::const_iterator AStrVal(TempVals.begin());

        for (vector<float>::iterator ANewVal(NewVals.begin()); 
	     ANewVal != NewVals.end(); 
	     ANewVal++, AStrVal++)
        {
                *ANewVal = StrToFloat(*AStrVal);
        }

        return(NewVals);
}

/*! \brief Changes lower-case letters into upper-case letters in a string.
 *
 *  \param Line		String to convert to upper-case.
 *  \return		String copy of Line, but converted to upper-case where possible.
 *
*/
string StrToUpper(string Line)
{
	for (string::iterator AChar = Line.begin(); 
	     AChar != Line.end(); 
	     AChar++)
	{
		*AChar = toupper(*AChar);
	}
	return(Line);
}

/*! \brief Changes upper-case letters into lower-case letters in a string.
 *
 *  \param Line         String to convert to lower-case.
 *  \return             String copy of Line, but converted to lower-case where possible.
 *
*/
string StrToLower(string Line)
{
	for (string::iterator AChar = Line.begin(); 
	     AChar != Line.end(); 
	     AChar++)
        {
                *AChar = tolower(*AChar);
        }
        return(Line);
}

/*! \brief Reverses the order of the characters in a string.
 *
 *  \param Line         String to flip.
 *  \return             String copy of Line, but with characters in reversed order.
 *
*/
string FlipString(string Line)
{
	reverse(Line.begin(), Line.end());
	return(Line);
}


/*! \brief Changes lower-case letters into upper-case letters in each string of a vector.
 *
 *  This function merely uses StrToUpper(string) upon a vector of strings.
 *  \param SomeStrings	Strings to convert to upper-case.
 *  \return             Copy of SomeStrings, but with each element converted 
 *			to upper-case where possible.
 *
*/
vector <string> StrToUpper(vector <string> SomeStrings)
{
	for (vector<string>::iterator AString = SomeStrings.begin(); 
	     AString != SomeStrings.end(); 
	     AString++)
	{
		*AString = StrToUpper(*AString);
	}

	return(SomeStrings);
}


/*! \brief Changes upper-case letters into lower-case letters in each string of a vector.
 *
 *  This function merely uses StrToLower(string) upon a vector of strings.
 *  \param SomeStrings  Strings to convert to lower-case.
 *  \return             Copy of SomeStrings, but with each element converted 
 *                      to lower-case where possible.
 *
*/
vector <string> StrToLower(vector <string> SomeStrings)
{
        for (vector<string>::iterator AString = SomeStrings.begin(); 
	     AString != SomeStrings.end(); 
	     AString++)
        {
                *AString = StrToLower(*AString);
        }

	return(SomeStrings);
}


/*! \brief Reverses each string of a vector.
 *
 *  This function merely uses FlipString(string) upon a vector of strings.
 *  \param SomeStrings  Strings to convert to reverse.
 *  \return             Copy of SomeStrings, but with each element having its
 *                      string reversed.
 *
*/
vector <string> FlipString(vector <string> SomeStrings)
{
        for (vector<string>::iterator AString = SomeStrings.begin(); 
	     AString != SomeStrings.end(); 
	     AString++)
        {
                *AString = FlipString(*AString);
        }

	return(SomeStrings);
}





/*! \brief Produces a string representation of an integer.
 *
 *  This function is slightly specialized.  If unable to produce
 *  a string for the number, it will return the mysql string for null (\N).
 *
 *  Converse of StrToInt(const string&)
 *
 *  \param Number	The number for converting.
 *  \return             String representation of Number or "\N" on error.
 *
*/
string IntToStr(const int &Number)
{
	// Allocation is done inside asprintf()
	char *StringPointer = 0;
	
	if (asprintf(&StringPointer, "%i", Number) != -1)
	{
		string TheReturnStr(StringPointer);
                free(StringPointer);
                return(TheReturnStr);
	}
	else
	{
		if (0 != StringPointer)
		{
			// In other words, allocation was done,
			// but something still went wrong.
			free(StringPointer);
		}

		return("\\N");		// mySQL representation of NULL
	}
}

/*! \brief Produces a string representation of a long integer.
 *
 *  This function is slightly specialized.  If unable to produce
 *  a string for the number, it will return the mysql string for null (\N).
 *
 *  Converse of StrToLong(const string&)
 *
 *  \param Number       The number for converting.
 *  \return             String representation of Number or "\N" on error.
 *
*/
string LongToStr(const long int &Number)
{
	// Allocation is done inside asprintf()
        char* StringPointer = 0;

        if (asprintf(&StringPointer, "%li", Number) != -1)
        {
		string TheReturnStr(StringPointer);
                free(StringPointer);
                return(TheReturnStr);
	}
	else
	{
		if (0 != StringPointer)
		{
			// In other words, allocation was done,
			// but something still went wrong.
	                free(StringPointer);
		}

                return("\\N");		// mySQL representation of NULL
        }
}


/*! \brief Produces a string representation of a double-percision number.
 *
 *  This function is slightly specialized.  If unable to produce
 *  a string for the number, it will return the mysql string for null (\N).
 *  It also recognizes any non-finite value (i.e. - NAN or INF) as mysql's null.
 *
 *  If SigDigs is less than 0, then the function will still work,
 *  but it is not known how many significant digits will be produced.
 *  If SigDigs is zero, then it will behave as if SigDigs was 1.
 *
 *  Converse of StrToDouble(const string&)
 *
 *  \param Number       The number for converting.
 *  \param SigDigs	The number of significant digits to use.
 *  \return             String representation of Number or "\N" on error.
 *
*/
string DoubleToStr(const double &Number, const int &SigDigs)
{
        if (!finite(Number))
        {
                return("\\N");		// If the number is a NaN 
					// or Infinite, then return 
					// the mySQL representation of NULL
        }

        char* StringPointer = 0;

        if (asprintf(&StringPointer, "%.*g", SigDigs, Number) != -1)
        {
		string TheReturnStr(StringPointer);
                free(StringPointer);
                return(TheReturnStr);
	}
	else
	{
		if (0 != StringPointer)
                {
                        // In other words, allocation was done,
                        // but something still went wrong.
                        free(StringPointer);
                }
                
                return("\\N");
        }
}

/*! \brief Produces a string representation of a size_t number.
 *
 *  This function is slightly specialized.  If unable to produce
 *  a string for the number, it will return "string::npos".
 *  It also recognizes the value, string::npos, and returns "string::npos".
 *
 *  Converse of StrToSize_t(const string&)
 *
 *  \param Value        The number for converting.
 *  \return             String representation of value or "string::npos" on error.
 *
*/
string Size_tToStr(const size_t &Value)
{
	if (Value == string::npos)
	{
		return("string::npos");
	}
	
	// Allocation done inside asprintf()
	char* StringPointer = 0;

        if (asprintf(&StringPointer, "%u", Value) != -1)
        {
		string TheReturnStr(StringPointer);
                free(StringPointer);
                return(TheReturnStr);
	}
	else
	{
		if (0 != StringPointer)
                {
                        // In other words, allocation was done,
                        // but something still went wrong.
                        free(StringPointer);
                }
                
                return("string::npos");
        }
}


/*! \brief Produces a string representation of a single-percision number.
 *
 *  This function is merely a wrapper around the DoubleToStr(const double&, const int&) function.
 *
 *  Converse of StrToFloat(const string&)
 *
 *  \param Value	The number for converting.
 *  \param SigDigs	The number of significant digits to use.
 *  \return             String representation of Number or "\N" on error.
 *
*/
string FloatToStr(const float &Value, const int &SigDigs)
{
	return(DoubleToStr((double) Value, SigDigs));
}

/*! \brief Produces string representations for a vector of double-percision numbers.
 *
 *  This function uses the the DoubleToStr(const double&, const int&) upon each element of a vector of doubles.
 *
 *  Converse of StrToDouble(const string&)
 *
 *  \param NumberList	The vector of numbers to convert.
 *  \param SigDigs	The number of significant digits to produce for each number.
 *  \return		A vector of strings representing each element of NumberList.
 *
*/
vector <string> DoubleToStr(const vector <double> &NumberList, 
			    const int &SigDigs)
{
	vector <string> NewList(NumberList.size());
        vector<double>::const_iterator TheVal = NumberList.begin();

        for (vector<string>::iterator NewValue = NewList.begin(); 
	     NewValue != NewList.end(); 
	     NewValue++, TheVal++)
        {
                *NewValue = DoubleToStr(*TheVal, SigDigs);
        }

        return(NewList);
}

/*! \brief Produces string representations for a vector of integers.
 *
 *  This function uses the the IntToStr(const int&) upon each element of a vector of integers.
 *
 *  Converse of StrToInt(const vector<string>&)
 *
 *  \param NumberList   The vector of numbers to convert.
 *  \return             A vector of strings representing each element of NumberList.
 *
*/
vector <string> IntToStr(const vector <int> &NumberList)
{
        vector <string> NewList(NumberList.size());
	vector<int>::const_iterator TheVal = NumberList.begin();

        for (vector<string>::iterator NewValue = NewList.begin(); 
	     NewValue != NewList.end(); 
	     NewValue++, TheVal++)
        {
                *NewValue = IntToStr(*TheVal);
        }

        return(NewList);
}


/*! \brief Produces string representations for a vector of long integers.
 *
 *  This function uses the the LongToStr(const long int&) upon each element of a vector of long integers.
 *
 *  Converse of StrToLong(const vector<string>&)
 *
 *  \param NumberList   The vector of numbers to convert.
 *  \return             A vector of strings representing each element of NumberList.
 *
*/
vector <string> LongToStr(const vector <long int> &NumberList)
{
        vector <string> NewList(NumberList.size());
        vector<long int>::const_iterator TheVal = NumberList.begin();

        for (vector<string>::iterator NewValue = NewList.begin(); 
	     NewValue != NewList.end(); 
	     NewValue++, TheVal++)
        {
                *NewValue = LongToStr(*TheVal);
        }

        return(NewList);
}


/*! \brief Produces string representations for a vector of size_t.
 *
 *  This function uses the the Size_tToStr(const size_t&) upon each element of a vector of size_t.
 *
 *  Converse of StrToSize_t(const vector<string>&)
 *
 *  \param NumberList   The vector of numbers to convert.
 *  \return             A vector of strings representing each element of NumberList.
 *
*/
vector <string> Size_tToStr(const vector <size_t> &NumberList)
{
        vector <string> NewList(NumberList.size());
        vector<size_t>::const_iterator TheVal = NumberList.begin();

        for (vector<string>::iterator NewValue = NewList.begin(); 
	     NewValue != NewList.end(); 
	     NewValue++, TheVal++)
        {
                *NewValue = Size_tToStr(*TheVal);
        }

        return(NewList);
}

/*! \brief Produces string representations for a vector of single-percision numbers.
 *
 *  This function uses the the FloatToStr(const float&, const int&) upon each element of a vector of floats.
 *
 *  Converse of StrToFloat(const vector<string>&)
 *
 *  \param NumberList   The vector of numbers to convert.
 *  \param SigDigs	The number of significant digits to produce.
 *  \return             A vector of strings representing each element of NumberList.
 *
*/
vector <string> FloatToStr(const vector <float> &NumberList, 
			   const int &SigDigs)
{
        vector <string> NewList(NumberList.size());
        vector<float>::const_iterator TheVal = NumberList.begin();

        for (vector<string>::iterator NewValue = NewList.begin(); 
	     NewValue != NewList.end(); 
	     NewValue++, TheVal++)
        {
                *NewValue = FloatToStr(*TheVal, SigDigs);
        }

        return(NewList);
}





/*! \brief Breaks a string up into a vector of strings, using a delimiter.
 *
 *  Returns a zero-element vector if TempHold is an empty string.
 *
 *  Converse of GiveDelimitedList(const vector<string>&, const char&).
 *
 *  \param TempHold	The string containing information to break up into separate strings.
 *  \param Delimiter    The character that would be delimiting the information in TempHold.
 *  \return             A vector of strings, each element a token of TempHold.
 *
*/
vector <string> TakeDelimitedList(const string &TempHold, 
				  const char &Delimiter)
{
        if (TempHold.empty())
	{
		return(vector<string>(0));
	}

	vector <string> StringList(0);

	size_t OldPos = 0;
	size_t DelimPos = TempHold.find(Delimiter);

        while (DelimPos != string::npos)
        {
		//assigns an item of delimited string
                StringList.push_back(TempHold.substr(OldPos, 
						     DelimPos - OldPos));

		OldPos = DelimPos + 1;
                DelimPos = TempHold.find(Delimiter, OldPos);
        }

	//gets the last word into the list        
        StringList.push_back(TempHold.substr(OldPos));
        return(StringList);
}


/*! \brief Breaks a string up into a vector of strings, using a delimiter.
 *
 *  Returns a zero-element vector if TempHold or Delimiter is an empty string.
 *
 *  Converse of GiveDelimitedList(const vector<string>&, const string&).
 *
 *  \todo Change the behavior regarding Delimiter being an empty string.
 *
 *  \param TempHold     The string containing information to break up into separate strings.
 *  \param Delimiter    The string that would be delimiting the information in TempHold.
 *  \return             A vector of strings, each element a token of TempHold.
 *
*/
vector <string> TakeDelimitedList(const string &TempHold, 
				  const string &Delimiter)
{
        if (TempHold.empty() || Delimiter.empty())
        {
                return(vector<string>(0));
        }

	vector <string> StringList(0);

        size_t OldPos = 0;
        size_t DelimPos = TempHold.find(Delimiter);

        while (DelimPos != string::npos)
        {
		//assigns an item of delimited string
                StringList.push_back(TempHold.substr(OldPos, 
						     DelimPos - OldPos));

                OldPos = DelimPos + Delimiter.size();
                DelimPos = TempHold.find(Delimiter, OldPos);
        }

	//gets the last word into the list
        StringList.push_back(TempHold.substr(OldPos));
        return(StringList);
}


/*! \brief Joins the elements of a vector of strings into a single string, using a delimiter.
 *
 *  Returns an empty string if TheList is empty.
 *  This function is the converse of TakeDelimitedList(const string&, const string&).
 *
 *  \param TheList      The vector of strings to join together into a single string.
 *  \param Delimiter    The string that would be delimiting the elements of TheList.
 *  \return             A string containing each element of TheList, delimited by Delimiter.
 *
*/
string GiveDelimitedList(const vector <string> &TheList, 
			 const string &Delimiter)
{
	string StrBuild = "";

	if (!TheList.empty())
	{
		StrBuild += TheList[0];
		for (vector<string>::const_iterator AVal = TheList.begin() + 1; 
		     AVal != TheList.end(); 
		     AVal++)
		{
			StrBuild += Delimiter + *AVal;
		}
	}

	return(StrBuild);
}

/*! \brief Joins the elements of a vector of strings into a single string, using a delimiter.
 *
 *  Returns an empty string if TheList is empty.
 *  This function is the converse of TakeDelimitedList(const string&, const char&).
 *
 *  \param TheList      The vector of strings to join together into a single string.
 *  \param Delimiter    The character that would be delimiting the elements of TheList.
 *  \return             A string containing each element of TheList, delimited by Delimiter.
 *
*/
string GiveDelimitedList(const vector <string> &TheList, 
			 const char &Delimiter)
{
        string StrBuild = "";

        if (!TheList.empty())
        {
                StrBuild += TheList[0];
                for (vector<string>::const_iterator AVal = TheList.begin() + 1; 
		     AVal != TheList.end(); 
		     AVal++)
                {
                        StrBuild += Delimiter + *AVal;
                }
        }

        return(StrBuild);
}


/*! \brief Checks to see if a string contains only digits.
 *
 *  Returns false if NumRep is an empty string.
 *
 *  \param NumRep	The string to check the characters for digits.
 *  \return             True if all characters are digits, false otherwise.
 *
*/
bool OnlyDigits(const string &NumRep)
{
        if (NumRep.empty())
        {
                return(false);
        }

        for (size_t i = 0; i < NumRep.size(); i++)
        {
                if (!isdigit(NumRep[i]))
                {
                        return(false);
                }
        }

        return(true);
}

/*! \brief Checks to see if a string contains only alphabetic characters.
 *
 *  Returns false if WordRep is an empty string.
 *
 *  \param WordRep      The string to check the characters for alphabetic characters.
 *  \return             True if all characters are alphabetic, false otherwise.
 *
*/
bool OnlyAlpha(const string &WordRep)
{
        if (WordRep.empty())
        {
                return(false);
        }

        for (size_t i = 0; i < WordRep.size(); i++)
        {
                if (!isalpha(WordRep[i]))
                {
                        return(false);
                }
        }

        return(true);
}

#endif
