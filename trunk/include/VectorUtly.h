#ifndef _VECTORUTLY_H
#define _VECTORUTLY_H

/*! \defgroup VectorUtly Vector Utilities
 *  \brief Some basic utility functions based on the vector<> container.
 *
 *  \deprecated These were developed before the knowledge of iterators
 *              and the standard "algorithms" module.  In addition,
 *              they don't work well as a shared library object due
 *              to the lack of 'export' statements.
 *
 *  @{
*/

/*! \file VectorUtly.h
 *
*/

#include <vector>

template <class GenType> vector <size_t> FindList(const GenType &Item, const vector <GenType> &Values);

template <class GenType> vector <GenType> SubsetList(const vector <GenType> &Values, const vector <size_t> &WantedIndicies);

template <class GenType> vector <GenType> Unique(vector <GenType> Values);

template <class GenType> vector <GenType> Merge(const vector <GenType> &AVect, const vector <GenType> &BVect);

template <class GenType> vector <GenType> MergeUnique(const vector <GenType> &AVect, const vector <GenType> &BVect);

/*! @} */	// end of VectorUtly group

#endif
