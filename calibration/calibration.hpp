#ifndef CALIBRATION_H
#define CALIBRATION_H

// #include <iosfwd>
#include <vector>
#include <experimental/filesystem>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"

using namespace std;
using namespace cv;

class Calibration
{
    int cameraId;
    float squaredEdgeLength;
    string loadPath;
    string savePath;
    Size boardSize = Size(6,9);
    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
    Mat distortionCoefficients;
    vector<Mat> imagesContainer;
    vector<vector<Point2f>> foundCorners;

    void _createKnownBoardPoints(vector<Point3f> &corners);
    void _getChessboardCorners(vector<vector<Point2f>> &foundCorners, bool show);

public:
    Calibration(float edgeLength, int camId, string loadPath, string savePath) : squaredEdgeLength(edgeLength), cameraId(camId), loadPath(loadPath), savePath(savePath) {};

    void cameraCalibration(bool show = false);
    void captureImagesForCalibration();
    void saveImagesToDirectory();
    void loadImagesFromDirectory();
    Mat getCameraMatrix() const;
    Mat getDistortionCoefficients() const;
    void printResult() const;
};

#endif