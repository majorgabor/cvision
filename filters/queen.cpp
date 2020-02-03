#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

int b;
int g = 255;
int r = 127;
const int MAX_VALUE = 255;
const int ROWS = 619;
const int COLS = 1091;
cv::Scalar color;
cv::Mat inv_masked_original_img, background, mask, final_result;

void changeColor(int, void*);


int main(int argc, char** argv)
{
    cv::Mat original_img = cv::imread("../queen.jpg");
    if (original_img.empty())
    {
        std::cerr << "failed to open image" << std::endl;
        return EXIT_FAILURE;
    }
    
    cv::namedWindow("result", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("blue: ", "result", &b, MAX_VALUE, changeColor);
    cv::createTrackbar("green:", "result", &g, MAX_VALUE, changeColor);
    cv::createTrackbar("red:   ","result", &r, MAX_VALUE, changeColor);

    cv::Mat hsv_img;
    cv::cvtColor(original_img, hsv_img, cv::COLOR_BGR2HSV);
    cv::inRange(hsv_img, cv::Scalar(46, 147, 20), cv::Scalar(62, 255, 255), mask);
    cv::Mat inverse_mask = MAX_VALUE - mask;
    cv::bitwise_and(original_img, original_img, inv_masked_original_img, inverse_mask);
    background = cv::Mat(ROWS, COLS, CV_8UC3, color);    
    cv::cvtColor(background, background, cv::COLOR_HSV2BGR);
    cv::bitwise_xor(inv_masked_original_img, background, final_result);

    cv::imshow("result", final_result);
    cv::waitKey(0);
    
    return 0;
}

void changeColor(int, void*)
{
    color = cv::Scalar(b, g, r, 1);
    background = cv::Mat(619, 1091, CV_8UC3, color);
    cv::cvtColor(background, background, cv::COLOR_HSV2BGR);
    cv::bitwise_xor(inv_masked_original_img, background, final_result, mask);
    cv::imshow("result", final_result);
}