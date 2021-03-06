/// @addtogroup autodiff
/// @{

/////////////////////////////////////////////////////////////////////////////
/// @file EvalExp.h
///
/// @author Daniel Wilczak
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) 2000-2012 by the CAPD Group.
//
// This file constitutes a part of the CAPD library,
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.ii.uj.edu.pl/ for details.

#ifndef _CAPD_AUTODIFF_EVAL_EXP_H_
#define _CAPD_AUTODIFF_EVAL_EXP_H_

#include "capd/autodiff/NodeType.h"

namespace capd{
namespace autodiff{

// -------------------- Exp ------------------------------------

namespace Exp
{
  template<class T>
  inline void evalC0(const T* left, const T* /* right*/, T* result, const unsigned coeffNo)
  {
    if(coeffNo)
    {
      T temp = TypeTraits<T>::zero();
      for(unsigned j=0;j<coeffNo;++j)
        temp += double(coeffNo-j) * result[j]*left[coeffNo-j];
      result[coeffNo] = temp/(double)coeffNo;
    }else
      *result = exp(*left);
  }

  template<class T>
  inline void evalC1(const T* left, const T* right, T* result, const unsigned dim, const unsigned order, const unsigned coeffNo)
  {
    evalC0(left,right,result,coeffNo);
    // shift pointers to proper coefficients
    T* resultDer = result + order + coeffNo;
    const T* leftDer = left + order;

    for(unsigned derNo=0;derNo<dim;++derNo,resultDer+=order, leftDer+=order)
    {
      T temp = capd::TypeTraits<T>::zero();
      for(unsigned j=0;j<=coeffNo;++j)
        temp += leftDer[coeffNo-j] * result[j];
      *resultDer = temp;
    }
  }

  template<class T>
  inline void evalCn(const unsigned degree, const T* left, const T* /*right*/, T* result, const unsigned dim, const unsigned order, const unsigned coeffNo)
  {
    using capd::vectalg::Multiindex;
    const unsigned shift = binomial(dim+degree-1,dim);
    const unsigned end = binomial(dim+degree,dim);
    Multiindex a(dim),b(dim),c(dim);
    unsigned i,k,p;
    for(i=shift*order+coeffNo;i<end*order+coeffNo;i+=order)
      result[i] = TypeTraits<T>::zero();

    for(i=1;i<(degree+1)/2;++i){
      a.clear();
      a[0]=i;
      const unsigned shiftA = binomial(dim+i-1,dim);
      const unsigned shiftB = binomial(dim+(degree-i)-1,dim);
      do{
        b.clear();
        b[0]=degree-i;
        const unsigned sa = (shiftA + a.index(i))*order;
        do{
          p = sumAndFindMax(a.begin(),b.begin(),c.begin(),dim);
          unsigned sb = (shiftB + b.index(degree-i))*order;
          T ra = TypeTraits<T>::zero(), rb = TypeTraits<T>::zero();
          for(k=0;k<=coeffNo;++k) {
            ra += result[sb+k]*left[sa+coeffNo-k];
            rb += result[sa+k]*left[sb+coeffNo-k];
          }
          result[(shift + c.index(degree))*order+coeffNo] += a[p]*ra + b[p]*rb;
        }while(b.hasNext());
      }while(a.hasNext());
    }

    if(degree%2==0){
      i = degree/2;
      a.clear();
      a[0]=i;
      const unsigned shiftA = binomial(dim+i-1,dim);
      do{
        b.clear();
        b[0]=i;
        const unsigned sa = (shiftA + a.index(i))*order;
        do{
          const unsigned sb = (shiftA + b.index(degree-i))*order;
          if(sa<sb) continue;
          p = sumAndFindMax(a.begin(),b.begin(),c.begin(),dim);
          T ra = TypeTraits<T>::zero(), rb = TypeTraits<T>::zero();
          if(sa!=sb){
            for(k=0;k<=coeffNo;++k) {
              ra += result[sb+k]*left[sa+coeffNo-k];
              rb += result[sa+k]*left[sb+coeffNo-k];
            }
            result[(shift + c.index(degree))*order+coeffNo] += a[p]*ra + b[p]*rb;
          }
          else{
            for(k=0;k<=coeffNo;++k) ra += result[sa+k]*left[sa+coeffNo-k];
            result[(shift + c.index(degree))*order+coeffNo] += a[p]*ra;
          }
        }while(b.hasNext());
      }while(a.hasNext());
    }

    c.clear();
    c[0] = degree;
    do{
      p = findMax(c.begin(),dim);
      const unsigned s = (shift + c.index(degree))*order;
      T r = result[coeffNo]*left[s];
      for(k=0;k<coeffNo;++k) {
        r += result[k]*left[s+coeffNo-k];
      }
      result[s+coeffNo] += c[p]*r;
      result[s+coeffNo] /= typename TypeTraits<T>::Real(c[p]);
    }while(c.hasNext());
  }

  template<class T>
  inline void eval(const unsigned degree, const T* left, const T* right, T* result, const unsigned dim, const unsigned order, const unsigned coeffNo)
  {
    switch(degree)
    {
      case 0:
        evalC0(left,right,result,coeffNo);
        break;
      default:
        evalC1(left,right,result,dim,order,coeffNo);
        for(unsigned i=2;i<=degree;++i)
          evalCn(i,left,right,result,dim,order,coeffNo);
    }
  }

  template<class T>
  inline void evalC0HomogenousPolynomial(const T* left, const T* /*right*/, T* result)
  {
    *result = exp(*left);
  }

  template<class T>
  inline void evalC1HomogenousPolynomial(const T* left, const T* /*right*/, T* result, const unsigned dim, const unsigned order)
  {
    T* resultDer = result + order;
    const T* leftDer = left + order;

    for(unsigned derNo=0;derNo<dim;++derNo,resultDer+=order, leftDer+=order)
      *resultDer = (*leftDer) * (*result);
  }

  template<class T>
  inline void evalCnHomogenousPolynomial(const unsigned degree, const T* left, const T* /*right*/, T* result, const unsigned dim, const unsigned order)
  {
    using capd::vectalg::Multiindex;
    const unsigned shift = binomial(dim+degree-1,dim);
    const unsigned end = binomial(dim+degree,dim);
    Multiindex a(dim),b(dim),c(dim);
    unsigned i,p;
    for(i=shift*order;i<end*order;i+=order)
      result[i] = TypeTraits<T>::zero();

    for(i=1;i<(degree+1)/2;++i){
      a.clear();
      a[0]=i;
      const unsigned shiftA = binomial(dim+i-1,dim);
      const unsigned shiftB = binomial(dim+(degree-i)-1,dim);
      do{
        b.clear();
        b[0]=degree-i;
        const unsigned sa = (shiftA + a.index(i))*order;
        do{
          p = sumAndFindMax(a.begin(),b.begin(),c.begin(),dim);
          const unsigned sb = (shiftB + b.index(degree-i))*order;
          result[(shift + c.index(degree))*order] += a[p]*result[sb]*left[sa] + b[p]*result[sa]*left[sb];
        }while(b.hasNext());
      }while(a.hasNext());
    }

    if(degree%2==0){
      i = degree/2;
      a.clear();
      a[0]=i;
      const unsigned shiftA = binomial(dim+i-1,dim);
      do{
        b.clear();
        b[0]=i;
        const unsigned sa = (shiftA + a.index(i))*order;
        do{
          const unsigned sb = (shiftA + b.index(degree-i))*order;
          if(sa<sb) continue;
          p = sumAndFindMax(a.begin(),b.begin(),c.begin(),dim);
          if(sa!=sb)
            result[(shift + c.index(degree))*order] += a[p]*result[sb]*left[sa] + b[p]*result[sa]*left[sb];
          else
            result[(shift + c.index(degree))*order] += a[p]*result[sa]*left[sa];
        }while(b.hasNext());
      }while(a.hasNext());
    }

    c.clear();
    c[0] = degree;
    do{
      p = findMax(c.begin(),dim);
      const unsigned s = (shift + c.index(degree))*order;
      result[s] += c[p]*(*result)*left[s];
      result[s] /= typename TypeTraits<T>::Real(c[p]);
    }while(c.hasNext());
  }

  template<class T>
  inline void evalHomogenousPolynomial(const unsigned degree, const T* left, const T* right, T* result, const unsigned dim, const unsigned order)
  {
    switch(degree)
    {
      case 1:
        evalC1HomogenousPolynomial(left,right,result,dim,order);
        break;
      case 0:
        evalC0HomogenousPolynomial(left,right,result);
        break;
      default:
        evalCnHomogenousPolynomial(degree,left,right,result,dim,order);
    }
  }
}

namespace ExpFunTime
{
  template<class T>
  inline void evalC0(const T* left, const T* right, T* result, const unsigned coeffNo)
  {
    Exp::evalC0(left,right,result,coeffNo);
  }

  template<class T>
  inline void eval(const unsigned /*degree*/, const T* left, const T* right, T* result, const unsigned /*dim*/, const unsigned /*order*/, const unsigned coeffNo)
  {
    Exp::evalC0(left,right,result,coeffNo);
  }

  template<class T>
  inline void evalC0HomogenousPolynomial(const T* left, const T* /*right*/, T* result)
  {
    *result = exp(*left);
  }

  template<class T>
  inline void evalHomogenousPolynomial(const unsigned degree, const T* left, const T* /*right*/, T* result, const unsigned /*dim*/, const unsigned /*order*/)
  {
    if(degree==0)
      *result = exp(*left);
  }
}

namespace ExpTime
{
  template<class T>
  inline void evalC0(const T* left, const T* /*right*/, T* result, const unsigned coeffNo)
  {
    if(coeffNo)
      result[coeffNo] = result[coeffNo-1]/(double)coeffNo;
    else
      *result = exp(*left);
  }

  template<class T>
  inline void eval(const unsigned /*degree*/, const T* left, const T* right, T* result, const unsigned /*dim*/, const unsigned /*order*/, const unsigned coeffNo)
  {
    evalC0(left,right,result,coeffNo);
  }

  template<class T>
  inline void evalC0HomogenousPolynomial(const T* left, const T* /*right*/, T* result)
  {
    *result = exp(*left);
  }

  template<class T>
  inline void evalHomogenousPolynomial(const unsigned degree, const T* left, const T* /*right*/, T* result, const unsigned /*dim*/, const unsigned /*order*/)
  {
    if(degree==0)
      *result = exp(*left);
  }
}

namespace ExpConst
{
  template<class T>
  inline void evalC0(const T* left, const T* /*right*/, T* result, const unsigned coeffNo)
  {
    if(coeffNo)
      {}
    else
      *result = exp(*left);
  }

  template<class T>
  inline void eval(const unsigned /*degree*/, const T* left, const T* right, T* result, const unsigned /*dim*/, const unsigned /*order*/, const unsigned coeffNo)
  {
    evalC0(left,right,result,coeffNo);
  }

  template<class T>
  inline void evalC0HomogenousPolynomial(const T* left, const T* /*right*/, T* result)
  {
    *result = exp(*left);
  }

  template<class T>
  inline void evalHomogenousPolynomial(const unsigned degree, const T* left, const T* /*right*/, T* result, const unsigned /*dim*/, const unsigned /*order*/)
  {
    if(degree==0)
      *result = exp(*left);
  }
}

// ----------------------------------------------------------------------------------

//use macro to define classes

CAPD_MAKE_CLASS_NODE(Exp);
CAPD_MAKE_CLASS_NODE(ExpConst);
CAPD_MAKE_CLASS_NODE(ExpTime);
CAPD_MAKE_CLASS_NODE(ExpFunTime);

}} // namespace capd::autodiff

#endif
