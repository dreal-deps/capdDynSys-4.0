
/////////////////////////////////////////////////////////////////////////////
/// @file TripletonSet.cpp
///
/// @author Daniel Wilczak
/// Created on: Apr 18, 2014
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) 2001-2014 by the CAPD Group.
//
// This file constitutes a part of the CAPD library,
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.ii.uj.edu.pl/ for details.

#include "capd/vectalg/mplib.h"
#include "capd/geomset/CenteredTripletonSet.hpp"

#ifdef __HAVE_MPFR__
namespace capd{
namespace geomset{
  template class CenteredTripletonSet<capd::MpIMatrix >;
}}
#endif

