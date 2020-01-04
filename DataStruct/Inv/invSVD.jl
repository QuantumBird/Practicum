using LinearAlgebra

function invSVD(A)
  U, S, V = svd(A)
  nS, = size(S)
  pS = zeros(nS, nS)
  for i = 1:nS
    pS[i, i] = 1 / S[i]
  end
  V*pS*U'
end