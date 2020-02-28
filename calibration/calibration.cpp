#include <iostream>

#include "calibration.hpp"

void Calibration::_createKnownBoardPoints(vector<Point3f> &corners)
{
    for (int i = 0; i < this->boardSize.height; i++)
    {
        for (int j = 0; j < this->boardSize.width; j++)
        {
            corners.push_back(Point3f(j * this->squaredEdgeLength, i * this->squaredEdgeLength, 0.0f));
        }
    }
}

void Calibration::_getChessboardCorners(vector<vector<Point2f>> &foundCorners, bool show)
{
    for (vector<Mat>::iterator it = this->imagesContainer.begin(); it != this->imagesContainer.end(); it++)
    {
        vector<Point2f> cornerBuffer;
        bool found = findChessboardCorners(*it, Size(6,9), cornerBuffer, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

        if (found)
        {
            foundCorners.push_back(cornerBuffer);
            
            if (show)
            {
                drawChessboardCorners(*it, this->boardSize, cornerBuffer, found);
                imshow("found corners", *it);
                waitKey(0);
            }
        }
    }
}

void Calibration::cameraCalibration(bool show)
{
    vector<vector<Point2f>> chessboardSpacePoints;
    _getChessboardCorners(chessboardSpacePoints, show);

    vector<vector<Point3f>> wordSpaceCornerPoints(1);
    _createKnownBoardPoints(wordSpaceCornerPoints[0]);
    wordSpaceCornerPoints.resize(chessboardSpacePoints.size(), wordSpaceCornerPoints[0]);

    vector<Mat> rVectors, tVectors;
    this->distortionCoefficients = Mat::zeros(8, 1, CV_64F);

    cout << "Calibration started." << endl;
    calibrateCamera(wordSpaceCornerPoints, chessboardSpacePoints, this->boardSize, this->cameraMatrix, this->distortionCoefficients, rVectors, tVectors);
    cout << "Calibration finished." << endl;
}

void Calibration::captureImagesForCalibration()
{
    cout << "Opening camera for image capture" << endl;

    VideoCapture camera(this->cameraId);
    Mat frame;

    if (!camera.isOpened())
    {
        cerr << "Camera id: " << this->cameraId << " can NOT be opened.\nEXIT FAILURE" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "usage:\nto capture image press SPACE\nto start calibrating press ENTER\nto terminate press ESC" << endl;
    for (;;)
    {
        camera >> frame;
        imshow("webcam", frame);

        int k = waitKey(1000/24);
        switch (k)
        {
        case 13: // enter
            return; // continue the execution

        case 27: // ESC
            exit(EXIT_SUCCESS);

        case 32: // space
            Mat buffer;
            frame.copyTo(buffer);
            this->imagesContainer.push_back(buffer); // capture image
            cout << "image captured (n." << this->imagesContainer.size() << ")" << endl;
        }
    }
}

void Calibration::saveImagesToDirectory()
{
    cout << "Saving images to \"" << this->savePath << "\"\nPlease wait..." << endl;

    int counter = 1;
    for (vector<Mat>::iterator it = this->imagesContainer.begin(); it != this->imagesContainer.end(); it++)
    {
        string filename = this->savePath + to_string(counter) + ".jpg";
        imwrite(filename, *it);
        counter++;
    }

    cout << "Saved " << counter-1 << " images." << endl;
}

void Calibration::loadImagesFromDirectory()
{
    cout << "Loading images from \"" << this->loadPath << "\"\nPlease wait..." << endl;
    
    for (const auto & entry : experimental::filesystem::directory_iterator(this->loadPath))
    {
        Mat buffer = imread(entry.path(), IMREAD_UNCHANGED);
        this->imagesContainer.push_back(buffer);
    }
    
    cout << "Loaded " << this->imagesContainer.size() << " images." << endl;
}

Mat Calibration::getCameraMatrix() const
{
    return this->cameraMatrix;
}

Mat Calibration::getDistortionCoefficients() const
{
    return this->distortionCoefficients;
}

void Calibration::printResult() const
{
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++\nResults:" 
        << "\nCamera Matrix:"
        << "\n\tvertical focal length\t\t" << this->cameraMatrix.at<double>(0,0)
        << "\n\thorizontal focal lenght\t\t" << this->cameraMatrix.at<double>(1,1)
        << "\n\tvertival principal point\t" << this->cameraMatrix.at<double>(0,2)
        << "\n\thorizontal principal point\t" << this->cameraMatrix.at<double>(1,2) 
        << "\nDistortion Matrix:" 
        << "\n\tradial distortion coefficients: "
        << "\n\tK1: " << this->distortionCoefficients.at<double>(0)
        << "\tK2: " << this->distortionCoefficients.at<double>(1)
        << "\tK3: " << this->distortionCoefficients.at<double>(4)
        << "\n\ttangential distortion coefficients: "
        << "\n\tP1: " << this->distortionCoefficients.at<double>(2)
        << "\tP2: " << this->distortionCoefficients.at<double>(3)
        << endl;
}