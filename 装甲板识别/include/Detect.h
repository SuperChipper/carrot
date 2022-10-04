//
// Created by zihan on 22-7-9.
//
/**
 *
 * @file Detect.h
 * @author 林梓涵
 * @version 1.0
 * @date 2022.7.14
 */
#ifndef DETECT_H
#define DETECT_H
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <cmath>

//#include <opencv2/highgui.hpp>
//#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;
class Detect{
private:
    Mat RGBchannels[3];
    //储存三个颜色通道
    Mat Binary;
    //用于返回二值化结果
    Mat _struct;
    //形态学操作算子
    Mat erodeBinary;
    //形态学操作结果
    Mat _image;
    //储存图像结果
public:
    Detect(Mat frame);
    Mat Get();
    //返回图像结果
    Mat Blue_channel();//返回相应颜色通道
    Mat Red_channel();
    Mat Green_channel();
    Mat Binary_Blue();//返回相应颜色通道二值化的结果
    Mat Binary_Red();
    Mat Binary_Green();
    Mat Diff();
    //将三个通道颜色结合比较再二值化
    vector<vector<Point>> CompareContour(vector<vector<Point>>,vector<vector<Point>>);
    //轮廓矩比较（弃用）
    void Draw_rect(RotatedRect);//绘制矩形
};


class Rrect{
private:
    vector<RotatedRect> rrect;
    //最小外接矩形的集合
    vector<Point2f> rec_points;
    //疑似为装甲板轮廓的外接矩形的中心点
    vector<RotatedRect> critical_rect;
    //疑似为装甲板轮廓的外接矩形
    vector<Point2f> armor;
    //装甲板中心点
    double ref_x=0;
    //判断坐标顺序用

public:
    vector<Point2f> pnp_points;
    //储存解算角点的集合
    vector<Point3f> ref_points;
    //转换到三维
    Rrect(vector<vector<Point>> contour);
    //寻找最小外接矩形
    void find(Detect);
    //在矩形中找到装甲板并绘制
    void draw_side(RotatedRect,Mat);
    //绘制矩形角点
    Point3f center;
    //储存二维转化为三维的点

};
struct rec_size;

rec_size adjust_size(RotatedRect);

void Detector(Mat);//检测图像

void Detect_target(string,string,int);//根据文件类型调用检测函数

class pnp_sol{
private:
    Mat camera_mat=( Mat_<double> ( 3,3 )<< 1.2853517927598091e+03, 0., 3.1944768628958542e+02, 0.,
                              1.2792339468697937e+03, 2.3929354061292258e+02, 0., 0., 1.);
    Mat_<double> dist_coef= ( Mat_<double> ( 5,1)<<-6.3687295852461456e-01, -1.9748008790347320e+00,
                            3.0970703651800782e-02, 2.1944646842516919e-03, 0.);
    //相机内参

    vector<Point3f> reference;
    //参考系坐标轴
    Mat rvecs;
    //旋转向量
    Mat tvecs;
    //平移向量
    vector<Point2f> img_points;
    //储存三维到二维的映射坐标轴
public:
pnp_sol(Rrect,Mat);
//解算相机位姿并在图像绘制坐标
Mat Get_rotate();
//由旋转向量转化为旋转矩阵
};
#endif DETECT_H
