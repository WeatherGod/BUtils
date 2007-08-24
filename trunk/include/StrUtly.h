#ifndef _STRUTLY_H
#define _STRUTLY_H

#include <string>
#include <vector>
#include <cstddef>	// for off_t, size_t


void StripWhiteSpace(string &FatString);
void StripWhiteSpace(vector <string>&);
string RipWhiteSpace(string);
vector <string> RipWhiteSpace(vector <string>);

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


string StrToUpper(string);
string StrToLower(string);
string FlipString(string);


vector <string> StrToUpper(vector <string>);
vector <string> StrToLower(vector <string>);
vector <string> FlipString(vector <string>);

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

vector <string> TakeDelimitedList(const string &, const char &);
vector <string> TakeDelimitedList(const string &, const string &);
string GiveDelimitedList(const vector <string> &, const char &);
string GiveDelimitedList(const vector <string> &, const string &);

bool OnlyDigits(const string &WordRep);
bool OnlyAlpha(const string &WordRep);

#endif
