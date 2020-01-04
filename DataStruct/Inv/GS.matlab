function [x, y]= Gauss_Seidel(n, A ,b)

    %y = zeros(1000,1);
    eps = 1.0e-6;
    D = diag(diag(A));
    L = -tril(A, -1);
    U = -triu(A, 1);

    B = (D - L)\U;
    f = (D - L)\b;

    count = 1;
    x0 = zeros(n,1);
    x = B*x0 + f;

    tic;
    while norm(x-x0) > eps

        x0 = x;
       % y(count) = norm(x-A\b);
        x = B*x0 + f;
        count = count + 1;

        if count > 2000
            disp('error:该矩阵不收敛');
            return;
        end
    end
    toc;
    y = toc;
    disp(count);
end
