// basic_mat.h
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string.h>

enum MatType {
  GE, // general
  GB, // general band
  SY, // symmetric
  SB, // symmetric packed
  SP, // symmetric packed
  HE, // hemmitian 
  HB, // hemmitian band
  TR, // triangular
  TB, // triangular band 
  TP  // triangular packed
};

typedef std::pair<int, int> MatShape;
/*
template<typename T> 
class GEmat {
  int _rows_, _cols_;
  T ** mat;
public:
  // construct
  GEmat(int rows, int cols, bool fill=false, T fill_elem=0);
  GEmat(MatShape shape, bool fill=false, T fill_elem=0);
  // Matrix operate
  MatShape shape();
  T getElem(int idxr, int idxc);
  MatType getType();
  void display();
};
*/