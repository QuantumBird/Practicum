#include "basic_mat.h"
#pragma once
//#include "GEmat.hpp"
/*
template<typename T>
class Mat {
public:
  MatType _type_;
  void * matPtr = NULL;
  // -------- matrix classify --------------
  bool isSquare = false;
  //----------------------------------------
  Mat(int rows, int cols, bool fill=false, 
      T fill_val=0, MatType type=GE,) {
    if(rows == 0 || cols == 0) {
      throw ;// TODO: fix - if rows or cols is zero
    }
    if (rows == cols) {
      isSquare = true;
    }
    // TODO: finish classify check
    switch(type) {
      case GE:  matPtr = new GEmat<T>(rows, cols); break;
      // TODO: fill it !
      default:
        matPtr = new GEmat<T>(rows, cols);
    }
    if (matPtr == NULL) {
      throw ; // TODO: fix it!!!!! - if is bad_alloc
              // or change it to try{ ... }catch{ .. }
    }
  }
  Mat(void * mat, MatType type=GE) {
    matPtr = mat;
    _type_ = type;
  }
  ~Mat() {
    delete matPtr; // TODO: check if need type transfrom
  }
  // operate
  MatShape shape() {
    switch(_type_) {
      case GE: return (GEmat *)matPtr -> shape();
      // TODO: fill it !
      default:
        return (GEmat *)matPtr -> shape();
    }
  }
  MatType getType() {
    return _type_;
  }
  T getElem(int idxr, int idxc) {
    switch(_type_) {
      case GE: return (GEmat *)matPtr -> getElem(idxr, idxc);
      // TODO: fill it !
      default:
        return (GEmat *)matPtr -> getElem(idxr, idxc);
    }
  }
  bool setElem(int idxr, int idxc, T elem) {
    switch(_type_) {
      case GE: return (GEmat *)matPtr -> setElem(idxr, idxc, elem);
      // TODO: fill it !
      default:
        return (GEmat *)matPtr -> setElem(idxr, idxc, elem);
    }
  }
  void display() {
    switch(_type_) {
      case GE: return (GEmat *)matPtr -> display();
      // TODO: fill it !
      default:
        return (GEmat *)matPtr -> display();
    }
  }
  T operator[](int idxr, int idxc) {
    return getElem(idxr, idxc);
  }
  bool operator()(int idxr, int idxc, T elem) {
    return setElem()
  }
};
*/

/*
  Matrix duck template
  ------------------------------------------
  需要使用的矩阵类型定义了以下方法：
  1. shape
  2. getType
  3. setElem
  4. getElem
  5. display -> toString
  6. copy
  * * * * * TODO * * * * * * * *
  * (+) Mat -> Mat -> Mat           ok
  * (-) Mat -> Mat -> Mat           ok
  * (*) Mat -> Mat -> Mat           ok
  * (/) Mat -> Mat -> Mat
  * (+) (Num p) => Mat -> p -> Mat  ok
  * (-) (Num p) => Mat -> p -> Mat  ok
  * (*) (Num p) => Mat -> p -> Mat  ok
  * (/) (Num p) => Mat -> p -> Mat
  * transp Mat -> Mat
*/

// SPACE_NAME is defined in basic_mat.h
namespace SPACE_NAME {
// namespace begin
template<class MType>
class Mat {
public:
  typedef typename MType::ElemType ElemType;
  MType * mat = NULL;
  // -------- matrix classify --------------
  bool isSquare = false;
  //---------- fill locater ----------------
  int fill_pos_x = 0;
  int fill_pos_y = 0;
  //----------------------------------------
  Mat(int rows, int cols, bool fill=false, 
      typename MType::ElemType fill_val=0) {
    if(rows == 0 || cols == 0) {
      throw ;// TODO: fix - if rows or cols is zero
    }
    if (rows == cols) {
      isSquare = true;
    }
    mat = new MType(rows, cols, fill, fill_val);
    if (mat == NULL) {
      throw ; // TODO: fix it!!!!! - if is bad_alloc
              // or change it to try{ ... }catch{ .. }
    }
  }
  // TODO & WARN: may have error whem (m + m)
  Mat(MType m) { // may core dump, because double free!!!!
    //mat = & m;
    // need auto ptr;
    mat = m.new_and_copy();
  }
  ~Mat() {
    delete mat; // TODO: may have some problem
  }
  // operate
  MatShape shape() {
    return mat -> shape();
  }
  MatType getType() {
    return mat -> getType();
  }
  typename MType::ElemType getElem(int idxr, int idxc) {
    return mat -> getElem(idxr, idxc);
  }
  bool setElem(int idxr, int idxc, typename MType::ElemType elem) {
    return mat -> setElem(idxr, idxc, elem);
  }
  void display() {
    mat -> display();
  }
  std::string toString() {
    return mat -> toString();
  }
  typename MType::ElemType operator()(int idxr, int idxc) {
    return getElem(idxr, idxc);
  }
  bool operator()(int idxr, int idxc, typename MType::ElemType elem) {
    return setElem(idxr, idxc, elem);
  }
  /*
  Mat<MType> operator*(Mat<MType> & m) {
    return (*mat) * (*(m.mat));
  }
  Mat<MType> operator+(Mat<MType> & m) {
    return (*mat) + (*(m.mat));
  }
  Mat<MType> operator-(Mat<MType> & m) {
    return (*mat) - (*(m.mat));
  }
  Mat<MType> operator*(ElemType cst) {
    return (*mat) * cst;
  }
  Mat<MType> operator+(ElemType cst) {
    return (*mat) + cst;
  }
  Mat<MType> operator-(ElemType cst) {
    return (*mat) - cst;
  }*/
};

template<class MType>
std::ostream & operator<<(std::ostream & out, Mat<MType> & m) {
  out << m.toString();
  return out;
}

template<class MType>
bool operator<<(Mat<MType> & m, typename MType::ElemType val) {
  MatShape p = m.shape();
  if (0 <= m.fill_pos_x && m.fill_pos_x < p.second 
   && 0 <= m.fill_pos_y && m.fill_pos_y < p.first) {
    m(m.fill_pos_y, m.fill_pos_x, val);
    m.fill_pos_x ++;
    if (m.fill_pos_x >= p.second){
      m.fill_pos_x = 0;
      m.fill_pos_y ++;
    }
    return true;
  }else{
    return false;
  }
}
// TODO: need to modify
template<class MType>
Mat<MType> operator*(Mat<MType> & A, Mat<MType> & B) {
  //return *(A.mat) * *(B.mat);
  return MatMultM(*(A.mat), *(B.mat));
}

template<class MType>
Mat<MType> operator+(Mat<MType> & A, Mat<MType> & B) {
  //return *(A.mat) + *(B.mat);
  return MatPlusM(*(A.mat), *(B.mat));
}

template<class MType>
Mat<MType> operator-(Mat<MType> & A, Mat<MType> & B) {
  //return *(A.mat) - *(B.mat);
  return MatSubtM(*(A.mat), MatMultC(*(B.mat)));
}
//////////////////////////
template<class MType>
Mat<MType> operator*(Mat<MType> & A, typename MType::ElemType & cst) {
  //return *(A.mat) * cst;
  return MatMultC(*(A.mat), cst);
}

template<class MType>
Mat<MType> operator*(typename MType::ElemType & cst, Mat<MType> & A) {
  //return *(A.mat) * cst;
  return MatMultC(*(A.mat), cst);
}
////
template<class MType>
Mat<MType> operator+(Mat<MType> & A, typename MType::ElemType & cst) {
  //return *(A.mat) + cst;
  return MatPlusC(*(A.mat), cst);
}

template<class MType>
Mat<MType> operator+(typename MType::ElemType & cst, Mat<MType> & A) {
  //return *(A.mat) + cst;
  return MatPlusC(*(A.mat), cst);
}
////
template<class MType>
Mat<MType> operator-(Mat<MType> & A, typename MType::ElemType & cst) {
  //return *(A.mat) - cst;
  return MatPlusC(*(A.mat), cst);
}
// namespace end;
}
// TODO
/*
template<class MType>
bool operator<<(Mat<MType> & m, 
  pair<Position, typename MType::ElemType> elem) {
  MatShape p = m.shape();
  if (0 <= m.fill_pos_x && m.fill_pos_x < p.second 
   && 0 <= m.fill_pos_y && m.fill_pos_y < p.first) {
  }
}
*/