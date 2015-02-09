/////////////////////////////////////////////////////////////////////////////
/// @file IntMatrixAlgorithmsFactory
///
/// @author Mateusz Juda <mateusz.juda@{ii.uj.edu.pl,gmail.com}>
///
/// @date 2014-08-17
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000-2014 by the CAPD Group.
//
// This file constitutes a part of the CAPD library (capdAlg),
// distributed under the terms of the GNU General Public License.
// Consult http://capd.ii.uj.edu.pl and  http://redhom.ii.edu.pl/ for details.
/////////////////////////////////////////////////////////////////////////////

#ifndef CAPD_FILE_CAPDALG_MATRIXALGORITHMS_INTMATRIXALGORITHMSFACTORY_H
#define CAPD_FILE_CAPDALG_MATRIXALGORITHMS_INTMATRIXALGORITHMSFACTORY_H

// #include
#include "SmithFormFactory.h"
#include <memory>

namespace capd
{
  namespace matrixAlgorithms
  {

    struct IntMatrixAlgorithmsFactory
    {
      template<typename Matrix>
      struct SmithForm
      {
        struct SmithFormThroughFactory
        {
          typedef capd::matrixAlgorithms::SmithForm<Matrix> SmithFormType;

          SmithFormThroughFactory(Matrix& B, bool computeQ, bool computeQinv, bool computeR, bool computeRinv)
          {
            SmithFormFactory factory(true);
            _smithForm.reset(factory(B, computeQ, computeQinv, computeR, computeRinv));
          }

          void operator()()
          {
            (*_smithForm)();
          }

          const typename SmithFormType::SqMatrix1& getQ() const { return _smithForm->getQ(); }
          const typename SmithFormType::SqMatrix1& getQinv() const { return _smithForm->getQinv(); }
          const typename SmithFormType::SqMatrix2& getR() const { return _smithForm->getR(); }
          const typename SmithFormType::SqMatrix2& getRinv() const { return _smithForm->getRinv(); }

          const int& getT() const { return _smithForm->getT(); }
          const int& getS() const { return _smithForm->getS(); }

        private:
          std::auto_ptr<SmithFormType> _smithForm;
        };

        typedef SmithFormThroughFactory type;
      };

      template<typename Matrix>
      struct SolveLinearEquation
      {
        typedef matrixAlgorithms::SolveLinearEquation<Matrix, IntMatrixAlgorithmsFactory> type;
      };

      template<typename Matrix, typename IntVector>
      struct QuotientBaseMatrix
      {
        typedef matrixAlgorithms::QuotientBaseMatrix<Matrix, IntVector, IntMatrixAlgorithmsFactory> type;
      };

    };


  }
}

#endif // CAPD_FILE_CAPDALG_MATRIXALGORITHMS_INTMATRIXALGORITHMSFACTORY_H
