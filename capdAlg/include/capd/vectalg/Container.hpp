/// @addtogroup vectalg
/// @{

/////////////////////////////////////////////////////////////////////////////
/// @file Container.hpp
///
/// @author Daniel Wilczak 2005-2008
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) 2000-2005 by the CAPD Group.
//
// This file constitutes a part of the CAPD library,
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.ii.uj.edu.pl/ for details.

#ifndef _CAPD_VECTALG_CONTAINER_HPP_
#define _CAPD_VECTALG_CONTAINER_HPP_

#include <algorithm>
#include "capd/vectalg/Container.h"
#include "capd/basicalg/TypeTraits.h"

#include <iostream>
namespace capd{
namespace vectalg{


// C++11 --------------------------------------------------------
#ifdef CAPD_HAVE_CXX11

  /// Move constructor
template<typename Scalar>
Container<Scalar,0>::Container(Container && a_container) noexcept
  : data(a_container.data), capacity(a_container.capacity)
{
  a_container.data = 0;
  a_container.capacity = 0;
}

template<typename Scalar>
Container<Scalar,0>& Container<Scalar,0>::operator=(Container&& a_c) {
//  Self assigment check removed: it is rare.  
//  if(&a_c != this) {
    std::swap(capacity, a_c.capacity);
    std::swap(data, a_c.data);
//  }
  return *this;
}
#endif

// --------------- member definitions ----------------------------- //

template<typename Scalar, __size_type capacity>
void Container<Scalar,capacity>::clear(){
  for(iterator i=begin();i!=end();++i)
    *i = TypeTraits<ScalarType>::zero();
}

template<typename Scalar>
void Container<Scalar,0>::clear(){
  for(iterator i=begin();i!=end();++i)
    *i = TypeTraits<ScalarType>::zero();
}

template<typename Scalar, __size_type capacity>
Container<Scalar,capacity>::Container(){
   clear();
}

template<typename Scalar, __size_type capacity>
Container<Scalar,capacity>::Container(size_type){
  clear();
}


template<typename Scalar, __size_type capacity>
Container<Scalar,capacity>& Container<Scalar,capacity>::operator=(const Container& a_c)
{
  if(&a_c != this)
    std::copy(a_c.begin(),a_c.end(),begin());
  return *this;
}

template<typename Scalar, __size_type capacity>
void Container<Scalar,capacity>::resize(size_type newCapacity)
{
  if(newCapacity!=capacity)
    throw std::range_error("Cannot change capacity of static container");
}


template<typename Scalar>
Container<Scalar,0>::Container() : data(0), capacity(defaultSize)
{
  if(capacity)
  {
    data = new ScalarType[capacity];
    clear();
  }
}

template<typename Scalar>
Container<Scalar,0>::Container(size_type a_capacity) : capacity(a_capacity)
{
  data = new ScalarType[capacity];
  clear();
}


template<typename Scalar>
Container<Scalar,0>::Container(const Container& a_container) : capacity(a_container.capacity)
{
  data = new ScalarType[capacity];
  std::copy(a_container.begin(),a_container.end(),begin());
}

template<typename Scalar>
Container<Scalar,0>& Container<Scalar,0>::operator=(const Container& a_c)
{
  if(&a_c != this)
  {
    if(capacity!=a_c.capacity)
    {
      delete [] data;
      capacity =  a_c.capacity;
      data = new ScalarType[capacity];
    }
    std::copy(a_c.begin(),a_c.end(),begin());
  }
  return *this;
}

template<typename Scalar>
void Container<Scalar,0>::resize(size_type A_newCapacity)
{
  if(capacity!=A_newCapacity)
  {
    if(data) delete[] data;
    capacity = A_newCapacity;
    data = new ScalarType[capacity];
  }
  clear();
}


template<typename Scalar>
typename Container<Scalar,0>::size_type Container<Scalar,0>::defaultSize = 0;

}} // namespace capd::vectalg

#endif // _CAPD_VECTALG_CONTAINER_HPP_

/// @}
