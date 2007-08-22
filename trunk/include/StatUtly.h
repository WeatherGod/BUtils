#ifndef _STATUTLY_H
#define _STATUTLY_H

#include <iostream>		// for cerr messages
#include <vector>
#include <algorithm>		// for sort()
#include <cmath>		// for sqrt(), pow(), remainder()

// NOTE: these functions are not the best way to do these things!
// I developed these before knowing the existance of other stuff!

// Also, these functions are NOT NaN-friendly!  For example, Avg() does not skip any NaNs.
// Only InterquartileVal is NaN-friendly.


double Sum(const vector <double> &Values);
int Sum(const vector <int> &Values);
unsigned int Sumu(const vector <unsigned int> &Values);
long double Suml(const vector <long double> &Values);
long double Suml(const vector <double> &Values);

double WeightedSum(const vector <double> &Values, const vector <double> &Weights);
double WeightedSum(const vector <int> &Values, const vector <double> &Weights);
long double WeightedSuml(const vector <long double> &Values, const vector <long double> &Weights);
long double WeightedSuml(const vector <double> &Values, const vector <double> &Weights);

double Avg(const vector <double> &Values);
double Avg(const vector <int> &Values);
long double Avgl(const vector <long double> &Values);

double WeightedAvg(const vector <double> &Values, const vector <double> &Weights);


double Variance(const vector <int> &Values);
double Variance(const vector <double> &Values);
long double Variancel(const vector <long double> &Values);
long double Variancel(const vector <double> &Values);

double InterquartileVal(const int Quartile, vector <double> TheValues);

#ifndef _DOLINKING_
#include "StatUtly.h"
#endif

#endif
