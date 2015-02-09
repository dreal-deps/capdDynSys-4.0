/////////////////////////////////////////////////////////////////////////////
/// @file PARIIntMatrixAlgorithms
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

#ifndef CAPD_FILE_CAPDALG_MATRIXALGORITHMS_PARIINTMATRIXALGORITHMS_H
#define CAPD_FILE_CAPDALG_MATRIXALGORITHMS_PARIINTMATRIXALGORITHMS_H

// #include
#include "PARISmithForm.h"
#include "SolveLinearEquation.h"
#include "QuotientBaseMatrix.h"

namespace capd
{
  namespace matrixAlgorithms
  {

    struct PARIIntMatrixAlgorithms
    {
      template<typename Matrix>
      struct SmithForm
      {
        typedef matrixAlgorithms::PARISmithForm<typename Matrix::ScalarType> type;
      };

      template<typename Matrix>
      struct SolveLinearEquation
      {
        typedef matrixAlgorithms::SolveLinearEquation<Matrix, PARIIntMatrixAlgorithms> type;
      };

      template<typename Matrix, typename IntVector>
      struct QuotientBaseMatrix
      {
        typedef matrixAlgorithms::QuotientBaseMatrix<Matrix, IntVector, PARIIntMatrixAlgorithms> type;
      };
    };

  }
}

#endif // CAPD_FILE_CAPDALG_MATRIXALGORITHMS_PARIINTMATRIXALGORITHMS_H
