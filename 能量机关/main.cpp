
#include "WindmillDetect.h"
using namespace std;
using namespace cv;
int main(int argc,char const *argv[]){
    WindmillDetect wind(true);
    VideoCapture cap("../能量机关.avi");
    Mat img;
    while(1){
        cap>>img;
        if(img.empty())
            break;

        vector<cv::Point2f> points=wind.process(img);
        //cout<<points;
        //for(Point2f &point:points.begin();points.end()){
        //    wind.drawTetragon(img, point, Scalar(0, 255, 255));
        //}
        cv::imshow("img",wind.show);
        waitKey(20);
        
    }

}