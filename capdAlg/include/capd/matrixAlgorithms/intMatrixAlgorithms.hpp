/// @addtogroup matrixAlgorithms
/// @{

/////////////////////////////////////////////////////////////////////////////
/// @file intMatrixAlgorithms.hpp
///
/// @author Marian Mrozek
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) 2000-2005 by the CAPD Group.
//
// This file constitutes a part of the CAPD library,
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.wsb-nlu.edu.pl/ for details.

#ifndef _CAPD_MATRIXALGORITHMS_INTMATRIXALGORITHMS_HPP_
#define _CAPD_MATRIXALGORITHMS_INTMATRIXALGORITHMS_HPP_

#include <capd/auxil/Logger.h>

#include "Invert.h"
#include "CAPDSmithForm.h"
#include "MatrixOp.h"
#include "capd/auxil/minmax.h"
#include "capd/auxil/debuger.h"
#include "capd/vectalg/MatrixSlice.h"
#include "capd/vectalg/Matrix.hpp"
#include <cmath>

namespace capd{
  namespace matrixAlgorithms{

            // *** partial reduction *** //

/* ------------------------  ------------------------ */
template<class matrix>
void kernelImage(matrix& B,matrix& kernel,matrix& image){
  int m=B.numberOfRows();
  int n=B.numberOfColumns();
  matrix R=matrix::Identity(n);
  matrix Rinv = emptyMatrix<matrix>();
  int k;
  columnEchelon(B,R,Rinv,k);
  kernel=MatrixSlice<matrix>(R,1,n,k+1,n);
  image=MatrixSlice<matrix>(B,1,m,1,k);
}

/* ------------------------  ------------------------ */

template<class matrix, class sqMatrix1, class sqMatrix2>
void smithForm(matrix& B,
		   sqMatrix1& Q, sqMatrix1& Qinv,
		   sqMatrix2& R, sqMatrix2& Rinv,
		   int &s,int &t)
{
  typedef CAPDSmithForm<matrix, SmithFormTraitsBasic<matrix, sqMatrix1, sqMatrix2> > SmithFormType;
  SmithFormType smithForm(B, Q.numberOfRows() > 0, Qinv.numberOfRows() > 0,
			  R.numberOfRows() > 0, Rinv.numberOfRows() > 0);

  smithForm();

  Q = smithForm.getQ();
  Qinv = smithForm.getQinv();
  R = smithForm.getR();
  Rinv = smithForm.getRinv();

  s = smithForm.getS();
  t = smithForm.getT();
}

/* ------------------------  ------------------------ */

template<class matrix>
class SolveLinearEquation
{

public:
  explicit SolveLinearEquation(const matrix& A):
    _m(A.numberOfRows()), _n(A.numberOfColumns()),
    _A(A), _B(A), _Qinv(_m, _m), _R(_n, _n)
  {
    matrix Q = emptyMatrix<matrix>();
    matrix Rinv = emptyMatrix<matrix>();
    smithForm(_B, Q, _Qinv, _R, Rinv, _s, _t);
  }

  template<class vector, class colVector>
  bool operator()(const colVector& b, vector& x)
  {
    vector c = _Qinv * b; // the method and this vector should be const, however there is a bug in Z2 operators and the code cannot be compiled
    x = vector(_n);
    bool result = true;

    for(int i=1; i<=_t && result; ++i){
      if(isDivisible(c(i),_B(i,i))){
	x(i)=c(i)/_B(i,i);
      }else{
	result = false;
      }
    }

    for(int i=_t+1; i <= _m && result;++i){
      if(c(i) == typename matrix::ScalarType(0) ){
	if(i<=_n) x(i)=0;
      }else{
	result = false;
      }
    }

    if (result) {
      x=_R*x;
    }

    return result;
  }

private:
  int _m, _n;
  const matrix& _A;
  matrix _B, _Qinv, _R;
  int _s, _t;
};

template<class matrix, class vector, class colVector>
bool solveLinearEquation(const matrix& A,const colVector& b,vector& x)
{
  const int m=A.numberOfRows();
  const int n=A.numberOfColumns();

  CAPD_TRACE("solveLinearEquation for matrix size: " << m << "x" << n);
  const bool trace = (n <= 100 && m <= 100);

  if (trace) {
    CAPD_TRACE("solveLinearEquation args: " << cppReprezentation(A, "A", "TYPE") << " "
	       << cppReprezentation(b, "b", "TYPE"));
  }

  SolveLinearEquation<matrix> solver(A);

  const bool result = solver(b, x);

  if (result) {
    if (trace) {
      CAPD_TRACE("solveLinearEquation result: " << cppReprezentation(x, "x", "TYPE"));
    }
  } else {
    CAPD_TRACE("solveLinearEquation result: " << cppReprezentation(vector((unsigned)0), "x", "TYPE"));
  }

  return result;
}


/* ------------------------  ------------------------ */

template<class matrix>
bool invert(const matrix& A,matrix& Ainv)
{
  Invert<matrix> invertOp(A);

  return invertOp(Ainv);
}


    // template<typename matrix>
    // std::string serialize
/* ------------------------  ------------------------ */
template<class matrix,class IntVector>
void quotientBaseMatrix(
  const matrix& A_W,                       // input: basis of G \subset Z^p as columns of A_W,
  const matrix& A_V,                       // input: basis of H\subset G \subset Z^p as columns of A_V,
  matrix& A_U,                             // output: pseudobasis of G/H as columns of A_U,
  IntVector& A_orders                      // output: IntVector of finite orders
                                           // of elements of pseudobasis A_U
){
   typedef typename matrix::ColumnVectorType VectorType;
   int p=A_W.numberOfRows();
   int m=A_W.numberOfColumns();
   int n=A_V.numberOfColumns();
   const bool trace = (p < 100 && m < 100 && n < 100);

   CAPD_TRACE("quotientBaseMatrix with sizes: " << p << " " << m << " " << n);

   if (trace) {
     CAPD_TRACE("quotientBaseMatrix args: " << cppReprezentation(A_W, "A_W", "TYPE") << " "
		<< cppReprezentation(A_V, "A_V", "TYPE"));
   }

   VectorType a;
   matrix B(m,n);
   SolveLinearEquation<matrix> solver(A_W);

   for(int j=0;j<n;++j){
     solver(A_V.column(j),a);
     for(int i=0;i<m;++i) B[i][j]=a[i];
   }
   matrix Q(m, m), Qinv = emptyMatrix<matrix>();
   matrix R = emptyMatrix<matrix>(), Rinv = emptyMatrix<matrix>();
   int s,t;
   smithForm(B,Q, Qinv, R, Rinv, s, t);


   matrix WQ=A_W*Q;
   A_U=MatrixSlice<matrix>(WQ,1,p,s+1,m);
   A_orders=IntVector(n-s);    // finite orders greater than one
   for(int i=s;i<n;++i) A_orders[i-s]=B[i][i];

   if (trace) {
     CAPD_TRACE("quotientBaseMatrix result: " << cppReprezentation(A_U, "A_U", "TYPE") << " "
		<< cppReprezentation(A_orders, "A_orders", "TYPE"));
   }

}
/* ------------------------  ------------------------ */
template<class matrix>
void copy(const matrix &A, matrix &result, int row, int col){ // copy matrix A to matrix result starting at position
																														  // result[row][col]
	for(int i=0;i<A.numberOfRows();++i)
		for(int j=0;j<A.numberOfColumns();++j)
			result[row+i][col+j] = A[i][j];
}

/* ------------------------  ------------------------ */
template<class matrix>
void spaceIntersection(const matrix &A,const matrix &B,matrix &C){ // input: basis of space A as columns of A,
																																	 // input: basis of space B as columns of B,
																																	 // output: basis of A intersection B as columns of C
	int A_n = A.numberOfColumns();
	int A_m = A.numberOfRows();
	int B_n = B.numberOfColumns();
	//int B_m = B.numberOfRows();
	int D_n = A_n + B_n, D_m = A_m;
	matrix D(D_m, D_n);
	copy(A,D,0,0);
	copy(B,D,0,A_n);

	matrix kernel,image,Dcopy = D;
	kernelImage(Dcopy,kernel,image);
	D = MatrixSlice<matrix>(D,1,A_m,1,A_n);
	kernel = MatrixSlice<matrix>(kernel,1,A_n,1,kernel.numberOfColumns());
	C = D * kernel;
}

/* ------------------------  ------------------------ */

  } // end of namespace matrixAlgorithms

} // end of namespace capd;
#endif // _CAPD_MATRIXALGORITHMS_INTMATRIXALGORITHMS_HPP_

/// @}
