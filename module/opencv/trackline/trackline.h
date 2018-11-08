//
// Created by zf on 2/28/18.
//

#ifndef ANDROIDBIGSCREEN_TRACKLINE_H
#define ANDROIDBIGSCREEN_TRACKLINE_H

#include "vision/vision.h"

typedef struct {
    float r;
    float g;
    float b;
    float a;
} rgbaColor;

typedef struct _staticLineSegment {
    float startX;
    float startY;
    float endX;
    float endY;
    float width;
    rgbaColor color;
    struct _staticLineSegment *next;
} staticLineSegment;

typedef struct {
    float startY;
    float length;
    float width;
    rgbaColor color;
} dynamicLineAttrib;

typedef struct {
    float sw_ratio;//转向比
    float max_swAngle;
    float min_swAngle;
    float wheelbase;//轴距
    float trackwidth;
    float dist_bumper2rearaxle;//后轮至后保险杠距离
} vehicleAttrib;

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
} cameraCalibPara;

struct TrackinglinePara {
    staticLineSegment staticLineProp;
    dynamicLineAttrib dynamicLineProp;
    vehicleAttrib vehicleProp;
    cameraCalibPara cameraProp;
    float swAngle;
    bool hideOverlappingDynamicLine;
};


#define VERTEX_POS_SIZE         4
#define VERTEX_COLOR_SIZE       4
#define VERTEX_ATTRIB_SIZE (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE)
#define VERTEX_POS_INDEX        0
#define VERTEX_COLOR_INDEX      1

using namespace std;

class trackline{
public:

    trackline();

    ~trackline();

    virtual bool Render();

    virtual bool Init();

    virtual void Deinit();


private:
    TrackinglinePara *trackinglinePara;
    //shading program object
    GLuint m_programObject;
    Parameters *parameter;
    GLuint mVertexShader;
    GLuint mFragmentShader;

    virtual void drawGL();

    void CalculateProjectionMatrix();

    GLfloat m_transparentWidth = 0.05;

    void SetVertex(vector<GLfloat> &vec, GLfloat x, GLfloat y, rgbaColor color, bool transparent);

    void SetVertex(vector<GLfloat> &vec, GLfloat x, GLfloat y);

    vector<GLfloat> m_fStaticVertices;
    vector<GLubyte> m_nStaticIndices;
    int m_nStaticVertexCnt;

    void SetStaticLine();

    vector<GLfloat> m_fDynamicVertices[2];
    vector<GLfloat> m_fDynamicSmoothVertices[2][2];
    GLfloat m_fDynamicColor[4];
    int m_nDynamicVertexCnt[2];

    void SetDynamicLine();


    float m_fProjection[3][3] = {};

    int g_width = 720;
    int g_height = 480;


    const char *vShaderStr =
            "#version 330 core                                                    \n"
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

    const char *fShaderStr =
            "#version 330 core                                            \n"
                    "precision mediump float;                                   \n"
                    "flat in vec4 aColor;                                       \n"
                    "out vec4 fragColor;                                        \n"
                    "void main()                                                \n"
                    "{                                                          \n"
                    "   fragColor = aColor;                                     \n"
                    "}                                                          \n";
};


#endif //ANDROIDBIGSCREEN_TRACKLINE_H
