// Ann Tupek
// CS611 HW 3A
// Due 10/16/14
//
// gcs.h
// returns greatest contiguous sum of a sequence

#ifndef GCS_H
#define GCS_H

#include<tuple>
#include<iterator>
#include<algorithm>
using std::tuple;
using std::make_tuple;
using std::get;
using std::max;

#include<iostream>
using std::cout;
using std::endl;

typedef tuple<int, int, int, int> workingSums;


template<typename RAIter>
workingSums gcsHelper(RAIter first, RAIter last)
{
    const int A = 0; //indices of workingSums
    const int B = 1;
    const int C = 2;
    const int D = 3;
    
    int gcs;            //A: GCS of sequence
    int gcsFromStart;   //B: GCS that includes first term
    int gcsFromEnd;     //C: GCS that includes last term
    int totalSum;       //D: total sum of the sequence
    size_t size = distance(first, last);
    
    //base cases
    if(size == 0)       //if empty, return 0
    {
        return 0;
    }
    if(size <=1)
    {
        gcs = max(*first, 0);
        gcsFromStart = max(*first, 0);
        gcsFromEnd = max(*first, 0);
        totalSum = *first;
        workingSums gcsValues = make_tuple(gcs, gcsFromStart, gcsFromEnd, totalSum);

        return gcsValues;
    }
    
    //recursive case
    RAIter middle = first;
    advance(middle, size/2);

    workingSums gcsValues1 = gcsHelper(first, middle);
    workingSums gcsValues2 = gcsHelper(middle, last);
    
    //in these cases, negative numbers have been taken care of in the base case,
    //so no need to do another comparison with 0 here
    //calculate gcs as max of gcs of first, gcs of second, gcsFromEnd of first plus gcsFromStart of second
    gcs = max(get<A>(gcsValues1), max(get<A>(gcsValues2),
              (get<C>(gcsValues1)+get<B>(gcsValues2))));
    //calculate gcsFromStart as max of totalSum of first plus gcsFromStart of second, gcsFromStart of first
    gcsFromStart = max((get<D>(gcsValues1)+get<B>(gcsValues2)), get<B>(gcsValues1));
    //calculate gcsFromEnd as max of gcsFromEnd of first plus totalSum of second, gcsFromEnd of second
    gcsFromEnd = max((get<C>(gcsValues1)+get<D>(gcsValues2)), get<C>(gcsValues2));
    //calculate totalSum as totalSum of first plus totalSum of second
    totalSum = (get<D>(gcsValues1)+get<D>(gcsValues2));

    workingSums gcsValues = make_tuple(gcs, gcsFromStart, gcsFromEnd, totalSum);

    return gcsValues;
}

template<typename RAIter>
int gcs(RAIter first, RAIter last)
{
    workingSums finalSums = gcsHelper(first, last);
    
    return get<0>(finalSums);
}

#endif
