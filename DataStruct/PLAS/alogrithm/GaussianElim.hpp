#include "basic_mat.h"
#include "Mat.hpp"

// SPACE_NAME is defined in basic_mat.h
namespace SPACE_NAME {
// namespace begin

template<class MType>
Mat<MType> GaussianElim(Mat<MType> & A) {
  MatShape p = A.shape();
  int rows = p.first;
  int cols = p.second;
  /* 当不可解时抛出异常 */
  // TODO: 判断不可解条件
  MType ans = A.mat -> copy();
  for (int i = 0; i < rows; i ++) {
    int r = i;
    for (int j = i + 1; j < cols; j ++) {
      if (std::abs(ans(j, i)) > std::abs(ans(r, i))) { // may have trouble
        r = j;
      }
    }
    if (r != i) {
      for (int j = 0; j < cols; j ++) {
        auto tmp = ans(r, j);
        ans(r, j, ans(i, j));
        ans(i, j, tmp);
      }
    }
    for (int k = i + 1; k < rows; k ++) {
      auto f = ans(k, i) / ans(i, i);
      for (int j = i; j < cols; j ++) {
        auto tmp = ans(k, j) - f * ans(i, j);
        ans(k, j, tmp);
      }
    }
  }
  for (int i = rows - 1; i >= 0; i --) {
    for (j = i + 1; j < n; j ++) {
      auto tmp = ans(i, ) // fuck! there have some problem!
    }
  }
}

// namespace end
}
