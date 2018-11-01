//
// Created by czh on 18-10-31.
//

#ifndef OPENGL_PRO_CV_RW_H
#define OPENGL_PRO_CV_RW_H

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

class Vision {
public:
    static void dispConfig(cv::Mat img);

    static cv::Mat read(std::string file_path, int flags = cv::IMREAD_ANYCOLOR | cv::IMREAD_ANYDEPTH);

    static cv::Mat write(std::string file_path, int flags = cv::IMREAD_ANYCOLOR | cv::IMREAD_ANYDEPTH);
};


#endif //OPENGL_PRO_CV_RW_H
