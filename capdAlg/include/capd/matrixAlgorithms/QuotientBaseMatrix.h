/////////////////////////////////////////////////////////////////////////////
/// @file QuotientBaseMatrix
///
/// @author Mateusz Juda <mateusz.juda@{ii.uj.edu.pl,gmail.com}>
///
/// @date 2014-08-09
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000-2014 by the CAPD Group.
//
// This file constitutes a part of the CAPD library (capdAlg),
// distributed under the terms of the GNU General Public License.
// Consult http://capd.ii.uj.edu.pl and  http://redhom.ii.edu.pl/ for details.
/////////////////////////////////////////////////////////////////////////////

#ifndef CAPD_FILE_CAPDALG_MATRIXALGORITHMS_QUOTIENTBASEMATRIX_H
#define CAPD_FILE_CAPDALG_MATRIXALGORITHMS_QUOTIENTBASEMATRIX_H

// #include
#include <capd/auxil/Logger.h>


namespace capd
{
  namespace matrixAlgorithms
  {

    template<class Matrix, typename IntVector, typename Traits>
    class QuotientBaseMatrix
    {
      typedef typename Matrix::ScalarType ScalarType;
    public:

      QuotientBaseMatrix(const Matrix& A_W,
                         const Matrix& A_V):
        A_W(A_W), A_V(A_V)
      {}

      virtual ~QuotientBaseMatrix() {}

      void operator()()
      {
        typedef typename Matrix::ColumnVectorType VectorType;
        const int p=A_W.numberOfRows();
        const int m=A_W.numberOfColumns();
        const int n=A_V.numberOfColumns();
        const bool trace = (p < 100 && m < 100 && n < 100);

        CAPD_DEBUG("quotientBaseMatrix with sizes: " << p << " " << m << " " << n);

        if (trace) {
          CAPD_TRACE("quotientBaseMatrix args: " << cppReprezentation(A_W, "A_W", "TYPE") << " "
                     << cppReprezentation(A_V, "A_V", "TYPE"));
        }

        VectorType a;
        Matrix B(m,n);
        SolveLinearEquation<Matrix, Traits> solver(A_W);

        for(int j=0;j<n;++j){
          solver(A_V.column(j),a);
          for(int i=0;i<m;++i) B[i][j]=a[i];
        }

        typedef typename Traits::template SmithForm<Matrix>::type SmithForm;
        SmithForm smithForm(B, true, false, false, false);
        smithForm();

        Matrix WQ=A_W * smithForm.getQ();
        const int s = smithForm.getS();
        // const int t = smithForm.getT(); // DW: unused variable causes lots of warnings

        A_U=MatrixSlice<Matrix>(WQ,1,p,s+1,m);
        A_orders.resize(n-s);    // finite orders greater than one
        for(int i=s;i<n;++i) A_orders[i-s]=B[i][i];

        if (trace) {
          CAPD_TRACE("quotientBaseMatrix result: " << cppReprezentation(A_U, "A_U", "TYPE") << " "
                     << cppReprezentation(A_orders, "A_orders", "TYPE"));
        }
      }
      const Matrix& pseudoBasis() const { return A_U; }
      const IntVector& orders() const { return A_orders; }

    private:
      const Matrix& A_W;
      const Matrix& A_V;
      Matrix A_U;
      IntVector A_orders;
    };


  }
}

#endif // CAPD_FILE_CAPDALG_MATRIXALGORITHMS_QUOTIENTBASEMATRIX_H
