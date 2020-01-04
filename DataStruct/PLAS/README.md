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
      3. SY - SYmmetric 对称矩阵                > 可看作 GE 的子类
      4. SB - Symmetric Band 对称带状矩阵
      5. SP - Symmetric Packed 压缩存储对称矩阵
      6. HE - HEmmitian Hemmitian矩阵           > 可看作 GE 的子类
      7. HB - Hemmitian Band 带状Hemmitian矩阵
      8. TR - TRiangular 三角矩阵               > 可看作 GE 的子类
      9. TB - Triangular Band 三角带状矩阵
      10.  TP - Triangular Packed 压缩存储三角矩阵
      11. SE - SparsE 稀疏矩阵
    * 矩阵类的操作：
      1. 建立一个矩阵
      2. 得到矩阵的参数
      3. 通过下标访问矩阵的元素
      3. 得到矩阵的类型
    * 基础矩阵操作函数：[低层 `API`]
      1. MatCopy : 拷贝一个矩阵（深拷贝）
      2. MatElemTypeTrans : 矩阵元素类型转换
      3. MatTransp : 矩阵转置
      4. MatMultM : 矩阵相乘
      5. MatMultC : 矩阵与元素相乘
      6. MatPlusM ： 矩阵相加
      7. MatPlusC : 矩阵元素相加
      8. MatSubtM : 矩阵相减
      9. MatSubtC : 矩阵减去元素
      10. MatDivC : 矩阵与元素相除
      11. MatInv : 求逆矩阵 // 不适合放在这里
      12. MatDet : 求行列式 // 同上
      ----
      对于不是 GE 类型的矩阵来说， 还有：
      1. MatToGE ： 将矩阵转为 GE 类型
      2. MatFromGE ： 从 GE 类型构造矩阵
