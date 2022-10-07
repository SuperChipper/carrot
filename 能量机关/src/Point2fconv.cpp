#include "Point2fconv.h"

adj_point::adj_point(cv::RotatedRect rrect)
{
    int height = rrect.size.height;
    int width = rrect.size.width;

    cv::Mat straighten_rect;

    Point2f dstPt[4];
    rrect.points(srcPt);

    if (rrect.size.width > rrect.size.height)
    {
        straighten_rect = cv::Mat(height, width, CV_8UC1); // rows, cols
        dstPt[0] = Point2f(0, height - 1);                 // -> bottom left of dst rect
        dstPt[1] = Point2f(0, 0);                          // -> top left of dst rect
        dstPt[2] = Point2f(width - 1, 0);                  // -> top right of dst rect
        dstPt[3] = Point2f(width - 1, height - 1);         // -> bottom right of dst rect
    }
    else
    {
        straighten_rect = cv::Mat(width, height, CV_8UC1);
        dstPt[0] = Point2f(0, 0);                  // -> top left of dst rect
        dstPt[1] = Point2f(height - 1, 0);         // -> top right of dst rect
        dstPt[2] = Point2f(height - 1, width - 1); // -> bottom right of dst rect
        dstPt[3] = Point2f(0, width - 1);          // -> bottom left of dst rect
    }

    cv::Mat M = cv::getPerspectiveTransform(srcPt, dstPt);
    //cv::warpPerspective(img, straighten_rect, M, straighten_rect.size());
    cv::imshow("straighten", straighten_rect);
    }