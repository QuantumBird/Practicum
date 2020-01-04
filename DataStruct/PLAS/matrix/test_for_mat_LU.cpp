#include <iostream>
#include "GEmat.hpp"
#include "Mat.hpp"
#include <cstdlib>
#include <vector>
#include <chrono>
using namespace std;
using namespace PLAS;

Mat<GEmat<double>> GeneMat(int n, int a=3, int down=0, int top=114514) {
  srand(42);
  //int a = 3;
  vector<double> arr;
  for (int i = 0; i < n; i ++) {
    arr.push_back(rand()%(top - down) + down);
  }
  Mat<GEmat<double>> ans(n, n, true);
  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < n; j ++) {
      double tmp = arr[i]*arr[j] + (i == j? a: 0);
      ans(i, j, tmp);
    }
  }
  return ans;
}

template<typename T>
bool LU(Mat<GEmat<T>> & A, 
        Mat<GEmat<T>> & L, 
        Mat<GEmat<T>> & U,
        double eps=1e-15) 
{
  bool ret = true;
  MatShape pA = A.shape();
  MatShape pL = L.shape();
  MatShape pU = U.shape();
  if (pA.first != pA.second) return false;
  if (pL.first != pL.second) return false;
  if (pU.first != pU.second) return false;
  if (pA.first != pL.first) return false;
  if (pL.first != pU.first) return false;

/*
  for j = 1:(n - 1)
    if abs(U[j, j]) < eps
      println(j, U[j, j])
      @error "the matrix is a sigular matrix";
    end
    for i = (j + 1):n
      mult = U[i, j] / U[j, j];
      L[i, j] = mult;
      for k = j:n
        U[i, k] = U[i, k] - mult * U[j, k];
      end
    end
  end
*/
  int n = pA.first;
  for (int i = 0; i < n; i ++) {
    L(i, i, 1);
  }
  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < n; j ++) {
      U(i, j, A(i, j));
    }
  }
  for (int j = 0; j < n - 1; j ++) {
    if (abs(A(j, j)) < eps) {
      ret = false;
    }
    for (int i = j + 1; i < n; i ++) {
      double mult = U(i, j) / U(j, j);
      L(i, j, mult);
      for (int k = j; k < n; k ++) {
        double tmp = U(i, k) - mult * U(j, k);
        U(i, k, tmp);
      }
    }
  }
  return ret;
}

template<typename T>
Mat<GEmat<T>> inv(Mat<GEmat<T>> & A) {
  MatShape pA = A.shape();
  if (pA.first != pA.second) {
    throw ; // TODO
  }
  int n = pA.first;
  Mat<GEmat<T>> L(n, n, true);
  Mat<GEmat<T>> U(n, n, true);
  bool ret = LU(A, L, U);
  if (ret == false) {
    throw ; // TODO
  }
  // inv U
  Mat<GEmat<T>> V(n, n, true);
  for (int i = 0; i < n; i ++) {
    V(i, i, 1 / U(i, i));
    for (int k = i - 1; k >= 0; k --) {
      T anst = 0;
      for (int j = k + 1; j <= i; j ++) {
        anst += U(k, j) * V(j, i);
      }
      T uki = V(k, i) - anst / U(k, k);
      V(k, i, uki);
    }
  }
  // inv L
  Mat<GEmat<T>> R(n, n, true);
  for (int i = 0; i < n; i ++) {
    R(i, i, 1);
    for (int k = i + 1; k < n; k ++) {
      for (int j = i; j < k; j ++) {
        double tmp = R(k, i) - L(k, j) * R(j, i);
        R(k, i, tmp);
      }
    }
  }
  return U * R;
}

void testbench(int dim=10, bool display=true) {
  cout << "Matrix dim:" << dim << endl;
  Mat<GEmat<double>> rnd = GeneMat(dim);
  //cout << rnd << endl;
  cout << "Random Matrix Gene CMPL" << endl;
  Mat<GEmat<double>> L(dim, dim, true);
  Mat<GEmat<double>> U(dim, dim, true);
  chrono::steady_clock::time_point start = chrono::steady_clock::now();
  bool ret = true;//LU(rnd, L, U);
  inv(rnd);
  chrono::steady_clock::time_point end = chrono::steady_clock::now();
  chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(end - start);
  if (ret) {
    cout << "LU: success!" << endl;
  } else {
    cout << "LU: failed!" << endl; 
  }
  cout << "time used: " << time_used.count() << endl;
  if (display) {
    cout << "L:" << endl;
    cout << L << endl;
    cout << "U:" << endl;
    cout << U << endl;
  }
}

int main(int argc, const char * argv[]){
  if (argc > 1) {
    cout << "input matrix dim:" << endl;
    int n;
    cin>>n;
    Mat<GEmat<double>> inp(n, n, true);
    double tmp;
    for (int i = 0; i < n; i ++) { 
      for (int j = 0; j < n; j ++) {
        cin>>tmp;
        inp(i, j, tmp);
      }
    }
    Mat<GEmat<double>> ans = inv(inp);
    cout << "inv of matrix: " << endl;
    cout << ans << endl;
    return 0;
  }
  vector<int> dims = {10, 50, 100, 200, 500};
  for (int dim: dims) {
    testbench(dim, false);
  }
  cout << "test CMPL" << endl;
  return 0;
}