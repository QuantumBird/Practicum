/******************************************************
GMmat.hpp
author: Junzhe Gao
date  : 2019-12-25 
last modify: 2019-12-25 4: 56 pm
------------------------------------------------------
在本文件中实现了基础的GM矩阵类： GEmat
以及GEmat的一些操作：
    * GEmultM
    * GEmultC
    * GEcopy
******************************************************/


#include "basic_mat.h"

#define NAIVE_VER
/*
  条件编译宏
  NAIVE_VER:
    这个宏是为了标记朴素算法和高级算法的区别
    例如矩阵乘法的 O(n^3) 和 O(n^2.7) 实现
*/

//#define PARALLEL
/*
  条件编译宏
  PARALLEL:
    这个宏是为了标记使用 openMP 并行化的部分
*/


template<typename T> 
class GEmat {
public:
  int _rows_, _cols_;
  T ** mat;
  // construct
  GEmat(int rows, int cols, bool fill=false, T fill_elem=0){
    _rows_ = rows;
    _cols_ = cols;
    if (rows == 0 || cols == 0) {
      throw ; // TODO: fix if is zero
    }
    mat = (T **)malloc(sizeof(T) * rows);
    if (mat == NULL) {
      throw; // TODO: finish exception: bad_alloc
    }
    for (int i = 0; i < rows; i ++) {
      mat[i] = (T *)malloc(sizeof(T) * rows);
      if (mat[i] == NULL) {
        throw ; // TODO: throw bad_alloc
      }
    }
    if (fill == true) {
      for(int i = 0; i < rows; i ++) {
        if (fill_elem == 0) {
          memset(mat[0], 0, sizeof(T) * cols);
        } else {
          for (int j = 0; j < cols; j ++) {
            mat[i][j] = fill_elem;
          }
        }
      }
    }
  }
  GEmat(MatShape shape, bool fill=false, T fill_elem=0) {
    GEmat(shape.first, shape.second, fill, fill_elem);
  }
  ~GEmat(){
    for (int i = 0; i < _rows_; i ++) {
      free(mat[i]); // TODO: finish expection: if free fail
    }
    free(mat);
  }
  // Matrix operate
  MatShape shape() {
    return MatShape(_rows_, _cols_);
  }
  T getElem(int idxr, int idxc) {
    return mat[idxr][idxc];
  }
  void setElem(int idxr, int idxc, T elem) {
    mat[idxr][idxc] = elem;
  }
  MatType getType(){
    return GE;
  }
  void display() {
    std :: cout << "rows: " << _rows_
                << " cols: " << _cols_ << std :: endl;
    std :: cout << "MatType: GE" << std :: endl;
    for (int i = 0; i < _rows_; i ++) { 
      for (int j = 0; j < _cols_; j ++ ) {
        std :: cout << mat[i][j] << " ";
      }
      std :: cout << std :: endl;
    }
  }
};



template<typename T>
GEmat<T> GEmultM(GEmat<T> & A, GEmat<T> & B) {
#ifdef NAIVE_VER
    /*
        ans = A * B
        this is the naive version for GE matrix multiplication
        use O(n^3) algoithm: too slow, but easy to code
    */
    MatShape shapeA = A.shape();
    MatShape shapeB = B.shape();
    if (shapeA.second != shapeB.first) {
        throw ; // TODO: finish exception: if A and B can't mult
    }
    GEmat<T> ans(shapeA.first, shapeB.second);
    for (int i = 0; i < shapeA.first; i ++) {
        for (int j = 0; j < shapeB.second; j ++) {
            T tmp = 0;
            for (int k = 0; k < shapeA.second; k ++) {
                tmp += A.getElem(i, k) * B.getElem(k, j);
            }
            ans.setElem(i, j, tmp);
        }
    }
    return ans;
#else
    ;
#endif
}

template<typename T>
GEmat<T> GEcopy(GEmat<T> A) {
  MatShape sp = A.shape();
  GEmat<T> ans(sp);
  for (int i = 0; i < sp.first; i ++) {
    for (int j = 0; j < sp.second; j ++) {
      ans.mat[i][j] = A.mat[i][j];
    }
  }
  return ans;
}

template<typename T>
GEmat<T> GEmultC(T cst, GEmat<T> & A) {
#ifdef NAIVE_VER
  /*
    ans = cst * A
    cst is a constant value
    this function do cst * A[i][j] for A[i][j] in A
  */
  GEmat<T> ans = GEcopy(A);
#ifdef PARALLEL
  #pragma omp parallel
  #pragma omp for  
#endif
  for (int i = 0; i < ans._rows_; i ++) {
    for (int j = 0; j < ans._cols_; j ++) {
      ans.mat[i][j] = ans.mat[i][j] * cst;
    }
  }
  return ans;
#else
  ;
#endif
}

// TODO: check, may have some problem
template<typename T>
GEmat<T> GEtransp(GEmat<T> & A) {
  GEmat<T> ret(A._cols_, A._rows_);
  for (int i = 0; i < A._rows_; i ++) {
    for (int j = 0; j < A._cols_; j ++) {
      ret.mat[j][i] = A.mat[i][j];
    }
  }
  return ret;
}


