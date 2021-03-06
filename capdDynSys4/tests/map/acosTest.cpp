//////////////////////////////////////////////////////////////////////////////
//   Package:          CAPD

/////////////////////////////////////////////////////////////////////////////
//
/// @file acosTest.cpp
///
/// @author Daniel Wilczak
//
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) CAPD group
//
// This file constitutes a part of the CAPD library,
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.ii.uj.edu.pl/ for details.

//#define BOOST_TEST_MODULE acosTest
#include "compare.h"
BOOST_AUTO_TEST_SUITE(acosSuite)

std::vector<double> computeAcosDer(MapType::VectorType & u){
  double x = u[0].leftBound();
  double y = u[1].leftBound();

  // code generated by the following Mathematica code
  // W[n_,m_]:=D[ArcCos[x*y],{x,n},{y,m}]/(n!m!)//FullSimplify
  // Table[Table[W[m-n,n]//CForm,{n,0,m}],{m,0,5}]//Flatten
  capd::rounding::DoubleRounding::roundNearest();
  double r[] = {ArcCos(x*y),-(y/Sqrt(1 - Power(x,2)*Power(y,2))),-(x/Sqrt(1 - Power(x,2)*Power(y,2))),-(x*Power(y,3))/(2.*Power(1 - Power(x,2)*Power(y,2),1.5)),-Power(1 - Power(x,2)*Power(y,2),-1.5),-(Power(x,3)*y)/(2.*Power(1 - Power(x,2)*Power(y,2),1.5)),-(Power(y,3)*(1 + 2*Power(x,2)*Power(y,2)))/(6.*Power(1 - Power(x,2)*Power(y,2),2.5)),(-3*x*Power(y,2))/(2.*Power(1 - Power(x,2)*Power(y,2),2.5)),(-3*Power(x,2)*y)/(2.*Power(1 - Power(x,2)*Power(y,2),2.5)),-(Power(x,3)*(1 + 2*Power(x,2)*Power(y,2)))/(6.*Power(1 - Power(x,2)*Power(y,2),2.5)),-(x*Power(y,5)*(3 + 2*Power(x,2)*Power(y,2)))/(8.*Power(1 - Power(x,2)*Power(y,2),3.5)),-(Power(y,2) + 4*Power(x,2)*Power(y,4))/(2.*Power(1 - Power(x,2)*Power(y,2),3.5)),-(6*x*y + 9*Power(x,3)*Power(y,3))/(4.*Power(1 - Power(x,2)*Power(y,2),3.5)),-(Power(x,2) + 4*Power(x,4)*Power(y,2))/(2.*Power(1 - Power(x,2)*Power(y,2),3.5)),-(Power(x,5)*y*(3 + 2*Power(x,2)*Power(y,2)))/(8.*Power(1 - Power(x,2)*Power(y,2),3.5)),-(Power(y,5)*(3 + 24*Power(x,2)*Power(y,2) + 8*Power(x,4)*Power(y,4)))/(40.*Power(1 - Power(x,2)*Power(y,2),4.5)),(-5*x*Power(y,4)*(3 + 4*Power(x,2)*Power(y,2)))/(8.*Power(1 - Power(x,2)*Power(y,2),4.5)),-(y*(2 + 21*Power(x,2)*Power(y,2) + 12*Power(x,4)*Power(y,4)))/(4.*Power(1 - Power(x,2)*Power(y,2),4.5)),-(x*(2 + 21*Power(x,2)*Power(y,2) + 12*Power(x,4)*Power(y,4)))/(4.*Power(1 - Power(x,2)*Power(y,2),4.5)),(-5*Power(x,4)*y*(3 + 4*Power(x,2)*Power(y,2)))/(8.*Power(1 - Power(x,2)*Power(y,2),4.5)),-(Power(x,5)*(3 + 24*Power(x,2)*Power(y,2) + 8*Power(x,4)*Power(y,4)))/(40.*Power(1 - Power(x,2)*Power(y,2),4.5))};
  return std::vector<double> (r,r+sizeof(r)/sizeof(double));
}

BOOST_AUTO_TEST_CASE(xacos)
{
  std::string txt = "var:x,y;fun:acos(x*y);",
              msg = "Function \"" + txt + "\"  x = " ;
  MapType f(txt,5);
  VectorType x(2);
  JetType df(1,2,5);

  x[0] = .5; x[1] = 0.25;
  std::vector<double> expected = computeAcosDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(0.5,0.25)");

  MapType g("par:pi;var:x,y;fun:pi-acos(-x*y);",5);
  g.setParameter(0,ScalarType::pi());
  g(x,df);
  compareResults(expected, df, msg+"(0.5,0.25)");
 
  x[0] = -0.75; x[1] = -0.1;
  expected = computeAcosDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(-0.75,-0.1)");

  x[0] = 0.0; x[1]= 0.0;
  expected = computeAcosDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(0.0,0.0)");
}

using capd::autodiff::Node;

void _f(Node /*t*/, Node in[], int /*dimIn*/, Node out[], int /*dimOut*/, Node params[], int /*noParams*/)
{
  out[0] = params[0]-acos(-in[0]*in[1]);
}

BOOST_AUTO_TEST_CASE(xacosnode)
{
  std::string msg = "Function \"pi-acos(-x)\"  x = " ;
  MapType f(_f,2,1,1,5);
  f.setParameter(0,ScalarType::pi());
  VectorType x(2);
  JetType df(1,2,5);

  x[0] = .1; x[1]=1;
  std::vector<double> expected = computeAcosDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(.1,1)");

  x[0] = -0.143; x[1] = 0.6;
  expected = computeAcosDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(-0.143,0.6)");

  x[0] = 0.0; x[1] = 0.0;
  expected = computeAcosDer(x);
  f(x,df);
  compareResults(expected, df, msg+"(0.0,0.0)");
}
BOOST_AUTO_TEST_SUITE_END()