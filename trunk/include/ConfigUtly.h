#ifndef _CONFIGUTLY_H
#define _CONFIGUTLY_H

/*! \defgroup ConfigUtly Configuration Reader Utility
 *  \brief Provides some useful functions for reading XML-like files.
 *         Typically these files are basic configuration files.
 *
 *  You can use this if you want a build a simple reader for your configuraion
 *  files, but do not expect perfection.
 *
 * @{
*/

/*! \file ConfigUtly.h
 *
*/

#include <fstream>
#include <string>


bool FoundStartTag(const string &LineRead, const string &TagWord);
bool FoundEndTag(const string &LineRead, const string &TagWord);
string ReadNoComments(ifstream &ReadData);
string ReadNoComments(fstream &ReadData);
string StripTags(string TheLine, const string &TheTagWord);

/*! @} */	// end of ConfigUtly group
#endif
