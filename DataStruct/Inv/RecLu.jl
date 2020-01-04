#=
function Crout!(k, A)
  m, n = size(A)
  if k <= m && k <= n
    A[k, (k + 1):end] /= A[k, k]
    A[(k + 1):end, (k + 1):end] -= A[(k + 1):end, k] * A[k, (k + 1):end]
    Crout!(k + 1, A)
  end    
end

function RecLU(A)
  m, n = size(A)
  k = min(m, n)
  Crout!(1, A)
  L, U = zeros(m, k), zeros(k, n)
  for i = 1:m
    for j = 1:i
      L[i, j] = A[i, j]
    end
  end
  for i = 1:m
    U[i, i] = 1
    for j = (i + 1):n
      U[i, j] = A[i, j]
    end
  end
  L, U
end
=#

function LU!(A, eps=1e-15)
  rows, cols = size(A);
  if rows != cols
    @error "the matrix must be a spuare matrix";
  end
  L = zeros(cols, cols);
  U = copy(A);
  n = cols;
  #=
  for i = 1:n
    L[i, i] = 1
  end
  =#
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
  L + U
end

#=
function Crout!(A)

end

function RecLU(A)
    L, U
end
=#

test = true
if test
  A = [1 2 3; 4 5 6; 7 8 9]
  #L, U = RecLU(A)
  display(A)
  println()
  #display(LU!(A))
  LU!(A)
  display(A)
  println()
end
