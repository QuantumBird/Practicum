#include "basic_mat.hpp"
using namespace std;
int main () {
    cout << "test bench for basic_mat" << endl;
    cout << "1. build a 3x3 all-zero int matrix" << endl;
    GEmat<int> m(3, 3, true, 0);
    m.display();
    return 0;
}