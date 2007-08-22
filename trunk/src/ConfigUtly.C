#ifndef _CONFIGUTLY_C
#define _CONFIGUTLY_C
using namespace std;

#include <fstream>
#include <string>

#include "ConfigUtly.h"
#include "StrUtly.h"		// for StripWhiteSpace()


bool FoundStartTag(const string &LineRead, const string &TagWord)
{
	return(LineRead.find('<' + TagWord + '>') != string::npos);
}


bool FoundEndTag(const string &LineRead, const string &TagWord)
{
	return(LineRead.find("</"+TagWord+'>') != string::npos);
}


string ReadNoComments(ifstream &ReadData)
//  assumes '#' is the only kind of To-End-Of-Line comment marker
//  no escape sequence will be recognized, as of now.  That may change.
//  if there is nothing but white-space before the comment marker in the line, it will continue reading the file.

//  If the read reaches the end of the file without finding any noncomment info, then it will return an empty string.
//  Returns a white-space stripped line of noncommented information.
//  The last read of the file in this function will ALWAYS be the getline() that read the line being returned, 
//				no more, no less....
{
        string LineRead = "";
	bool HaveNonCommentInfo = false;

	getline(ReadData, LineRead);

        while (!HaveNonCommentInfo && ReadData.good())
       	{
		StripWhiteSpace(LineRead);
                size_t CommentPos = LineRead.find('#');

                if (CommentPos != string::npos)     // i.e. - if a comment marker was found in the line
                {
                        LineRead = LineRead.substr(0, CommentPos);      // return a substring of LineRead from the beginning to the comment position
                        StripWhiteSpace(LineRead);			 // gets rid of any white space that exists.
                }

		if (LineRead.empty())
		{
			getline(ReadData, LineRead);
		}
		else
		{
			HaveNonCommentInfo = true;
		}
        }

        return(LineRead);
}

string ReadNoComments(fstream &ReadData)
//  assumes '#' is the only kind of To-End-Of-Line comment marker
//  no escape sequence will be recognized, as of now.  That may change.
//  if there is nothing but white-space before the comment marker in the line, it will continue reading the file.

//  If the read reaches the end of the file without finding any noncomment info, then it will return an empty string.
//  Returns a white-space stripped line of noncommented information.
//  The last read of the file in this function will ALWAYS be the getline() that read the line being returned,
//                              no more, no less....
{
        string LineRead = "";
        bool HaveNonCommentInfo = false;

        getline(ReadData, LineRead);

        while (!HaveNonCommentInfo && ReadData.good())
        {
                StripWhiteSpace(LineRead);
                size_t CommentPos = LineRead.find('#');

                if (CommentPos != string::npos)     // i.e. - if a comment marker was found in the line
                {
                        LineRead = LineRead.substr(0, CommentPos);      // return a substring of LineRead from the beginning to the comment position
                        StripWhiteSpace(LineRead);                       // gets rid of any white space that exists.
                }

                if (LineRead.empty())
                {
                        getline(ReadData, LineRead);
                }
                else
                {
                        HaveNonCommentInfo = true;
                }
        }

        return(LineRead);
}



string StripTags(string TheLine, const string &TheTagWord)
// returns the substring of whatever is between the opening and corresponding closing tag
// contained in the string, which is typically a line, but doesn't have to be.
// This function does not test to make sure the tags correspond to each other, so NO COMPLEX NESTING
//     the same tags within each other!
//     so avoid using this function on config files that have tricky lines to parse!
//     If you aren't sure if it will work, TEST IT!!!!!
{
        if (FoundStartTag(TheLine, TheTagWord) && FoundEndTag(TheLine, TheTagWord))
        {
                size_t StartTagPos = TheLine.find('<' + TheTagWord + '>');
                size_t EndTagPos = TheLine.rfind("</" + TheTagWord + ">");
                string StrippedLine = TheLine.substr(StartTagPos + TheTagWord.size() + 2, EndTagPos - (StartTagPos + TheTagWord.size() + 2));

                return(StrippedLine);
        }
        else
        {
                return("");
        }
}


#endif
