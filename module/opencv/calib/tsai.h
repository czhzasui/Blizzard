//
// Created by czh on 18-10-15.
//

#ifndef OPENGL_PRO_TASI_H
#define OPENGL_PRO_TASI_H

#include "vision/vision.h"
#include <stdio.h>
#include <linux/videodev2.h>

enum cordinate {
    Cord_X=0,
    Cord_Y=1,
    Cord_Z=2
};

typedef struct{
    float r11;
    float r12;
    float r21;
    float r22;
    float r31;
    float r32;
    float t1;
    float t2;
    float t3;
    float s;
    float f;
    float k1;
    float x0;
    float y0;
}cameraPara;

bool isValidNumber(float f);
bool tsaiCalibStep1(std::vector<cv::Point2f> wcPts, std::vector<cv::Point2f> pcPts, cameraPara &para);
float tsaiCalibStep2(std::vector<cv::Point2f> wcPts, std::vector<cv::Point2f> pcPts, cameraPara &para, float alpha, cv::TermCriteria cond);
float iterateImageCenter(std::vector<cv::Point2f> wcPts, std::vector<cv::Point2f> pcPts, cameraPara &para, enum cordinate cord, float *step);
float iterateFactorS(std::vector<cv::Point2f> wcPts, std::vector<cv::Point2f> pcPts, cameraPara &para);

bool calibCamera(unsigned char *imgBuffer, unsigned int pixelformat, int imgWidth, int imgHeight, float contrast, int darkness, std::vector<cv::Point2f> wcPts, int ptscntRow, int ptscntColumn, cameraPara &camPara, unsigned char *outputBuffer);


class Tsai {
public:
    Tsai(){};

    static int init(cv::Mat cb_source, int aqXnum, int aqYnum);

};


#endif //OPENGL_PRO_TASI_H
