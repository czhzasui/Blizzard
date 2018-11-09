//
// Created by czh on 18-11-7.
//

#ifndef BLIZZARD_TRACKLINE_H
#define BLIZZARD_TRACKLINE_H

#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <math.h>

typedef struct {
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct {
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
} CameraParam;

typedef struct _StaticLineParam{
    float startX;
    float startY;
    float endX;
    float endY;
    float width;
    Color color;
    _StaticLineParam *next;
} StaticLineParam;

typedef struct {
    float startY;
    float length;
    float width;
    Color color;
} DynamicLineParam;

typedef struct {
    float sw_ratio;//转向比
    float max_swAngle;
    float min_swAngle;
    float wheelbase;//轴距
    float trackwidth;
    float dist_bumper2rearaxle;//后轮至后保险杠距离
} VehicleParam;

struct TrackinglineParam {
    bool hideDynamicLine;
    float swAngle;
    VehicleParam vehicleParam;
    CameraParam cameraParam;
    DynamicLineParam dynamicLineParam;
    StaticLineParam staticLineParam;
};

class Trackline{
public:
    int staticVertexCnt;
    std::vector<GLfloat> vertices;
    std::vector<GLubyte> indices;
    float m_fProjection[3][3] = {};
    GLfloat lineWidth = 0.05;

    Trackline();

    ~Trackline();

    void init();

    void setMatrix();

    void setStaticLine();

    void setVertices(std::vector<GLfloat> &vec, GLfloat x, GLfloat y, Color color, bool alpha);


private:
    const char *vShader =
            "#version 330 core                                          \n"
            "uniform float k1;                                          \n"
            "uniform float f;                                           \n"
            "uniform float x0;                                          \n"
            "uniform float y0;                                          \n"
            "uniform mat3 u_mvpMat;                                     \n"
            "layout(location = 0) in vec4 vPosition;                    \n"
            "layout(location = 1) in vec4 vColor;                       \n"
            "layout(location = 2) in float grad;                        \n"
            "flat out vec4 aColor;                                      \n"
            "void main()                                                \n"
            "{                                                          \n"
            "   vec3 pos = vec3(vPosition.x, vPosition.y, 1.0)*u_mvpMat;\n"
            "   float xp=(f*pos.x/pos.z)+x0;                            \n"
            "   float yp=(f*pos.y/pos.z)+y0;                            \n"
            "   float xx=xp*(1.0+k1*(xp*xp+yp*yp));                     \n"
            "   float yy=yp*(1.0+k1*(xp*xp+yp*yp));                     \n"
            "   gl_Position = vec4(xx, yy, 0.0, 1.0);                   \n"
            "   aColor = vColor;                                        \n"
            "}                                                          \n";

    const char *fShader =
            "#version 330 core                                            \n"
            "precision mediump float;                                   \n"
            "flat in vec4 aColor;                                       \n"
            "out vec4 fragColor;                                        \n"
            "void main()                                                \n"
            "{                                                          \n"
            "   fragColor = aColor;                                     \n"
            "}                                                          \n";

    TrackinglineParam *trackinglineParam;
};


#endif //BLIZZARD_TRACKLINE_H
