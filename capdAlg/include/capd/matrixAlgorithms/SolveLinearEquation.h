/////////////////////////////////////////////////////////////////////////////
/// @file SolveLinearEquation
///
/// @author Mateusz Juda <mateusz.juda@{ii.uj.edu.pl,gmail.com}>
///
/// @date 2014-08-08
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000-2014 by the CAPD Group.
//
// This file constitutes a part of the CAPD library (capdAlg),
// distributed under the terms of the GNU General Public License.
// Consult http://capd.ii.uj.edu.pl and  http://redhom.ii.edu.pl/ for details.
/////////////////////////////////////////////////////////////////////////////

#ifndef CAPD_FILE_CAPDALG_MATRIXALGORITHMS_SOLVELINEAREQUATION_H
#define CAPD_FILE_CAPDALG_MATRIXALGORITHMS_SOLVELINEAREQUATION_H

// #include

namespace capd
{
  namespace matrixAlgorithms
  {

    template<class matrix, typename Traits>
    class SolveLinearEquation
    {

    public:
      explicit SolveLinearEquation(const matrix& A):
        _m(A.numberOfRows()), _n(A.numberOfColumns()),
        _A(A), _B(A), _Qinv(), _R()
      {
        typedef typename Traits::template SmithForm<matrix>::type SmithForm;
        SmithForm smithForm(_B, false, true, true, false);
        smithForm();

        _s = smithForm.getS();
        _t = smithForm.getT();
        _Qinv = smithForm.getQinv();
        _R = smithForm.getR();
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


  }
}

#endif // CAPD_FILE_CAPDALG_MATRIXALGORITHMS_SOLVELINEAREQUATION_H
