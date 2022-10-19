/**
 * @file Kalmanfilter.cpp
 * @author 林梓涵 (1625703948@qq.com)
 * @brief 
 * @version 1.0
 * @date 2022-10-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Kalmanfilter.h"
filterKF::filterKF()
{
    KalmanFilter f(stateNum, measureNum, 0);
    KF = f;
    KF.transitionMatrix = (Mat_<float>(stateNum, stateNum) << 1, 0, 1, 0, // A 状态转移矩阵
                           0, 1, 0, 1,
                           0, 0, 1, 0,
                           0, 0, 0, 1);
    //这里没有设置控制矩阵B，默认为零
    setIdentity(KF.measurementMatrix);                      // H=[1,0,0,0;0,1,0,0] 测量矩阵
    setIdentity(KF.processNoiseCov, Scalar::all(1e-5));     // Q高斯白噪声，单位阵
    setIdentity(KF.measurementNoiseCov, Scalar::all(8e-2)); // R高斯白噪声，单位阵
    setIdentity(KF.errorCovPost, Scalar::all(1));           // P后验误差估计协方差矩阵，初始化为单位阵
    randn(KF.statePost, Scalar::all(0), Scalar::all(0.1));  //初始化状态为随机值
    //std::cout<<KF.statePost;
}
Mat filterKF::predict(Point2f point)
{
    Mat measurement = Mat::zeros(measureNum, 1, CV_32F);
    measurement.at<float>(0) = (float)point.x;
    measurement.at<float>(1) = (float)point.y;
    prediction = KF.predict();
    Mat newpred=KF.correct(measurement);
    return newpred;
}
void filterKF::set_state(Point2f state){
    Mat statePost = Mat::ones(stateNum, 1, CV_32F);
    statePost.at<float>(0) = (float)state.x;
    statePost.at<float>(1) = (float)state.y;
    KF.statePost=statePost;
}