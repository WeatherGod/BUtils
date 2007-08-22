#ifndef _TIMEUTLY_H
#define _TIMEUTLY_H

#include <vector>
#include <string>
#include <ctime>


int MonthIndex(string MonthName);
int TakeYearStr(const string &YrStr, const int CutOffPoint = 50);
int TakeMonthStr(const string &MnthStr);
string GradConvert(string GradDateForm);
string DateTime2Grad(const string &DateTimeString);

struct TimeIncrement_t
{
        int YearInterval;
        int MonthInterval;
        int DayInterval;
        int HourInterval;
        int MinuteInterval;
        int SecInterval;

        TimeIncrement_t();
        bool IsValid();
};

void RoundHour(time_t &TheTime, const int HourIncrement, const int HourOffset = 0);
time_t GiveRandomDate(const time_t &MinDate, const time_t &MaxDate);

time_t IncrementDateTime(const time_t &OrigTime, const struct TimeIncrement_t &Interval);
time_t IncrementDateTimeUTC(const time_t &OrigTime, const struct TimeIncrement_t &Interval);
vector <time_t> FindMissedDates(const vector <time_t> &DateTimes, const struct TimeIncrement_t &Interval, const bool IncreasingInterval = true);
vector <size_t> FindOutOfPlaceDates(const vector <time_t> &DateTimes, const struct TimeIncrement_t &Interval, bool IncreasingInterval = true);

time_t GetTime(const string &DateTimeStr, const string &FormatString = "%Y-%m-%d %H:%M:%S");
time_t GetTimeUTC(const string &DateTimeStr, const string &FormatString = "%Y-%m-%d %H:%M:%S");

string GiveTime(const time_t &TheDateTime, const string &FormatString = "%Y-%m-%d %H:%M:%S");
string GiveTimeUTC(const time_t &TheDateTime, const string &FormatString = "%Y-%m-%d %H:%M:%S");

#ifndef _DOLINKING_
// for now...
#include "TimeUtly.C"
#endif
	
#endif
