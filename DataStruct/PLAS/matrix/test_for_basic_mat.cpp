#include "GEmat.hpp"
#define  APART cout << "----------------------------------" << endl
using namespace std;

int main () {
    cout << "test bench for basic_mat" << endl;
    /***********************************************/
    APART;
    cout << "1. build a 3x3 all-zero int matrix" << endl;
    GEmat<int> m(3, 3, true, 0);
    m.display();
    /***********************************************/
    APART;
    cout<< "2. build 2 3x3 matrix and set val" << endl;
    GEmat<int> A(3, 3, true);
    GEmat<int> B(3, 3, true);
    for (int i = 0; i < 3; i ++) {
        A.setElem(i, i, i + 1);
        B.setElem(i, i, 2);
    }
    cout<<"A: "<<endl;
    A.display();
    cout<<"B: "<<endl;
    B.display();
    
    /***********************************************/
    APART;
    cout<< "3. mult 2 3x3 matrix" << endl;
    GEmat<int> C = GEmultM(A, B);
    C.display();
    /***********************************************/
    APART;
    cout << "4. transpose a 3x2 matrix" << endl;
    GEmat<int> D32(3, 2, true);
    D32.setElem(0, 0, 1);
    D32.setElem(1, 1, 2);
    D32.display(); 
    GEmat<int> D23 = GEtransp(D32);
    D23.display();
    /**********************************************/
    APART;
    cout << "test for '*' between D32 and D23" << endl;
    GEmat<int> ans = D23 * D32;
    ans.display();
    /**********************************************/
    APART;
    cout << "test for '+'" << endl;
    GEmat<int> ans2 = A + B;
    ans2.display();
    /**********************************************/
    APART;
    cout << "test for operator << " << endl;
    cout << ans2 << endl;
    /**********************************************/
    //cout << "5. test for GEcopy" << endl;
    //GEmat<int> cpy(D32);
    //cpy.display();
    /**********************************************/
    return 0;
}