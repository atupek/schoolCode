// huffcode.h 
// Ann Tupek
// CS 611
// 6 Dec 2012
// Assignment 6
// 
// Header for class HuffCode
// Skeleton from Glenn G Chappell

#ifndef FILE_HUFFCODE_H_INCLUDED
#define FILE_HUFFCODE_H_INCLUDED

#include <string>         // for std::string
using std::string;
#include <unordered_map>  // for std::unordered_map

#include <tuple>
using std::tuple;
using std::make_tuple;
using std::get;

#include <vector>
using std::vector;

#include <queue>
using std::priority_queue;

#include <algorithm>
using std::sort;

#include <map>
using std::map;



// Class HuffCode
// Encoding & decoding using a Huffman code
class HuffCode {

// ***** HuffCode: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, copy =, dctor used

// ***** HuffCode: general public functions *****
public:

    void setWeights(const std::unordered_map<char, int> & theweights);

    std::string encode(const std::string & text) const;

    std::string decode(const std::string & codestr) const;

// ***** HuffCode: data members *****
private:


};  // End class HuffCode


#endif //#ifndef FILE_HUFFCODE_H_INCLUDED

