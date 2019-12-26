### 在设计时遇到的困难与解决方法
----
1. 在设计较高层次API时遇到代码重复的问题

    在进行`Mat`这个类时，由于它是地层不同矩阵类的包装，要根据不同类调用不同方法。在设计之初，我借鉴了`Python` 中的“鸭子类型”(duck type)的概念，虽然后面证明这是一个较为正确的选择，但如何简单的实现是一个问题。

    起初我使用`switch`语句完成不同类型的选择工作，但写出来的代码重复性高，极为丑陋。此时`Mat`定义如下。

    ```
    template<typename T, class MType>
    class Mat {...}
    ```
    但使用一些模板的trick，修改底部的矩阵类型的定义，其中加入：
    ```
    typedef const T ElemType;
    ```
    `Mat`的定义即可修改为：
    ```
    template<class MType>
    class Mat
    ```
    此时，在`Mat`中，我们可以直接使用
    ```
    typedef typename MType::ElemType ElemType;
    ```
    将被包装的矩阵的元素类型提取出来。