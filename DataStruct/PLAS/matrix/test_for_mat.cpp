#include <iostream>
#include "GEmat.hpp"
#include "Mat.hpp"
using namespace std;

int main(){
  Mat<GEmat<int>> m(3, 3, true, 0);
  m.display();
  m(1, 1, 1);
  m(2, 2, 2);
  m(0, 0, 3);
  m.display();
  return 0;
}