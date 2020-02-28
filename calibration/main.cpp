#include <iostream>
#include "cxxopts.hpp"

#include "calibration.hpp"

int main(int argc, char** argv)
{
    cxxopts::Options options(argv[0], "A brief description");

    options.add_options()
        ("s,save", "save captured images", cxxopts::value<bool>()->default_value("false"))
        ("l,load", "load captured images", cxxopts::value<bool>()->default_value("false"))
        ("show", "show found corners", cxxopts::value<bool>()->default_value("false"))
        ("h,help", "Print this message")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
      std::cout << options.help() << std::endl;
      return EXIT_SUCCESS;
    }

    Calibration calibration = Calibration(0.016f, 0, "../imgs", "..imgs2");


    if (result["load"].as<bool>())
    {
        calibration.loadImagesFromDirectory();
    }
    else
    {
        calibration.captureImagesForCalibration();
    }

    calibration.cameraCalibration();


    if (result["save"].as<bool>())
    {
        calibration.saveImagesToDirectory();
    }

    calibration.printResult();

    return 0;
}