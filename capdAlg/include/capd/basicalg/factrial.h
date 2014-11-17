
/////////////////////////////////////////////////////////////////////////////
/// @file factrial.h
///
/// @author The CAPD Group
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) 2000-2005 by the CAPD Group.
//
// This file constitutes a part of the CAPD library, 
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.ii.uj.edu.pl/ for details.
#include <vector>
#ifndef _CAPD_CAPD_FACTRIAL_H_ 
#define _CAPD_CAPD_FACTRIAL_H_ 

namespace capd{

class Newton{
public:
  static Newton& getInstance(){
    return instance;
  }
  unsigned long long factorial(unsigned n);
  unsigned long long newton(unsigned n, unsigned k);
private:
  Newton() : first_unknown_factorial(0), first_unknown_newton_level(0) {}
  std::vector<unsigned long long> factorial_storage;
  unsigned first_unknown_factorial;
  std::vector<unsigned long long> newton_storage;
  unsigned first_unknown_newton_level;

  inline unsigned index(unsigned n,unsigned k)
  {
    return n*(n+1)/2+k;
  }
  static Newton instance;
};

/// @addtogroup basicalg
/// @{
template <long N, long K>
struct Binomial
{
   static const long value = Binomial<N-1,K-1>::value + Binomial<N-1,K>::value;
};

template <long K>
struct Binomial<0,K>
{
   static const long value = 0;
};

template <long N>
struct Binomial<N,0>
{
   static const long value = 1;
};

template<long N>
struct Binomial<N,N>
{
   static const long value=1;
};

template <>
struct Binomial<0,0>
{
   static const long value = 1;
};

template<long N>
struct Factorial
{
   static const long value = N*Factorial<N-1>::value;
};

template<>
struct Factorial<1>
{
   static const long value = 1;
};

template<>
struct Factorial<0>
{
   static const long value = 1;
};

/// @}

} // namespace capd

///< compute and store n factorial
inline unsigned long long factorial(unsigned n){
  return capd::Newton::getInstance().factorial(n);
}

///< compute and store newton symbol (n \over k)
inline unsigned long long newton(unsigned n, unsigned k){
  return capd::Newton::getInstance().newton(n,k);
}

#endif // _CAPD_CAPD_FACTRIAL_H_ 
