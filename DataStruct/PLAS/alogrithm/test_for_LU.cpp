#include "Mat.hpp"
#include "GEmat.hpp"
#include <iostream>
#include "LU.hpp"
using namespace std;
using namespace PLAS;

int main (){
  Mat<GEmat<double>> A(3, 3, false);
  int cntr = 1;
  for (int i = 0; i < 3; i ++) {
    for (int j = 0; j < 3; j ++) {
      A(i, j, cntr ++);
    }
  }
  cout << A << endl;

  return 0;
}