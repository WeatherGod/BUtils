#ifndef _VECTORUTLY_C
#define _VECTORUTLY_C
using namespace std;

/*! \file VectorUtly.C
 *  \ingroup VectorUtly
 *
*/

#include <vector>
#include <algorithm>		// for unique(), sort(),....

#include "VectorUtly.h"

template <class GenType>
vector <size_t> FindList(const GenType &Item, const vector <GenType> &Values)
//  if no matches are found, then a zero sized vector is returned
// returns the index numbers where the items were found.
{
	vector <size_t> IndexList(0);

	for (size_t i = 0; i < Values.size(); i++)
	{
		if (Item == Values[i])
		{
			IndexList.push_back(i);
		}
	}

	return(IndexList);
}

template <class GenType>
vector <GenType> SubsetList(const vector <GenType> &Values, const vector <size_t> &WantedIndicies)
{
	vector <GenType> NewValues(WantedIndicies.size());

	for (size_t ValueIndex = 0; ValueIndex < NewValues.size(); ValueIndex++)
	{
		NewValues[ValueIndex] = Values[WantedIndicies[ValueIndex]];
	}

	return(NewValues);
}

template <class GenType>
vector <GenType> Unique(vector <GenType> FullList)
{
	sort(FullList.begin(), FullList.end());
	typename vector<GenType>::iterator NewEnd = unique(FullList.begin(), FullList.end());
	FullList.resize(NewEnd - FullList.begin());
        return(FullList);
}

template <class GenType>
vector <GenType> Merge(const vector <GenType> &AVect, const vector <GenType> &BVect)
// Merges two sorted vectors together, resulting in a new, sorted vector.
{
	vector <GenType> NewList(AVect.size() + BVect.size());
	merge(AVect.begin(), AVect.end(), BVect.begin(), BVect.end(), NewList.begin());

	return(NewList);
}

template <class GenType>
vector <GenType> MergeUnique(const vector <GenType> &AVect, const vector <GenType> &BVect)
// Merges two sorted vectors together, resulting in a new, sorted vector of unique values.
{
        vector <GenType> NewList(AVect.size() + BVect.size());
	typename vector<GenType>::iterator EndNewVect = set_union(AVect.begin(), AVect.end(), BVect.begin(), BVect.end(), NewList.begin());
        NewList.resize(EndNewVect - NewList.begin());

        return(NewList);
}


#endif
