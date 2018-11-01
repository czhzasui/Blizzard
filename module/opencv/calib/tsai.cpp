//
// Created by czh on 18-10-15.
//

#include "tsai.h"
#include <stdio.h>
#include <linux/videodev2.h>
#include <glad/glad.h>
#include <resource_manager.h>

/*******************************************************************************************************
Function: isValidNumber()
Description: check whether number is NaN(Not a number) or Inf(INFINITY)
Input:  number to check
Output: false if input number is NaN(Not a number) or Inf(INFINITY)
*******************************************************************************************************/
bool isValidNumber(float f) {
    if (std::isnan(f) || std::isinf(f))
        return false;
    else
        return true;
}

/*******************************************************************************************************
Function: tsaiCalibStep1
Description: Step 1 in Tsai camera calibration method
Input:  wcPts, a vector of OpenCV Point2f data struct, points position in world coordinates
        pcPts, a vector of OpenCV Point2f data struct, points position in camera coordinates
        para, struct cameraPara, includes all camera parameters
Output: false if any camera parameter is not a valid number
*******************************************************************************************************/
bool tsaiCalibStep1(std::vector<cv::Point2f> wcPts, std::vector<cv::Point2f> pcPts, cameraPara &para) {
    cv::Mat wcMat(wcPts);
    std::vector<cv::Mat> mv1;
    cv::split(wcMat, mv1);
    cv::Mat wc_x = mv1[0];
    cv::Mat wc_y = mv1[1];

    cv::Mat pcMat(pcPts);
    std::vector<cv::Mat> mv2;
    cv::split(pcMat, mv2);
    cv::Mat pc_x = mv2[0];
    cv::Mat pc_y = mv2[1];
    pc_x = pc_x - para.x0;
    pc_y = pc_y - para.y0;

    cv::Mat wc_x_prime, wc_y_prime, pc_x_prime, pc_y_prime;
    cv::transpose(wc_x, wc_x_prime);
    cv::transpose(wc_y, wc_y_prime);
    cv::transpose(pc_x, pc_x_prime);
    cv::transpose(pc_y, pc_y_prime);

    //---------------------------------------------- algorithm explanation, comment 1 --------------------------------------
    cv::Mat X = para.s * wc_x_prime.mul(pc_y_prime);
    X.push_back(cv::Mat(para.s * wc_y_prime.mul(pc_y_prime)));
    X.push_back(cv::Mat(para.s * pc_y_prime));
    X.push_back(cv::Mat(-1.0 * wc_x_prime.mul(pc_x_prime)));
    X.push_back(cv::Mat(-1.0 * wc_y_prime.mul(pc_x_prime)));
    cv::transpose(X, X);
    cv::Mat Y(pc_x);

    cv::Mat A, XInv, XPrime;
    cv::transpose(X, XPrime);
    cv::invert(XPrime * X, XInv);
    A = XInv * XPrime * Y;

    float a1 = A.at<float>(0);
    float a2 = A.at<float>(1);
    float a3 = A.at<float>(2);
    float a4 = A.at<float>(3);
    float a5 = A.at<float>(4);
    //----------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------- algorithm explanation, comment 2 --------------------------------------
    para.t2 = -1.0 * sqrt((a1 * a1 - sqrt((a1 * a1 - 2 * a1 * a5 + a2 * a2 + 2 * a2 * a4 + a4 * a4 + a5 * a5) *
                                          (a1 * a1 + 2 * a1 * a5 + a2 * a2 - 2 * a2 * a4 + a4 * a4 + a5 * a5)) +
                           a2 * a2 + a4 * a4 + a5 * a5) /
                          (2 * (a1 * a1 * a5 * a5 - 2 * a1 * a2 * a4 * a5 + a2 * a2 * a4 * a4)));
    para.r11 = a1 * para.t2;
    para.r12 = a2 * para.t2;
    para.r21 = a4 * para.t2;
    para.r22 = a5 * para.t2;
    para.t1 = a3 * para.t2;
    para.r31 = sqrt(1 - para.r11 * para.r11 - para.r21 * para.r21);
    para.r32 = sqrt(1 - para.r12 * para.r12 - para.r22 * para.r22);
    //----------------------------------------------------------------------------------------------------------------------
    if (!isValidNumber(para.r11) ||
        !isValidNumber(para.r12) ||
        !isValidNumber(para.r21) ||
        !isValidNumber(para.r22) ||
        !isValidNumber(para.r31) ||
        !isValidNumber(para.r32) ||
        !isValidNumber(para.t1) ||
        !isValidNumber(para.t2)) {
        printf("Parameter is invalid!\n");
        return false;
    } else
        return true;
}

/*******************************************************************************************************
Function: tsaiCalibStep2()
Description: Step 2 in Tsai camera calibration method
Input:  wcPts, a vector of OpenCV Point2f data struct, points position in world coordinates
        pcPts, a vector of OpenCV Point2f data struct, points position in camera coordinates
        para, struct cameraPara, includes all camera parameters
        alpha, step length used in gradient descent
        cond, OpenCV TermCriteria struct, indicates gradient descent terminate condition
*******************************************************************************************************/
float tsaiCalibStep2(std::vector<cv::Point2f> wcPts, std::vector<cv::Point2f> pcPts, cameraPara &para, float alpha,
                     cv::TermCriteria cond) {
    cv::Mat wcMat(wcPts);
    std::vector<cv::Mat> mv1;
    cv::split(wcMat, mv1);
    cv::Mat wc_x = mv1[0];
    cv::Mat wc_y = mv1[1];

    cv::Mat pcMat(pcPts);
    std::vector<cv::Mat> mv2;
    cv::split(pcMat, mv2);
    cv::Mat pc_x = mv2[0];
    cv::Mat pc_y = mv2[1];
    pc_x = pc_x - para.x0;
    pc_y = pc_y - para.y0;

    cv::Mat wc_x_prime, wc_y_prime, pc_x_prime, pc_y_prime;
    cv::transpose(wc_x, wc_x_prime);
    cv::transpose(wc_y, wc_y_prime);
    cv::transpose(pc_x, pc_x_prime);
    cv::transpose(pc_y, pc_y_prime);


    //---------------------------------------------- algorithm explanation, comment 3 --------------------------------------
    cv::Mat X = para.s * (para.r11 * wc_x_prime + para.r12 * wc_y_prime + para.t1);
    X.push_back(cv::Mat(-1.0 * pc_x_prime));
    cv::Mat X2 = para.r21 * wc_x_prime + para.r22 * wc_y_prime + para.t2;
    X2.push_back(cv::Mat(-1.0 * pc_y_prime));
    transpose(X, X);
    transpose(X2, X2);
    X.push_back(X2);
    cv::Mat Y = pc_x.mul(para.r31 * wc_x + para.r32 * wc_y);
    Y.push_back(cv::Mat(pc_y.mul(para.r31 * wc_x + para.r32 * wc_y)));

    cv::Mat B, XInv, XPrime;
    cv::transpose(X, XPrime);
    cv::invert(XPrime * X, XInv);
    B = XInv * XPrime * Y;

    para.k1 = 0.0f;
    para.f = B.at<float>(0);
    para.t3 = B.at<float>(1);
    //----------------------------------------------------------------------------------------------------------------------


    //---------------------------------------------- algorithm explanation(gradient descent), comment 4 --------------------
    cv::Mat xt = para.r11 * wc_x + para.r12 * wc_y + para.t1;
    cv::Mat yt = para.r21 * wc_x + para.r22 * wc_y + para.t2;
    cv::Mat wt = para.r31 * wc_x + para.r32 * wc_y + para.t3;

    cv::Mat fx, fy, d, wt_square, wt_cube, wt_4thpower, mat_temp;
    cv::Mat j_k1x, j_k1y, j_fx, j_fy, j_t3x, j_t3y;
    float j_k1, j_f, j_t3, j2_k1, j2_f, j2_t3, j2_k1_f, j2_k1_t3, j2_f_t3;
    cv::Matx33f hessian, hessian_inv;
    cv::Vec3f gradient, newtonstep;
    float temp0, temp1, temp2;
    float f_square = para.f * para.f;
    float f_cube = f_square * para.f;

    int i = 0;
    float lastcost;
    float cost = 100000.0f;
    alpha = alpha / wc_x.size().height;
    while (1) {
        lastcost = cost;

        d = para.s * para.s * xt.mul(xt) + yt.mul(yt);
        wt_square = wt.mul(wt);
        wt_cube = wt_square.mul(wt);
        wt_4thpower = wt_cube.mul(wt);

        mat_temp = (1 + para.k1 * f_square * d / wt_square) / wt;
        fx = para.s * para.f * xt.mul(mat_temp) - pc_x;
        fy = para.f * yt.mul(mat_temp) - pc_y;
        cost = (cv::sum(fx.mul(fx))[0] + cv::sum(fy.mul(fy))[0]) / wc_x.size().height;
        if ((cond.type == cv::TermCriteria::COUNT && i >= cond.maxCount) ||
            (cond.type == cv::TermCriteria::EPS && lastcost - cost < cond.epsilon))
            break;

        j_k1x = f_cube * para.s * xt.mul(d) / wt_cube;
        j_k1y = f_cube * yt.mul(d) / wt_cube;
        mat_temp = (1 + 3 * para.k1 * f_square * d / wt_cube) / wt;
        j_fx = para.s * xt.mul(mat_temp);
        j_fy = yt.mul(mat_temp);
        j_t3x = -1.0 * para.f * para.s * xt.mul(mat_temp) / wt_square;
        j_t3y = -1.0 * para.f * yt.mul(mat_temp) / wt_square;

        j_k1 = cv::sum(fx.mul(j_k1x))[0] + cv::sum(fy.mul(j_k1y))[0];
        j_f = cv::sum(fx.mul(j_fx))[0] + cv::sum(fy.mul(j_fy))[0];
        j_t3 = cv::sum(fx.mul(j_t3x))[0] + cv::sum(fy.mul(j_t3y))[0];

        temp0 = para.k1 - alpha * j_k1;
        temp1 = para.f - alpha * j_f;
        temp2 = para.t3 - alpha * j_t3;
        para.k1 = temp0;
        para.f = temp1;
        para.t3 = temp2;
        i++;
    }
    //----------------------------------------------------------------------------------------------------------------------

    //---------------------------------------------- algorithm explanation(Newton's method), comment 6 ---------------------
//    while(1) {
//        lastcost = cost;

//        d = para.s*para.s*xt.mul(xt)+yt.mul(yt);
//        wt_square = wt.mul(wt);
//        wt_cube = wt_square.mul(wt);
//        wt_4thpower = wt_cube.mul(wt);

//        mat_temp = (1+para.k1*f_square*d/wt_square)/wt;
//        fx = para.s*para.f*xt.mul(mat_temp)-pc_x;
//        fy = para.f*yt.mul(mat_temp)-pc_y;
//        cost = (cv::sum(fx.mul(fx))[0]+cv::sum(fy.mul(fy))[0])/wc_x.size().height;
//        if ((cond.type == cv::TermCriteria::COUNT && i>=cond.maxCount) || (cond.type == cv::TermCriteria::EPS && lastcost-cost<cond.epsilon))
//            break;

//        j_k1x = f_cube*para.s*xt.mul(d)/wt_cube;
//        j_k1y = f_cube*yt.mul(d)/wt_cube;
//        mat_temp = (1+3*para.k1*f_square*d/wt_square)/wt;
//        j_fx = para.s*xt.mul(mat_temp);
//        j_fy = yt.mul(mat_temp);
//        j_t3x = -1.0*para.f*para.s*xt.mul(mat_temp)/wt;
//        j_t3y = -1.0*para.f*yt.mul(mat_temp)/wt;

//        j_k1 = cv::sum(fx.mul(j_k1x))[0]+cv::sum(fy.mul(j_k1y))[0];
//        j_f = cv::sum(fx.mul(j_fx))[0]+cv::sum(fy.mul(j_fy))[0];
//        j_t3 = cv::sum(fx.mul(j_t3x))[0]+cv::sum(fy.mul(j_t3y))[0];

//        j2_k1 = cv::sum(j_k1x.mul(j_k1x))[0]+cv::sum(j_k1y.mul(j_k1y))[0];
//        mat_temp = 6*para.k1*para.f*d/wt_cube;
//        j2_f = cv::sum(j_fx.mul(j_fx)+fx.mul(para.s*mat_temp.mul(xt)))[0]+cv::sum(j_fy.mul(j_fy)+fy.mul(mat_temp.mul(yt)))[0];
//        mat_temp = 2*para.f*(1+6*para.k1*f_square*d/wt_square)/wt_cube;
//        j2_t3 = cv::sum(j_t3x.mul(j_t3x)+fx.mul(para.s*mat_temp.mul(xt)))[0]+cv::sum(j_t3y.mul(j_t3y)+fy.mul(mat_temp.mul(yt)))[0];
//        mat_temp = 3*f_square*d/wt_cube;
//        j2_k1_f = cv::sum(j_k1x.mul(j_fx)+fx.mul(para.s*mat_temp.mul(xt)))[0]+cv::sum(j_k1y.mul(j_fy)+fy.mul(mat_temp.mul(yt)))[0];
//        mat_temp = 3*f_cube*d/wt_4thpower;
//        j2_k1_t3 = cv::sum(j_k1x.mul(j_t3x)-fx.mul(para.s*mat_temp.mul(xt)))[0]+cv::sum(j_k1y.mul(j_t3y)-fy.mul(mat_temp.mul(yt)))[0];
//        mat_temp = (1+9*para.k1*f_square*d/wt_square)/wt_square;
//        j2_f_t3 = cv::sum(j_fx.mul(j_t3x)-fx.mul(para.s*mat_temp.mul(xt)))[0]+cv::sum(j_fy.mul(j_t3y)-fy.mul(mat_temp.mul(yt)))[0];

//        hessian(0,0) = j2_k1;
//        hessian(0,1) = j2_k1_f;
//        hessian(0,2) = j2_k1_t3;
//        hessian(1,0) = j2_k1_f;
//        hessian(1,1) = j2_f;
//        hessian(1,2) = j2_f_t3;
//        hessian(2,0) = j2_k1_t3;
//        hessian(2,1) = j2_f_t3;
//        hessian(2,2) = j2_t3;
//        hessian_inv = hessian.inv();

//        gradient(0) = j_k1;
//        gradient(1) = j_f;
//        gradient(2) = j_t3;

//        newtonstep = hessian_inv*gradient;
//        para.k1 -= newtonstep(0);
//        para.f -= newtonstep(1);
//        para.t3 -= newtonstep(2);
//    }
    //----------------------------------------------------------------------------------------------------------------------
    if (cost > lastcost)
        printf("abnormal exit: cost=%.15f,lastcost=%.15f\n", cost, lastcost);
    return cost;
}

/*******************************************************************************************************
Function: iterateImageCenter()
Description: iterate image center until get minimum cost value
Input:  wcPts, a vector of OpenCV Point2f data struct, points position in world coordinates
        pcPts, a vector of OpenCV Point2f data struct, points position in camera coordinates
        para, struct cameraPara, includes all camera parameters
        cord, 'X' or 'Y' indicating iterate direction
Output: minimum value of cost function
*******************************************************************************************************/
float iterateImageCenter(std::vector<cv::Point2f> wcPts, std::vector<cv::Point2f> pcPts, cameraPara &para,
                         enum cordinate cord) {
    //---------------------------------------------- algorithm explanation, comment 8 --------------------------------------
    float factor = sqrt(10.0);
    float stepLimit = 0.003;
    float cost[3];
    cv::TermCriteria cond(cv::TermCriteria::EPS, 10, 0.00000001);

    float step = 0.1;

    cv::Point2f cmpPts[3];
    cmpPts[1].x = para.x0;
    cmpPts[1].y = para.y0;
    if (cord == Cord_X) {
        cmpPts[0].x = cmpPts[1].x - step;
        cmpPts[0].y = cmpPts[1].y;
        cmpPts[2].x = cmpPts[1].x + step;
        cmpPts[2].y = cmpPts[1].y;
    } else {
        cmpPts[0].x = cmpPts[1].x;
        cmpPts[0].y = cmpPts[1].y - step;
        cmpPts[2].x = cmpPts[1].x;
        cmpPts[2].y = cmpPts[1].y + step;
    }
    for (int i = 0; i < 3; i++) {
        para.x0 = cmpPts[i].x;
        para.y0 = cmpPts[i].y;
        if (tsaiCalibStep1(wcPts, pcPts, para))
            cost[i] = tsaiCalibStep2(wcPts, pcPts, para, 1.0, cond);
        else
            cost[i] = 1000000.0;
    }
    while (1) {
        if (cost[0] < cost[1] && cost[0] < cost[2]) {
            cost[2] = cost[1];
            cmpPts[2] = cmpPts[1];
            cost[1] = cost[0];
            cmpPts[1] = cmpPts[0];
            if (cord == Cord_X) {
                cmpPts[0].x = cmpPts[1].x - step;
            } else {
                cmpPts[0].y = cmpPts[1].y - step;
            }
            para.x0 = cmpPts[0].x;
            para.y0 = cmpPts[0].y;
            if (tsaiCalibStep1(wcPts, pcPts, para))
                cost[0] = tsaiCalibStep2(wcPts, pcPts, para, 1.0, cond);
            else
                cost[0] = 1000000.0;
        } else if (cost[2] < cost[0] && cost[2] < cost[1]) {
            cost[0] = cost[1];
            cmpPts[0] = cmpPts[1];
            cost[1] = cost[2];
            cmpPts[1] = cmpPts[2];
            if (cord == Cord_X) {
                cmpPts[2].x = cmpPts[1].x + step;
            } else {
                cmpPts[2].y = cmpPts[1].y + step;
            }
            para.x0 = cmpPts[2].x;
            para.y0 = cmpPts[2].y;
            if (tsaiCalibStep1(wcPts, pcPts, para))
                cost[2] = tsaiCalibStep2(wcPts, pcPts, para, 1.0, cond);
            else
                cost[2] = 1000000.0;
        } else {
            if (step <= stepLimit)
                break;
            else {
                step = step / factor;
                if (cord == Cord_X) {
                    cmpPts[0].x = cmpPts[1].x - step;
                    cmpPts[2].x = cmpPts[1].x + step;
                } else {
                    cmpPts[0].y = cmpPts[1].y - step;
                    cmpPts[2].y = cmpPts[1].y + step;
                }
                para.x0 = cmpPts[0].x;
                para.y0 = cmpPts[0].y;
                if (tsaiCalibStep1(wcPts, pcPts, para))
                    cost[0] = tsaiCalibStep2(wcPts, pcPts, para, 1.0, cond);
                else
                    cost[0] = 1000000.0;
                para.x0 = cmpPts[2].x;
                para.y0 = cmpPts[2].y;
                if (tsaiCalibStep1(wcPts, pcPts, para))
                    cost[2] = tsaiCalibStep2(wcPts, pcPts, para, 1.0, cond);
                else
                    cost[2] = 1000000.0;
            }
        }
    }
    para.x0 = cmpPts[1].x;
    para.y0 = cmpPts[1].y;

    return cost[1];
}

/*******************************************************************************************************
Function: iterateFactorS()
Description: iterate camera parameter 's' until get minimum cost value
Input:  wcPts, a vector of OpenCV Point2f data struct, points position in world coordinates
        pcPts, a vector of OpenCV Point2f data struct, points position in camera coordinates
        para, struct cameraPara, includes all camera parameters
Output: minimum value of cost function
*******************************************************************************************************/
float iterateFactorS(std::vector<cv::Point2f> wcPts, std::vector<cv::Point2f> pcPts, cameraPara &para) {
    //---------------------------------------------- algorithm explanation, comment 7 --------------------------------------
    float sign;
    float cost, lastCost, lastS;
    cv::TermCriteria cond(cv::TermCriteria::EPS, 10, 0.00000001);

    tsaiCalibStep1(wcPts, pcPts, para);
    cost = tsaiCalibStep2(wcPts, pcPts, para, 1.0, cond);
    lastCost = cost;
    lastS = para.s;
    para.s += 0.05;
    if (tsaiCalibStep1(wcPts, pcPts, para))
        cost = tsaiCalibStep2(wcPts, pcPts, para, 1.0, cond);
    else
        cost = 1000000.0;
    if (std::isnan(cost) || std::isinf(cost) || cost > lastCost) {
        para.s = lastS - 0.05;
        sign = -1.0f;
        if (tsaiCalibStep1(wcPts, pcPts, para))
            cost = tsaiCalibStep2(wcPts, pcPts, para, 1.0, cond);
        else
            cost = 1000000.0;
        printf("%f\t%f\t\n", cost, para.s);
        if (std::isnan(cost) || std::isinf(cost) || cost > lastCost) {
            para.s = lastS;
            return lastCost;
        }
    } else
        sign = 1.0f;

    do {
        lastS = para.s;
        para.s += sign * (0.005);
        lastCost = cost;
        if (tsaiCalibStep1(wcPts, pcPts, para))
            cost = tsaiCalibStep2(wcPts, pcPts, para, 1.0, cond);
        else
            cost = 1000000.0;
    } while (!std::isnan(cost) && !std::isinf(cost) && cost < lastCost);
    para.s = lastS;
    return lastCost;
}

/*******************************************************************************************************
Function: calibCamera()
Description: calibration camera to get camera parameters
Input:  imgBuffer, an unsigned char array storing image
        pixelformat, fourcc format of input image, current support formats: YUYV,RGB,BGR,RGBA,BGRA
        imgWidth, width of input image
        imgHeight, height of input image
        contrast,darkness: adjust image's contrast and brightness in case the chessboard image is not clear enough
        wcPts, coordinates in world coordinate of reference points
        ptscntRow, reference points count per column
        ptscntColumn, reference points count per row
        camPara, camera parameter struct.
        outputBuffer, an unsigned char array storing image, marked with redrawed points with camera parameters
Output: return false if finding chessboard corners fail, or there's any INF/NaN number in camera parameter
*******************************************************************************************************/
bool calibCamera(unsigned char *imgBuffer, unsigned int pixelformat, int imgWidth, int imgHeight, float contrast,
                 int darkness, std::vector<cv::Point2f> wcPts, int ptscntRow, int ptscntColumn, cameraPara &camPara,
                 unsigned char *outputBuffer) {
    cv::Mat rawImg, img, outputImg;

    switch (pixelformat) {
        case GL_RGB:
            rawImg.create(imgHeight, imgWidth, CV_8UC3);
            memcpy(rawImg.data, imgBuffer, sizeof(unsigned char) * imgWidth * imgHeight * 3);
            cv::cvtColor(rawImg, img, CV_RGB2GRAY);
            break;
        case V4L2_PIX_FMT_YUYV:
            rawImg.create(imgHeight, imgWidth, CV_8UC2);
            memcpy(rawImg.data, imgBuffer, sizeof(unsigned char) * imgWidth * imgHeight * 2);
            cv::cvtColor(rawImg, img, CV_YUV2RGBA_YUYV);
            cv::cvtColor(img, img, CV_RGBA2GRAY);
            break;
        case V4L2_PIX_FMT_BGR24:
            rawImg.create(imgHeight, imgWidth, CV_8UC3);
            memcpy(rawImg.data, imgBuffer, sizeof(unsigned char) * imgWidth * imgHeight * 3);
            cv::cvtColor(img, img, CV_BGR2GRAY);
            break;
        case V4L2_PIX_FMT_RGB24:
            rawImg.create(imgHeight, imgWidth, CV_8UC3);
            memcpy(rawImg.data, imgBuffer, sizeof(unsigned char) * imgWidth * imgHeight * 3);
            cv::cvtColor(img, img, CV_RGB2GRAY);
            break;
//        case V4L2_PIX_FMT_BGRA32:
//            rawImg.create(imgHeight, imgWidth, CV_8UC4);
//            memcpy(rawImg.data, imgBuffer, sizeof(unsigned char)*imgWidth*imgHeight*4);
//            cv::cvtColor(img, img, CV_BGRA2GRAY);
//            break;
//        case V4L2_PIX_FMT_RGBA32:
//            rawImg.create(imgHeight, imgWidth, CV_8UC4);
//            memcpy(rawImg.data, imgBuffer, sizeof(unsigned char)*imgWidth*imgHeight*4);
//            cv::cvtColor(img, img, CV_RGBA2GRAY);
//            break;
        default:
            printf("image format not support!\n");
            return false;
    }
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            img.at<uchar>(y, x) = cv::saturate_cast<uchar>(contrast * (img.at<uchar>(y, x)) - darkness);
        }
    }

    std::vector<cv::Point2f> corners;
    bool patternfound = cv::findChessboardCorners(img, cv::Size(ptscntColumn, ptscntRow), corners);
    if (!patternfound) {
        printf("no chessboard corners found!\n");
        return false;
    }

    for (int i = 0; i < ptscntColumn * ptscntRow; i++) {
        corners[i].x = 2 * corners[i].x / img.size().width - 1.0;
        corners[i].y = 1.0 - 2 * corners[i].y / img.size().height;
    }

    camPara.x0 = 0;
    camPara.y0 = 0;
    camPara.s = 1.0;
    float cost;
    cv::Point2f lastOrigin;
    do {
        lastOrigin.x = camPara.x0;
        lastOrigin.y = camPara.y0;
        cost = iterateFactorS(wcPts, corners, camPara);
        cost = iterateImageCenter(wcPts, corners, camPara, Cord_X);
        cost = iterateImageCenter(wcPts, corners, camPara, Cord_Y);
    } while (lastOrigin.x != camPara.x0 || lastOrigin.y != camPara.y0);

    cv::TermCriteria cond(cv::TermCriteria::EPS, 5, 0.0000000001);
    if(tsaiCalibStep1(wcPts, corners, camPara) == false){
        printf("#Error tsaiCalibStep1\n");
        return false;
    }
    cost = tsaiCalibStep2(wcPts, corners, camPara, 1.0, cond);

    if (!isValidNumber(camPara.r11)) {
        printf("Parameter r11 is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.r12)) {
        printf("Parameter r12 is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.r21)) {
        printf("Parameter r21 is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.r22)) {
        printf("Parameter r22 is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.r31)) {
        printf("Parameter r31 is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.r32)) {
        printf("Parameter r32 is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.t1)) {
        printf("Parameter t1 is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.t2)) {
        printf("Parameter t2 is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.t3)) {
        printf("Parameter t3 is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.f)) {
        printf("Parameter f is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.s)) {
        printf("Parameter s is NaN!!\n");
        return false;
    }
    if (!isValidNumber(camPara.k1)) {
        printf("Parameter k1 is NaN!!\n");
        return false;
    }

    std::vector<cv::Point2f> drawPts(ptscntColumn * ptscntRow);
    float xp, yp;
    for (int i = 0; i < ptscntColumn * ptscntRow; i++) {
        xp = camPara.f * (camPara.r11 * wcPts[i].x + camPara.r12 * wcPts[i].y + camPara.t1) /
             (camPara.r31 * wcPts[i].x + camPara.r32 * wcPts[i].y + camPara.t3) + camPara.x0;
        yp = camPara.f * (camPara.r21 * wcPts[i].x + camPara.r22 * wcPts[i].y + camPara.t2) /
             (camPara.r31 * wcPts[i].x + camPara.r32 * wcPts[i].y + camPara.t3) + camPara.y0;
        drawPts[i].x = xp * (1 + camPara.k1 * (xp * xp + yp * yp));
        drawPts[i].y = yp * (1 + camPara.k1 * (xp * xp + yp * yp));
    }

    cv::cvtColor(img, outputImg, CV_GRAY2RGBA);
    for (int i = 0; i < ptscntColumn * ptscntRow; i++) {
        cv::circle(outputImg, cv::Point((drawPts[i].x + 1.0) * img.size().width / 2.0,
                                        (1.0 - drawPts[i].y) * img.size().height / 2.0), 5, CV_RGB(255, 0, 0), 2);
    }


    memcpy(outputBuffer, outputImg.data, sizeof(unsigned char) * imgWidth * imgHeight * 4);

    return true;
}

int Tsai::init(cv::Mat cb_source, int aqXnum, int aqYnum) {
    std::vector<cv::Point2f> wcPts(aqXnum * aqYnum);
    float step = 5.0f;
    int k = 0;
    for (int i = 0; i < aqYnum; i++) {
        for (int j = 0; j < aqXnum; j++, k++) {
            wcPts[k].x = (j - aqXnum / 2) * step;
            wcPts[k].y = (aqYnum - i) * step;
        }
    }
    unsigned char *outputBuffer = (unsigned char *) malloc(sizeof(unsigned char) * cb_source.size().width * cb_source.size().height * 4);
    cameraPara camPara;
    if (calibCamera(cb_source.data, GL_RGB, cb_source.size().width, cb_source.size().height, 1.0, 0, wcPts, aqYnum, aqXnum,
                    camPara, outputBuffer)) {
        printf("r11=%f\n", camPara.r11);
        printf("r12=%f\n", camPara.r12);
        printf("r21=%f\n", camPara.r21);
        printf("r22=%f\n", camPara.r22);
        printf("r31=%f\n", camPara.r31);
        printf("r32=%f\n", camPara.r32);
        printf("t1=%f\n", camPara.t1);
        printf("t2=%f\n", camPara.t2);
        printf("t3=%f\n", camPara.t3);
        printf("f=%f\n", camPara.f);
        printf("s=%f\n", camPara.s);
        printf("k1=%f\n", camPara.k1);
        printf("x0=%f\n", camPara.x0);
        printf("y0=%f\n", camPara.y0);
    }

    cv::Mat cb_final;
    cb_final.create(cb_source.size().height, cb_source.size().width, CV_8UC4);
    memcpy(cb_final.data, outputBuffer, sizeof(unsigned char) * cb_source.size().width * cb_source.size().height * 4);
    ResourceManager::loadTextureVision("cb_final", &cb_final);
}
