### PLAS (Practical Linear Algreba Subprograms)
----
* 这个库旨在建立一个供学习使用的基础线性代数库（neta BLAS）
----
结构以及目标：
  * matrix：
    在这个部分中，实现一个基础的矩阵类。
    矩阵类中，应实现稀疏矩阵与稠密矩阵的区分，
    但其接口应相同，以便于后期算法可以对其进行统一的操作。
    * BLAS中矩阵的分类：
      1. GE - GEnearl 稠密矩阵
      2. GB - Genearl Band 带状矩阵
      3. SY - SYmmetric 对称矩阵
      4. SB - Symmetric Packed 对称带状矩阵
      5. SP - Symmetric Packed 压缩存储对称矩阵
      6. HE - HEmmitian Hemmitian矩阵
      7. HB - Hemmitian Band 带状Hemmitian矩阵
      8. TR - TRiangular 三角矩阵
      9. TB - Triangular Band 三带状矩阵
      10 TP - Triangular Packed 压缩存储三角矩阵
    * 矩阵类的操作：
      1. 建立一个矩阵
      2. 得到矩阵的参数
      3. 通过下标访问矩阵的元素
      3. 得到矩阵的类型

