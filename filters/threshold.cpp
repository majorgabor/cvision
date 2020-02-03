#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

int main(int argc, char **argv)
{
    cv::Mat img = cv::imread("../bookpage.jpg");
    if (img.empty())
    {
        std::cout << "Error opening image" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat img_gray;
    cv::cvtColor(img, img_gray, cv::COLOR_RGB2GRAY);

    cv::Mat threshold;
    cv::Mat threshold_gray;
    cv::Mat threshold_adaptive;
    cv::threshold(img, threshold, 12, 255, cv::THRESH_BINARY);
    cv::threshold(img_gray, threshold_gray, 12, 255, cv::THRESH_BINARY);
    cv::adaptiveThreshold(img_gray, threshold_adaptive, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 115, 1);


    cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
    cv::imshow("original", img);
    cv::namedWindow("threshold", cv::WINDOW_AUTOSIZE);
    cv::imshow("threshold", threshold);
    cv::namedWindow("threshold gray", cv::WINDOW_AUTOSIZE);
    cv::imshow("threshold gray", threshold_gray);
    cv::namedWindow("threshold adaptive gray", cv::WINDOW_AUTOSIZE);
    cv::imshow("threshold adaptive gray", threshold_adaptive);
    
    cv::waitKey(0);
    return 0;
}