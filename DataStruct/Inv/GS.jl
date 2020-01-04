using LinearAlgebra

function GaussSeidel(A, b)
  eps = 1.0e-6;
  n, _ = size(A)
  D = diagm(diag(A));
  L = -tril(A, -1);
  U = -triu(A, 1);

  B = (D - L)\U;
  f = (D - L)\b;

  count = 1;
  x0 = zeros(n,1);
  x = B*x0 + f;

  while norm(x-x0) > eps
      x0 = x;
      x = B*x0 + f;
      count = count + 1;
      if count > 2000
          @error "can not stop normally"
          return;
      end
  end
  x
end


