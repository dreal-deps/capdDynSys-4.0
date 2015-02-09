/////////////////////////////////////////////////////////////////////////////
/// @file SmithForm.h
///
/// @author Mateusz Juda <mateusz.juda@{ii.uj.edu.pl,gmail.com}>
///
/// @date 2014-06-19
/////////////////////////////////////////////////////////////////////////////

// Copyright (C) 2000-2014 by the CAPD Group.
//
// This file constitutes a part of the CAPD library,
// distributed under the terms of the GNU General Public License.
// Consult  http://capd.ii.edu.pl/ for details.

#ifndef CAPD_FILE_SMITHFORM_H
#define CAPD_FILE_SMITHFORM_H

namespace capd
{

  namespace matrixAlgorithms
  {

    template<class MatrixT, typename SqMatrix1T, typename SqMatrix2T>
    struct SmithFormTraitsBasic
    {
      typedef typename MatrixT::ScalarType ScalarType;
      typedef typename MatrixT::size_type size_type;
      typedef MatrixT Matrix;
      typedef SqMatrix1T SqMatrix1;
      typedef SqMatrix2T SqMatrix2;
    };

    template<class MatrixT>
    struct SmithFormTraits : SmithFormTraitsBasic<MatrixT, void*, void*>
    {
      typedef SmithFormTraitsBasic<MatrixT, void*, void*> Basic;
      typedef typename Basic::Matrix Matrix;
      typedef typename Basic::ScalarType ScalarType;
      typedef typename MatrixT::template rebind<ScalarType>::other SqMatrix1;
      typedef typename MatrixT::template rebind<ScalarType>::other SqMatrix2;
    };

    template<class MatrixT, typename TraitsT=SmithFormTraits<MatrixT> >
    class SmithForm
    {
    public:
      typedef TraitsT Traits;
      typedef typename Traits::Matrix Matrix;
      typedef typename Traits::SqMatrix1 SqMatrix1;
      typedef typename Traits::SqMatrix2 SqMatrix2;

      SmithForm(MatrixT& B, bool computeQ, bool computeQinv, bool computeR, bool computeRinv):
        _B(B),
        _m(_B.numberOfRows()), _n(_B.numberOfColumns()),
        _Q(computeQ ? SqMatrix1::Identity(_m) : SqMatrix1()),
        _Qinv(computeQinv ? SqMatrix1::Identity(_m) : SqMatrix1()),
        _R(computeR ? SqMatrix2::Identity(_n) : SqMatrix2()),
        _Rinv(computeRinv ? SqMatrix2::Identity(_n) : SqMatrix2()),
        _s(0), _t(0)
      {
      }

      const SqMatrix1& getQ() const { return _Q; }
      const SqMatrix1& getQinv() const { return _Qinv; }
      const SqMatrix2& getR() const { return _R; }
      const SqMatrix2& getRinv() const { return _Rinv; }

      const int& getT() const { return _t; }
      const int& getS() const { return _s; }

      virtual void operator()() = 0;
      virtual ~SmithForm() {}

    protected:
      MatrixT& _B;
      int _m, _n;
      SqMatrix1 _Q, _Qinv;
      SqMatrix2 _R, _Rinv;
      int _s, _t;
    };

  }

}

#endif // CAPD_FILE_SMITHFORM_H
