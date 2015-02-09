/////////////////////////////////////////////////////////////////////////////
/// @file CAPDIntMatrixAlgorithms
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

#ifndef CAPD_FILE_CAPDALG_MATRIXALGORITHMS_CAPDINTMATRIXALGORITHMS_H
#define CAPD_FILE_CAPDALG_MATRIXALGORITHMS_CAPDINTMATRIXALGORITHMS_H

// #include
#include "CAPDSmithForm.h"
#include "SolveLinearEquation.h"
#include "QuotientBaseMatrix.h"

namespace capd
{
  namespace matrixAlgorithms
  {

    struct CAPDIntMatrixAlgorithms
    {
      template<typename Matrix>
      struct SmithForm
      {
        typedef matrixAlgorithms::CAPDSmithForm<Matrix> type;
      };

      template<typename Matrix>
      struct SolveLinearEquation
      {
        typedef matrixAlgorithms::SolveLinearEquation<Matrix, CAPDIntMatrixAlgorithms> type;
      };

      template<typename Matrix, typename IntVector>
      struct QuotientBaseMatrix
      {
        typedef matrixAlgorithms::QuotientBaseMatrix<Matrix, IntVector, CAPDIntMatrixAlgorithms> type;
      };
    };


  }
}

#endif // CAPD_FILE_CAPDALG_MATRIXALGORITHMS_CAPDINTMATRIXALGORITHMS_H
