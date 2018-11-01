//
// Created by czh on 18-10-31.
//

#ifndef BLIZZARD_CHECKERBOARD_H
#define BLIZZARD_CHECKERBOARD_H

#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

class Checkerborad {
public:
    static cv::Mat makeCheckerboard(int bkgWidth, int bkgHeight, int sqXnum, int sqYnum = 0, int borderThickness = 0,
                                    char *savePath = NULL);
};


#endif //BLIZZARD_CHECKERBOARD_H
