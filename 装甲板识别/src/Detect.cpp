/**
 * @file Detect.cpp
 * @author 林梓涵 (1625703948@qq.com)
 * @brief 
 * @version 1.0
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Detect.h"

/**
 *
 * @param frame 传入图像帧
 */
struct rec_size
{
    int width;
    int height;
};
Detect::Detect(Mat frame)
{

    const Mat _struct = getStructuringElement(1, Size(3, 3));
    _image = frame;
    split(_image, RGBchannels);
    split(_image, RGBchannels);
};
Mat Detect::Get()
{
    return _image;
}
/**
 *
 * @return 返回图像的对应颜色通道
 */
Mat Detect::Blue_channel()
{
    return RGBchannels[0];
}
Mat Detect::Red_channel()
{
    return RGBchannels[2];
}
Mat Detect::Green_channel()
{
    return RGBchannels[1];
}
/**
 *
 * @return 返回二值化结果
 */
Mat Detect::Binary_Blue()
{
    threshold(Blue_channel(), Binary, 230, 255, THRESH_BINARY);
    morphologyEx(Binary, erodeBinary, MORPH_CLOSE, _struct, Point(-1, -1), 1);
    return Binary;
}
Mat Detect::Binary_Red()
{
    threshold(Red_channel(), Binary, 125, 255, THRESH_BINARY);
    morphologyEx(Binary, erodeBinary, MORPH_CLOSE, _struct, Point(-1, -1), 2);
    return erodeBinary;
}
Mat Detect::Binary_Green()
{
    threshold(Green_channel(), Binary, 125, 255, THRESH_BINARY);
    return Binary;
}
/**
 * @brief 综合各个通道的颜色来进行二值化
 *
 * @return 返回图像的二值化结果
 */
Mat Detect::Diff()
{
    Mat image = 0.05 * Blue_channel() + 0.6 * Green_channel() + 0.25 * Red_channel();

    threshold(image, Binary, 190, 255, THRESH_BINARY);
    morphologyEx(Binary, erodeBinary, MORPH_DILATE, _struct, Point(-1, -1), 1);
    return erodeBinary;
};
/**
 *
 * @param contourR 传入相似的两个轮廓
 * @param contourB
 * @return 比较后相似的轮廓
 */
vector<vector<Point>> Detect::CompareContour(vector<vector<Point>> contourR, vector<vector<Point>> contourB)
{ //预期返回一个向量包含比较后相似的轮廓
    vector<vector<Point>> contour;
    for (int n = 0; n < contourR.size(); n++)
    {
        Moments mm = moments(contourR[n]);
        Mat hum;
        HuMoments(mm, hum);
        double dist;
        for (int i = 0; i < contourB.size(); i++)
        {
            Moments mm2 = moments(contourB[i]);
            Mat hu2;
            HuMoments(mm2, hu2);
            dist = matchShapes(hum, hu2, CONTOURS_MATCH_I1, 0);
            if (dist < 1)
            {
                // drawContours(img,contourR,n,Scalar(0,0,255),3,8);
                contour.push_back(contourB[i]); //末尾添加轮廓
            }
        }
    }
    return contour;
}
/**
 * @brief 绘制矩形
 *
 * @param rrect 旋转矩形 Rotatedrect
 */
void Detect::Draw_rect(RotatedRect rrect)
{
    Mat img = _image;
    Point2f points[4];
    rrect.points(points);
    Point2f cent = rrect.center;
    for (int i = 0; i < 4; i++)
    {
        if (i == 3)
        {
            line(img, points[i], points[0], Scalar(0, 0, 255), 2, 8, 0);
            break;
        }
        line(img, points[i], points[i + 1], Scalar(0, 0, 255), 2, 8, 0);
    }
    circle(img, cent, 2, Scalar(200, 150, 0), 2, 8, 0);
}
/**
 *
 * @param img 传入图像
 *
 * @brief 图像检测函数封装
 *
 */
void Detector(Mat img)
{
    // namedWindow("img", WINDOW_FREERATIO);
    // namedWindow("bin", WINDOW_FREERATIO);
    Detect image(img); //初始化，传入图像
    Mat bin;
    vector<vector<Point>> contour;
    vector<Vec4i> hierarchy1;
    bin = image.Diff();
    findContours(bin, contour, hierarchy1, RETR_TREE, CHAIN_APPROX_SIMPLE);
    vector<RotatedRect> rrect;
    Rrect rec(contour);
    rec.find(image);
    pnp_sol p(rec, image.Get());

    // cv_bridge::CvImageConstPtr toCvShare(const sensor_msgs::ImageConstPtr& source,
    //                           const std::string& encoding = std::string());
    // imshow("bin", bin);
    imshow("img", image.Get());
}
/**
 *
 * @param type 检测类型，分为video和image
 * @param path 检测的文件的路径
 * @param waitkey 每一帧等待时间毫秒
 *
 * @brief 核心检测函数,根据文件类型调用检测函数
 *
 */
void Detect_target(string type, string path, int waitkey)
{
    Mat img;
    if (type == "video")
    {
        VideoCapture video(path);
        while (1)
        {
            video >> img;
            if (img.empty())
            {
                break;
            }
            Detector(img);
            waitKey(waitkey);
        }
    }
    else if (type == "image")
    {
        img = imread(path);
        if (!img.empty())
        {
            Detector(img);
            waitKey(waitkey);
        }
    }
    else
        cout << "Error, invalid type, please insert \"video\" or \"image\"";
}
/**
 *
 * @param contour 轮廓
 *
 * @brief 根据轮廓寻找最小外接矩形
 */
Rrect::Rrect(vector<vector<Point>> contour)
{
    for (auto &cont : contour)
    {
        Point2f p[4];
        RotatedRect r = minAreaRect(cont);
        rrect.push_back(r);
        /*      r.points(p);
                points.push_back(p);
                for(auto&point:p){
                    cout<<point;
                }
                cout<<endl;
        */
    }
}
/**
 * @brief 因为旋转矩形可能出现宽高搞反的情况，因此编写函数矫正
 * @param rect 旋转矩形
 * @return size 自定义struct，包含width和height，类型为int
 */
rec_size adjust_size(RotatedRect rect)
{

    rec_size size;
    if (rect.size.height > rect.size.width)
    {
        size.width = rect.size.height;
        size.height = rect.size.width;
    }
    else
    {
        size.width = rect.size.width;
        size.height = rect.size.height;
    }
    return size;
}
/**
 * @brief 筛选可能的装甲板并得到装甲板中心点cri
 *
 * @param image 传入Detect类进行筛选
 */
void Rrect::find(Detect image)
{
    for (auto &rec : rrect)
    {
        rec_size size1 = adjust_size(rec);
        // if (((rec.angle > 40) && (rec.angle < 140)) || ((rec.angle > 220) && (rec.angle < 320))) {
        if ((size1.width / size1.height > 1.7) && (size1.width / size1.height < 15))
        {
            for (auto &cri : critical_rect)
            {
                Point2f ptr = cri.center;
                if ((abs(ptr.x - rec.center.x) > 1.8 * size1.width) &&
                    (abs(ptr.x - rec.center.x) < 4.5 * size1.width) &&
                    ((ptr.y - rec.center.y == 0) || (abs(ptr.x - rec.center.x) / abs(ptr.y - rec.center.y) > 3))
                    //&&(abs(cri.angle-rec.angle)<6)
                )
                {
                    rec_size size2 = adjust_size(cri);
                    if ((size1.width > 0.6 * size2.width) && (0.6 * size1.width < size2.width))
                    {
                        line(image.Get(), ptr, rec.center, Scalar(100, 200, 255), 2, 8, 0);
                        ;
                        circle(image.Get(), (rec.center + ptr) / 2, 2, Scalar(255, 20, 255), 2, 8, 0);
                        draw_side(cri, image.Get());
                        draw_side(rec, image.Get());
                        armor.push_back((rec.center + ptr) / 2);
                    }
                }
            }
            critical_rect.push_back(rec);
            rec_points.push_back(rec.center);
            // cout<<rec.size.width<<"\t"<<rec.size.height<<endl;
            // image.Draw_rect(rec);
        }
        //}
    }
}
/**
 * @brief 得到装甲板角点数据并绘制，并且通过装甲板灯条长度的数据得到相对的z坐标并且计算装甲板中心的三维坐标
 *
 * @param rect 传入旋转矩形，进行坐标计算
 * @param image 传入绘制的图像
 */

void Rrect::draw_side(RotatedRect rect, Mat image)
{
    Point2f points[4];
    rect.points(points);
    Point2f point1, point2;
    if (rect.size.height < rect.size.width)
    {
        point1 = 0.5 * (points[0] + points[1]), point2 = 0.5 * (points[2] + points[3]);
    }
    else
    {
        point1 = 0.5 * (points[1] + points[2]), point2 = 0.5 * (points[3] + points[0]);
    }
    circle(image, point1, 2, Scalar(255, 120, 255), 2, 8, 0);
    circle(image, point2, 2, Scalar(255, 120, 255), 2, 8, 0);
    pnp_points.push_back(point1);
    pnp_points.push_back(point2);
    Point3f pp1(0, 0, 0), pp2(0, 0, 0);
    if (ref_x < 0.5 * (point1 + point2).x)
    {
        if (!ref_points.empty())
        {
            ref_points[0].x -= 138;
            ref_points[1].x -= 138;
        }
        pp1.x += 138;
        pp2.x += 138;
    }
    ref_x = 0.5 * (point1 + point2).x;
    if (point1.y > point2.y)
    {
        pp1.y += 46;
    }
    else
    {
        pp2.y += 46;
    }

    // int coef=(point1.y-point2.y)*(point1.y-point2.y)+(point1.x-point2.x)*(point1.x-point2.x);
    // double z=0;
    /*if(!armor.empty()){
        double h=sqrt(pow((point1-point2).x,2)+pow((point1-point2).y,2))/2;
        double w=sqrt(pow(((point1+point2)/2-armor[0]).x,2)+pow(((point1+point2)/2-armor[0]).y,2));
        //double scale=(h/w)*138/52;
        z=(h/w)*138/52;}
    else{
        z=0;
    }*/
    //=0.15*(4000-sqrt(coef));
    // pp1.z=z;
    // pp2.z=z;
    ref_points.push_back(pp1);
    ref_points.push_back(pp2);
    center.x += 0.25 * point1.x + 0.25 * point2.x;
    center.y += 0.25 * point1.y + 0.25 * point2.y;
    center.z = 0;
}
template <typename _tp>
vector<_tp> convertMat2Vec(const Mat &a)
{
    return (vector<_tp>)(a.reshape(1, 1));
}
/**
 * @brief 解算姿态的核心函数
 * @param rec 传入Rrect类来解算相对装甲板位姿
 * @param image 传入原始图像指针来绘制参考坐标轴
 */

pnp_sol::pnp_sol(Rrect rec, Mat image)
{
    reference.push_back({0., 0, 0.});
    reference.push_back({50, 0., 0.});
    reference.push_back({0., 50, 0.});
    reference.push_back({0, 0, 50});
    // rec.ref_points.push_back({138,58,0});
    rvecs = Mat::zeros(3, 1, CV_64FC1);
    tvecs = Mat::zeros(3, 1, CV_64FC1);
    // if((rec.ref_points.size()==4)&&rec.pnp_points.size()==4)
    solvePnP(rec.ref_points, rec.pnp_points, camera_mat, dist_coef, rvecs, tvecs, false, SOLVEPNP_ITERATIVE);
    projectPoints(reference, rvecs, tvecs, camera_mat, dist_coef, img_points);
    line(image, img_points[0], img_points[1], Scalar(0, 0, 255));
    line(image, img_points[0], img_points[2], Scalar(0, 255, 0));
    line(image, img_points[0], img_points[3], Scalar(255, 0, 0));
    // cout<<img_points[0]<<"\t"<<((Get_rotate().t())*tvecs).row(2)<<endl;
    // double out=((Get_rotate().t())*tvecs);
    //((Get_rotate().t())*tvecs).col();
    double font_sz=1.5;
    Mat a = 0.001 * ((Get_rotate().t()) * tvecs).row(2);
    // string prt = "";
    string prt0= "distance:",prt1="";
    vector<double> angles(to_angle(Get_rotate()));
    for (double &temp : convertMat2Vec<double>(a))
    {
        prt1 += to_string(temp)+" m";
    }
    vector<string> prt;
    prt.push_back("alpha:" + to_string(angles[0]));
    prt.push_back("beta:" + to_string(angles[1]));
    prt.push_back("gamma:" + to_string(angles[2]));
    // cout<<prt<<endl;
    int baseline;
    
    Size sz = getTextSize(prt1, FONT_HERSHEY_PLAIN, font_sz, 1, &baseline);
    Point2f p = img_points[0];
    cv::putText(image, prt1, img_points[0], FONT_HERSHEY_PLAIN, font_sz, Scalar(255, 255, 255));
    p.y-=1.2*sz.height;
    cv::putText(image, prt0, p, FONT_HERSHEY_PLAIN, font_sz, Scalar(255, 255, 255));
    for (auto &pt : prt)
    {
        p.y-=1.2*sz.height;
        putText(image, pt, p, FONT_HERSHEY_PLAIN, font_sz, Scalar(255, 255, 255));
    }
    p.y-=1.2*sz.height;
    putText(image, "Eular angle:", p, FONT_HERSHEY_PLAIN, font_sz, Scalar(255, 255, 255));
}
/**
 * @brief 将旋转向量转换成旋转矩阵
 * @return rotMat旋转矩阵
 */
Mat pnp_sol::Get_rotate()
{
    Mat rotMat;
    Rodrigues(rvecs, rotMat);
    return rotMat;
};

vector<double> to_angle(Mat rotM)
{
    vector<double> result;
    double theta_x, theta_y, theta_z;
    //根据旋转矩阵求出坐标旋转角
    theta_x = atan2(rotM.at<double>(2, 1), rotM.at<double>(2, 2));
    theta_y = atan2(-rotM.at<double>(2, 0),
                    sqrt(rotM.at<double>(2, 1) * rotM.at<double>(2, 1) + rotM.at<double>(2, 2) * rotM.at<double>(2, 2)));
    theta_z = atan2(rotM.at<double>(1, 0), rotM.at<double>(0, 0));

    //将弧度转化为角度
    theta_x = theta_x * (180 / M_PI);
    theta_y = theta_y * (180 / M_PI);
    theta_z = theta_z * (180 / M_PI);
    result.push_back(theta_x);
    result.push_back(theta_y);
    result.push_back(theta_z);
    return result;
}
