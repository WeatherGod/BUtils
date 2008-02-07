#ifndef _CONFIGUTLY_C
#define _CONFIGUTLY_C
using namespace std;

/*! \file ConfigUtly.C
 *  \ingroup ConfigUtly
 *
*/

#include <fstream>
#include <string>

#include "ConfigUtly.h"
#include "StrUtly.h"		// for StripWhiteSpace()

/*! \brief Determines if the starting tag for the specified element
 *          in in the given string.
 *
 *  Starting tags have the following form: "<Tag>".
 *
 *  \param LineRead	String to check for the opening tag.
 *  \param TagWord	The tag name to find.
 *  \return		True if the starting tag is found in LineRead.
*/
bool FoundStartTag(const string &LineRead, const string &TagWord)
{
	return(LineRead.find('<' + TagWord + '>') != string::npos);
}

/*! \brief Determines if the ending tag for the specified element
 *          in in the given string.
 *
 *  Ending tags have the following form: "</Tag>".
 *
 *  \param LineRead     String to check for the ending tag.
 *  \param TagWord      The tag name to find.
 *  \return             True if the ending tag is found in LineRead.
*/
bool FoundEndTag(const string &LineRead, const string &TagWord)
{
	return(LineRead.find("</"+TagWord+'>') != string::npos);
}

/*! \brief Advances the input file stream, searching for a line with content.
 *
 *  A line with content is a line that, when stripped of whitespace,
 *  contains more than just commented information.
 *  Comments are recognized as unescapable '#', and goes to the end of the line.
 *
 *  The last read of the input file stream will ALWAYS be the getline() that
 *  read the line being returned.  No more, no less.
 *
 *  \param ReadData     Input file stream.
 *  \return             A white-space stripped line of content without the comment,
 *                      or empty string if none found.
*/
string ReadNoComments(ifstream &ReadData)
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

/*! \brief Advances the input stream, searching for a line with content.
 *
 *  A line with content is a line that, when stripped of whitespace,
 *  contains more than just commented information.
 *  Comments are recognized as unescapable '#', and goes to the end of the line.
 *
 *  The last read of the input stream will ALWAYS be the getline() that
 *  read the line being returned.  No more, no less.
 *
 *  \param ReadData     Input stream.
 *  \return             A white-space stripped line of content without the comment,
 *                      or empty string if none found.
*/
string ReadNoComments(fstream &ReadData)
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


/*! \brief Returns the content contained within the opening and closing tags.
 *
 *  \warning This function does not test to see if the tags correspond to
 *           each other.  So NO COMPLEX NESTING of the same tags!
 *           If you aren't sure if it will work, TEST IT!!!
 *
 *  \param TheLine      String to find the content between the tags.
 *  \param TheTagWord	The element name to search for.
 *  \return             The content between the tags,
 *                      or empty string if opening and closing tags are not found.
*/
string StripTags(string TheLine, const string &TheTagWord)
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
