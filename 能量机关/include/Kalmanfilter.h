/**
 * @file Kalmanfilter.h
 * @author 林梓涵 (1625703948@qq.com)
 * @brief 
 * @version 1.0
 * @date 2022-10-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <opencv2/opencv.hpp>

using namespace cv;
class filterKF
{
private:
    int stateNum = 4;
    int measureNum = 2;
    KalmanFilter KF;
    Mat prediction;

public:
    filterKF();
    Mat predict(Point2f point);
    void set_state(Point2f);
};