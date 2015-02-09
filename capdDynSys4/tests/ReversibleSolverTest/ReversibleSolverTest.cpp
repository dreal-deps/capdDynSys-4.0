//////////////////////////////////////////////////////////////////////////////
//   Package:          CAPD

/////////////////////////////////////////////////////////////////////////////
//
/// @file ReversibleSolverTest.cpp
///
/// @author Daniel Wilczak
//
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) CAPD group
//
// This file constitutes a part of the CAPD library,
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.ii.uj.edu.pl/ for details.

#define BOOST_TEST_MODULE ReversibleSolverTest
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "capd/capdlib.h"
#include "capd/dynset/C2DoubletonSet.hpp"
#include "capd/dynsys/C2Solver.hpp"
using namespace capd;

/**
 * The Michelson system is reversible with respect to involution (x,y,z,t) -> (-x,y,-z,-t)
 * We check rigorous C^0-C^n solvers for preserving this property.
 */

BOOST_AUTO_TEST_SUITE(ReversibleSolverTestSuite)

template<class S, class TM>
void doC0test(TM& tm, IVector x){
  S s(x);

  // integrate over time 1
  IVector z = tm(1.,s);

  // apply reversing symmetry
  z[2] = -z[2];
  z[0] = -z[0];

  s = S(z);
  // integrate over time 1
  z = tm(1.,s);

  // apply reversing symmetry
  z[2] = -z[2];
  z[0] = -z[0];

  // we should obtain identity map
  BOOST_REQUIRE_MESSAGE(subset(x,z),"x=" << x << ", z=" << z);
}

BOOST_AUTO_TEST_CASE(C0Test)
{
  IMap f="par:c;var:x,y,z;fun:y,z,1-y-0.5*x*x;";
  IOdeSolver solver(f,10);
  ITimeMap tm(solver);
  IVector x(0.,1.563,0.);

  doC0test<C0Rect2Set>(tm,x);
  doC0test<C0Pped2Set>(tm,x);
  doC0test<C0TripletonSet>(tm,x);
  doC0test<C0HORect2Set>(tm,x);
  doC0test<C0HOTripletonSet>(tm,x);
}

template<class S, class TM>
void doC1test(TM& tm, IVector x){
  S s(x);

  // integrate over time 1
  IVector z = tm(1.,s);
  IMatrix D = IMatrix(s);

  // matrix of reversing symmetry
  IMatrix R(3,3);
  R[0][0] = -1;
  R[2][2] = -1;
  R[1][1] = 1;

  // apply reversing symmetry
  z = R*z;
  D = R*D;

  s = S(typename S::C0BaseSet(z),typename S::C1BaseSet(D));
  // integrate over time 1
  z = tm(1.,s);
  D = IMatrix(s);

  // apply reversing symmetry
  z = R*z;
  D = R*D;

  // we should obtain identity map
  BOOST_REQUIRE_MESSAGE(subset(x,z),"x=" << x << ", z=" << z);
  BOOST_REQUIRE_MESSAGE(subset(IMatrix::Identity(3),D),"D=" << D);
}

BOOST_AUTO_TEST_CASE(C1Test)
{
  IMap f="par:c;var:x,y,z;fun:y,z,1-y-0.5*x*x;";
  IOdeSolver solver(f,10);
  ITimeMap tm(solver);
  IVector x(0.,1.563,0.);

  doC1test<C1Rect2Set>(tm,x);
  doC1test<C1Pped2Set>(tm,x);
  doC1test<C1HORect2Set>(tm,x);
  doC1test<C1HOPped2Set>(tm,x);
}

template<class S, class TM>
void doC2test(TM& tm, IVector x){
  S s = S(x);

  // matrix of reversing symmetry
  IMatrix R(3,3);
  R[0][0] = -1;
  R[2][2] = -1;
  R[1][1] = 1;

  // integrate over time 1
  IVector z = tm(1.,s);

  IMatrix D = IMatrix(s);
  IHessian H = IHessian(s);

  // apply reversing symmetry
  z = R*z;
  D = R*D;
  H = R*H;

  s = S(typename S::C0BaseSet(z),typename S::C1BaseSet(D),H);
  // integrate over time 1
  z = tm(1.,s);
  D = IMatrix(s);
  H = IHessian(s);

  // apply reversing symmetry
  z = R*z;
  D = R*D;
  H = R*H;

  // we should obtain identity map
  BOOST_REQUIRE_MESSAGE(subset(x,z),"x=" << x << ", z=" << z);
  BOOST_REQUIRE_MESSAGE(subset(IMatrix::Identity(3),D),"D=" << D);
  BOOST_REQUIRE(subset(IHessian(3,3),H));
}

BOOST_AUTO_TEST_CASE(C2Test)
{
  IMap f("par:c;var:x,y,z;fun:y,z,1-y-0.5*x*x;",2);
  IC2OdeSolver solver(f,10);
  IC2TimeMap tm(solver);
  IVector x(0.,1.563,0.);

  doC0test<C0Rect2Set>(tm,x);
  doC0test<C0Pped2Set>(tm,x);
  doC0test<C0TripletonSet>(tm,x);

  doC1test<C1Rect2Set>(tm,x);
  doC1test<C1Pped2Set>(tm,x);

  doC2test<C2Rect2Set>(tm,x);
}

template<class S, class TM>
void doCntest(TM& tm, IVector x){
  const int degree = tm.getSolver().getVectorField().degree();
  S s = S(x,degree);

  // matrix of reversing symmetry
  IMatrix R(3,3);
  R[0][0] = R[2][2] = -1;
  R[1][1] = 1;

  // integrate over time 1
  IVector z = tm(1.,s);
  IJet D = s.currentSet();

  // apply reversing symmetry
  D = R*D;
  s = S(D);

  // integrate over time 1
  z = tm(1.,s);
  D = s.currentSet();

  // apply reversing symmetry
  D = R*D;

  IJet J(x.dimension(),degree);
  J() = x;
  J.setMatrix(IMatrix::Identity(x.dimension()));
  // we should obtain identity map
  BOOST_REQUIRE_MESSAGE(subset(J,D),"J=" << J.toString() << ", D=" << D.toString());
}

BOOST_AUTO_TEST_CASE(CnTest)
{
  IMap f("par:c;var:x,y,z;fun:y,z,1-y-0.5*x*x;",3);
  ICnOdeSolver solver(f,10);
  ICnTimeMap tm(solver);
  IVector x(0.,1.563,0.);

  doC0test<C0Rect2Set>(tm,x);
  doC0test<C0Pped2Set>(tm,x);
  doC0test<C0TripletonSet>(tm,x);

  doC1test<C1Rect2Set>(tm,x);
  doC1test<C1Pped2Set>(tm,x);

  doC2test<C2Rect2Set>(tm,x);

  doCntest<CnRect2Set>(tm,x);
  doCntest<CnMultiMatrixRect2Set>(tm,x);
}

BOOST_AUTO_TEST_SUITE_END()
