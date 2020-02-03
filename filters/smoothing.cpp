#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

int kernel_size = 1;
const int MAX_KERNEL_LENGTH = 50;
cv::Mat img; 
cv::Mat fil_img;
const char fil_window_name[] = "filtered image";
const char diff_window_name[] = "difference";
int name_pos = 0;
const char *filter_name[] = {"Blur", "Gaussianblur", "Medianblur", "Bilinear"};

void (*fptr)(){};
void _blur();
void _gaussianBlur();
void _medianBlur();
void _bilateralFilter();

void kernelCantBeZero();
void updateKernelSize(int, void*);

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        std::cout << "not enought parameter" << std::endl;
        std::cout << "usage: " << argv[0] << " <path/to/image.format>" << std::endl;
        return 1;
    }
    img = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (img.empty())
    {
        std::cout << "Error opening image" << std::endl;
        return EXIT_FAILURE;
    }
    cv::resize(img, img, img.size()/2);
    cv::namedWindow("original image", cv::WINDOW_AUTOSIZE);
    cv::imshow("original image", img);

    cv::namedWindow(fil_window_name, cv::WINDOW_AUTOSIZE);
    cv::namedWindow(diff_window_name, cv::WINDOW_AUTOSIZE);
    const char* kernel_label = "kernel size:";
    cv::createTrackbar(kernel_label, fil_window_name, &kernel_size, MAX_KERNEL_LENGTH, updateKernelSize);

    fptr = _blur;
    updateKernelSize(1, 0);

    int k = 0;
    while (k != 27 && k != -1)
    {
        k = cv::waitKey(0);
        switch (k)
        {
        case 49: // press key 1
            fptr = _blur;
            name_pos = 0;
            break;
        case 50: // press key 2
            fptr = _gaussianBlur;
            name_pos = 1;
            break;
        case 51: // press key 3
            fptr = _medianBlur;
            name_pos = 2;
            break;
        case 52: // press key 4
            fptr = _bilateralFilter;
            name_pos = 3;
            break;
        default:
            break;
        }
        updateKernelSize(kernel_size, 0);;
    }

    return 0;
}

void updateKernelSize(int, void*)
{
    if (kernel_size == 0) 
    {
        kernelCantBeZero();
    } 
    else 
    {
        fptr();
        cv::imshow(diff_window_name, img-fil_img);
        cv::putText(
            fil_img,
            filter_name[name_pos],
            cv::Point(30, 30),
            cv::FONT_HERSHEY_COMPLEX,
            1,
            cv::Scalar(255, 0, 255) //blue, green, red
        );
        cv::imshow(fil_window_name, fil_img);
    }
}

void _blur()
{
    cv::blur(img, fil_img, cv::Size(kernel_size, kernel_size), cv::Point(-1,-1));
}

void _gaussianBlur()
{
    if (kernel_size % 2 != 1) kernel_size += 1;
    cv::GaussianBlur(img, fil_img, cv::Size(kernel_size, kernel_size), 0, 0);
}

void _medianBlur()
{
    if (kernel_size % 2 != 1) kernel_size += 1;
    cv::medianBlur(img, fil_img, kernel_size);
}

void _bilateralFilter()
{
    if (kernel_size % 2 != 1) kernel_size += 1;
    bilateralFilter(img, fil_img, kernel_size, kernel_size*2, kernel_size/2);
}

void kernelCantBeZero()
{
    fil_img = cv::Mat::zeros( img.size(), img.type());
    cv::putText(
        fil_img,
        "Kernel size can't be 0",
        cv::Point( fil_img.cols/4, fil_img.rows/2),
        cv::FONT_HERSHEY_COMPLEX,
        1,
        cv::Scalar(0, 0, 255) //blue, green, red
    );
    cv::imshow(fil_window_name, fil_img);
}