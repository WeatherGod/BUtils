#ifndef _CONFIGUTLY_H
#define _CONFIGUTLY_H


#include <fstream>
#include <string>

#include "StrUtly.h"            // for StripWhiteSpace()


bool FoundStartTag(const string &LineRead, const string &TagWord);
bool FoundEndTag(const string &LineRead, const string &TagWord);
string ReadNoComments(ifstream &ReadData);
string ReadNoComments(fstream &ReadData);
string StripTags(string TheLine, const string &TheTagWord);

#ifndef _DOLINKING_
// For now...
#include "ConfigUtly.C"
#endif

#endif
