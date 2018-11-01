//
// Created by czh on 18-10-31.
//

#ifndef OPENGL_PRO_CALIB_H
#define v

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

class Checkerborad {
public:
    static cv::Mat makeCheckerboard(int bkgWidth, int bkgHeight, int sqXnum, int sqYnum = 0, int borderThickness = 0,
                                    char *savePath = NULL);
};


#endif //OPENGL_PRO_CALIB_H
