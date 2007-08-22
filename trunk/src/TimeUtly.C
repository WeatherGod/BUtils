#ifndef _TIMEUTLY_C
#define _TIMEUTLY_C
using namespace std;

#include <vector>
#include <string>
#include <cstdio>				// for sprintf()
#include <ctime>
#include <cmath>				// for fmod()
#include <algorithm>
#include "StrUtly.h"				// for StrToUpper(), StrToInt(), OnlyDigits(), OnlyAlphas()

#include "TimeUtly.h"


int MonthIndex(string MonthName)
// assumes MonthName has at least three characters
// returns a number between 1 and 12, inclusive, corresponding to the month if there is a match
// returns -1 if there is no match
{
        vector <string> MonthNames(12, "");

	if (MonthName.size() == 2)
	{
		MonthNames[0] = "JA";
                MonthNames[1] = "FE";
                MonthNames[2] = "MR";
                MonthNames[3] = "AP";
                MonthNames[4] = "MY";
                MonthNames[5] = "JN";
                MonthNames[6] = "JL";
                MonthNames[7] = "AU";
                MonthNames[8] = "SE";
                MonthNames[9] = "OC";
                MonthNames[10] = "NO";
                MonthNames[11] = "DE";

		MonthName = StrToUpper(MonthName);
	}
	else
	{
        	MonthNames[0] = "JAN";
	        MonthNames[1] = "FEB";
        	MonthNames[2] = "MAR";
	        MonthNames[3] = "APR";
        	MonthNames[4] = "MAY";
	        MonthNames[5] = "JUN";
        	MonthNames[6] = "JUL";
	        MonthNames[7] = "AUG";
        	MonthNames[8] = "SEP";
	        MonthNames[9] = "OCT";
        	MonthNames[10] = "NOV";
	        MonthNames[11] = "DEC";

		MonthName = StrToUpper(MonthName.substr(0, 3));
        }                                                                                                                                                 
           
        for (int i = 0; i < 12; i++)
        {
                if (MonthName == MonthNames[i])
                {
                        return(i + 1);
                }
        }
                                                                                                                                                             
        return(-1);
}

/*
string MonthName(int MonthNum)
// assumes that MonthNum is a number between 1 and 12, inclusive.
// returns empty string if it is not.
{
        vector <string> MonthNames(12, "");
        MonthNames[0] = "JANUARY";
        MonthNames[1] = "FEBRUARY";
        MonthNames[2] = "MARCH";
        MonthNames[3] = "APRIL";
        MonthNames[4] = "MAY";
        MonthNames[5] = "JUNE";
        MonthNames[6] = "JULY";
        MonthNames[7] = "AUGUST";
        MonthNames[8] = "SEPTEMBER";
        MonthNames[9] = "OCTOBER";
        MonthNames[10] = "NOVEMBER";
        MonthNames[11] = "DECEMBER";
                                                                                                                                                             
        if (MonthNum >= 1 && MonthNum <= 12)
        {
                return(MonthNames[MonthNum - 1]);
        }
        else
        {
                return("");
        }
}
*/


int TakeYearStr(const string &YrStr, const int CutOffPoint)
// Assumes no whitespace in the string, and also assumes only numbers.
// Assumes that the string is either 1,2 or 4 characters long
// if a 2 digit year comes up, and it is equal to or greater than the CutOffPoint, it will be interpreated as (1900 + CutOffPoint) or greater
// otherwise, a 2 digit year is interpreated as being in 2000 or greater. (i.e. for CutOffPoint = 50,    "26" --> 2026,  "74" --> 1974)
{
	if (!OnlyDigits(YrStr))
	{
		return(-1);
	}

	if (YrStr.length() == 2)
	{
		int DecadePart = StrToInt(YrStr);

		if (DecadePart >= CutOffPoint)
		{
			return(1900 + DecadePart);
		}
		else
		{
			return(2000 + DecadePart);
		}
	}
	else if (YrStr.length() == 4)
	{
		return(StrToInt(YrStr));
	}

	return(-1);			// if something goes wrong, this should help
}

int TakeMonthStr(const string &MnthStr)
{
	if (OnlyAlpha(MnthStr))
	{
		if (MnthStr.length() < 2)
		{
			return(-1);
		}
		else
		{
			return(MonthIndex(MnthStr));
		}
	}

	if (OnlyDigits(MnthStr))
	{
		int MnthNum = StrToInt(MnthStr);
		if (MnthNum >= 1 && MnthNum <= 12)
		{
			return(MnthNum);
		}
		else
		{
			return(-1);
		}
	}

	return(-1);
}

string GradConvert(string GradDateForm)
//  converts hhZddmmmyyyy form into yyyy-mm-dd hh form
{
	char DateTypForm[14];
	memset(DateTypForm, '\0', 14);
	struct tm GradTime;
	GradDateForm = StrToUpper(GradDateForm);
	strptime(GradDateForm.c_str(), "%HZ%d%b%Y", &GradTime);
	strftime(&DateTypForm[0], 14, "%Y-%m-%d %H", &GradTime);
//	sprintf(DateTypForm, "%s-%02i-%s %s", YearPart.c_str(), MonthInt, DayPart.c_str(), HourPart.c_str());

	return(DateTypForm);
}

string DateTime2Grad(const string &DateTimeString)
{
	char GradStr[13];
	memset(GradStr, '\0', 13);

	struct tm DateTime;
	DateTime.tm_sec = 0;
	DateTime.tm_min = 0;
	DateTime.tm_hour = 0;
	DateTime.tm_mday = 1;
	DateTime.tm_mon = 0;
	strptime(DateTimeString.c_str(), "%Y%b%d %H", &DateTime);
	strftime(&GradStr[0], 13, "%HZ%d%b%Y", &DateTime);

	return(GradStr);
}



TimeIncrement_t::TimeIncrement_t()			// constructor
{
	YearInterval = 0;
	MonthInterval = 0;
	DayInterval = 0;
	HourInterval = 0;
	MinuteInterval = 0;
	SecInterval = 0;
}

bool TimeIncrement_t::IsValid()
{
	return(SecInterval != 0 || MinuteInterval != 0 || HourInterval != 0 || 
	       DayInterval != 0 || MonthInterval != 0 || YearInterval != 0);
}




void RoundHour(time_t &TheTime, const int HourIncrement, const int HourOffset)
{
        struct tm RoundedTime;
        localtime_r(&TheTime, &RoundedTime);

	// RoundedTime will have the year, month, day and hour of TheTime.  Seconds and Minutes are set to zero by default.
	// This time will be incremented through possible rounded values for the day and compared with the actual value.
	// The smallest difference will be the rounded time.
        RoundedTime.tm_sec = 0;
        RoundedTime.tm_min = 0;

        double LowestDiff = 999999;		// way more than the number of seconds in a day

        for (int Hour = HourOffset; Hour <= (24 + (HourIncrement - (24 % HourIncrement))); Hour += HourIncrement)
        {
                RoundedTime.tm_hour = Hour;
                double TheDiff = difftime(TheTime, mktime(&RoundedTime));
                if (labs((long int) TheDiff) < labs((long int) LowestDiff))
                {
                        LowestDiff = TheDiff;
                }
        }

        TheTime -= (int) LowestDiff;
}

time_t GiveRandomDate(const time_t &MinDate, const time_t &MaxDate)
{
	const double TimeDifference = difftime(MaxDate, MinDate);
	time_t RandomTime = ((time_t) ((((double) rand())/((double) RAND_MAX)) * TimeDifference)) + MinDate;
}


time_t IncrementDateTime(const time_t &OrigTime, const struct TimeIncrement_t &Interval)
// WARNING: localtime_r and mktime will do time conversions assuming you want the local timezone used.  Difficult to tell it otherwise...
{
        struct tm FirstTime;
        localtime_r(&OrigTime, &FirstTime);

        FirstTime.tm_sec += Interval.SecInterval;
        FirstTime.tm_min += Interval.MinuteInterval;
        FirstTime.tm_hour += Interval.HourInterval;
        FirstTime.tm_mday += Interval.DayInterval;
        FirstTime.tm_mon += Interval.MonthInterval;
        FirstTime.tm_year += Interval.YearInterval;
        return(mktime(&FirstTime));
}

time_t IncrementDateTimeUTC(const time_t &OrigTime, const struct TimeIncrement_t &Interval)
{
        struct tm FirstTime;
        gmtime_r(&OrigTime, &FirstTime);

        FirstTime.tm_sec += Interval.SecInterval;
        FirstTime.tm_min += Interval.MinuteInterval;
        FirstTime.tm_hour += Interval.HourInterval;
        FirstTime.tm_mday += Interval.DayInterval;
        FirstTime.tm_mon += Interval.MonthInterval;
        FirstTime.tm_year += Interval.YearInterval;
        return(timegm(&FirstTime));
}





vector <time_t> FindMissedDates(const vector <time_t> &DateTimes, const struct TimeIncrement_t &Interval, const bool IncreasingInterval)
// WARNING: IncrementDateTime will do time conversions assuming you want the local timezone used.  Difficult to tell it otherwise...
// It will assume that the first time in the vector is the correct time
{
        vector <time_t> MissedDates(0);

        if (!DateTimes.empty())
        {
                time_t NextStep = IncrementDateTime(DateTimes[0], Interval);

                if (IncreasingInterval)
                {
                        while (NextStep <= DateTimes[DateTimes.size() - 1])
                        {
                                if (!binary_search(DateTimes.begin(), DateTimes.end(), NextStep))
                                {
                                        MissedDates.push_back(NextStep);
                                }

                                NextStep = IncrementDateTime(NextStep, Interval);                        }
                }
                else
                {
                        while (NextStep >= DateTimes[DateTimes.size() - 1])
                        {
                                if (!binary_search(DateTimes.rbegin(), DateTimes.rend(), NextStep))
                                {
                                        MissedDates.push_back(NextStep);
                                }

                                NextStep = IncrementDateTime(NextStep, Interval);                        }
                }
        }

        return(MissedDates);
}

vector <size_t> FindOutOfPlaceDates(const vector <time_t> &DateTimes, const struct TimeIncrement_t &Interval, bool IncreasingInterval)
// WARNING: IncrementDateTime will do time conversions assuming you want the local timezone used.  Difficult to tell it otherwise...
// It will assume that the first time in the vector is correct
{
        vector <size_t> OutOfIntervalIndices(0);

        if (!DateTimes.empty())
        {
                time_t NextStep = DateTimes[0];

                if (IncreasingInterval)
                {
                        for (size_t TimeIndex = 1; TimeIndex < DateTimes.size(); TimeIndex++)
                        {
                                while (NextStep < DateTimes[TimeIndex])
                                {
                                        NextStep = IncrementDateTime(NextStep, Interval);
                                }

                                if (NextStep > DateTimes[TimeIndex])
                                {
                                        OutOfIntervalIndices.push_back(TimeIndex);
                                }
                        }
                }
                else
                {
                        for (size_t TimeIndex = 1; TimeIndex < DateTimes.size(); TimeIndex++)
                        {
                                while (NextStep > DateTimes[TimeIndex])
                                {
                                        NextStep = IncrementDateTime(NextStep, Interval);
                                }

                                if (NextStep < DateTimes[TimeIndex])
                                {
                                        OutOfIntervalIndices.push_back(TimeIndex);
                                }
                        }
                }
        }

        return(OutOfIntervalIndices);
}

time_t GetTime(const string &DateTimeStr, const string &FormatString)
// No error handling here!

// WARNING, this function uses functions that will use the local timezone to do time zone specifications.
// Even if you add a timezone thing to the FormatString and tell it what timezone you want to use, it will ignore that and
// use the local timezone.  It is really stupid, but oh-well.
{
        struct tm ThisDateTime;
	ThisDateTime.tm_sec = 0;
	ThisDateTime.tm_min = 0;
	ThisDateTime.tm_hour = 0;
	ThisDateTime.tm_mday = 1;
	ThisDateTime.tm_mon = 1;

        strptime(DateTimeStr.c_str(), FormatString.c_str(), &ThisDateTime);

        return(mktime(&ThisDateTime));
}

time_t GetTimeUTC(const string &DateTimeStr, const string &FormatString)
// No error handling here!
{
        struct tm ThisDateTime;
        ThisDateTime.tm_sec = 0;
        ThisDateTime.tm_min = 0;
        ThisDateTime.tm_hour = 0;
        ThisDateTime.tm_mday = 1;
        ThisDateTime.tm_mon = 1;

        strptime(DateTimeStr.c_str(), FormatString.c_str(), &ThisDateTime);

        return(timegm(&ThisDateTime));
}


string GiveTime(const time_t &TheDateTime, const string &FormatString)
// very little error handling here!

// WARNING, this function uses functions that will use the local timezone to do time zone specifications.
// Even if you add a timezone thing to the FormatString and tell it what timezone you want to use, it will ignore that and
// use the local timezone.  It is really stupid, but oh-well.  Temporary solution is to setenv("TZ", "UTC UTC", 1) at the beginning of the
// program, but that doesn't really do the job, it just makes the function default to UTC.  Can't change it to anything else.
{
	char DateStr[255];
	memset(DateStr, '\0', 255);

	if (strftime(DateStr, 255, FormatString.c_str(), localtime(&TheDateTime)) != 0)
	{
		return(DateStr);
	}
	else
	{
		return("");
	}
}

string GiveTimeUTC(const time_t &TheDateTime, const string &FormatString)
// very little error handling here!
{
        char DateStr[255];
        memset(DateStr, '\0', 255);

        if (strftime(DateStr, 255, FormatString.c_str(), gmtime(&TheDateTime)) != 0)
        {
                return(DateStr);
        }
        else
        {
                return("");
        }
}
	
#endif
