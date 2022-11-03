# Googletest单元测试
利用gtest模块有两种方式，依赖于Bazel和CMake两种
这里选用CMake,一来是在工程中比较好管理是否测试，二来是CMake比较熟悉
## gtest中的断言和打印
``` c++
expect_*
assert_*
```
两种基础的断言
## 宏函数TEST
利用Test来编写基本的测试单元
## F_TEST
编写类来对函数进行一些预先的操作
官方文档中的示例
```c++
template <typename E>  // E is the element type.
class Queue {
 public:
  Queue();
  void Enqueue(const E& element);
  E* Dequeue();  // Returns NULL if the queue is empty.
  size_t size() const;
  ...
};
```
对于示例中的QueueTest，类在TEST_F的声明中被预先调用，对测试进行一些先决的操作，提供测试环境等等（个人理解）
```c++
class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
     q1_.Enqueue(1);
     q2_.Enqueue(2);
     q2_.Enqueue(3);
  }

  // void TearDown() override {}

  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;
};
```
然后是TEST_F的调用示例（这样的好处是每次测试不用重新再把测试条件写一遍吧）
```c++
TEST_F(QueueTest, IsEmptyInitially) {
  EXPECT_EQ(q0_.size(), 0);
}

TEST_F(QueueTest, DequeueWorks) {
  int* n = q0_.Dequeue();
  EXPECT_EQ(n, nullptr);

  n = q1_.Dequeue();
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(*n, 1);
  EXPECT_EQ(q1_.size(), 0);
  delete n;

  n = q2_.Dequeue();
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(*n, 2);
  EXPECT_EQ(q2_.size(), 1);
  delete n;
}
```
## 测试设计：针对自己代码库中的WindmillDe.h
将“能量机关.avi”和“装甲板.avi”放在gtest目录下

 |利用已有的能量机关视频| 利用装甲板视频|
 |---|---|
 |确保返回的四边形点坐标不为0且数目正确|确保装甲板不会被当成符文机关识别|