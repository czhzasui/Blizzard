//
// Created by zf on 2/28/18.
//

#include "trackline.h"
#include <math.h>

trackline::~trackline() {
    delete trackinglinePara;
    Deinit();
}

void trackline::drawGL() {
    Render();
}

//
// Created by zwy on 1/3/18.
//


/*******************************************************************************************************
Function: Render()
Description: render trackline
Input:
*******************************************************************************************************/
bool trackline::Render() {
    glUseProgram(m_programObject);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if (!m_fStaticVertices.empty()) {
        // Load the vertex data
        glVertexAttribPointer(VERTEX_POS_INDEX, 4, GL_FLOAT, false, 8 * sizeof(GLfloat), &m_fStaticVertices[0]);
        glEnableVertexAttribArray(VERTEX_POS_INDEX);

        // Load the color data
        glVertexAttribPointer(VERTEX_COLOR_INDEX, 4, GL_FLOAT, false, 8 * sizeof(GLfloat),
                              &m_fStaticVertices[0] + 4);
        glEnableVertexAttribArray(VERTEX_COLOR_INDEX);

        glDrawElements(GL_TRIANGLE_STRIP, m_nStaticVertexCnt - 1, GL_UNSIGNED_BYTE, &m_nStaticIndices[0]);

    }
    m_fDynamicColor[0] = 0;
    m_fDynamicColor[1] = 1;
    m_fDynamicColor[2] = 1;
    m_fDynamicColor[3] = 1;
    SetDynamicLine();
    //------------------------------------------------------------------------------------------------
    //Draw dynamic tracking line (don't draw dynamic tracking line if steering wheel angle is close to 0)
    if (!m_fDynamicVertices[0].empty()) {
        for (int j = 0; j < 2; j++) {

            // Load the vertex data
            glVertexAttribPointer(VERTEX_POS_INDEX, VERTEX_POS_SIZE, GL_FLOAT, false, 0, &m_fDynamicVertices[0][0]);
            glEnableVertexAttribArray(VERTEX_POS_INDEX);

            // Load the color data
            glVertexAttrib4fv(VERTEX_COLOR_INDEX, m_fDynamicColor);
            glDisableVertexAttribArray(VERTEX_COLOR_INDEX);

            glDrawArrays(GL_TRIANGLE_STRIP, 0, m_fDynamicVertices[0].size() / 8);

            for (int i = 0; i < 2; i++) {
                glVertexAttribPointer(VERTEX_POS_INDEX, VERTEX_POS_SIZE, GL_FLOAT, false,
                                      VERTEX_ATTRIB_SIZE * sizeof(GLfloat), &m_fDynamicSmoothVertices[j][i][0]);
                glEnableVertexAttribArray(VERTEX_POS_INDEX);

                // Load the color data
                glVertexAttribPointer(VERTEX_COLOR_INDEX, VERTEX_COLOR_SIZE, GL_FLOAT, false,
                                      VERTEX_ATTRIB_SIZE * sizeof(GLfloat),
                                      &m_fDynamicSmoothVertices[j][i][0] + VERTEX_POS_SIZE);
                glEnableVertexAttribArray(VERTEX_COLOR_INDEX);

                glDrawArrays(GL_TRIANGLE_STRIP, 0, m_nDynamicVertexCnt[j]);
            }
        }

        for (int j = 0; j < 2; j++) {

            // Load the vertex data
            glVertexAttribPointer(VERTEX_POS_INDEX, VERTEX_POS_SIZE, GL_FLOAT, false, 0, &m_fDynamicVertices[1][0]);
            glEnableVertexAttribArray(VERTEX_POS_INDEX);

            // Load the color data
            glVertexAttrib4fv(VERTEX_COLOR_INDEX, m_fDynamicColor);
            glDisableVertexAttribArray(VERTEX_COLOR_INDEX);

            glDrawArrays(GL_TRIANGLE_STRIP, 0, m_fDynamicVertices[1].size() / 8);

            for (int i = 0; i < 2; i++) {
                glVertexAttribPointer(VERTEX_POS_INDEX, VERTEX_POS_SIZE, GL_FLOAT, false,
                                      VERTEX_ATTRIB_SIZE * sizeof(GLfloat), &m_fDynamicSmoothVertices[j][i][0]);
                glEnableVertexAttribArray(VERTEX_POS_INDEX);

                // Load the color data
                glVertexAttribPointer(VERTEX_COLOR_INDEX, VERTEX_COLOR_SIZE, GL_FLOAT, false,
                                      VERTEX_ATTRIB_SIZE * sizeof(GLfloat),
                                      &m_fDynamicSmoothVertices[j][i][0] + VERTEX_POS_SIZE);
                glEnableVertexAttribArray(VERTEX_COLOR_INDEX);

                glDrawArrays(GL_TRIANGLE_STRIP, 0, m_nDynamicVertexCnt[j]);
            }
        }
    }

    return true;
}


/*******************************************************************************************************
Function: CalculateProjectionMatrix()
Description: init ProjectionMatrix
Input:  about camera para come from cameraCalib
*******************************************************************************************************/
void trackline::CalculateProjectionMatrix() {
    cameraCalibPara para = this->trackinglinePara->cameraProp;

    m_fProjection[0][0] = para.r11;
    m_fProjection[0][1] = para.r12;
    m_fProjection[0][2] = para.t1;

    m_fProjection[1][0] = para.r21;
    m_fProjection[1][1] = para.r22;
    m_fProjection[1][2] = para.t2;

    m_fProjection[2][0] = para.r31;
    m_fProjection[2][1] = para.r32;
    m_fProjection[2][2] = para.t3;
}

/*******************************************************************************************************
Function: SetVertex()
Description: set vertex
Input:
*******************************************************************************************************/
void trackline::SetVertex(vector<GLfloat> &vec, GLfloat x, GLfloat y, rgbaColor color, bool transparent) {
    vec.push_back(x);
    vec.push_back(y);
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(color.r);
    vec.push_back(color.g);
    vec.push_back(color.b);
    if (transparent)
        vec.push_back(0.0);
    else
        vec.push_back(color.a);
}

void trackline::SetVertex(vector<GLfloat> &vec, GLfloat x, GLfloat y) {
    vec.push_back(x);
    vec.push_back(y);
    vec.push_back(0);
    vec.push_back(1);
}


/*******************************************************************************************************
Function: SetStaticLine()
Description: set Static Line
Input:
*******************************************************************************************************/
void trackline::SetStaticLine() {

    vector<GLfloat>().swap(m_fStaticVertices);
    vector<GLubyte>().swap(m_nStaticIndices);
    m_nStaticVertexCnt = 0;

    staticLineSegment *seg = &trackinglinePara->staticLineProp;


    seg = seg->next;
    int index = 0;
    if (seg != NULL) {

        while (seg != NULL) {
            GLfloat halfwidth = seg->width / 2.0;
            if (seg->startX == seg->endX) {

                SetVertex(m_fStaticVertices, (seg->startX - halfwidth), seg->startY, seg->color, false);
                SetVertex(m_fStaticVertices, (seg->startX + halfwidth), seg->startY, seg->color, false);
                SetVertex(m_fStaticVertices, (seg->endX - halfwidth), seg->endY, seg->color, false);
                SetVertex(m_fStaticVertices, (seg->endX + halfwidth), seg->endY, seg->color, false);

                SetVertex(m_fStaticVertices, (seg->startX - halfwidth), seg->startY, seg->color, false);
                SetVertex(m_fStaticVertices, (seg->startX - halfwidth - m_transparentWidth), seg->startY, seg->color,
                          true);
                SetVertex(m_fStaticVertices, (seg->endX - halfwidth), seg->endY, seg->color, false);
                SetVertex(m_fStaticVertices, (seg->endX - halfwidth - m_transparentWidth), seg->endY, seg->color, true);

                SetVertex(m_fStaticVertices, (seg->startX + halfwidth), seg->startY, seg->color, false);
                SetVertex(m_fStaticVertices, (seg->startX + halfwidth + m_transparentWidth), seg->startY, seg->color,
                          true);
                SetVertex(m_fStaticVertices, (seg->endX + halfwidth), seg->endY, seg->color, false);
                SetVertex(m_fStaticVertices, (seg->endX + halfwidth + m_transparentWidth), seg->endY, seg->color, true);
            } else if (seg->startY == seg->endY) {

                SetVertex(m_fStaticVertices, seg->startX, seg->startY - halfwidth, seg->color, false);
                SetVertex(m_fStaticVertices, seg->startX, seg->startY + halfwidth, seg->color, false);
                SetVertex(m_fStaticVertices, seg->endX, seg->endY - halfwidth, seg->color, false);
                SetVertex(m_fStaticVertices, seg->endX, seg->endY + halfwidth, seg->color, false);

                SetVertex(m_fStaticVertices, seg->startX, seg->startY - halfwidth, seg->color, false);
                SetVertex(m_fStaticVertices, seg->startX, seg->startY - halfwidth - m_transparentWidth, seg->color,
                          true);
                SetVertex(m_fStaticVertices, seg->endX, seg->endY - halfwidth, seg->color, false);
                SetVertex(m_fStaticVertices, seg->endX, seg->endY - halfwidth - m_transparentWidth, seg->color, true);

                SetVertex(m_fStaticVertices, seg->startX, seg->startY + halfwidth, seg->color, false);
                SetVertex(m_fStaticVertices, seg->startX, seg->startY + halfwidth + m_transparentWidth, seg->color,
                          true);
                SetVertex(m_fStaticVertices, seg->endX, seg->endY + halfwidth, seg->color, false);
                SetVertex(m_fStaticVertices, seg->endX, seg->endY + halfwidth + m_transparentWidth, seg->color, true);
            } else {
                GLfloat grad = (seg->endY - seg->startY) / (seg->endX - seg->startX);
                GLfloat part_x = halfwidth * grad / sqrt(1.0 + grad * grad);
                GLfloat part_y = halfwidth / sqrt(1.0 + grad * grad);
                GLfloat transWidth_x = m_transparentWidth * grad / sqrt(1.0 + grad * grad);
                GLfloat transWidth_y = m_transparentWidth / sqrt(1.0 + grad * grad);
                SetVertex(m_fStaticVertices, seg->startX - part_x, seg->startY + part_y, seg->color, false);
                SetVertex(m_fStaticVertices, seg->startX + part_x, seg->startY - part_y, seg->color, false);
                SetVertex(m_fStaticVertices, seg->endX - part_x, seg->endY + part_y, seg->color, false);
                SetVertex(m_fStaticVertices, seg->endX + part_x, seg->endY - part_y, seg->color, false);


                SetVertex(m_fStaticVertices, seg->startX - part_x, seg->startY + part_y, seg->color, false);
                SetVertex(m_fStaticVertices, seg->startX - part_x - transWidth_x, seg->startY + part_y + transWidth_y,
                          seg->color, false);
                SetVertex(m_fStaticVertices, seg->endX - part_x, seg->endY + part_y, seg->color, false);
                SetVertex(m_fStaticVertices, seg->endX - part_x - transWidth_x, seg->endY + part_y + transWidth_y,
                          seg->color, false);

                SetVertex(m_fStaticVertices, seg->startX + part_x, seg->startY - part_y, seg->color, false);
                SetVertex(m_fStaticVertices, seg->startX + part_x + transWidth_x, seg->startY - part_y - transWidth_y,
                          seg->color, false);
                SetVertex(m_fStaticVertices, seg->endX + part_x, seg->endY - part_y, seg->color, false);
                SetVertex(m_fStaticVertices, seg->endX + part_x + transWidth_x, seg->endY - part_y - transWidth_y,
                          seg->color, false);
            }
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(255);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(255);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(index++);
            m_nStaticIndices.push_back(255);
            m_nStaticVertexCnt += 12;
            seg = seg->next;

        }
    } else {

    }
    m_nStaticIndices.size();
}

/*******************************************************************************************************
Function: SetDynamicLine()
Description: set Dynamic Line
Input:
*******************************************************************************************************/

void trackline::SetDynamicLine() {

    int angle = parameter->GetPara(Parameters::STEERING_WHEEL_ANGLE);
    if (int(trackinglinePara->swAngle) == angle) {

        return;
    }
    trackinglinePara->swAngle = angle;
    for (int i = 0; i < 2; i++) {
        vector<GLfloat>().swap(m_fDynamicVertices[i]);
        m_nDynamicVertexCnt[i] = 0;
        for (int j = 0; j < 2; j++)
            vector<GLfloat>().swap(m_fDynamicSmoothVertices[i][j]);
    }

    dynamicLineAttrib paintProp = trackinglinePara->dynamicLineProp;

    if (trackinglinePara->hideOverlappingDynamicLine && trackinglinePara->swAngle < 1.0 &&
        trackinglinePara->swAngle > -1.0)
        return;line

    float trackwidth = trackinglinePara->vehicleProp.trackwidth;
    float swAngle;
    if (trackinglinePara->swAngle > trackinglinePara->vehicleProp.max_swAngle)
        swAngle = trackinglinePara->vehicleProp.max_swAngle;
    else if (trackinglinePara->swAngle < trackinglinePara->vehicleProp.min_swAngle)
        swAngle = trackinglinePara->vehicleProp.min_swAngle;
    else
        swAngle = trackinglinePara->swAngle;

    float turningAngle = swAngle / trackinglinePara->vehicleProp.sw_ratio;
    GLfloat R = trackinglinePara->vehicleProp.wheelbase / tan((M_PI * turningAngle) / 180);
    GLfloat r[2] = {R + trackwidth / 2, R - trackwidth / 2};
    GLfloat startX[2] = {-trackwidth / 2, trackwidth / 2};
    GLfloat linewidth = paintProp.width / 2.0;

    GLfloat dx, dy;
    GLfloat sn, cs;
    //j: left/right
    for (int j = 0; j < 2; j++) {
        // If TurningAngle is close to 0, just paint straight line
        // Only x/y is coordinate, z represents left/right offset in x direction, w is not used
        if (turningAngle < 0.05 && turningAngle > -0.05) {
            // set 4 corners of the rect been drawn. color is not changing so it's not necessary to include color in the array
            SetVertex(m_fDynamicVertices[j], startX[j] - linewidth, paintProp.startY);
            SetVertex(m_fDynamicVertices[j], startX[j] + linewidth, paintProp.startY);
            SetVertex(m_fDynamicVertices[j], startX[j] - linewidth, paintProp.startY + paintProp.length);
            SetVertex(m_fDynamicVertices[j], startX[j] + linewidth, paintProp.startY + paintProp.length);

            // set rect besides for smooth, 4 corners each side
            SetVertex(m_fDynamicSmoothVertices[j][0], startX[j] - linewidth, paintProp.startY, paintProp.color, false);
            SetVertex(m_fDynamicSmoothVertices[j][0], startX[j] - linewidth - m_transparentWidth, paintProp.startY,
                      paintProp.color, true);
            SetVertex(m_fDynamicSmoothVertices[j][0], startX[j] - linewidth, paintProp.startY + paintProp.length,
                      paintProp.color, false);
            SetVertex(m_fDynamicSmoothVertices[j][0], startX[j] - linewidth - m_transparentWidth,
                      paintProp.startY + paintProp.length, paintProp.color, true);

            SetVertex(m_fDynamicSmoothVertices[j][1], startX[j] + linewidth, paintProp.startY, paintProp.color, false);
            SetVertex(m_fDynamicSmoothVertices[j][1], startX[j] + linewidth + m_transparentWidth, paintProp.startY,
                      paintProp.color, true);
            SetVertex(m_fDynamicSmoothVertices[j][1], startX[j] + linewidth, paintProp.startY + paintProp.length,
                      paintProp.color, false);
            SetVertex(m_fDynamicSmoothVertices[j][1], startX[j] + linewidth + m_transparentWidth,
                      paintProp.startY + paintProp.length, paintProp.color, true);

            m_nDynamicVertexCnt[j] = 4;
        } else {
            GLfloat endY =
                    fabs(r[j]) * sin(paintProp.length / (fabs(r[j]) > fabs(r[1 - j]) ? fabs(r[j]) : fabs(r[1 - j])));
            // dy: step in y direction, each step draw two points
            // Only x/y is coordinate, z represents left/right offset in x direction, w is not used
            // Stop condition: longer side: draw till STOP_PAINT_DIST
            //                 shorter side: draw till radial from turning center to longer side's terminal
            for (dy = paintProp.startY; dy <= endY; dy += 0.2) {
                if ((dy + 0.2) > endY) {        // this point is terminal point
                    dy = endY;
                }
                sn = (dy + trackinglinePara->vehicleProp.dist_bumper2rearaxle) / r[j];
                cs = sqrt(1 - sn * sn);
                dx = r[j] * cs;
                // Draw two vertices, color is not changing so it's not necessary to include color in the array
                SetVertex(m_fDynamicVertices[j], R - dx - linewidth * cs, dy + linewidth * sn);
                SetVertex(m_fDynamicVertices[j], R - dx + linewidth * cs, dy - linewidth * sn);

                //j: left/right tracking line
                //k: left/right smooth rectangle besides each tracking line
                //i: draw two vertices, color is included as alpha value is different
                SetVertex(m_fDynamicSmoothVertices[j][0], R - dx - linewidth * cs, dy + linewidth * sn, paintProp.color,
                          false);
                SetVertex(m_fDynamicSmoothVertices[j][0], R - dx - (linewidth + m_transparentWidth) * cs,
                          dy + (linewidth + m_transparentWidth) * sn, paintProp.color, true);
                SetVertex(m_fDynamicSmoothVertices[j][1], R - dx + linewidth * cs, dy - linewidth * sn, paintProp.color,
                          false);
                SetVertex(m_fDynamicSmoothVertices[j][1], R - dx + (linewidth + m_transparentWidth) * cs,
                          dy - (linewidth + m_transparentWidth) * sn, paintProp.color, true);

                m_nDynamicVertexCnt[j] = 2;
            }
        }
    }
}

bool trackline::Init() {
    m_programObject = GLshader::CompileShaders(vShaderStr, fShaderStr, mVertexShader, mFragmentShader);

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

    glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    return true;
}

void trackline::Deinit() {
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragmentShader);
    glDeleteProgram(m_programObject);
}

trackline::trackline(){
    cameraCalibPara campara;
    campara.r11 = 0.999944;
    campara.r12 = 0.00604776;
    campara.r21 = -0.010565;
    campara.r22 = 0.613928;
    campara.r31 = 0.000281733;
    campara.r32 = 0.789339;
    campara.t1 = -0.613515;
    campara.t2 = -1.63526;
    campara.t3 = 12.3962;
    campara.f = 0.693994;
    campara.s = 0.99965;
    campara.k1 = -0.0428289;
    campara.x0 = 0.0505395;
    campara.y0 = -0.0625922;

    //静态轨迹线参数
    static staticLineSegment data[9];

    data[0].startX = 5;
    data[0].startY = -10;
    data[0].endX = 5;
    data[0].endY = -5;
    data[0].width = 0.5;
    data[0].color.r = 1;
    data[0].color.g = 0;
    data[0].color.b = 0;
    data[0].color.a = 1;
    data[0].next = &data[1];

    data[1].startX = -5;
    data[1].startY = -10;
    data[1].endX = -5;
    data[1].endY = -5;
    data[1].width = 0.5;
    data[1].color.r = 1;
    data[1].color.g = 0;
    data[1].color.b = 0;
    data[1].color.a = 1;
    data[1].next = &data[2];

    data[2].startX = 4.98;
    data[2].startY = -5;
    data[2].endX = 4.98;
    data[2].endY = 1;
    data[2].width = 0.42;
    data[2].color.r = 1;
    data[2].color.g = 1;
    data[2].color.b = 0;
    data[2].color.a = 1;
    data[2].next = &data[3];

    data[3].startX = -4.98;
    data[3].startY = -5;
    data[3].endX = -4.98;
    data[3].endY = 1;
    data[3].width = 0.42;
    data[3].color.r = 1;
    data[3].color.g = 1;
    data[3].color.b = 0;
    data[3].color.a = 1;
    data[3].next = &data[4];

    data[4].startX = 3.72;
    data[4].startY = -5;
    data[4].endX = 3.72;
    data[4].endY = -4.5;
    data[4].width = 3;
    data[4].color.r = 1;
    data[4].color.g = 0;
    data[4].color.b = 0;
    data[4].color.a = 1;
    data[4].next = &data[5];

    data[5].startX = -3.72;
    data[5].startY = -5;
    data[5].endX = -3.72;
    data[5].endY = -4.5;
    data[5].width = 3;
    data[5].color.r = 1;
    data[5].color.g = 0;
    data[5].color.b = 0;
    data[5].color.a = 1;
    data[5].next = &data[6];

    data[6].startX = -3.75;
    data[6].startY = 0.5;
    data[6].endX = -3.75;
    data[6].endY = 1;
    data[6].width = 2;
    data[6].color.r = 1;
    data[6].color.g = 1;
    data[6].color.b = 0;
    data[6].color.a = 1;
    data[6].next = &data[7];

    data[7].startX = 3.75;
    data[7].startY = 0.5;
    data[7].endX = 3.75;
    data[7].endY = 1;
    data[7].width = 2;
    data[7].color.r = 1;
    data[7].color.g = 1;
    data[7].color.b = 0;
    data[7].color.a = 1;
    data[7].next = &data[8];

    data[8].endX = 0;
    data[8].endY = 0;
    data[8].startX = 0;
    data[8].startY = 0;
    data[8].width = 0;
    data[8].color.r = 0;
    data[8].color.g = 1;
    data[8].color.b = 1;
    data[8].color.a = 0;
    data[8].next = NULL;

    //动态轨迹线参数
    vehicleAttrib vehicleA;
    vehicleA.max_swAngle = 528;
    vehicleA.min_swAngle = -528;
    vehicleA.sw_ratio = 18.0;
    vehicleA.wheelbase = 15.5;
    vehicleA.trackwidth = 11;
    vehicleA.dist_bumper2rearaxle = 15;

    dynamicLineAttrib dynamicLineA;
    dynamicLineA.color.r = 1;
    dynamicLineA.color.g = 1;
    dynamicLineA.color.b = 1;
    dynamicLineA.color.a = 1;
    dynamicLineA.length = 25;
    dynamicLineA.startY = -10;
    dynamicLineA.width = 0.5;

    //轨迹线参数：使用到了标定参数，静态轨迹线参数，动态轨迹线参数
    trackinglinePara = new TrackinglinePara;
    trackinglinePara->cameraProp = campara;
    trackinglinePara->staticLineProp = data[0];
    trackinglinePara->dynamicLineProp = dynamicLineA;
    trackinglinePara->vehicleProp = vehicleA;
    trackinglinePara->swAngle = 20;
    trackinglinePara->hideOverlappingDynamicLine = false;

    CalculateProjectionMatrix();
    SetStaticLine();
    Init();
}
