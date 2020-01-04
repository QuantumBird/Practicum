function RandInvableMat(n, times_rng=50:200)
    A = zeros(n, n)
    for i = 1: n
      A[i, i] = 1
    end
        times = rand(times_rng)
    for i = 1: times
      opt = rand(1:5)
      if opt == 1
        rowa = rand(1:n)
        rowb = rand(1:n)
        if rowa != rowb
          for j = 1:n
            A[rowa, j], A[rowb, j] = A[rowb, j], A[rowa, j]
          end
        end
      end
      if opt == 2
        cola = rand(1:n)
        colb = rand(1:n)
        if cola != colb
          for k = 1: n
            A[k, cola], A[k, colb] = A[k, colb], A[k, cola]
          end
        end
      end
      if opt == 3
        row = rand(1:n)
        num = rand(2:n)
        A[row, :] *= num
      end
      if opt == 4
        col = rand(1:n)
        num = rand(1:n)
        A[:, col] *= num
      end
      if opt == 5
        cola = rand(1:n)
        colb = rand(1:n)
        A[:, cola] += A[:, colb]
      end
      if opt == 6
        rowa = rand(1:n)
        rowb = rand(1:n)
        A[rowa, :] += A[rowb, :]
      end
    end
    A    
end

#A = RandInvableMat(50)
#display(A)
#println()
#@time inv(A)

function RandMat(n, a=3)
    v = randn(n)
    ans = v*v'
    for i = 1:n
      ans[i, i] += a
    end
    ans
end


