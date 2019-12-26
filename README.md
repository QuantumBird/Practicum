# Practicum
---
DataStruct:
  BUG: 
    模板函数
    ```
      template<class MType>
      std::string getElemTypeStr(MType mat)
    ```
    在运行时没有得到预期结果，运行测试时发生core dump
  in ./DataStruct/PLAS/matrix/ 
    extratype.hpp: line 
    test_for_extratype.cpp: line 10 ~ 11
  复现：
    1. 进入 ./matrix
    2. make testET

