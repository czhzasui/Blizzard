//
// Created by czh on 18-11-7.
//

#include "trackline.h"

Trackline::Trackline() {

    CameraParam cameraParam;
    cameraParam.r11 = 0.999944;
    cameraParam.r12 = 0.00604776;
    cameraParam.r21 = -0.010565;
    cameraParam.r22 = 0.613928;
    cameraParam.r31 = 0.000281733;
    cameraParam.r32 = 0.789339;
    cameraParam.t1 = -0.613515;
    cameraParam.t2 = -1.63526;
    cameraParam.t3 = 12.3962;
    cameraParam.f = 0.693994;
    cameraParam.s = 0.99965;
    cameraParam.k1 = -0.0428289;
    cameraParam.x0 = 0.0505395;
    cameraParam.y0 = -0.0625922;

    static StaticLineParam staticLineParam[9];

    staticLineParam[0].startX = 5;
    staticLineParam[0].startY = -10;
    staticLineParam[0].endX = 5;
    staticLineParam[0].endY = -5;
    staticLineParam[0].width = 0.5;
    staticLineParam[0].color.r = 1;
    staticLineParam[0].color.g = 0;
    staticLineParam[0].color.b = 0;
    staticLineParam[0].color.a = 1;
    staticLineParam[0].next = &staticLineParam[1];

    staticLineParam[1].startX = -5;
    staticLineParam[1].startY = -10;
    staticLineParam[1].endX = -5;
    staticLineParam[1].endY = -5;
    staticLineParam[1].width = 0.5;
    staticLineParam[1].color.r = 1;
    staticLineParam[1].color.g = 0;
    staticLineParam[1].color.b = 0;
    staticLineParam[1].color.a = 1;
    staticLineParam[1].next = &staticLineParam[2];

    staticLineParam[2].startX = 4.98;
    staticLineParam[2].startY = -5;
    staticLineParam[2].endX = 4.98;
    staticLineParam[2].endY = 1;
    staticLineParam[2].width = 0.42;
    staticLineParam[2].color.r = 1;
    staticLineParam[2].color.g = 1;
    staticLineParam[2].color.b = 0;
    staticLineParam[2].color.a = 1;
    staticLineParam[2].next = &staticLineParam[3];

    staticLineParam[3].startX = -4.98;
    staticLineParam[3].startY = -5;
    staticLineParam[3].endX = -4.98;
    staticLineParam[3].endY = 1;
    staticLineParam[3].width = 0.42;
    staticLineParam[3].color.r = 1;
    staticLineParam[3].color.g = 1;
    staticLineParam[3].color.b = 0;
    staticLineParam[3].color.a = 1;
    staticLineParam[3].next = &staticLineParam[4];

    staticLineParam[4].startX = 3.72;
    staticLineParam[4].startY = -5;
    staticLineParam[4].endX = 3.72;
    staticLineParam[4].endY = -4.5;
    staticLineParam[4].width = 3;
    staticLineParam[4].color.r = 1;
    staticLineParam[4].color.g = 0;
    staticLineParam[4].color.b = 0;
    staticLineParam[4].color.a = 1;
    staticLineParam[4].next = &staticLineParam[5];

    staticLineParam[5].startX = -3.72;
    staticLineParam[5].startY = -5;
    staticLineParam[5].endX = -3.72;
    staticLineParam[5].endY = -4.5;
    staticLineParam[5].width = 3;
    staticLineParam[5].color.r = 1;
    staticLineParam[5].color.g = 0;
    staticLineParam[5].color.b = 0;
    staticLineParam[5].color.a = 1;
    staticLineParam[5].next = &staticLineParam[6];

    staticLineParam[6].startX = -3.75;
    staticLineParam[6].startY = 0.5;
    staticLineParam[6].endX = -3.75;
    staticLineParam[6].endY = 1;
    staticLineParam[6].width = 2;
    staticLineParam[6].color.r = 1;
    staticLineParam[6].color.g = 1;
    staticLineParam[6].color.b = 0;
    staticLineParam[6].color.a = 1;
    staticLineParam[6].next = &staticLineParam[7];

    staticLineParam[7].startX = 3.75;
    staticLineParam[7].startY = 0.5;
    staticLineParam[7].endX = 3.75;
    staticLineParam[7].endY = 1;
    staticLineParam[7].width = 2;
    staticLineParam[7].color.r = 1;
    staticLineParam[7].color.g = 1;
    staticLineParam[7].color.b = 0;
    staticLineParam[7].color.a = 1;
    staticLineParam[7].next = &staticLineParam[8];

    staticLineParam[8].endX = 0;
    staticLineParam[8].endY = 0;
    staticLineParam[8].startX = 0;
    staticLineParam[8].startY = 0;
    staticLineParam[8].width = 0;
    staticLineParam[8].color.r = 0;
    staticLineParam[8].color.g = 1;
    staticLineParam[8].color.b = 1;
    staticLineParam[8].color.a = 0;
    staticLineParam[8].next = NULL;

    VehicleParam vehicleParam;
    vehicleParam.max_swAngle = 528;
    vehicleParam.min_swAngle = -528;
    vehicleParam.sw_ratio = 18.0;
    vehicleParam.wheelbase = 15.5;
    vehicleParam.trackwidth = 11;
    vehicleParam.dist_bumper2rearaxle = 15;

    DynamicLineParam dynamicLineParam;
    dynamicLineParam.color.r = 1;
    dynamicLineParam.color.g = 1;
    dynamicLineParam.color.b = 1;
    dynamicLineParam.color.a = 1;
    dynamicLineParam.length = 25;
    dynamicLineParam.startY = -10;
    dynamicLineParam.width = 0.5;

    //轨迹线参数：使用到了标定参数，静态轨迹线参数，动态轨迹线参数
    trackinglineParam = new TrackinglineParam;
    trackinglineParam->cameraParam = cameraParam;//相机参数
    trackinglineParam->staticLineParam = staticLineParam[0];//静态轨迹线参数
    trackinglineParam->dynamicLineParam = dynamicLineParam;//动态轨迹线参数
    trackinglineParam->vehicleParam = vehicleParam;//汽车参数
    trackinglineParam->swAngle = 20;//转向角
    trackinglineParam->hideDynamicLine = false;

    setMatrix();
    init();
}

Trackline::~Trackline() {

}

void Trackline::init() {
/*    m_programObject = GLshader::CompileShaders(vShaderStr, fShaderStr, mVertexShader, mFragmentShader);

    glUseProgram(m_programObject);
    GLint g_mvpMatrix = glGetUniformLocation(m_programObject, "u_mvpMat");
    glUniformMatrix3fv(g_mvpMatrix, 1, false, &m_fProjection[0][0]);

    GLint g_k1 = glGetUniformLocation(m_programObject, "k1");
    glUniform1f(g_k1, trackinglinePara->cameraProp.k1);

    GLint g_f = glGetUniformLocation(m_programObject, "f");
    glUniform1f(g_f, trackinglinePara->cameraProp.f);

    GLint g_x0 = glGetUniformLocation(m_programObject, "x0");
    glUniform1f(g_x0, trackinglinePara->cameraProp.x0);

    GLint g_y0 = glGetUniformLocation(m_programObject, "y0");
    glUniform1f(g_y0, trackinglinePara->cameraProp.y0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#define GL_PRIMITIVE_RESTART_FIXED_INDEX  0x8D69

    glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);*/
}

void Trackline::setMatrix() {
    m_fProjection[0][0] = trackinglineParam->cameraParam.r11;
    m_fProjection[0][1] = trackinglineParam->cameraParam.r12;
    m_fProjection[0][2] = trackinglineParam->cameraParam.t1;

    m_fProjection[1][0] = trackinglineParam->cameraParam.r21;
    m_fProjection[1][1] = trackinglineParam->cameraParam.r22;
    m_fProjection[1][2] = trackinglineParam->cameraParam.t2;

    m_fProjection[2][0] = trackinglineParam->cameraParam.r31;
    m_fProjection[2][1] = trackinglineParam->cameraParam.r32;
    m_fProjection[2][2] = trackinglineParam->cameraParam.t3;
}

void Trackline::setVertices(std::vector<GLfloat> &vertices, GLfloat x, GLfloat y, Color color, bool alpha) {
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(0);
    vertices.push_back(1);
    vertices.push_back(color.r);
    vertices.push_back(color.g);
    vertices.push_back(color.b);
    if (alpha)
        vertices.push_back(0.0);
    else
        vertices.push_back(color.a);
}

void Trackline::setStaticLine() {
    staticVertexCnt = 0;
    StaticLineParam *staticLineParam = &trackinglineParam->staticLineParam;

    staticLineParam = staticLineParam->next;
    int index = 0;

    if(staticLineParam != NULL){
        while (staticLineParam != NULL){
            GLfloat halfwidth = staticLineParam->width / 2.0;
            if (staticLineParam->startX == staticLineParam->endX) {

                setVertices(vertices, (staticLineParam->startX - halfwidth), staticLineParam->startY, staticLineParam->color, false);
                setVertices(vertices, (staticLineParam->startX + halfwidth), staticLineParam->startY, staticLineParam->color, false);
                setVertices(vertices, (staticLineParam->endX - halfwidth), staticLineParam->endY, staticLineParam->color, false);
                setVertices(vertices, (staticLineParam->endX + halfwidth), staticLineParam->endY, staticLineParam->color, false);

                setVertices(vertices, (staticLineParam->startX - halfwidth), staticLineParam->startY, staticLineParam->color, false);
                setVertices(vertices, (staticLineParam->startX - halfwidth - lineWidth), staticLineParam->startY, staticLineParam->color, true);
                setVertices(vertices, (staticLineParam->endX - halfwidth), staticLineParam->endY, staticLineParam->color, false);
                setVertices(vertices, (staticLineParam->endX - halfwidth - lineWidth), staticLineParam->endY, staticLineParam->color, true);

                setVertices(vertices, (staticLineParam->startX + halfwidth), staticLineParam->startY, staticLineParam->color, false);
                setVertices(vertices, (staticLineParam->startX + halfwidth + lineWidth), staticLineParam->startY, staticLineParam->color, true);
                setVertices(vertices, (staticLineParam->endX + halfwidth), staticLineParam->endY, staticLineParam->color, false);
                setVertices(vertices, (staticLineParam->endX + halfwidth + lineWidth), staticLineParam->endY, staticLineParam->color, true);
            } else if (staticLineParam->startY == staticLineParam->endY) {

                setVertices(vertices, staticLineParam->startX, staticLineParam->startY - halfwidth, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->startX, staticLineParam->startY + halfwidth, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->endX, staticLineParam->endY - halfwidth, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->endX, staticLineParam->endY + halfwidth, staticLineParam->color, false);

                setVertices(vertices, staticLineParam->startX, staticLineParam->startY - halfwidth, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->startX, staticLineParam->startY - halfwidth - lineWidth, staticLineParam->color, true);
                setVertices(vertices, staticLineParam->endX, staticLineParam->endY - halfwidth, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->endX, staticLineParam->endY - halfwidth - lineWidth, staticLineParam->color, true);

                setVertices(vertices, staticLineParam->startX, staticLineParam->startY + halfwidth, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->startX, staticLineParam->startY + halfwidth + lineWidth, staticLineParam->color, true);
                setVertices(vertices, staticLineParam->endX, staticLineParam->endY + halfwidth, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->endX, staticLineParam->endY + halfwidth + lineWidth, staticLineParam->color, true);
            } else {
                GLfloat grad = (staticLineParam->endY - staticLineParam->startY) / (staticLineParam->endX - staticLineParam->startX);
                GLfloat part_x = halfwidth * grad / sqrt(1.0 + grad * grad);
                GLfloat part_y = halfwidth / sqrt(1.0 + grad * grad);
                GLfloat transWidth_x = lineWidth * grad / sqrt(1.0 + grad * grad);
                GLfloat transWidth_y = lineWidth / sqrt(1.0 + grad * grad);
                setVertices(vertices, staticLineParam->startX - part_x, staticLineParam->startY + part_y, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->startX + part_x, staticLineParam->startY - part_y, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->endX - part_x, staticLineParam->endY + part_y, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->endX + part_x, staticLineParam->endY - part_y, staticLineParam->color, false);


                setVertices(vertices, staticLineParam->startX - part_x, staticLineParam->startY + part_y, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->startX - part_x - transWidth_x, staticLineParam->startY + part_y + transWidth_y, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->endX - part_x, staticLineParam->endY + part_y, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->endX - part_x - transWidth_x, staticLineParam->endY + part_y + transWidth_y, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->startX + part_x, staticLineParam->startY - part_y, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->startX + part_x + transWidth_x, staticLineParam->startY - part_y - transWidth_y, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->endX + part_x, staticLineParam->endY - part_y, staticLineParam->color, false);
                setVertices(vertices, staticLineParam->endX + part_x + transWidth_x, staticLineParam->endY - part_y - transWidth_y, staticLineParam->color, false);
            }
            indices.push_back(index++);
            indices.push_back(index++);
            indices.push_back(index++);
            indices.push_back(index++);
            indices.push_back(255);
            indices.push_back(index++);
            indices.push_back(index++);
            indices.push_back(index++);
            indices.push_back(index++);
            indices.push_back(255);
            indices.push_back(index++);
            indices.push_back(index++);
            indices.push_back(index++);
            indices.push_back(index++);
            indices.push_back(255);
            staticVertexCnt += 12;
            staticLineParam = staticLineParam->next;
        }
    } else {
        printf("#Linked list error\n");
    }
}

