#include("LU.jl")
include("LUinv.jl")
include("RandInvableMat.jl")
include("invSVD.jl")
#A = RandMat(50)

#@time inv(A)
#@time LU(A)
#=
for dim ∈ [50, 100, 1000, 2000]
  println("dim of matrix:", dim)
  A = RandMat(dim)
  println("inv:")
  @time inv(A)
  @time LU(A)
  println("----------------------------")
end
=#
test_use = true

if test_use
  A = RandMat(5)
  println("Rand Gene Matrix: (dim = 5)")
  display(A)
  println("Lapack inv res:")
  display(inv(A))
  println("Lapack inv mul : (A * A^-1)")
  display(inv(A)*A)
  println("LU inv res:")
  display(invLU(A))
  println("LU inv mul : (A * A^-1)")
  display(invLU(A)*A)
end 

for dim ∈ [50, 100, 500, 1000, 2000]
  println("Matrix dim: $(dim)x$(dim)")
  A = RandMat(dim)
  println("Lapack inv: ")
  @time inv(A)
  println("My LU inv: ")
  @time invLU(A)
  println("SVD inv:")
  @time invSVD(A)
  println("-"^70)
end



