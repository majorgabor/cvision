#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "not enought parameter" << std::endl;
        std::cout << "usage: " << argv[0] << " <path/to/image.format>" << std::endl;
        return 1;
    }
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Error opening image" << std::endl;
        return EXIT_FAILURE;
    }
    cv::resize(img, img, img.size()/2);
    cv::namedWindow("original image", cv::WINDOW_AUTOSIZE);
    cv::imshow("original image", img);

    // cv::Mat gray_img;
    // cv::cvtColor(img, gray_img, cv::COLOR_RGB2GRAY);

    // cv::namedWindow("gray image", cv::WINDOW_AUTOSIZE);
    // cv::imshow("gray image", gray_img);

    cv::Mat salt_pepper_noise = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);
    cv::randu(salt_pepper_noise, 0, 255);

    cv::Mat black = salt_pepper_noise < 15;
    cv::Mat white = salt_pepper_noise > 240;

    cv::Mat salt_pepper_img = img.clone();
    salt_pepper_img.setTo(255, white);
    salt_pepper_img.setTo(0, black);

    cv::namedWindow("noisy img", cv::WINDOW_AUTOSIZE);
    cv::imshow("noisy img", salt_pepper_img);

    cv::Mat filtered_img;
    cv::medianBlur(salt_pepper_img, filtered_img, 3);
    cv::namedWindow("filtered img", cv::WINDOW_AUTOSIZE);
    cv::imshow("filtered img", filtered_img);
    
    cv::medianBlur(filtered_img, filtered_img, 3);
    cv::namedWindow("filtered img round 2", cv::WINDOW_AUTOSIZE);
    cv::imshow("filtered img round 2", filtered_img);

    cv::medianBlur(salt_pepper_img, filtered_img, 5);
    cv::namedWindow("filtered img kernel 5", cv::WINDOW_AUTOSIZE);
    cv::imshow("filtered img kernel 5", filtered_img);

    cv::waitKey(0);
    return 0;
}