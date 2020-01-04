#include "mats.hpp"
#include <bits/stdc++.h>
/*
namespace SPACE_NAME {
// namespace begin
template<class MType>
struct LUret {
  //typedef typename MType::ElemType ElemType;
  //typedef Mat<GEmat<ElemType>> mat_type;
  //typedef std::pair<mat_type, mat_type> type;
  using ElemType = typename MType::ElemType;

};

template<class MType>
typename LUret<MType>::type LU(Mat<MType> & A) {
  MatShape p = A.shape();
  int rows = p.first;
  int cols = p.second;
  if (rows != cols) {
    throw; // A is not square matrix
  }
  LUret<MType>::mat_type L(cols, cols, true, 0);
  LUret<MType>::mat_type U = A.copy();

  for (int i = 0; i < cols; i ++) {
    L(i, i) = LUret<MType>::ElemType(1);
  }
  for (int j = 0; j < cols - 1; j ++) {
    if (std::abs(U(j, j)) < eps) {
      throw ; // if the matrix is sigular
    }
    for (int i = j + 1; i < cols; i ++) {
      auto mult = U(i, j) / U(j, j);
      L(i, j, mult);
      for (int k = j; k < cols; k ++) {
        auto tmp = U(i, k) - mult * U(j, k);
        U(i, k, tmp);
      }
    }
  }
  LUret<MType>::type ans(L, U);
  return ans;
}
// namespace end
}*/
using namespace PLAS;
template<typename T>
std::pair<Mat<GEmat<T>>, Mat<GEmat<T>>> LU(Mat<GEmat<T>> & A) {
  MatShape p = A.shape();
  int rows = p.first;
  int cols = p.second;
  if (rows != cols) {
    throw; // A is not square matrix
  }
  Mat<GEmat<T>> L(cols, cols, true, 0);
  Mat<GEmat<T>> U = A.copy();

  for (int i = 0; i < cols; i ++) {
    L(i, i) = T(1);
  }
  for (int j = 0; j < cols - 1; j ++) {
    if (std::abs(U(j, j)) < eps) {
      throw ; // if the matrix is sigular
    }
    for (int i = j + 1; i < cols; i ++) {
      auto mult = U(i, j) / U(j, j);
      L(i, j, mult);
      for (int k = j; k < cols; k ++) {
        auto tmp = U(i, k) - mult * U(j, k);
        U(i, k, tmp);
      }
    }
  }
  std::pair<Mat<GEmat<T>>, Mat<GEmat<T>>> ans(L, U);
  return ans;
}