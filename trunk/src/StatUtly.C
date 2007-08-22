#ifndef _STATUTLY_C
#define _STATUTLY_C

using namespace std;

#include <iostream>		// for cerr messages
#include <vector>
#include <algorithm>		// for sort()
#include <cmath>		// for sqrt(), pow(), remainder()

// NOTE: these functions are not the best way to do these things!
// I developed these before knowing the existance of other stuff!

// Also, these functions are NOT NaN-friendly!  For example, Avg() does not skip any NaNs.
// Only InterquartileVal is NaN-friendly.


double Sum(const vector <double> &Values)
{
	double RunSum = 0.0;

	for (vector<double>::const_iterator AValue = Values.begin(); AValue != Values.end(); AValue++)
	{
		RunSum += *AValue;
	}

	return(RunSum);
}

int Sum(const vector <int> &Values)
{
	int RunSum = 0;

	for (vector<int>::const_iterator AValue = Values.begin(); AValue != Values.end(); AValue++)
	{
		RunSum += *AValue;
	}

	return(RunSum);
}


unsigned int Sumu(const vector <unsigned int> &Values)
{
	unsigned int RunSum = 0;

	for (vector<unsigned int>::const_iterator AValue = Values.begin(); AValue != Values.end(); AValue++)
	{
		RunSum += *AValue;
	}

	return(RunSum);
}

long double Suml(const vector <long double> &Values)
{
	long double RunSum = 0.0;

	for (vector<long double>::const_iterator AValue = Values.begin(); AValue != Values.end(); AValue++)
	{
		RunSum += *AValue;
	}

	return(RunSum);
}

long double Suml(const vector <double> &Values)
{
        long double RunSum = 0.0;

        for (vector<double>::const_iterator AValue = Values.begin(); AValue != Values.end(); AValue++)
        {
                RunSum += ((long double) *AValue);
        }

        return(RunSum);
}


double WeightedSum(const vector <double> &Values, const vector <double> &Weights)
{
	if (Values.size() != Weights.size())
	{
		cerr << "\n\tThe Values vector and the Weights vector need to be the same size in WeightedSum().  Returning NAN\n\n";
		return(nan("nan"));
	}

	double RunSum = 0.0;

	for (vector<double>::const_iterator AValue = Values.begin(), AWeight = Weights.begin();
	     AValue != Values.end() && AWeight != Weights.end();
	     AValue++, AWeight++)
	{
		RunSum += (*AValue)*(*AWeight);
	}
	
	return(RunSum);
}

double WeightedSum(const vector <int> &Values, const vector <double> &Weights)
{
	if (Values.size() != Weights.size())
	{
		cerr << "\n\tThe Values vector and the Weights vector need to be the same size in WeightedSum(). Returning NAN\n\n";
		return(nan("nan"));
	}

	double RunSum = 0.0;

	vector<double>::const_iterator AWeight = Weights.begin();
	for (vector<int>::const_iterator AValue = Values.begin();
             AValue != Values.end() && AWeight != Weights.end();
             AValue++, AWeight++)
	{
		RunSum += (*AValue)*(*AWeight);
	}

	return(RunSum);
}


long double WeightedSuml(const vector <long double> &Values, const vector <long double> &Weights)
{
        if (Values.size() != Weights.size())
        {
                cerr << "\n\tThe Values vector and the Weights vector need to be the same size in WeightedSuml().  Returning NAN\n\n";
                return(nanl("nan"));
        }

        long double RunSum = 0.0;
        for (vector<long double>::const_iterator AValue = Values.begin(), AWeight = Weights.begin();
             AValue != Values.end() && AWeight != Weights.end();
             AValue++, AWeight++)
        {
                RunSum += (*AValue)*(*AWeight);
        }

        return(RunSum);
}

long double WeightedSuml(const vector <double> &Values, const vector <double> &Weights)
{
        if (Values.size() != Weights.size())
        {
                cerr << "\n\tThe Values vector and the Weights vector need to be the same size in WeightedSuml().  Returning NAN\n\n";
                return(nanl("nan"));
        }

        long double RunSum = 0.0;
        for (vector<double>::const_iterator AValue = Values.begin(), AWeight = Weights.begin();
             AValue != Values.end() && AWeight != Weights.end();
             AValue++, AWeight++)
        {
                RunSum += ((long double) ((*AValue)*(*AWeight)));
        }

        return(RunSum);
}

double Avg(const vector <double> &Values)
{
	if (!Values.empty())
	{
		return(Suml(Values)/((long double) Values.size()));
	}
	else
	{
		return(nan("nan"));
	}
}

double Avg(const vector <int> &Values)
{
	if (!Values.empty())
	{
		return(((double) Sum(Values))/((double) Values.size()));
	}
	else
	{
		return(nan("NAN"));
	}
}

long double Avgl(const vector <long double> &Values)
{
	if (!Values.empty())
	{
		return(Suml(Values)/((long double) Values.size()));
	}
	else
	{
		return(nanl("NAN"));
	}
}

double WeightedAvg(const vector <double> &Values, const vector <double> &Weights)
{
	if (!Values.empty())
	{
		return(WeightedSum(Values, Weights)/(Sum(Weights)));
	}
	else
	{
		return(nan("nan"));
	}
}

double Variance(const vector <int> &Values)
{
	if (Values.size() > 1)
	{
		long double RunSum1 = 0.0;
		long double RunSum2 = 0.0;

		for (vector<int>::const_iterator AValue = Values.begin(); AValue != Values.end(); AValue++)
		{
			RunSum1 += powl((long double) *AValue, 2.0);
			RunSum2 += ((long double) *AValue);
		}

		return((RunSum1 - (powl(RunSum2, 2.0)/((long double) Values.size()))) / (((long double) Values.size()) - 1.0));
	}
	else
	{
		return(nan("NAN"));
	}
}

double Variance(const vector <double> &Values)
{
        if (Values.size() > 1)
        {
                long double RunSum1 = 0.0;
                long double RunSum2 = 0.0;

                for (vector<double>::const_iterator AValue = Values.begin(); AValue != Values.end(); AValue++)
                {
                        RunSum1 += powl((long double) *AValue, 2.0);
                        RunSum2 += ((long double) *AValue);
                }

                return((RunSum1 - (powl(RunSum2, 2.0)/((long double) Values.size()))) / (((long double) Values.size()) - 1.0));
        }
        else
        {
                return(nan("nan"));
        }
}

long double Variancel(const vector <long double> &Values)
{
        if (Values.size() > 1)
        {
                long double RunSum1 = 0.0;
                long double RunSum2 = 0.0;

                for (vector<long double>::const_iterator AValue = Values.begin(); AValue != Values.end(); AValue++)
                {
                        RunSum1 += powl(*AValue, 2.0);
                        RunSum2 += *AValue;
                }

                return((RunSum1 - (powl(RunSum2, 2.0)/((long double) Values.size()))) / (((long double) Values.size()) - 1.0));
        }
        else
        {
                return(nanl("nan"));
        }
}

long double Variancel(const vector <double> &Values)
{
        if (Values.size() > 1)
        {
                long double RunSum1 = 0.0;
                long double RunSum2 = 0.0;

                for (vector<double>::const_iterator AValue = Values.begin(); AValue != Values.end(); AValue++)
                {
                        RunSum1 += powl((long double) *AValue, 2.0);
                        RunSum2 += (long double) *AValue;
                }

                return((RunSum1 - (powl(RunSum2, 2.0)/((long double) Values.size()))) / (((long double) Values.size()) - 1.0));
        }
        else
        {
                return(nanl("nan"));
        }
}

double InterquartileVal(const int Quartile, vector <double> TheValues)
//  I am using the Minitab method of finding quartiles as described in Dr. Math forum: http://mathforum.org/library/drmath/view/60969.html
//    essentially, find out what element we are looking for by the formula   ElementNum = (Quartile/4)*(n+1) - 1
//    The minus one is because the first element is index number 0 in a Cpp vector.
//    The ElementNumber is not rounded as we use the fractional part to do a linear interpolation between elements ((int) ElementNum) and
//    ((int) ElementNum) + 1.
{
	for (vector<double>::iterator AValue = TheValues.begin(); AValue != TheValues.end(); AValue++)
	{
		if (isnan(*AValue))
		{
			AValue = TheValues.erase(AValue);
		}
	}

        if (TheValues.size() < 4)               // this is to prevent index out-of-range errors
        {
                return(nan("NAN"));
        }

        sort(TheValues.begin(), TheValues.end());

        if (Quartile > 0 && Quartile < 4)
        {

                double ElementNum = (((double) Quartile)/4.0)*(((double) TheValues.size()) + 1.0) - 1.0;  // the -1.0 is for vector indexing offset
                double DecimalPart = remainder(((double) Quartile)*(((double) TheValues.size()) + 1.0), 4.0)/4.0;
                return(TheValues[((int) ElementNum)] + (DecimalPart*(TheValues[((int) ElementNum) + 1] - TheValues[((int) ElementNum)])));
        }
        else
        {
                return(nan("NAN"));
        }
}


		
#endif
