#ifndef _HISTOGRAM_H
#define _HISTOGRAM_H


#include <vector>


class Histogram
{
	public:
		Histogram();
		Histogram(const vector <int> &TheValues);
		Histogram(const vector <double> &TheValues);
		
		void BuildHistogram(const vector <int> &TheValues);
		void BuildHistogram(const vector <double> &TheValues);
		unsigned int FreqMax() const;
		unsigned int FreqMin() const;
		unsigned int Freq(const int &BinNum) const;
		double MinRange() const;
		double MaxRange() const;
		double BinSize() const;
		size_t BinCount() const;
		double Center(const int &BinNum) const;
		vector <double> Hinges(const int &BinNum) const;
		bool SourceValsInt() const;

		double OptimalBinSize(vector <double> TheValues) const;
		double OptimalBinSize(const vector <int> &TheValues) const;

		int WhichBin(const double &Value) const;
		int WhichBin(const int &Value) const;

		void PrintHistogram() const;

	private:
		vector <unsigned int> myFrequencies;
		double myMinRange;
		double myMaxRange;
		double myBinSize;
		int myBinCount;
		bool myIntSourceVals;

		// This is an optimized version, assumes that there are no NaNs and that the values are sorted...
		double InterquartileVal(const int &Quartile, const vector <double> &TheValues) const;
};

#endif
