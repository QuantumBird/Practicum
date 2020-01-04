#include <iostream>
#include "GEmat.hpp"
#include "Mat.hpp"
using namespace std;
using namespace PLAS;

int main(){
  Mat<GEmat<int>> m(3, 3, true, 0);
  m.display();
  m(1, 1, 1);
  m(2, 2, 2);
  m(0, 0, 3);
  m.display();
  cout << m << endl;
  Mat<GEmat<int>> ta(3, 3, true);
  ta << 1;
  ta << 2;
  ta << 3;
  cout << ta << endl;
  //auto ans = *(m.mat) + *(ta.mat);
  Mat<GEmat<int>> ans = m + ta;
  cout << ans << endl;
  auto tb = 3 + m;
  cout << tb << endl;
  MatShape p = tb.shape();
  cout << "-----------------------------------" << endl;
  for (int i = 0; i < p.first; i ++) {
    for (int j = 0; j < p.second; j ++) {
      cout << tb(i, j) << " ";
    }
    cout << endl;
  }
  return 0;
}