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

        cv::imshow("img",wind.show);
        waitKey(60);
        
    }

}