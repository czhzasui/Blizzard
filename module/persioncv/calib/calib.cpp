//
// Created by czh on 18-10-31.
//

#include "calib.h"

cv::Mat Vision::makeCheckerboard(int bkgWidth, int bkgHeight, int sqXnum, int sqYnum, int thickNum, char *savePath) {
    if(sqYnum == 0){
        sqYnum = sqXnum;
    }
    if(savePath == NULL){
        char *defaultPath = (char *)"../res/calibration/maths.png";
        savePath = defaultPath;
    }
    int checkboardX = 0;//棋盘x坐标
    int checkboardY = 0;//棋盘y坐标
    int xLen = bkgWidth / sqXnum;//x方格长度
    int yLen = bkgHeight / sqYnum;//y方格长度
    cv::Mat img(bkgHeight + thickNum * 2, bkgWidth + thickNum * 2, CV_8UC4, cv::Scalar(0, 255, 255, 255));
    for (int i = 0; i < img.rows; i++) {

        for (int j = 0; j < img.cols; j++) {

            if (i < thickNum || i >= thickNum + bkgHeight || j < thickNum || j >= thickNum + bkgWidth) {
                img.at<Vec<uchar, 4>>(i, j) = cv::Scalar(0, 0, 0, 255);
                continue;
            }
            checkboardX = j - thickNum;
            checkboardY = i - thickNum;
            if (checkboardY / yLen % 2 == 0) {
                if ((checkboardX) / xLen % 2 == 0) {
                    img.at<Vec<uchar, 4>>(i, j) = cv::Scalar(255, 255, 255, 255);
                } else {
                    img.at<Vec<uchar, 4>>(i, j) = cv::Scalar(0, 0, 0, 255);
                }
            }
            else{
                if ((checkboardX) / xLen % 2 != 0) {
                    img.at<Vec<uchar, 4>>(i, j) = cv::Scalar(255, 255, 255, 255);
                } else {
                    img.at<Vec<uchar, 4>>(i, j) = cv::Scalar(0, 0, 0, 255);
                }
            }
        }
    }
    imwrite(savePath, img);    //保存生成的图片
    printf("#makeCheckerboard %d*%d\n", bkgWidth + thickNum, bkgHeight + thickNum);
    return img;
}