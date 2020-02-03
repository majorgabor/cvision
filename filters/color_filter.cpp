#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

int h_min;
int v_min;
int s_min;
int MAX_VALUE_HVS = 255;
int h_max = MAX_VALUE_HVS;
int v_max = MAX_VALUE_HVS;
int s_max = MAX_VALUE_HVS;

void setLowerBound(int pos, void *lower_bound)
{
    cv::Scalar *lb = static_cast<cv::Scalar*>(lower_bound);
    *lb = cv::Scalar(h_min, v_min, s_min);
}

void setUpperBound(int pos, void* upper_bound)
{
    cv::Scalar *ub = static_cast<cv::Scalar*>(upper_bound);
    *ub = cv::Scalar(h_max, v_max, s_max);
}

int main(int argc, char** argv)
{
    cv::VideoCapture camera(0);
    if (!camera.isOpened() )
    {
        std::cerr << "could not open camera" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Scalar lower_bound = cv::Scalar(h_min, v_min, s_min);
    cv::Scalar upper_bound = cv::Scalar(h_max, v_max, s_max);

    cv::namedWindow("HVS settings", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("h_lower:", "HVS settings", &h_min, MAX_VALUE_HVS, setLowerBound, &lower_bound);
    cv::createTrackbar("v_lower:", "HVS settings", &v_min, MAX_VALUE_HVS, setLowerBound, &lower_bound);
    cv::createTrackbar("s_lower:", "HVS settings", &s_min, MAX_VALUE_HVS, setLowerBound, &lower_bound);
    cv::createTrackbar("h_upper:", "HVS settings", &h_max, MAX_VALUE_HVS, setUpperBound, &upper_bound);
    cv::createTrackbar("v_upper:", "HVS settings", &v_max, MAX_VALUE_HVS, setUpperBound, &upper_bound);
    cv::createTrackbar("s_upper:", "HVS settings", &s_max, MAX_VALUE_HVS, setUpperBound, &upper_bound);


    cv::Mat frame, hvs, mask, result;
    cv::namedWindow("video camera", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("mask", cv::WINDOW_AUTOSIZE);

    int k = 0;
    while (k != 27)
    {
        camera >> frame;

        cv::cvtColor(frame, hvs, cv::COLOR_BGR2HSV);
        cv::inRange(hvs, lower_bound, upper_bound, mask);
        result = cv::Mat(frame.rows, frame.cols, CV_64F, double(0));
        cv::bitwise_and(frame, frame, result, mask);

        cv::imshow("video camera", frame);
        cv::imshow("mask", mask);
        cv::imshow("result", result);
        
        k = cv::waitKey(10);
    }
    return 0;
}