#include <iostream>
#include "extratype.hpp"
#include "GEmat.hpp"
using namespace std;

int main() {
  Type<int> a;
  cout << a.type << endl;
  cout << getTypeStr<int>() <<  endl;
  GEmat<int> mat(2, 2);
  cout << getElemTypeStr(mat) << endl;
  return 0;
}
