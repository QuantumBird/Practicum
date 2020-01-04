function invLU(A, eps=1e-15)
  rows, cols = size(A);
  if rows != cols
    @error "the matrix must be a spuare matrix";
  end
  n = cols;
  L = zeros(cols, cols);
  U = copy(A);
  V = zeros(n, n)
  R = zeros(n, n)
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
  for i = 1:n
    R[i, i] = 1
    for k = (i + 1):n
      for j = i:(k - 1)
        R[k, i] = R[k, i] - L[k, j] * R[j, i]
      end
    end
  end
  V * R
end
