//////////////////////////////////////////////////////////////////////////////
//   Package:          CAPD

/////////////////////////////////////////////////////////////////////////////
//
/// @file expTest.cpp
///
/// @author Daniel Wilczak
//
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) CAPD group
//
// This file constitutes a part of the CAPD library,
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.ii.uj.edu.pl/ for details.

//#define BOOST_TEST_MODULE expTest
#include "compare.h"
BOOST_AUTO_TEST_SUITE(expSuite)

std::vector<double> computeExpDer(MapType::VectorType & u){
  double x = u[0].leftBound();
  double y = u[1].leftBound();

  // code generated by the following Mathematica code
  // W[n_,m_]:=D[Exp[1-x*y*(x-y)],{x,n},{y,m}]/(n!m!)//FullSimplify
  // Table[Table[W[m-n,n]//CForm,{n,0,m}],{m,0,5}]//Flatten

  capd::rounding::DoubleRounding::roundNearest();
  double E = exp(1);
  double r[] = {Power(E,1 + x*y*(-x + y)),-(Power(E,1 + x*y*(-x + y))*(2*x - y)*y),-(Power(E,1 + x*y*(-x + y))*x*(x - 2*y)),(Power(E,1 + x*y*(-x + y))*y*(-2 + y*Power(-2*x + y,2)))/2.,Power(E,1 + x*y*(-x + y))*(2*y + x*(-2 + (x - 2*y)*(2*x - y)*y)),(Power(E,1 + x*y*(-x + y))*x*(2 + x*Power(x - 2*y,2)))/2.,-(Power(E,1 + x*y*(-x + y))*(2*x - y)*Power(y,2)*(-6 + y*Power(-2*x + y,2)))/6.,(Power(E,1 + x*y*(-x + y))*(-2 + 10*Power(x,2)*y - 4*x*(4 + Power(x,3))*Power(y,2) + 4*(1 + 3*Power(x,3))*Power(y,3) - 9*Power(x,2)*Power(y,4) + 2*x*Power(y,5)))/2.,(Power(E,1 + x*y*(-x + y))*(2 + x*(4*Power(x,2) - 2*x*(8 + Power(x,3))*y + (10 + 9*Power(x,3))*Power(y,2) - 12*Power(x,2)*Power(y,3) + 4*x*Power(y,4))))/2.,-(Power(E,1 + x*y*(-x + y))*Power(x,2)*(6 + x*Power(x - 2*y,2))*(x - 2*y))/6.,(Power(E,1 + x*y*(-x + y))*Power(y,2)*(12 + y*Power(-2*x + y,2)*(-12 + y*Power(-2*x + y,2))))/24.,(Power(E,1 + x*y*(-x + y))*y*(8*Power(x,5)*Power(y,2) - 28*Power(x,4)*Power(y,3) - 13*Power(x,2)*Power(y,2)*(-6 + Power(y,3)) + 6*y*(-3 + Power(y,3)) + 6*Power(x,3)*y*(-6 + 5*Power(y,3)) + 2*x*(12 - 21*Power(y,3) + Power(y,6))))/6.,(Power(E,1 + x*y*(-x + y))*(12*Power(x,2) - 18*x*(2 + Power(x,3))*y + 4*(3 + 18*Power(x,3) + Power(x,6))*Power(y,2) - 4*Power(x,2)*(18 + 5*Power(x,3))*Power(y,3) + 3*x*(6 + 11*Power(x,3))*Power(y,4) - 20*Power(x,3)*Power(y,5) + 4*Power(x,2)*Power(y,6)))/4.,(Power(E,1 + x*y*(-x + y))*x*(24*y + x*(-18 + (x - 2*y)*(-6*Power(x,2) + 2*x*(15 + Power(x,3))*y - 9*(2 + Power(x,3))*Power(y,2) + 12*Power(x,2)*Power(y,3) - 4*x*Power(y,4)))))/6.,(Power(E,1 + x*y*(-x + y))*Power(x,2)*(12 + x*(12 + x*Power(x - 2*y,2))*Power(x - 2*y,2)))/24.,-(Power(E,1 + x*y*(-x + y))*(2*x - y)*Power(y,3)*(60 + y*Power(-2*x + y,2)*(-20 + y*Power(-2*x + y,2))))/120.,(Power(E,1 + x*y*(-x + y))*y*(24 - 156*Power(x,2)*y + 8*x*(27 + 14*Power(x,3))*Power(y,2) - 4*(15 + 76*Power(x,3) + 4*Power(x,6))*Power(y,3) + 4*Power(x,2)*(63 + 16*Power(x,3))*Power(y,4) - 8*x*(10 + 11*Power(x,3))*Power(y,5) + 8*(1 + 7*Power(x,3))*Power(y,6) - 17*Power(x,2)*Power(y,7) + 2*x*Power(y,8)))/24.,(Power(E,1 + x*y*(-x + y))*(24*x - 12*(3 + 8*Power(x,3))*y + 60*Power(x,2)*(5 + Power(x,3))*Power(y,2) - 2*x*(102 + 131*Power(x,3) + 4*Power(x,6))*Power(y,3) + 2*(15 + 174*Power(x,3) + 22*Power(x,6))*Power(y,4) - 2*Power(x,2)*(84 + 43*Power(x,3))*Power(y,5) + x*(26 + 73*Power(x,3))*Power(y,6) - 28*Power(x,3)*Power(y,7) + 4*Power(x,2)*Power(y,8)))/12.,(Power(E,1 + x*y*(-x + y))*(24*y + x*(-6*(6 + 5*Power(x,3)) + 2*Power(x,2)*(102 + 13*Power(x,3))*y - 4*x*(75 + 42*Power(x,3) + Power(x,6))*Power(y,2) + 4*(24 + 87*Power(x,3) + 7*Power(x,6))*Power(y,3) - Power(x,2)*(262 + 73*Power(x,3))*Power(y,4) + 2*x*(30 + 43*Power(x,3))*Power(y,5) - 44*Power(x,3)*Power(y,6) + 8*Power(x,2)*Power(y,7))))/12.,-(Power(E,1 + x*y*(-x + y))*x*(-24 + x*(-4*Power(x,2)*(15 + 2*Power(x,3)) + 2*x*(108 + 40*Power(x,3) + Power(x,6))*y - (156 + 252*Power(x,3) + 17*Power(x,6))*Power(y,2) + 8*Power(x,2)*(38 + 7*Power(x,3))*Power(y,3) - 8*x*(14 + 11*Power(x,3))*Power(y,4) + 64*Power(x,3)*Power(y,5) - 16*Power(x,2)*Power(y,6))))/24.,-(Power(E,1 + x*y*(-x + y))*Power(x,3)*(60 + x*(20 + x*Power(x - 2*y,2))*Power(x - 2*y,2))*(x - 2*y))/120.};
  return std::vector<double> (r,r+sizeof(r)/sizeof(double));
}

BOOST_AUTO_TEST_CASE(xexp)
{
  std::string txt = "var:x,y;fun:exp(1-x*y*(x-y));",
              msg = "Function \"" + txt + "\"  x = " ;
  MapType f(txt,5);
  VectorType x(2);
  JetType df(1,2,5);

  x[0] = .5; x[1] = 0.75;
  std::vector<double> expected = computeExpDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(0.5,0.75)");

  MapType g("var:x,y;fun:1/exp(x*y*(x-y)-1);",5);
  g(x,df);
  compareResults(expected, df, msg+"(0.5,.75)");

  x[0] = -0.75; x[1] = 1.;
  expected = computeExpDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(-0.75,1)");

  x[0] = 0.0; x[1] = 0.0;
  expected = computeExpDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(0.0,0.0)");

}

using capd::autodiff::Node;

void _f(Node /*t*/, Node in[], int /*dimIn*/, Node out[], int /*dimOut*/, Node /*params*/[], int /*noParams*/)
{
  out[0] = exp(1-in[0]*in[1]*(in[0]-in[1]));
}

BOOST_AUTO_TEST_CASE(xexpnode)
{
  std::string msg = "Function \"exp(1-x*y*(x-y))\"  x = " ;
  MapType f(_f,2,1,0,5);
  VectorType x(2);
  x[0] = .125; x[1]=0.25;
  std::vector<double> expected = computeExpDer(x);
  JetType df(1,2,5);
  f(x,df);
  compareResults(expected, df, msg+"(0.125,0.25)");

  x[0] = -0.75; x[1]=2;
  expected = computeExpDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(-0.75,2.)");

  x[0] = 0.0; x[1] = 0.0;
  expected = computeExpDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(0.0,0.0)");
}
BOOST_AUTO_TEST_SUITE_END()