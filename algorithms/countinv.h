// Ann Tupek
// CS611 HW 3B
// Due 10/16/14
//
// countinv.h
// modified stable merge sort that
// returns number of inversions in a sequence
//
// Based on:
// merge_sort.cpp
// VERSION 2
// by Glenn G. Chappell
// 6 Oct 2014
//
// For CS 411/611 Fall 2014
// Merge Sort using Iterators


#ifndef CountInv_H
#define CountInv_H

#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;
#include <iterator>
using std::distance;
using std::advance;
#include <type_traits>
using std::remove_reference;
#include <cstdlib>
using std::size_t;
#include <algorithm>
using std::copy;

// stableMerge
// Merge two halves of a sequence, each sorted, into a single sorted
// sequence in the same location. Merge is done in a stable manner.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, middle) and [middle, last) are valid ranges, each sorted
//      by <.
// Post:
//     [first, last) contains the same items as it did initially, but
//      now sorted by < (in a stable manner).
template <typename RAIter>
size_t stableMerge(RAIter first, RAIter middle, RAIter last)
{
    // ** C++03:
    //typedef typename iterator_traits<FDIter>::value_type Value;
    // ** C++11:
    typedef typename remove_reference<decltype(*first)>::type Value;
    // ** Is this really better?
    
    size_t countInvSum = 0;
    size_t sizeOfFirst;
    
    vector<Value> buffer(distance(first, last));
    // Buffer for temporary copy of data
    RAIter in1 = first;         // Read location in 1st half
    RAIter in2 = middle;        // Read location in 2nd half
    auto out = buffer.begin();  // Write location in buffer
    // ** auto! That *is* better than vector<Value>::iterator
    
    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1)  // Must do comparison this way, to be stable.
        {
            
            *out++ = *in2++;
            
            //calculate remaining items in first partition and
            //add to inversion count
            sizeOfFirst = distance(in1, middle);
            countInvSum += sizeOfFirst;
        }
        else
        {
            *out++ = *in1++;
        }
    }
    
    // Copy remainder of original sequence to buffer.
    // Only one of the following two copy calls will do anything, since
    //  the other is given an empty source range.
    copy(in1, middle, out);
    copy(in2, last, out);
    
    // Copy buffer contents back to original sequence location.
    copy(buffer.begin(), buffer.end(), first);

    return countInvSum;
}

template<typename RAIter>
size_t countInv(RAIter first, RAIter last)
{
    size_t size = distance(first, last);

    size_t inversions = 0;
    
    // BASE CASE
    if (size <= 1)
        return 0;
    
    // RECURSIVE CASE
    RAIter middle = first;
    advance(middle, size/2);  // middle is iterator to middle of range
    
    // Recursively sort the two lists and add inversions
    size_t inversionsInTheFirstHalf = countInv(first, middle);
    size_t inversionsInTheSecondHalf = countInv(middle, last);
    inversions = inversionsInTheFirstHalf + inversionsInTheSecondHalf;
    
    // And merge them and add inversions
    inversions += stableMerge(first,middle,last);

    return inversions;

}

#endif