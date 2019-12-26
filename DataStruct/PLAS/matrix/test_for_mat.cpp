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
  cout << m << endl;
  Mat<GEmat<int>> ta(3, 3, true);
  ta << 1;
  ta << 2;
  ta << 3;
  cout << ta << endl;
  //auto ans = *(m.mat) + *(ta.mat);
  auto ans = m + ta;
  cout << ans << endl;
  return 0;
}