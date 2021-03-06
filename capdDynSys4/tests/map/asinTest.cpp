//////////////////////////////////////////////////////////////////////////////
//   Package:          CAPD

/////////////////////////////////////////////////////////////////////////////
//
/// @file asinTest.cpp
///
/// @author Daniel Wilczak
//
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) CAPD group
//
// This file constitutes a part of the CAPD library,
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.ii.uj.edu.pl/ for details.

//#define BOOST_TEST_MODULE asinTest
#include "compare.h"
BOOST_AUTO_TEST_SUITE(asinSuite)

std::vector<double> computeAsinDer(MapType::VectorType & u){
  double x = u[0].leftBound();
  double y = u[1].leftBound();

  // code generated by the following Mathematica code
  // W[n_,m_]:=D[ArcSin[x*y],{x,n},{y,m}]/(n!m!)//FullSimplify
  // Table[Table[W[m-n,n]//CForm,{n,0,m}],{m,0,5}]//Flatten

  capd::rounding::DoubleRounding::roundNearest();
  double r[] = {ArcSin(x*y),y/Sqrt(1 - Power(x,2)*Power(y,2)),x/Sqrt(1 - Power(x,2)*Power(y,2)),(x*Power(y,3))/(2.*Power(1 - Power(x,2)*Power(y,2),1.5)),Power(1 - Power(x,2)*Power(y,2),-1.5),(Power(x,3)*y)/(2.*Power(1 - Power(x,2)*Power(y,2),1.5)),(Power(y,3) + 2*Power(x,2)*Power(y,5))/(6.*Power(1 - Power(x,2)*Power(y,2),2.5)),(3*x*Power(y,2))/(2.*Power(1 - Power(x,2)*Power(y,2),2.5)),(3*Power(x,2)*y)/(2.*Power(1 - Power(x,2)*Power(y,2),2.5)),(Power(x,3) + 2*Power(x,5)*Power(y,2))/(6.*Power(1 - Power(x,2)*Power(y,2),2.5)),(x*Power(y,5)*(3 + 2*Power(x,2)*Power(y,2)))/(8.*Power(1 - Power(x,2)*Power(y,2),3.5)),(Power(y,2)*(1 + 4*Power(x,2)*Power(y,2)))/(2.*Power(1 - Power(x,2)*Power(y,2),3.5)),(3*x*y*(2 + 3*Power(x,2)*Power(y,2)))/(4.*Power(1 - Power(x,2)*Power(y,2),3.5)),(Power(x,2)*(1 + 4*Power(x,2)*Power(y,2)))/(2.*Power(1 - Power(x,2)*Power(y,2),3.5)),(Power(x,5)*y*(3 + 2*Power(x,2)*Power(y,2)))/(8.*Power(1 - Power(x,2)*Power(y,2),3.5)),(Power(y,5)*(3 + 24*Power(x,2)*Power(y,2) + 8*Power(x,4)*Power(y,4)))/(40.*Power(1 - Power(x,2)*Power(y,2),4.5)),(5*x*Power(y,4)*(3 + 4*Power(x,2)*Power(y,2)))/(8.*Power(1 - Power(x,2)*Power(y,2),4.5)),(y*(2 + 21*Power(x,2)*Power(y,2) + 12*Power(x,4)*Power(y,4)))/(4.*Power(1 - Power(x,2)*Power(y,2),4.5)),(x*(2 + 21*Power(x,2)*Power(y,2) + 12*Power(x,4)*Power(y,4)))/(4.*Power(1 - Power(x,2)*Power(y,2),4.5)),(5*Power(x,4)*y*(3 + 4*Power(x,2)*Power(y,2)))/(8.*Power(1 - Power(x,2)*Power(y,2),4.5)),(Power(x,5)*(3 + 24*Power(x,2)*Power(y,2) + 8*Power(x,4)*Power(y,4)))/(40.*Power(1 - Power(x,2)*Power(y,2),4.5))};
  return std::vector<double> (r,r+sizeof(r)/sizeof(double));
}

BOOST_AUTO_TEST_CASE(xasin)
{
  std::string txt = "var:x,y;fun:asin(x*y);",
              msg = "Function \"" + txt + "\"  x = " ;
  MapType f(txt,5);
  VectorType x(2);
  JetType df(1,2,5);
  std::vector<double> expected;

  x[0] = .5; x[1]=0.25;
  expected = computeAsinDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(0.5,0.25)");

  MapType g("var:x,y;fun:-asin(-x*y);",5);
  g(x,df);
  compareResults(expected, df, msg+"(0.5,0.25)");

  x[0] = -0.125; x[1] = 1;
  expected = computeAsinDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(-0.125,1)");

  x[0] = 0.0; x[1] = 0.0;
  expected = computeAsinDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(0.0,0.0)");

}

using capd::autodiff::Node;

void _f(Node /*t*/, Node in[], int /*dimIn*/, Node out[], int /*dimOut*/, Node /*params*/[], int /*noParams*/)
{
  out[0] = -asin(-in[0]*in[1]);
}

BOOST_AUTO_TEST_CASE(xasinnode)
{
  std::string msg = "Function \"-asin(-x*y)\"  x = " ;
  MapType f(_f,2,1,0,5);
  VectorType x(2);
  x[0] = .125; x[1] = 0.25;
  std::vector<double> expected = computeAsinDer(x);
  JetType df(1,2,5);
  f(x,df);
  compareResults(expected, df, msg+"(0.5,0.25)");

  x[0] = -0.75; x[1] = .5;
  expected = computeAsinDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(-0.75,.5)");

  x[0] = 0.0; x[1] = 0.0;
  expected = computeAsinDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(0.0,0.0)");
}

BOOST_AUTO_TEST_SUITE_END()