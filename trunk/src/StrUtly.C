#ifndef _STRUTLY_C
#define _STRUTLY_C
using namespace std;

#include <string>
#include <vector>
#include <cstddef>	// for off_t, size_t
#include <algorithm>	// for count(), reverse()
#include <cmath>	// for pow(), nan()
#include <cctype>	// for toupper(), tolower(), isspace()
#include <cstdlib>	// for atoi(), atof(), strtoul(), free()
#include <cstdio>	// for asprintf()
#include <errno.h>

#include "StrUtly.h"

//------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------
void StripWhiteSpace(string &FatString)
// Removes whitespaces (as defined by the function from cctype, isspace()) from the beginning and the end of FatString, if they exist.
// This function is similar, but different from RipWhiteSpace(string) in that 
// this modifies the string variable arguement instead of returning a string value (pass-by-reference vs. pass-by-value).
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


//-----------------------------------------------------------------------------------------------------------------------------

void StripWhiteSpace(vector <string> &FatVector)
//  this does StripWhiteSpace to each element of the string vector
{
	for (vector<string>::iterator AFatString = FatVector.begin(); AFatString != FatVector.end(); AFatString++)
	{
		StripWhiteSpace(*AFatString);
	}
}


//--------------------------------------------------------------------------------------------------------------------

string RipWhiteSpace(string FatString)
// Removes whitespaces (i.e. - \t \n and the space) in the beginning and the end of FatString, if they exist
// This function is similar, but different from ChompWhiteSpace(string&) [Deprecated, now use StripWhiteSpace(string&) in that 
// this returns a string instead of modifying the string variable arguement (pass by value vs. pass by reference).
{
	StripWhiteSpace(FatString);
	return(FatString);
}

//------------------------------------------------------------------------------------------

vector <string> RipWhiteSpace(vector <string> FatVector)
{
	StripWhiteSpace(FatVector);
	return(FatVector);
}

//-----------------------------------------------------------------------
int StrToInt(const string &Temp)
{
	return(atoi(Temp.c_str()));
}

long int StrToLong(const string &Temp)
{
	return(atol(Temp.c_str()));
}

double StrToDouble(const string &Temp)
{
	if (Temp.empty() || Temp == "\\N")
	{
		// this is support for the mySQL's Null.  I will treat them like NaNs.
		return(nan("nan"));
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
		return(nan("nan"));
	}
}

size_t StrToSize_t(const string &Temp)
// I should probably think this through better since string::npos is just the largest value available for size_t
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

off_t StrToOff_t(const string &Temp)
// Just a temporary stub for now.  Just wanted to abstract this out.
// There is no explicit converse function.
{
	return((off_t) StrToInt(Temp));
}

float StrToFloat(const string &Temp)
{
	if (Temp.empty() || Temp == "\\N")
        {
                // this is support for the mySQL's Null.  I will treat them like NaNs.
                return(nanf("nan"));
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
                return(nanf("nan"));
        }
}


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

vector <off_t> StrToOff_t(const vector <string> &TempVals)
// Just a stub for now.  I want to keep this abstracted out until I understand off_t better.
// There is no converse function.
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

string FlipString(string Line)
{
	reverse(Line.begin(), Line.end());
	return(Line);
}


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




string IntToStr(const int &Number)
// May need to rethink the return type.
{
	if (!finite(Number))
	{
		return("\\N");		// If the number is a NaN 
					// or Infinite, then return 
					// the mySQL representation of NULL
	}

	// Allocation is done inside asprintf()
	char *StringPointer;
	
	if (asprintf(&StringPointer, "%i", Number) != -1)
	{
		string TheReturnStr(StringPointer);
                free(StringPointer);
                return(TheReturnStr);
	}
	else
	{
		free(StringPointer);
		return("\\N");
	}
}

string LongToStr(const long int &Number)
// May need to rethink the return type.
{
        if (!finite(Number))
        {
                return("\\N");		// If the number is a NaN 
					// or Infinite, then return 
					// the mySQL representation of NULL
        }

	// Allocation is done inside asprintf()
        char* StringPointer;

        if (asprintf(&StringPointer, "%li", Number) != -1)
        {
		string TheReturnStr(StringPointer);
                free(StringPointer);
                return(TheReturnStr);
	}
	else
	{
                free(StringPointer);
                return("\\N");
        }
}



string DoubleToStr(const double &Number, const int &SigDigs)
// if SigDigs is less than 0, then the function will still work, 
// but it is not known how many sig digs the sprintf uses
// if SigDigs is zero, then sprintf treats it like if it was 1.
// May need to rethink the return type.
{
        if (!finite(Number))
        {
                return("\\N");		// If the number is a NaN 
					// or Infinite, then return 
					// the mySQL representation of NULL
        }

        char* StringPointer;

        if (asprintf(&StringPointer, "%.*g", SigDigs, Number) != -1)
        {
		string TheReturnStr(StringPointer);
                free(StringPointer);
                return(TheReturnStr);
	}
	else
	{
                free(StringPointer);
                return("\\N");
        }
}


string Size_tToStr(const size_t &Value)
{
	if (Value == string::npos)
	{
		return("string::npos");
	}
	
	// Allocation done inside asprintf()
	char* StringPointer;

        if (asprintf(&StringPointer, "%u", Value) != -1)
        {
		string TheReturnStr(StringPointer);
                free(StringPointer);
                return(TheReturnStr);
	}
	else
	{
                free(StringPointer);
                return("string::npos");
        }
}

string FloatToStr(const float &Value, const int &SigDigs)
{
	return(DoubleToStr((double) Value, SigDigs));
}


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






vector <string> TakeDelimitedList(const string &TempHold, 
				  const char &Delimiter)
// returns a zero sized vector if TempHold is an empty string.
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

vector <string> TakeDelimitedList(const string &TempHold, 
				  const string &Delimiter)
// returns a zero sized vector if TempHold or Delimiter is an empty string.
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
