#include "basic_mat.h"
#include "extratype.hpp"

namespace SPACE_NAME {
// namespace begin
template<typename T， 
        bool up_triangular=true,
        bool slash=true>
class TPmat {
public:
  typedef const T ElemType;
  int _rows_, _cols_;
  int _n_;
  const bool _up_triangular_ = up_triangular// true; 
  // 如果 这个 变量为false则为下三角矩阵
  const bool _slash_ = slash//true; 
  // 如果 _slash_ 为 false，则为转置矩阵
  // store
  T * mat = NULL;
  int elem_num = 0;
  // assist function
  inline int _get_num_(int n) {
    return n * (n + 1) / 2;
  }
  inline int _get_pos_n_(int idxr, int idxc) {
    if (_up_triangular_ == true && _slash_ == true) {
      if (idxr > idxc) return -1; // TODO: check the cond
      return (elem_num - _get_num_(_n_ - idxr)) + (idxc - idxr);
    }
    if (_up_triangular_ == false && _slash_ == true) {
      if (idxr < idxc) return -1; // TODO: check the cond 
      return _get_num_(idxr) + idxc;
    }
    if (_up_triangular_ == true && _slash_ == false) {
      if (idxc < idxr) return -1;
      return (elem_num - _get_num_(_n_ - idxr)) + idxc;
    }
    if (_up_triangular_ == false && _slash_ == false) {
      if (idxr > idxc) return -1;
      return _get_num_(idxr) + (idxr + idxc + 1 - _n_);
    }
  }
  // construct
  void construct(int n, 
                //bool up_triang=true, 
                //bool slash=true;
                bool fill=false, 
                T fill_elem=0) 
  {
    //_up_triangular_ = up_triang;
    //_slash_ = slash;
    _rows_ = _cols_ = n;
    elem_num = _get_num_(n); //n*(n + 1) / 2;
    mat = new T[elem_num];
    if (mat == NULL) {
      throw ; // TODO
    }
    if (fill == true) {
      if (fill_elem == 0) {
        memset(mat, 0, sizeof(0));
      } else {
        for (int i = 0; i < elem_num; i ++) {
          mat[i] = fill_elem;
        }
      }
    }
  }
  TPmat(int n, 
        //bool up_triang=true,
        //bool slash=true; 
        bool fill=false, 
        T fill_elem=0) 
  {
    construct(n, up_triang, slash, fill, fill_elem);
  }
  TPmat(int rows,
        int cols, 
        //bool up_triang=true,
        //bool slash=true; 
        bool fill=false, 
        T fill_elem=0) 
  {
    if (rows != cols) {
      throw ; // TODO
    }
    construct(rows, /*up_triang, slash, */fill, fill_elem);
  }
  TPmat(MatShape p, 
        //bool up_triang=true,
        //bool slash=true; 
        bool fill=false, 
        T fill_elem=0) 
  {
    int rows = p.first;
    int cols = p.second;
    if (rows != cols) {
      throw ; // TODO
    }
    construct(rows, /*up_triang, slash,*/ fill, fill_elem);
  }
  ~TPmat() {
    delete mat;
  }
  MatShape shape() {
    return MatShape(_rows_, _cols_);
  }

  T getElem(int idxr, int idxc) {
    if (0 > idxr || n <= idxr || 0 > idxc || n <= idxc) {
      throw ; // TODO: add exception;
    }
    int pos = _get_pos_n_(idxr, idxc);
    if (pos == -1) return 0;
    return mat[pos];
  }
  bool setElem(int idxr, int idxc, T elem) {
    if (0 > idxr || n <= idxr || 0 > idxc || n <= idxc) {
      return false;
    }
    int pos = _get_pos_n_(idxr, idxc);
    if (pos == -1) return false;
    mat[pos] = elem;
    return true;
  }
  MatType getType() {
    return TP;
  }
  std::string toString() {
    std::ostringstream ostr;
    ostr << "shape: " << _rows_ <<"x" << _cols_ << "\n";
    for (int i = 0; i < _n_; i ++) {
      for (int j = 0; j < _n_ ; j ++) {
        int pos = _get_pos_n_(i, j);
        if (pos == -1){
          ostr << T(0) << " ";
        } else {
          ostr << mat[pos] << " ";
        }
        ostr << "\n";
      }
    }
    ostr << "elem type: " << getTypeStr<T>() << "\n";
    return ostr.str();
  }
  void display() {
    std::cout << toString();
  }
  TPmat<T, up_triangular, slash> copy() {
    return MatCopy(*this); // need test!!
  }
  TPmat<T, up_triangular, slash> * new_and_copy() {
    TPmat<T> * ret = new TPmat<T, up_triangular, slash>(_n_, false);
    for (int i = 0; i < elem_num; i ++) {
      ret -> mat[i] = mat[i];
    }
    return ret;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & out, TPmat<T> & m){
  out << m.toString();
  return out;
}

template<typename T, bool up_triangular, bool slash>
TPmat<T, up_triangular, slash> MatCopy(TPmat<T, up_triangular, slash> & m) {
  TPmat<T> ret(m._n_, m._up_triangular_, m._slash_, false);
  for (int i = 0; i < m.elem_num; i ++) {
    ret.mat[i] = m.mat[i];
  }
  return ret;
}

template<typename Tt, typename Tf, bool up_triangular, bool slash>
TPmat<Tt, up_triangular, slash> MatElemTypeTrans(TPmat<Tf, up_triangular, slash> & m) {
  TPmat<Tt, up_triangular, slash> ret(m._n_, m._up_triangular_, m._slash_, false);
  for (int i = 0; i < m.elem_num; i ++) {
    ret.mat[i] = Tt(m.mat[i]);
  }
  return ret;  
}
// 三角矩阵转置:
// 由于三角矩阵转置后类型会变，所以要使用一些元编程技巧：）

/*
template<bool A, bool B>
struct cond_and {
  static const bool value = A && B;
};

template<bool A, bool B>
struct bool_same {
  static const bool value = (A == B);
};

template<class MType>
struct get_TPmat_transp_type {
  typedef conditional<
    cond_and<>
  >
}*/

/*
template<typename T, bool up_triangular, bool slash>
struct _get_TPmat_transp_type_ {
  typedef GEmat<T> type;
};

template<typename T>
struct _get_TPmat_transp_type_<T, true, true> {
  typedef TPmat<T, false, true> type;
};

template<typename T>
struct _get_TPmat_transp_type_<T, false, true> {
  typedef TPmat<T, true, true> type;
}

template<typename T>
struct _get_TPmat_transp_type_<T, true, false> {
  typedef TPmat
}*/

template<typename T, bool up_triangular, bool slash>
GEmat<T> MatTransp(TPmat<T, up_triangular, slash> & A) {
  GEmat<T> ans(A._n_, A._n_, false);
  for (int i = 0; i < A._n_; i ++) {
    for (int j = 0; j < A._n_; j ++) {
      ans.setElem(j, i, A.getElem(i, j));
    }
  }
  return ans;
}

template<typename T>
TPmat<T, false, false>
template<typename T, bool up_triangular, bool slash>
TPmat<T> MatMultM(TPmat<T> & A, TPmat<T> & B) {

}

template<typename T, bool up_triangular, bool slash>
TPmat<T> MatMultC(TPmat<T> & A, T cst)

template<typename T, bool up_triangular, bool slash>
TPmat<T> MatPlusM(TPmat<T> & A, TPmat<T> & B)

template<typename T, bool up_triangular, bool slash>
TPmat<T> MatSubtM(TPmat<T> & A, TPmat<T> & B)

template<typename T, bool up_triangular, bool slash>
TPmat<T> MatPlusC(TPmat<T> & A, T cst)

template<typename T, bool up_triangular, bool slash>
TPmat<T> MatSubtC(TPmat<T> & A, T cst)

template<typename T, bool up_triangular, bool slash>
TPmat<T> MatDivC(TPmat<T> & A, T cst)

//special function: 

// namespace end
}