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
    trackinglinePara = new TrackinglinePara;
    trackinglinePara->cameraProp = cameraParam;//相机参数
    trackinglinePara->staticLineProp = staticLineParam[0];//静态轨迹线参数
    trackinglinePara->dynamicLineProp = dynamicLineParam;//动态轨迹线参数
    trackinglinePara->vehicleProp = vehicleParam;//汽车参数
    trackinglinePara->swAngle = 20;//转向角
    trackinglinePara->hideOverlappingDynamicLine = false;

}

Trackline::~Trackline() {

}
