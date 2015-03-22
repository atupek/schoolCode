// colorstack_test2.cpp
// VERSION 2
// Glenn G. Chappell
// 16 Nov 2014
//
// For CS 411/611 Fall 2014
// Test program for function colorStack
// - Large problems added
// Used in Assignment 5, Exercise A
//
// History:
// - v2: Reduced size of large problems

// Includes for code to be tested
#include "colorstack.h" // For function colorStack
#include "colorstack.h" // Double inclusion test

// Includes for testing package & code common to all test programs
#include <iostream>     // for std::cout, std::endl, std::cin
#include <string>       // for std::string
#include <stdexcept>    // for std::runtime_error

// Additional includes for this test program
#include <vector>       // for std::vector


// ************************************************************************
// Testing Package:
//     Class Tester - For Tracking Tests
// ************************************************************************


// class Tester
// For extremely simple unit testing.
// Keeps track of number of tests and number of passes.
// Use test (with success/failure parameter) to do a test.
// Get results with numTests, numPassed, numFailed, allPassed.
// Restart testing with reset.
// Invariants:
//     countTests_ == number of tests (calls to test) since last reset.
//     countPasses_ == number of times function test called with true param
//      since last reset.
//     0 <= countPasses_ <= countTests_.
//     tolerance_ >= 0.
class Tester {

// ***** Tester: ctors, dctor, op= *****
public:

    // Default ctor
    // Sets countTests_, countPasses_ to zero, tolerance_ to given value
    // Pre: None.
    // Post:
    //     numTests == 0, countPasses == 0, tolerance_ == abs(theTolerance)
    // Does not throw (No-Throw Guarantee)
    Tester(double theTolerance = 0.0000001)
        :countTests_(0),
         countPasses_(0),
         tolerance_(theTolerance >= 0 ? theTolerance : -theTolerance)
    {}

    // Compiler-generated copy ctor, copy op=, dctor are used

// ***** Tester: general public functions *****
public:

    // test
    // Handles single test, param indicates pass/fail
    // Pre: None.
    // Post:
    //     countTests_ incremented
    //     countPasses_ incremented if (success)
    //     Message indicating test name (if given)
    //      and pass/fail printed to cout
    // Does not throw (No-Throw Guarantee)
    //  - Assuming exceptions have not been turned on for cout.
    void test(bool success,
              const std::string & testName = "")
    {
        ++countTests_;
        if (success) ++countPasses_;

        std::cout << "    ";
        if (testName != "")
        {
            std::cout << "Test: "
                      << testName
                      << " - ";
        }
        std::cout << (success ? "passed" : "********** FAILED **********")
                  << std::endl;
    }

    // ftest
    // Does single floating-point test.
    // Tests passes iff difference of first two values is <= tolerance.
    // Pre: None.
    // Post:
    //     countTests_ incremented
    //     countPasses_ incremented if (abs(val1-val2) <= tolerance_)
    //     Message indicating test name (if given)
    //      and pass/fail printed to cout
    // Does not throw (No-Throw Guarantee)
    void ftest(double val1,
               double val2,
               const std::string & testName = "")
    { test(val1-val2 <= tolerance_ && val2-val1 <= tolerance_, testName); }

    // reset
    // Resets *this to default constructed state
    // Pre: None.
    // Post:
    //     countTests_ == 0, countPasses_ == 0
    // Does not throw (No-Throw Guarantee)
    void reset()
    {
        countTests_ = 0;
        countPasses_ = 0;
    }

    // numTests
    // Returns the number of tests that have been done since last reset
    // Pre: None.
    // Post:
    //     return == countTests_
    // Does not throw (No-Throw Guarantee)
    int numTests() const
    { return countTests_; }

    // numPassed
    // Returns the number of tests that have passed since last reset
    // Pre: None.
    // Post:
    //     return == countPasses_
    // Does not throw (No-Throw Guarantee)
    int numPassed() const
    { return countPasses_; }

    // numFailed
    // Returns the number of tests that have not passed since last reset
    // Pre: None.
    // Post:
    //     return + countPasses_ == numTests_
    // Does not throw (No-Throw Guarantee)
    int numFailed() const
    { return countTests_ - countPasses_; }

    // allPassed
    // Returns true if all tests since last reset have passed
    // Pre: None.
    // Post:
    //     return == (countPasses_ == countTests_)
    // Does not throw (No-Throw Guarantee)
    bool allPassed() const
    { return countPasses_ == countTests_; }

    // setTolerance
    // Sets tolerance_ to given value
    // Pre: None.
    // Post:
    //     tolerance_ = abs(theTolerance)
    // Does not throw (No-Throw Guarantee)
    void setTolerance(double theTolerance)
    { tolerance_ = (theTolerance >= 0 ? theTolerance : -theTolerance); }

// ***** Tester: data members *****
private:

    int countTests_;    // Number of tests done since last reset
    int countPasses_;   // Number of tests passed since last reset
    double tolerance_;  // Tolerance for floating-point near-equality tests

};  // end class Tester


// ************************************************************************
// Testing Package:
//     Class TypeCheck - Helper Class for Type Checking
// ************************************************************************


// class TypeCheck
// This class exists in order to have static member function check, which
// takes a parameter of a given type, by reference. Objects of type
// TypeCheck<T> cannot be created.
// Usage:
//     TypeCheck<MyType>::check(x)
//     returns true if the type of x is (MyType) or (const MyType),
//     otherwise false.
// Invariants: None.
// Requirements on Types: None.
template<typename T>
class TypeCheck {

private:

    // Uncopyable class. Do not define copy ctor, copy assn.
    TypeCheck(const TypeCheck &);
    TypeCheck<T> & operator=(const TypeCheck &);

    // Compiler-generated dctor is used (but irrelevant).

public:

    // check
    // The function and function template below simulate a single function
    // that takes a single parameter, and returns true iff the parameter has
    // type T or (const T).

    // check (reference-to-const T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool check(const T & param)
    { return true; }

    // check (reference-to-const non-T)
    // Pre: None.
    // Post:
    //     Return is false.
    // Requirements on types: None.
    // Does not throw (No-Throw Guarantee)
    template <typename OtherType>
    static bool check(const OtherType & param)
    { return false; }

};  // End class TypeCheck


// ************************************************************************
// Testing Package:
//     Class Counter - Helper Class for Counting Calls & Objects, Throwing
// ************************************************************************


// class Counter
// Item type for counting ctor, dctor, op= calls, counting existing
//  objects, and possibly throwing on copy. Has operator< (which always
//  returns false), allowing it to be the value type of a sorted container.
// If static member copyThrow_ is set, then copy ctor and copy assn throw
//  std::runtime_error. Exception object's "what" member is set to "C" by
//  the copy ctor and "A" by copy assn.
// Increments static data member ctorCount_ on default construction and
//  successful copy construction. Increments static data member assnCount_
//  on successful copy assignment. Increments static data member
//  dctorCount_ on destruction.
// Increments static data member existing_ on construction, and decrements
//  it on destruction.
// Static data member maxExisting_ is highest value of existing_ since last
//  reset, or start of program if reset has never been called.
// Invariants:
//     Counter::existing_ is number of existing objects of this class.
//     Counter::ctorCount_ is number of successful ctor calls since
//      most recent call to reset, or start of program if reset has never
//      been called.
//     Counter::dctorCount_ is (similarly) number of dctor calls.
//     Counter::assnCount_ is (similarly) number of copy assn calls.
//     Counter::maxExisting_ is (similarly) highest value existing_ has
//      assumed.
class Counter {

// ***** Counter: Ctors, dctor, op= *****
public:

    // Default ctor
    // Pre: None.
    // Post:
    //     (ctorCount_ has been incremented.)
    //     (existing_ has been incremented.)
    // Does not throw (No-Throw Guarantee)
    Counter()
    {
        ++existing_;
        if (existing_ > maxExisting_)
            maxExisting_ = existing_;
        ++ctorCount_;
    }

    // Copy ctor
    // Throws std::runtime_error if copyThrow_.
    // Pre: None.
    // Post:
    //     (ctorCount_ has been incremented.)
    //     (existing_ has been incremented.)
    // May throw std::runtime_error
    // Strong Guarantee
    Counter(const Counter & other)
    {
        if (copyThrow_)
            throw std::runtime_error("C");
        ++existing_;
        if (existing_ > maxExisting_)
            maxExisting_ = existing_;
        ++ctorCount_;
    }

    // Copy assignment
    // Throws std::runtime_error if copyThrow_.
    // Pre: None.
    // Post:
    //     Return value is *this.
    //     (assnCount_ has been incremented.)
    // May throw std::runtime_error
    // Strong Guarantee
    Counter & operator=(const Counter & rhs)
    {
        if (copyThrow_)
            throw std::runtime_error("A");
        ++assnCount_;
        return *this;
    }

    // Dctor
    // Pre: None.
    // Post:
    //     (dctorCount_ has been incremented.)
    //     (existing_ has been decremented.)
    // Does not throw (No-Throw Guarantee)
    ~Counter()
    {
        --existing_;
        ++dctorCount_;
    }

// ***** Counter: Functions dealing with count *****
public:

    // reset
    // Pre: None.
    // Post:
    //     maxExisting_ == existing_.
    //     ctorCount_ == 0.
    //     dctorCount_ == 0.
    //     assnCount_ == 0.
    //     copyThrow_ == shouldThrow.
    // Does not throw (No-Throw Guarantee)
    static void reset(bool shouldThrow = false)
    {
        maxExisting_ = existing_;
        ctorCount_ = 0;
        dctorCount_ = 0;
        assnCount_ = 0;
        copyThrow_ = shouldThrow;
    }

    // getExisting
    // Pre: None.
    // Post:
    //     return == existing_.
    // Does not throw (No-Throw Guarantee)
    static int getExisting()
    { return existing_; }

    // getMaxExisting
    // Pre: None.
    // Post:
    //     return == maxExisting_.
    // Does not throw (No-Throw Guarantee)
    static int getMaxExisting()
    { return maxExisting_; }

    // getCtorCount
    // Pre: None.
    // Post:
    //     return == ctorCount_.
    // Does not throw (No-Throw Guarantee)
    static int getCtorCount()
    { return ctorCount_; }

    // getDctorCount
    // Pre: None.
    // Post:
    //     return == dctorCount_.
    // Does not throw (No-Throw Guarantee)
    static int getDctorCount()
    { return dctorCount_; }

    // getAssnCount
    // Pre: None.
    // Post:
    //     return == assnCount_.
    // Does not throw (No-Throw Guarantee)
    static int getAssnCount()
    { return assnCount_; }

    // setCopyThrow
    // Pre: None.
    // Post:
    //     copyThrow_ == shouldThrow
    // Does not throw (No-Throw Guarantee)
    static void setCopyThrow(bool shouldThrow)
    { copyThrow_ = shouldThrow; }

// ***** Counter: Data Members *****
private:

    static int existing_;     // # of existing objects
    static int maxExisting_;  // Max # of existing objects
    static int ctorCount_;    // # of successful (non-throwing) ctor calls
    static int dctorCount_;   // # of dctor calls
    static int assnCount_;    // # of successful (non-throwing) copy = calls
    static bool copyThrow_;   // true if copy operations (ctor, =) throw

};  // End class Counter

// Definition of static data member of class Counter
int Counter::existing_ = 0;
int Counter::maxExisting_ = 0;
int Counter::ctorCount_ = 0;
int Counter::dctorCount_ = 0;
int Counter::assnCount_ = 0;
bool Counter::copyThrow_ = false;


// operator< (Counter)
// Dummy-ish operator<, forming a strict weak order for Counter class
// Returns false (which is legal for a strict weak order; all objects of
//  type Counter are equivalent).
// Pre: None.
// Post:
//     Return value == false.
// Does not throw (No-Throw Guarantee)
bool operator<(const Counter & a,
               const Counter & b)
{ return false; }


// ************************************************************************
// Definitions for this test suite
// ************************************************************************


// Type for a block; must have size 4
typedef std::vector<int> Bk;

// Indices within a block
const int BC = 0;
const int TC = 1;
const int HT = 2;
const int WT = 3;

// makeb
// Make a block with the given values
Bk makeb(int bc, int tc, int ht, int wt)
{
    //return Bk { bc, tc, ht, wt };
    Bk b;
    b.push_back(bc);
    b.push_back(tc);
    b.push_back(ht);
    b.push_back(wt);
    return b;
}


// ************************************************************************
// Test Suite Functions
// ************************************************************************


// test_colorStack_small
// Test suite for function colorStack: small examples
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_colorStack_small(Tester & t)
{
    std::cout << "Test Suite: function colorStack - small examples"
              << std::endl;

    std::vector<Bk> blox;              // Holds collections of blocks
    const std::vector<Bk> & cb(blox);  // Const ref to above
    int minh;                          // Holds minimum height
    int ans;                           // Holds desired return value

    // Single block, does not stack on self, no solution
    blox.clear();
    blox.push_back(makeb(1, 2, 5, 2));
    minh = 6;
    ans = -1;
    t.test(colorStack(cb, minh) == ans,
        "Single block, no stack on self, no solution");

    // Single block, does not stack on self, has solution
    blox.clear();
    blox.push_back(makeb(1, 2, 5, 2));
    minh = 5;
    ans = 2;
    t.test(colorStack(cb, minh) == ans,
        "Single block, no stack on self, has solution");

    // Single block, stacks on self, small min ht
    blox.clear();
    blox.push_back(makeb(1, 1, 5, 2));
    minh = 4;
    ans = 2;
    t.test(colorStack(cb, minh) == ans,
        "Single block, stacks on self, small min ht");

    // Single block, stacks on self, larger min ht
    blox.clear();
    blox.push_back(makeb(1, 1, 5, 2));
    minh = 6;
    ans = 4;
    t.test(colorStack(cb, minh) == ans,
        "Single block, stacks on self, larger min ht");

    // Single block, stacks on self, even larger min ht
    blox.clear();
    blox.push_back(makeb(1, 1, 5, 2));
    minh = 30;
    ans = 12;
    t.test(colorStack(cb, minh) == ans,
        "Single block, stacks on self, even larger min ht");

    // Two blocks, no stack on each other, no solution
    blox.clear();
    blox.push_back(makeb(1, 2, 2, 4));
    blox.push_back(makeb(3, 4, 3, 3));
    minh = 5;
    ans = -1;
    t.test(colorStack(cb, minh) == ans,
        "Two blocks, no stack on each other, no solution");

    // Two blocks, no stack on each other, one solution
    blox.clear();
    blox.push_back(makeb(1, 2, 2, 4));
    blox.push_back(makeb(3, 4, 4, 3));
    minh = 4;
    ans = 3;
    t.test(colorStack(cb, minh) == ans,
        "Two blocks, no stack on each other, one solution");

    // Two blocks, no stack on each other, two solutions #1
    blox.clear();
    blox.push_back(makeb(1, 2, 2, 4));
    blox.push_back(makeb(3, 4, 4, 3));
    minh = 2;
    ans = 3;
    t.test(colorStack(cb, minh) == ans,
        "Two blocks, no stack on each other, two solutions #1");

    // Two blocks, no stack on each other, two solutions #2
    blox.clear();
    blox.push_back(makeb(1, 2, 2, 4));
    blox.push_back(makeb(3, 4, 4, 5));
    minh = 2;
    ans = 4;
    t.test(colorStack(cb, minh) == ans,
        "Two blocks, no stack on each other, two solutions #2");

    // Two blocks, stack on each other, no solution
    blox.clear();
    blox.push_back(makeb(1, 2, 2, 4));
    blox.push_back(makeb(2, 3, 4, 5));
    minh = 7;
    ans = -1;
    t.test(colorStack(cb, minh) == ans,
        "Two blocks, stack on each other, no solutions");

    // Two blocks, stack on each other, has solution
    blox.clear();
    blox.push_back(makeb(1, 2, 2, 4));
    blox.push_back(makeb(2, 3, 4, 5));
    minh = 6;
    ans = 9;
    t.test(colorStack(cb, minh) == ans,
        "Two blocks, stack on each other, has solution");

    // Two blocks, alternately stack, small min ht
    blox.clear();
    blox.push_back(makeb(1, 2, 2, 4));
    blox.push_back(makeb(2, 1, 4, 3));
    minh = 1;
    ans = 3;
    t.test(colorStack(cb, minh) == ans,
        "Two blocks, alternately stack, small min ht");

    // Two blocks, alternately stack, larger min ht
    blox.clear();
    blox.push_back(makeb(1, 2, 2, 4));
    blox.push_back(makeb(2, 1, 4, 3));
    minh = 10;
    ans = 10;
    t.test(colorStack(cb, minh) == ans,
        "Two blocks, alternately stack, larger min ht");

    // Two blocks, alternately stack, even larger min ht
    blox.clear();
    blox.push_back(makeb(1, 2, 2, 4));
    blox.push_back(makeb(2, 1, 4, 3));
    minh = 39;
    ans = 45;
    t.test(colorStack(cb, minh) == ans,
        "Two blocks, alternately stack, even larger min ht");

    // Example #1 from Assignment Description
    blox.clear();
    blox.push_back(makeb(1, 1, 2, 5));
    blox.push_back(makeb(2, 1, 5, 2));
    blox.push_back(makeb(1, 3, 4, 1));
    minh = 14;
    ans = 18;
    t.test(colorStack(cb, minh) == ans,
        "Example #1 from assignment description");

    // Example #2 from Assignment Description
    blox.clear();
    blox.push_back(makeb(1, 2, 4, 3));
    blox.push_back(makeb(2, 3, 5, 1));
    blox.push_back(makeb(3, 4, 2, 6));
    blox.push_back(makeb(4, 5, 1, 2));
    minh = 20;
    ans = -1;
    t.test(colorStack(cb, minh) == ans,
        "Example #2 from assignment description");
}


// test_colorStack_medium
// Test suite for function colorStack: medium examples
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_colorStack_medium(Tester & t)
{
    std::cout << "Test Suite: function colorStack - medium examples"
              << std::endl;

    std::vector<Bk> blox;              // Holds collections of blocks
    const std::vector<Bk> & cb(blox);  // Const ref to above
    int minh;                          // Holds minimum height
    int ans;                           // Holds desired return value


    // Medium Example #1
    blox.clear();
    blox.push_back(makeb(1, 3, 2, 3));
    blox.push_back(makeb(3, 4, 4, 3));
    blox.push_back(makeb(4, 1, 4, 2));
    blox.push_back(makeb(2, 2, 1, 4));
    blox.push_back(makeb(4, 1, 3, 3));
    blox.push_back(makeb(3, 4, 3, 4));
    blox.push_back(makeb(1, 3, 3, 2));
    blox.push_back(makeb(3, 2, 4, 1));
    blox.push_back(makeb(1, 4, 6, 6));
    minh = 37;
    ans = 22;
    t.test(colorStack(cb, minh) == ans,
        "Medium example #1");

    // Medium Example #2
    blox.clear();
    blox.push_back(makeb(5, 4, 4, 1));
    blox.push_back(makeb(2, 4, 9, 7));
    blox.push_back(makeb(1, 3, 9, 5));
    blox.push_back(makeb(3, 4, 8, 5));
    blox.push_back(makeb(2, 3, 3, 3));
    blox.push_back(makeb(1, 2, 5, 3));
    blox.push_back(makeb(3, 1, 9, 7));
    blox.push_back(makeb(4, 1, 5, 2));
    blox.push_back(makeb(5, 4, 3, 2));
    blox.push_back(makeb(3, 5, 5, 4));
    blox.push_back(makeb(4, 1, 4, 3));
    blox.push_back(makeb(2, 3, 4, 2));
    blox.push_back(makeb(1, 2, 6, 2));
    blox.push_back(makeb(3, 5, 5, 3));
    blox.push_back(makeb(5, 1, 9, 4));
    blox.push_back(makeb(2, 5, 8, 6));
    blox.push_back(makeb(1, 5, 9, 8));
    minh = 48;
    ans = 20;
    t.test(colorStack(cb, minh) == ans,
        "Medium example #2");
}


// test_colorStack_large
// Test suite for function colorStack: large examples
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_colorStack_large(Tester & t)
{
    std::cout << "Test Suite: function colorStack - large examples"
              << std::endl;

    std::vector<Bk> blox;              // Holds collections of blocks
    const std::vector<Bk> & cb(blox);  // Const ref to above
    int minh;                          // Holds minimum height
    int ans;                           // Holds desired return value

    {
    // Large Example #1
    blox.clear();
    const int levels = 100;
    for (int i = 0; i < levels; ++i)
    {
        blox.push_back(makeb(3*i+1, 3*i+2, 3, 3));
        blox.push_back(makeb(3*i+2, 3*i+3, 3, 3));
        blox.push_back(makeb(3*i+3, 3*i+4, 3, 3));
        blox.push_back(makeb(3*i+1, 3*i+3, 5, 5));
        blox.push_back(makeb(3*i+2, 3*i+4, 5, 5));
        blox.push_back(makeb(3*i+1, 3*i+2, 4, 2));
        blox.push_back(makeb(3*i+2, 3*i+3, 4, 2));
        blox.push_back(makeb(3*i+3, 3*i+4, 4, 2));
    }
    minh = 12*levels;
    ans = 6*levels;
    t.test(colorStack(cb, minh) == ans,
        "Large example #1");
    }

    {
    // Large Example #2
    blox.clear();
    const int levels = 5000;
    blox.push_back(makeb(1, 2, 3, 3));
    blox.push_back(makeb(2, 1, 3, 3));
    blox.push_back(makeb(1, 1, 3, 3));
    blox.push_back(makeb(2, 2, 3, 3));
    blox.push_back(makeb(2, 1, 3, 3));
    blox.push_back(makeb(1, 2, 4, 2));
    blox.push_back(makeb(2, 1, 4, 2));
    minh = 8*levels;
    ans = 4*levels;
    t.test(colorStack(cb, minh) == ans,
        "Large example #2");
    }
}


// test_colorStack
// Test suite for function colorStack
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate messages have been printed to cout.
// Does not throw (No-Throw Guarantee)
void test_colorStack(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR FUNCION colorStack" << std::endl;
    test_colorStack_small(t);
    test_colorStack_medium(t);
    test_colorStack_large(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs function colorStack test suite, prints results to cout.
int main()
{
    Tester t;
    test_colorStack(t);

    std::cout << std::endl;
    if (t.allPassed())
    {
        std::cout << "All tests successful"
                  << std::endl;
    }
    else
    {
        std::cout << "Tests ********** UNSUCCESSFUL **********"
                  << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Press ENTER to quit ";
    while (std::cin.get() != '\n') ;

    return 0;
}

