/// @addtogroup dynsys
/// @{

/////////////////////////////////////////////////////////////////////////////
/// @file approveRemainder.h
///
/// @author Daniel Wilczak
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) 2000-2015 by the CAPD Group.
//
// This file constitutes a part of the CAPD library,
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.ii.uj.edu.pl/ for details.

#include "capd/poincare/SaveStepControl.h"

#ifndef _CAPD_DYNSYS_APPROVEREMAINDER_H_
#define _CAPD_DYNSYS_APPROVEREMAINDER_H_

namespace capd{
namespace dynsys {

template<class Solver, class PhiType, class RemainderType>
void computeAndApproveRemainder(
      Solver& solver,
      const typename Solver::ScalarType& t,   //< @param[in] current time of ODE
      const typename Solver::VectorType& xx,  //< @param[in] set to be moved along the trajectories of ODE
      PhiType& o_phi,                         //< @param[out] bound for the truncated Taylor series of the solution
      RemainderType& o_rem,                   //< @param[out] bound for the error of numerical method over the time step
      RemainderType& o_enc                    //< @param[out] bound for the enclosure over the time step
  )
{
  typedef typename Solver::ScalarType ScalarType;
  typedef typename Solver::VectorType VectorType;
  typedef typename ScalarType::BoundType Real;
  
  capd::poincare::SaveStepControl<Solver> saveStepControl(solver);

  // IMPORTANT: this MUST be computed BEFORE call to computeReamainder!
  Real eps = Real(2.)*Solver::getEffectiveTolerance(solver,xx);

  // do not make time step larger than 2x previous step
  if(!isSingular(solver.getStep()))
    solver.setMaxStep(capd::min(solver.getMaxStep(),Real(1.5)*solver.getStep()));
  solver.computeTimeStep(t,xx);
  solver.computeRemainder(t,xx,o_enc,o_rem);
  
  // if changing step is allowed, validate remainder and adjust time step if necessary
  if(solver.isStepChangeAllowed() and !isSingular(solver.getStep())) {
    const static ScalarType I(TypeTraits<Real>::zero(),TypeTraits<Real>::one());

    Real remSize = rightBound(maxWidth((VectorType)o_rem));
    while( remSize > eps and solver.getMaxStep() > solver.getStepControl().getMinStepAllowed() )  {
      solver.adjustTimeStep((solver.getStep()*0.95).leftBound());
      solver.computeRemainder(t,xx,o_enc,o_rem);
      remSize = rightBound(maxWidth((VectorType)o_rem));
    }
  }
  
  // after approval of remainder compute phi, jacPhi, etc. 
  // with aproved time step
  solver.sumTaylorSeries(o_phi);
}

}} // namespace capd::dynsys

#endif

