#include <gtest/gtest.h>
#include "WindmillDetect.h"
#include <vector>
// Demonstrate some basic assertions.
//TEST(HelloTest, BasicAssertions)
//{
  // Expect two strings not to be equal.
//  EXPECT_STRNE("hello", "world");
  // Expect equality.
//  EXPECT_EQ(7 * 6, 42);
//}
class DetectTest : public ::testing::Test
{
protected:
  

  void SetUp() override
  {
    

  }
};
TEST_F(DetectTest, Basic1)
{
  WindmillDetect wind(false);
  VideoCapture cap("../能量机关.avi");
  Mat img;
  while(1){
    cap>>img;
    if(img.empty()) break;
    std::vector<Point2f> points=wind.process(img);
    //EXPECT_NE(*(points.begin()+1),*points.end());
    EXPECT_EQ(points.size(),4);
    for(auto&point:points){
      EXPECT_NE(point.x,0);
      EXPECT_NE(point.y,0);

    }
    //EXPECT_LT(point,0);
  
  
}
}
TEST_F(DetectTest, Basic2)
{
  WindmillDetect wind(false);
  VideoCapture cap("../装甲板.avi");
  Mat img;
  while(1){
    cap>>img;
    if(img.empty()) break;
    std::vector<Point2f> points=wind.process(img);
    //EXPECT_EQ(points.begin()+1,points.end());
    EXPECT_EQ(points.size(),0);


    }
    //EXPECT_LT(point,0);
  
  
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}