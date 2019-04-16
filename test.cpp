#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Compile with g++ code.cpp -lopencv_core -lopencv_highgui -lopencv_imgproc

int main()
{
    cv::Mat src = cv::imread("bottles.ppm", 1);
    cv::Mat dst;

    cv::Point2f pc(src.cols/2., src.rows/2.);
    cv::Mat r = cv::getRotationMatrix2D(pc, 1, 1.0);

    cv::warpAffine(src, dst, r, src.size()); // what size I should use?

    cv::imshow("pic",dst);
    cv::imwrite("rotated_im.ppm", dst);
    cv::waitKey(0);
    return 0;
}