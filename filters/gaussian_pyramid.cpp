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

    cv::Mat down_scaled;
    img.copyTo(down_scaled);
    for (int i = 1; i < 4; ++i)
    {
        char c = i+'0';
        cv::Mat gaussian_filtered;
        cv::GaussianBlur(down_scaled, gaussian_filtered, cv::Size(7,7), 0, 0);
        cv::Mat laplacian = down_scaled - gaussian_filtered;
        cv::pyrDown(gaussian_filtered, down_scaled, cv::Size(gaussian_filtered.cols*3/4, gaussian_filtered.rows*3/4));

        char laplacian_n[12] = {"laplacian "};
        laplacian_n[10] = c;
        cv::namedWindow(laplacian_n, cv::WINDOW_AUTOSIZE);
        cv::imshow(laplacian_n, laplacian);
        char pyramid_step_n[15] = {"pyramid step "};
        pyramid_step_n[13] = c;
        cv::namedWindow(pyramid_step_n, cv::WINDOW_AUTOSIZE);
        cv::imshow(pyramid_step_n, down_scaled);
    }

    cv::waitKey(0);
    return 0;
}