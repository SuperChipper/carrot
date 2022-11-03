# Googletest单元测试
利用gtest模块有两种方式，依赖于Bazel和CMake两种
这里选用CMake,一来是在工程中比较好管理是否测试，二来是CMake比较熟悉
## gtest中的断言和打印
``` c++
expect_*
assert_*
```
两种基础的断言
## 宏函数Test
利用Test来编写基本的测试单元