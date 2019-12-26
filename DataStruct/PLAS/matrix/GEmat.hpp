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
#include "extratype.hpp"
#define NAIVE_VER
/*
  条件编译宏
  NAIVE_VER:
    这个宏是为了标记朴素算法和高级算法的区别
    例如矩阵乘法的 O(n^3) 和 O(n^2.7) 的实现
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
  typedef const T ElemType;
  int _rows_, _cols_;
  T ** mat;
  // construct
  void construct( int rows, 
                  int cols, 
                  bool fill=false, 
                  T fill_elem=0 ) {
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
  GEmat(int rows,
        int cols,
        bool fill=false,
        T fill_elem=0) {
    construct(rows, cols, fill, fill_elem);
  }
  GEmat(MatShape shape, bool fill=false, T fill_elem=0) {
    construct(shape.first, shape.second, fill, fill_elem);
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
  bool setElem(int idxr, int idxc, T elem) {
    if ((idxr < 0 && idxr >= _rows_) || (idxc < 0 && idxc >= _cols_)) {
      return false;
    }
    mat[idxr][idxc] = elem;
    return true;
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
  std::string toString() {
    std::ostringstream ostr;
    //ostr << "rows: "  << _rows_
    //     << " cols: " << _cols_ << "\n";
    ostr << "shape: " << _rows_ << "x" << _cols_ << "\n"; 
    for (int i = 0; i < _rows_; i ++) {
      for (int j = 0; j < _cols_; j ++) {
        ostr << mat[i][j] << " ";
      }
      ostr << "\n";
    }
    ostr << "elem type: " << getTypeStr<T>() << "\n";
    return ostr.str();
  }
  /*
  void forAll(T (* func)(T)) {
    for (int i = 0; i < _rows_; i ++) {
      for (int j = 0; j < _cols_; j ++) {
        mat[i][j] = func(mat[i][j]);
      }
    }
  }
  T reduce(T (* func)(T), int dim=0) {
    ; // TODO
  }*/
  // redefine operator
  GEmat<T> operator*(GEmat<T> & m) {
    if (_cols_ != m._rows_) {
      throw ; // TODO
    }
    GEmat<T> ans(_rows_, m._cols_);
    for (int i = 0; i < _rows_; i ++) {
      for (int j = 0; j < m._cols_; j ++) {
        for (int k = 0; k < _cols_; k ++) {
          ans.mat[i][j] += mat[i][k] * m.mat[k][j];
        }
      }
    }
    return ans;
  }
  GEmat<T> operator+(GEmat<T> & m) {
    if ((_rows_ != m._rows_) || (_cols_ != m._cols_)) {
      throw ; // TODO
    }
    GEmat<T> ans(_rows_, _cols_);
    for (int i = 0; i < _rows_; i ++) {
      for (int j = 0; j < _cols_; j ++) {
        ans.mat[i][j] = mat[i][j] + m.mat[i][j];
      }
    }
    return ans;
  }
  GEmat<T> operator-(GEmat<T> & m) {
    if ((_rows_ != m._rows_) || (_cols_ != m._cols_)) {
      throw ; // TODO
    }
    GEmat<T> ans(_rows_, _cols_);
    for (int i = 0; i < _rows_; i ++) {
      for (int j = 0; j < _cols_; j ++) {
        ans.mat[i][j] = mat[i][j] - m.mat[i][j];
      }
    }
    return ans;
  }
  // untested !!!! TODO: test
  GEmat<T> operator*(T cst) {
    GEmat<T> ans(_rows_, _cols_);
    for (int i = 0; i < _rows_; i ++) {
      for (int j = 0; j < _cols_; j ++) {
        ans.mat[i][j] = mat[i][j] * cst;
      }
    }
    return ans;
  }
  GEmat<T> operator+(T cst) {
    GEmat<T> ans(_rows_, _cols_);
    for (int i = 0; i < _rows_; i ++) {
      for (int j = 0; j < _cols_; j ++) {
        ans.mat[i][j] = mat[i][j] + cst;
      }
    }
    return ans;
  }
  GEmat<T> operator-(T cst) {
    GEmat<T> ans(_rows_, _cols_);
    for (int i = 0; i < _rows_; i ++) {
      for (int j = 0; j < _cols_; j ++) {
        ans.mat[i][j] = mat[i][j] - cst;
      }
    }
    return ans;
  }
  GEmat<T> operator/(T cst) {
    GEmat<T> ans(_rows_, _cols_);
    for (int i = 0; i < _rows_; i ++) {
      for (int j = 0; j < _cols_; j ++) {
        ans.mat[i][j] = mat[i][j] / cst;
      }
    }
    return ans;
  }
  GEmat<T> copy() {
    return MatCopy(*this); // may have trouble
  }
  GEmat<T> * new_and_copy() {
    GEmat<T> * ret = new GEmat<T>(_rows_, _cols_, false);
    for (int i = 0; i < _rows_; i ++) {
      for (int j = 0; j < _cols_; j ++) {
        ret -> mat[i][j] = mat[i][j];
      }
    }
    return ret;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & out, GEmat<T> & m){
  out << m.toString();
  return out;
}

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
GEmat<T> MatCopy(GEmat<T> & m) {
  GEmat<T> ret(m._rows_, m._cols_, false);
  for (int i = 0; i < m._rows_; i ++) {
    for (int j = 0; j < m._cols_; j ++) {
      ret.mat[i][j] = m.mat[i][j];
    }
  }
  return ret;
}
template<typename Tt, typename Tf>
GEmat<Tt> MatElemTypeTrans(GEmat<Tf> & m) {
  GEmat<Tt> ret(m._rows_, m._cols_, false);
  for (int i = 0; i < m._rows_; i ++) {
    for (int j = 0; j < m._cols_; j ++) {
      ret.mat[i][j] = Tt(m.mat[i][j]);
    }
  }
  return ret;
}





////////////////////////////// useless ////////////////////////
/*
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
*/

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



