/**
 *
 * @file main.cpp
 * @author 林梓涵
 * @version 1.0
 * @date 2022.7.14
 */
#include "Detect.h"
#include <vector>
using namespace std;
using namespace cv;
int main(int argc, char *argv[]) {
    //Detect_target("image","../.png",0);
    Detect_target("video","../装甲板.avi",40);
    destroyAllWindows();
    return 0;
}