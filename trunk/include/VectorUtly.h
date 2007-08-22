#ifndef _VECTORUTLY_H
#define _VECTORUTLY_H

#include <vector>

template <class GenType> vector <size_t> FindList(const GenType &Item, const vector <GenType> &Values);

template <class GenType> vector <GenType> SubsetList(const vector <GenType> &Values, const vector <size_t> &WantedIndicies);

template <class GenType> vector <GenType> Unique(vector <GenType> Values);

template <class GenType> vector <GenType> Merge(const vector <GenType> &AVect, const vector <GenType> &BVect);

template <class GenType> vector <GenType> MergeUnique(const vector <GenType> &AVect, const vector <GenType> &BVect);

#ifndef _DOLINKING_
// For now...
#include "VectorUtly.C"
#endif

#endif
