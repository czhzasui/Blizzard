//
// Created by czh on 18-10-16.
//

#include "texture_vision.h"

TextureVision::TextureVision() : Texture2D() {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureVision::update(cv::Mat *img) {
    if (img->channels() == 1) {
        printf("#TextureVision update error: channels = 1\n");
        printf("\tAuto change into RGB\n");
        cv::cvtColor(*img, *img, CV_GRAY2RGB);
    }
    if (img->channels() == 3) {
        Internal_Format = GL_RGB;
        Image_Format = GL_BGR;
    } else if (img->channels() == 4) {
        Internal_Format = GL_RGBA;
        Image_Format = GL_RGBA;
    }
    glBindTexture(GL_TEXTURE_2D, ID);
    width = img->size().width;
    height = img->size().height;
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, img->data);
    glBindTexture(GL_TEXTURE_2D, 0);
}
