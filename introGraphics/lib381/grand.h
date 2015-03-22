// grand.h
// VERSION 1.1
// Glenn G. Chappell
// 22 Sep 2014
//
// Public Domain
//
// Header for class GRand
// Allows easy pseudorandom number generation
// There is no associated source file.
// Requires C++11 or later.
//
// Convenience wrapper around C++ Standard Library RNG.
// Intended for simple pseudorandom number generation, or as sample
// code. Not for cryptographic use.

/*

EXAMPLE USAGE

  GRand r;      // RNG object; seeded with unpredictable value
  GRand r2(7);  // Separate RNG; fixed seed gives predictable sequence
  r2.seed(2);   // Another way to seed

  // Print 5 values, each in { 0, 1, 2, ..., 99 }
  for (int k = 0; k < 5; ++k)
      cout << r.i(100) << endl;

  // Flip a coin
  if (r.b())
     cout << "HEADS" << endl;
  else
     cout << "tails" << endl;

  bool b75 = r.b(0.75);  // bool with 75% chance of being true
  double d1 = r.d();     // double in [0.0,1.0), uniformly distributed
  double d3 = r.d(3.0);  // double in [0.0,3.0), uniformly distributed

  // Randomly shuffle a dataset (v is a vector, deque, or array)
  std::shuffle(v.begin(), v.end(), r);

*/

#ifndef FILE_GRAND_H_INCLUDED
#define FILE_GRAND_H_INCLUDED

#include <random>
// For:
//   std::mt19937
//   std::random_device
//   std::uniform_int_distribution
//   std::uniform_real_distribution
//   std::bernoulli_distribution

// Version number
// Guaranteed to increase with with each release.
#define GRAND_PACKAGE_VERSION (10100)  // 1 01 00 means 1.1(.0)


// class GRand
// Good random number generation
// Convenience wrapper around C++ Standard Library RNG.
class GRand {

// ***** GRand: internal-use types *****
private:

    typedef std::mt19937 rng_type;  // Type of our RNG object

// ***** GRand: ctors, dctor, op= *****
public:

    // Default ctor
    // Seed RNG with unpredictable value.
    GRand()
        :_nondet_seed_needed(true),
         _rng()
    {}

    // Ctor from number
    // Seed RNG with given value.
    // Template so that any reasonable argument type gives no warnings.
    // Requirements on Types:
    //     SeedType must be convertible to rng_type::result_type
    //      (guaranteed to be an unsigned integral type).
    template <typename SeedType>
    GRand(SeedType s)
        :_nondet_seed_needed(false),
         _rng(rng_type::result_type(s))
    {}

    // Compiler-generated copy/move ctors, copy/move op=, dctor used.

// ***** GRand: general public functions *****
public:

    // seed - no parameters
    // Seed RNG with unpredictable value.
    void seed()
    { _nondet_seed_needed = true; }

    // seed from number
    // Seed RNG with given value.
    // Template so that any reasonable argument type gives no warnings.
    // Requirements on Types:
    //     SeedType must be convertible to rng_type::result_type
    //      (guaranteed to be an unsigned integral type).
    template <typename SeedType>
    void seed(SeedType s)
    {
        _nondet_seed_needed = false;
        _rng.seed(rng_type::result_type(s));
    }

    // i
    // Return random integer in range [0, n-1], or 0 if n <= 0. Range is
    //  {0, 1} if no parameter given.
    int i(int n=2)
    { return operator()(n); }

    // d
    // Return random double in range [0.0, d) if d > 0.0, in range
    //  (d, 0.0] if d < 0, or 0.0 if d == 0.0. Range is [0.0, 1.0) if no
    //  parameter given.
    double d(double d=1.0)
    {
        ck_nondet_seed();
        if (d > 0.0)
            return std::uniform_real_distribution<double>(0.0, d)(_rng);
        if (d < 0.0)
            return
                -std::uniform_real_distribution<double>(0.0, -d)(_rng);
        return 0.0;
    }

    // b
    // Return random bool value. Probability of true is given value, or
    //  0.5 if none given.
    bool b(double p=0.5)
    {
        ck_nondet_seed();
        if (p <= 0.0) return false;
        if (p >= 1.0) return true;
        return std::bernoulli_distribution(p)(_rng);
    }

// ***** GRand: support for C++ Standard concepts *****
public:

    // An object of type GRand meets the requirements for Uniform Random
    // Number Generator (C++11 26.5.1.3) and may be passed as the third
    // argument to std::shuffle (C++11 25.3.13).

    typedef rng_type::result_type result_type;

    result_type min() const
    { return rng_type::min(); }

    result_type max() const
    { return rng_type::max(); }

    // operator() - no arguments
    // Return random value of type result_type, in range [min(), max()].
    result_type operator()()
    {
        ck_nondet_seed();
        return _rng();
    }

    // An object of type GRand may be passed as the third argument to
    // std::random_shuffle (C++11 25.3.12).

    // operator() - one argument
    // Return random integer in range [0, n-1], or 0 if n <= 0.
    // Template so that any reasonable argument type gives no warnings.
    // Requirements on Types:
    //     IntType must be an integer type.
    // NOTE: This is also used to implement member function i(n).
    template <typename IntType>
    IntType operator()(IntType n)
    {
        ck_nondet_seed();
        if (n <= IntType(0)) return IntType(0);
        return std::uniform_int_distribution<IntType>(
            IntType(0),
            n-IntType(1))
                (_rng);
    }

    // NOTE: An object of type GRand does NOT meet the requirements for
    // Random Number Engine (C++11 26.5.1.4).

// ***** GRand: internal-use functions *****
private:

    void ck_nondet_seed()
    {
        if (!_nondet_seed_needed)
            return;
        _nondet_seed_needed = false;
        _rng.seed(std::random_device()());
    }

// ***** GRand: data members *****
private:

    bool _nondet_seed_needed;
                    // True if nondeterministic seed needs to be done
    rng_type _rng;  // Our random-number generator

};  // End class GRand

#endif //#ifndef FILE_GRAND_H_INCLUDED

