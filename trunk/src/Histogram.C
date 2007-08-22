#ifndef _HISTOGRAM_C
#define _HISTOGRAM_C

using namespace std;

#include <iostream>
#include <string>

#include <vector>
#include <algorithm>			// for sort(), min_element(), max_element()
#include <cmath>			// for sqrt, pow, powl, ceill, floor, isnan()
#include "StatUtly.h"			// for Sumu(), Variance()
#include "StrUtly.h"			// for DoubleToStr()

#include "Histogram.h"


Histogram::Histogram()
	:	myFrequencies(0),
		myMinRange(0.0),
		myMaxRange(0.0),
		myBinSize(0.0),
		myBinCount(0),
		myIntSourceVals(false)
{
}

Histogram::Histogram(const vector <int> &TheValues)
	:	myFrequencies(0),
		myMinRange(0.0),
		myMaxRange(0.0),
		myBinSize(0.0),
		myBinCount(0),
		myIntSourceVals(false)
{
	BuildHistogram(TheValues);
}

Histogram::Histogram(const vector <double> &TheValues)
	:	myFrequencies(0),
                myMinRange(0.0),
                myMaxRange(0.0),
                myBinSize(0.0),
                myBinCount(0),
                myIntSourceVals(false)
{
	BuildHistogram(TheValues);
}

void Histogram::BuildHistogram(const vector <int> &TheValues)
{
	myIntSourceVals = true;
	myBinSize = 0.0;
	myBinCount = 1;

	if (!TheValues.empty())
	{
        	myMinRange = ((double) *min_element(TheValues.begin(), TheValues.end()));
        	myMaxRange = ((double) *max_element(TheValues.begin(), TheValues.end()));

        	myBinSize = OptimalBinSize(TheValues);

        	if (myBinSize > 0.0)
        	{
                	myBinCount = (size_t) ceill(((long double) (myMaxRange - myMinRange))/((long double) myBinSize)) + 1;	
											// one extra since I am dealing with integers
        	}
        	else
        	{
                	myBinCount = 1;
        	}
	}


	if (!myFrequencies.empty())
	{
		// If the vector has already been sized, I want to eliminate all the old information
		// and replace it with the new set of information.
		myFrequencies.resize(0);
	}

	myFrequencies.resize(myBinCount, 0);

        for (vector<int>::const_iterator AValue( TheValues.begin() ); AValue != TheValues.end(); AValue++)
        {
//		cout << "WhichBin(" << TheValues[index] << "): " << WhichBin(TheValues[index]) << endl;
                myFrequencies[WhichBin(*AValue)]++;
        }

#ifdef _DEBUG_CHECK_
	if (Sumu(myFrequencies) != TheValues.size())
	{
		cerr << "\n\tHistogram bug in void Histogram::BuildHistogram(const vector <int> &Values)" << endl;
		cerr << "\t\tSumu(myFrequencies) != TheValues.size()" << endl;
		cerr << "\t\tSumu(myFrequencies): " << Sumu(myFrequencies) << "    TheValues.size(): " << TheValues.size() << endl;
		cerr << "\t\tHistogram was still built, but it is incorrect." << endl << endl;

		PrintHistogram();
	}
#endif

}

void Histogram::BuildHistogram(const vector <double> &TheValues)
{
	myIntSourceVals = false;
	myBinCount = 1;
	myBinSize = 0.0;		//if the vector is empty, then the one bin will be of size zero.

	if (!TheValues.empty())
	{
		double TempBinSize = OptimalBinSize(TheValues);
//		cerr << "TempSize: " << TempBinSize;

		// I don't have to worry about an iterator to TheValues.end() being returned since TheValues.empty() == false
		myMinRange = *min_element(TheValues.begin(), TheValues.end());
        	myMaxRange = *max_element(TheValues.begin(), TheValues.end());

//		cerr << "  Min: " << myMinRange << "  Max: " << myMaxRange << endl;

//		cout << "TempBinSize: " << TempBinSize << endl;

        	if (TempBinSize > 0.0)
        	{
                	myBinCount = (size_t) ceill(((long double) (myMaxRange - myMinRange))/((long double) TempBinSize));

	        	if (myBinCount == 0)
        		{
                		myBinCount = 1;
        		}
		}

        	myBinSize = ((long double) (myMaxRange - myMinRange))/((long double) myBinCount);

//		cerr << "Count: " << myBinCount << "   Size: " << myBinSize << endl;
	}

	if (!myFrequencies.empty())
	{
		// I want to eliminate any information that may be in the histogram
		myFrequencies.resize(0);
	}

	myFrequencies.resize(myBinCount, 0);	// initializes all elements to zero.

        for (vector<double>::const_iterator AVal( TheValues.begin() ); AVal != TheValues.end(); AVal++)
        {
//		cout << "WhichBin(" << TheValues[index] << "): " << WhichBin(TheValues[index]) << endl;
                myFrequencies[WhichBin(*AVal)]++;
        }

#ifdef _DEBUG_CHECK_
	if (Sumu(myFrequencies) != TheValues.size())
        {
                cerr << "\n\tHistogram bug in void Histogram::BuildHistogram(const vector <int> &Values)" << endl;
                cerr << "\t\tSumu(myFrequencies) != TheValues.size()" << endl;
		cerr << "\t\tSumu(myFrequencies): " << Sumu(myFrequencies) << "    TheValues.size(): " << TheValues.size() << endl;
                cerr << "\t\tHistogram was still built, but it is incorrect." << endl << endl;

		PrintHistogram();
        }
#endif

}

unsigned int Histogram::FreqMax() const
// Returns the value of the largest frequency.  Obviously has to be
// a positive number.  If myFrequencies is empty, then there is no
// histogram and the maximum frequency is 0.
{
	if (!myFrequencies.empty())
	{
		return(*max_element(myFrequencies.begin(), myFrequencies.end()));
	}
	else
	{
		return(0);
	}
}

unsigned int Histogram::FreqMin() const
// Returns the value of the smallest frequency.  Obviously has to be
// a positive number.  If myFrequencies is empty, then there is no
// histogram and the minimum frequency is 0.
{
        if (!myFrequencies.empty())
        {
                return(*min_element(myFrequencies.begin(), myFrequencies.end()));
        }
        else
        {
                return(0);
        }
}

unsigned int Histogram::Freq(const int &BinNum) const
// returns the frequency of the bin at BinNum
// Frequencies have to be positive.  If myFrequencies is empty,
// then there is no histogram, thus, the frequency at
// any bin would be zero.
// Any bins outside of the stored range of bins will be
// considered to have a frequency of zero.
{
	if (myFrequencies.empty())
	{
		return(0);
	}

        if (BinNum >= 0 && BinNum < myFrequencies.size())
	{
                return(myFrequencies[BinNum]);
        }
        else
        {
		// The requested bin is outside the stored range for the histogram.
		// It is defined that these hypothetical bins have a frequency of 0.
                return(0);
        }
}

double Histogram::MinRange() const
// Returns the value of the bottom of the range.
{
	if (!myFrequencies.empty())
	{
		return(myMinRange);
	}
	else
	{
		return(nan("NAN"));
	}
}

double Histogram::MaxRange() const
// Returns the value of the top of the range
{
	if (!myFrequencies.empty())
        {
                return(myMaxRange);
        }
        else
        {
                return(nan("NAN"));
        }
}

double Histogram::BinSize() const
// BinSize is the width of values that the bin represents.
// So, a histogram of 10 bins for values ranging from 0 to 5 (inclusive)
// would have a BinSize of 0.5
{
	if (!myFrequencies.empty())
	{
		return(myBinSize);
	}
	else
	{
		return(nan("NAN"));
	}
}

size_t Histogram::BinCount() const
// returns the number of bins
{
	return(myBinCount);
}

double Histogram::Center(const int &BinNum) const
// returns the value of the center of the bin BinNum
{
	if (!myFrequencies.empty())
	{
		vector <double> HingeVals = Hinges(BinNum);

		return((HingeVals[0] + HingeVals[1])/2.0);
	}
	else
	{
		return(nan("NAN"));
	}
}

vector <double> Histogram::Hinges(const int &BinNum) const
// Returns a two-element vector with the values that the edge
// of bin BinNum represents.
{
	vector <double> TheHinges(2, 0.0);

	if (!myFrequencies.empty())
	{
		if (!myIntSourceVals)
		{
			// The values stored for this histogram are doubles, so use real numbers for the edges.
			TheHinges[0] = myMinRange + (BinNum*myBinSize);
			TheHinges[1] = myMinRange + ((BinNum + 1)*myBinSize);
		}
		else
		{
			// The values stored for this histogram are integers, so need to consider discrete math
			// for this.  Technically speaking, the edges are just left and right of the center of
			// the bin, but since we are dealing with discrete values, the hinges are set to
			// the center.
			TheHinges[0] = myMinRange + BinNum;
			TheHinges[1] = myMinRange + BinNum;
		}
	}
	else
	{
		TheHinges[0] = nan("NAN");
		TheHinges[1] = nan("NAN");
	}

	return(TheHinges);
}

bool Histogram::SourceValsInt() const
{
	return(myIntSourceVals);
}

double Histogram::InterquartileVal(const int &Quartile, const vector <double> &TheValues) const
// This is an optimized version of InterquartileVal from StatUtly
// which assumes that TheValues has no NaNs and is already sorted.
{
	const double VectorSize = (double) TheValues.size();
        const size_t ElementNum = (size_t) ((((double) Quartile)/4.0)*(VectorSize + 1.0) - 1.0);  // the -1.0 is for vector indexing offset
        const double DecimalPart = fmod(((double) Quartile)*(VectorSize + 1.0), 4.0)/4.0;
        return(TheValues[ElementNum] + (DecimalPart*(TheValues[ElementNum + 1] - TheValues[ElementNum])));

//	cerr << "Quartile: " << Quartile << "  Size: " << VectorSize << "  ElementNum: " << ElementNum << "  DecimalPart: " << DecimalPart
//	     << "  IQV: " << IQV << endl;
}

double Histogram::OptimalBinSize(vector <double> TheValues) const
// This uses the equation presented in (Scott,1979) that would return the bin size (the histogram interval) that would produce the most
//  efficient, unbiased estimation of the probability density function.
// This equation was found here: http://www.fmrib.ox.ac.uk/analysis/techrep/tr00mj2/tr00mj2/node24.html


//  Another method, referenced on the same webpage was derived by Freedman and Diaconis (and mentioned in [Izenman, 1991]) which gives the bin
//     width to be = 2*(IQR)*N^(-1/3)

// TheValues has any and all NaNs removed and is sorted so that it may call an optimized version
// of InterquartileVal that assumes no NaNs and that the values are sorted, and assumes that the size is greater than 4 after removing NaNs.
{
//	cerr << "Before NaN removal: " << TheValues.size() << endl;

	for (vector<double>::iterator AValue( TheValues.begin() ); AValue != TheValues.end(); AValue++)
	{
		if (isnan(*AValue))
		{
			AValue = TheValues.erase(AValue);
		}
	}

//	cerr << "Vector count after NaN removal: " << TheValues.size() << endl;

	sort(TheValues.begin(), TheValues.end());

        if (TheValues.size() > 4)
        {
                return(2.0*(this->InterquartileVal(3, TheValues) - this->InterquartileVal(1, TheValues))*pow((double) TheValues.size(), (-1.0/3.0)));
        }
        else if (TheValues.size() > 1)
        {
                double VarianceVal = Variance(TheValues);
                if (VarianceVal == 0.0 || isnan(VarianceVal))
                {
                        return(0.1);
                }
                else
                {
                        return(3.49*sqrt(VarianceVal)*pow((double) TheValues.size(), (-1.0/3.0)));
                }
        }
        else
        {
                return(0.0);
        }
}

double Histogram::OptimalBinSize(const vector <int> &TheValues) const
//  for now, since the values are integers, I will just send back a bin size of 1.0 until I think of something better
{
	return(1.0);
}


int Histogram::WhichBin(const double &Value) const
// returns the vector index (a.k.a. - BinNum) that the value falls into
{
	if (!myFrequencies.empty())
	{
		int BinNum = (int) floor(((long double) (Value - myMinRange)) / ((long double) myBinSize));

		if (BinNum >= (myBinCount - 1))
		// if this is true, then I am just double-checking to make sure that the last bin is treated as inclusive
		// this also take avoids any round-off errors that could happen by comparing Value to the saved myMaxRange rather
		// than the calculated upper hinge of the last bin

		//  also note that the code flow will not go into here if Value is less than the lower hinge of the last bin
		{
			// we know that Value is greater than or equal to the lower hinge of the bin number (myBinCount - 1)
			if (Value <= myMaxRange)
			// if this is true, then the Value is within the last bin, being inclusive
			{
				BinNum = myBinCount - 1;
			}
		}

		return(BinNum);
	}
	else
	{
		return(-1);	// I know this is bad style, but I figure that if someone tries to figure out what bin some value is in
					// without properly setting it up, then there is a good possibility that they will try and use the number
					// for a vector index, causing a fault.
				// This can be confusing because -1 is a valid BinNumber if someone wants to know the BinNumber for a value
				// that is below the bottom range.
	}
}

int Histogram::WhichBin(const int &Value) const
// note that since we are dealing with integers, I do not allow the last bin to be "inclusive" since it does not make much sense
{
	if (myFrequencies.size() > 0)
	{
		return(Value - ((int) myMinRange));
	}
	else
	{
		// again, I know it is bad style, but since I am focusing on making it for me, I know I won't be stupid enough to try and get a
			//  binnumber without having built the histogram in the first place!
		return(-1);
	}
}

void Histogram::PrintHistogram() const
// This code isn't very good.  Just meant for debugging purposes...
{
	size_t TallestHist = FreqMax();
	bool ShorteningHoriz = false;
	bool ShorteningVert = false;

	if (myBinCount > 60)
	{
		ShorteningHoriz = true;
	}

	int GraphRows = TallestHist;
	
	if (TallestHist > 40)
	{
		ShorteningVert = true;
		GraphRows = 40;
	}

	double Scaler = max( (TallestHist / ((double) GraphRows)), 1.0);
	
	vector <string> BinLabels(myBinCount, "");

	for (size_t BinIndex = 0; BinIndex < myBinCount; BinIndex++)
	{
		BinLabels[BinIndex] = DoubleToStr(Center(BinIndex), 4);
	}

	for (size_t RowIndex = GraphRows; RowIndex > 0; RowIndex--)
	{
		if (fmod(RowIndex, (Scaler * 2.0)) == 0.0)
		{
			printf("%-3i ", ((int) floor(Scaler * RowIndex)));
		}
		else
		{
			cout << "    ";
		}

		for (size_t BinIndex = 0; BinIndex < myBinCount; BinIndex++)
		{
			if (!ShorteningHoriz)
			{
				if (myFrequencies[BinIndex] >= floor(Scaler * RowIndex))
				{
					cout << "###";
				}
				else
				{
					cout << "   ";
				}
			}
			else
			{
				if (myFrequencies[BinIndex] != 0)
				{
					if (myFrequencies[BinIndex] >= floor(Scaler * RowIndex))
	                                {
        	                                cout << "#";
                	                }
                        	        else
                                	{
                                        	cout << " ";
                                	}
				}
			}

		}
		cout << endl;
	}

	vector <size_t> Lengths(0);

	cout << "    ";
	for (size_t BinIndex = 0; BinIndex < myBinCount; BinIndex++)
	{
		if (!ShorteningHoriz)
		{
			cout << "---";
			Lengths.push_back(BinLabels[BinIndex].size());
		}
		else
		{
			if (myFrequencies[BinIndex] != 0)
			{
				cout << '-';
				Lengths.push_back(BinLabels[BinIndex].size());
			}
		}
	}

	cout << endl;

	size_t LabelRows;
	if (Lengths.empty())
	{
		LabelRows = 0;
	}
	else
	{
		LabelRows = *max_element(Lengths.begin(), Lengths.end());
	}
	
	for (size_t RowIndex = 0; RowIndex < LabelRows; RowIndex++)
	{
		cout << "    ";

		size_t ColIndex = 0;
		for (size_t BinIndex = 0; BinIndex < myBinCount; BinIndex++)
		{
			if (!ShorteningHoriz)
			{
				if (BinLabels[BinIndex].size() > RowIndex)
				{
					cout << ' ' << BinLabels[BinIndex][RowIndex] << ' ';
				}
				else
				{
					cout << "   ";
				}

				ColIndex++;
			}
			else
			{
				if (myFrequencies[BinIndex] != 0)
				{
					if ((ColIndex % 2) == 0)
					{
						if (BinLabels[BinIndex].size() > RowIndex)
						{
							cout << BinLabels[BinIndex][RowIndex];
						}
						else
						{
							cout << ' ';
						}
					}
					else
					{
						cout << ' ';
					}

					ColIndex++;
				}
			}
		}

		cout << endl;
	}

	cout << endl << endl;

	cout << "MinRange: " << myMinRange << "   MaxRange: " << myMaxRange << endl;
	cout << "BinSize: " << myBinSize << "    BinCount: " << myBinCount << endl;
	cout << "FreqMax: " << FreqMax() << "    FreqMin: " << FreqMin() << endl;
	cout << "myIntSourceVals: ";

	if (myIntSourceVals)
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}

}

	


#endif
