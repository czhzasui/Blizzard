//
// Created by czh on 18-10-31.
//

#include "vision.h"

void Vision::dispConfig(cv::Mat img) {
    printf("\tpixel:%d*%d, channels:%d\n", img.size().width, img.size().height, img.channels());
}

cv::Mat Vision::read(std::string file_path, int flags) {
    printf("#Vision read\n");
    cv::Mat img;
    img = cv::imread(file_path, flags);
    if (img.data == NULL) {
        printf("\tError:vision read\n");
    } else {
        dispConfig(img);
    }
    return img;
}