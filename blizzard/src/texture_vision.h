//
// Created by czh on 18-10-16.
//

#ifndef OPENGL_PRO_TEXTURE_VISION_H
#define OPENGL_PRO_TEXTURE_VISION_H

#include "texture.h"
#include "texture_vision.h"
#include "persioncv/vision/vision.h"

class TextureVision : public Texture2D {
public:
    GLuint Format;
    bool hasInit = false;

    TextureVision();

    void update(cv::Mat *img);

    void bind() const;

};


#endif //OPENGL_PRO_TEXTURE_VISION_H
