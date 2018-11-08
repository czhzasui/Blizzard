//
// Created by czh on 18-10-19.
//

#include <resource_manager.h>
#include "zhang.h"

int Zhang::init(cv::Mat cb_source, int aqXnum, int aqYnum) {

    cv::imwrite("../samples/camera/res/cb_source.png", cb_source);

    printf("#Start scan corner\n");
    cv::Mat img;
    std::vector<cv::Point2f> image_points;
    std::vector<std::vector<cv::Point2f>> image_points_seq; /* 保存检测到的所有角点 */
    if (cv::findChessboardCorners(cb_source, cv::Size(aqXnum, aqYnum), image_points) == 0) {
        printf("#Error: Corners not find ");
        return 0;
    } else {
        cvtColor(cb_source, img, CV_RGBA2GRAY);
        cv::imwrite("../samples/camera/res/cb_gray.png", img);
        //find4QuadCornerSubpix(img, image_points, cv::Size(5, 5));

        cv::cornerSubPix(img, image_points, cv::Size(11, 11), cv::Size(-1, -1),
                         cv::TermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 30, 0.01));

        image_points_seq.push_back(image_points);

        cv::Mat cb_corner;
        cb_corner = cb_source.clone();
        drawChessboardCorners(cb_corner, cv::Size(aqXnum, aqYnum), image_points, true);
        cv::imwrite("../samples/camera/res/cb_corner.png", cb_corner);
    }

    printf("#Start calibrate\n");
    cv::Size square_size = cv::Size(14.2222, 12);
    std::vector<std::vector<cv::Point3f>> object_points; /* 保存标定板上角点的三维坐标 */
    cv::Mat inMat = cv::Mat(3, 3, CV_32FC1, cv::Scalar::all(0)); /* 摄像机内参数矩阵 */
    cv::Mat distCoeffs = cv::Mat(1, 5, CV_32FC1, cv::Scalar::all(0)); /* 摄像机的5个畸变系数：k1,k2,p1,p2,k3 */
    std::vector<cv::Mat> tvecsMat;  /* 每幅图像的平移向量 */
    std::vector<cv::Mat> rvecsMat;  /* 每幅图像的旋转向量 */

    cv::Mat R33;

    std::vector<cv::Point3f> realPoint;
    for (int i = 0; i < aqYnum; i++) {
        for (int j = 0; j < aqXnum; j++) {
            cv::Point3f tempPoint;
            /* 假设标定板放在世界坐标系中z=0的平面上 */
            tempPoint.x = i * square_size.width;
            tempPoint.y = j * square_size.height;
            tempPoint.z = 0;
            realPoint.push_back(tempPoint);
        }
    }
    object_points.push_back(realPoint);

    printf("#objectPoints： %ld\n", sizeof(object_points[0]));
    std::cout << object_points[0] << std::endl;

    printf("#image_points： %ld\n", sizeof(image_points_seq[0]));
    std::cout << image_points << std::endl;

    printf("#image size\n");
    std::cout << SCREEN_WIDTH << "*" << SCREEN_HEIGHT << std::endl;

    cv::calibrateCamera(object_points, image_points_seq, cb_source.size(), inMat, distCoeffs, rvecsMat, tvecsMat,
                        CV_CALIB_FIX_K3);


    cv::Rodrigues(rvecsMat[0], R33);
    std::cout << "rvecsMat:\n" << rvecsMat[0] << std::endl;
    std::cout << "tvecsMat:\n" << tvecsMat[0] << std::endl;
    std::cout << "R33:\n" << R33 << std::endl;



    std::cout << "#inMat:\n" << inMat << std::endl;
    std::cout << "#distCoeffs:\n" << distCoeffs << std::endl;

    cv::Mat cb_final;

    cv::Mat mapx = cv::Mat(cb_source.size(), CV_32FC1);
    cv::Mat mapy = cv::Mat(cb_source.size(), CV_32FC1);
    cv::Mat R = cv::Mat::eye(3, 3, CV_32F);
    initUndistortRectifyMap(inMat, distCoeffs, R, cv::Mat(), cb_source.size(), CV_32FC1,
                            mapx, mapy);
    cv::remap(cb_source, cb_final, mapx, mapy, cv::INTER_LINEAR);

    //undistort(cb_source, cb_final, inMat, distCoeffs);

    cv::imwrite("../samples/camera/res/cb_final.png", cb_final);
    ResourceManager::loadTexture2D("cb_final", cb_final);
    cv::Mat cb_gray = Vision::read("../samples/camera/res/cb_gray.png");
    ResourceManager::loadTexture2D("cb_gray", cb_gray);
    cv::Mat cb_corner = Vision::read("../samples/camera/res/cb_corner.png");
    ResourceManager::loadTexture2D("cb_corner", cb_corner);

    return 0;
}
