#ifndef POINT2FCONV_H
#define POINT2FCONV_H
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
class adj_point{
public:
float angle;
Point2f dstPt[4];
adj_point(RotatedRect);

private:
cv::Point2f srcPt[4];
};
#endif