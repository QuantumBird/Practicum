function LU(A, eps=1e-15)
  rows, cols = size(A);
  if rows != cols
    @error "the matrix must be a spuare matrix";
  end
  L = zeros(cols, cols);
  U = copy(A);
  n = cols;
  for i = 1:n
    L[i, i] = 1
  end
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
  L, U
end

function invU(U)
  rows, cols = size(U)
  if rows ≠ cols
    @error "the matrix is not a square matrix"
  end
  n = rows
  V = zeros(n, n)
  for i = 1:n
    V[i, i] = 1 / U[i, i]
    for k = (i - 1):-1:1
      s = 0
      for j = (k + 1):i
        s += U[k, j] * V[j, i];
      end
      V[k, i] -= s / U[k, k];
    end
  end
  V
end

function invL(L)
  rows, cols = size(L)
  if rows ≠ cols
    @error "the matrix is not a square matrix"
  end
  n = rows
  R = zeros(n, n)
  for i = 1:n
    R[i, i] = 1
    for k = (i + 1):n
      for j = i:(k - 1)
        R[k, i] = R[k, i] - L[k, j] * R[j, i]
      end
    end
  end
  R
end

function invLU(A)
  L, U = LU(A)
  V = invU(U)
  R = invL(L)
  V * R
end

test = false

if test
  A = [1.0 2.0 3.0; 4.0 5.0 6.0; 7.0 8.0 9.0];
  println(LU(A));
  L, U = LU(A)
  println("L:")
  display(L)
  println("\nU:")
  display(U)
  println("A:")
  display(L * U)
  #println("\nA-1: inv")
  #display(inv(A))
  #println("\nA-1: LU")
  #display(inv(U)*inv(L))
end
