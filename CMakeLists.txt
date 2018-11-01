cmake_minimum_required(VERSION 3.10)
project(Blizzard)

set(CMAKE_CXX_STANDARD 14)

#common setting
include_directories(blizzard/lib)
include_directories(blizzard/src)
include_directories(blizzard/comm)
include_directories(module/opencv)

find_package(OpenCV REQUIRED)
find_package(glfw3 REQUIRED)
#cmake for bootanimation
#[[aux_source_directory(blizzard/lib/glad BOOTANIMATION_SOURCE_FILES)
aux_source_directory(blizzard/lib/stb_image BOOTANIMATION_SOURCE_FILES)
aux_source_directory(blizzard/src BOOTANIMATION_SOURCE_FILES)
aux_source_directory(module/persioncv/vision BOOTANIMATION_SOURCE_FILES)
aux_source_directory(samples/animation BOOTANIMATION_SOURCE_FILES)

add_executable(bootanimation ${BOOTANIMATION_SOURCE_FILES})

target_link_libraries(bootanimation glfw
        -lpthread
        glfw
        ${OpenCV_LIBS}
        -lopencv_highgui
        -lopencv_highgui
        -lopencv_calib3d
        -lopencv_features2d
        -lopencv_flann
        -lopencv_imgproc
        -lopencv_core
        -lopencv_imgcodecs)]]

#cmake for camera
aux_source_directory(blizzard/lib/glad CAMERA_SOURCE_FILES)
aux_source_directory(blizzard/src CAMERA_SOURCE_FILES)
aux_source_directory(module/opencv/vision CAMERA_SOURCE_FILES)
aux_source_directory(samples/camera/src CAMERA_SOURCE_FILES)

add_executable(camera ${CAMERA_SOURCE_FILES})

target_link_libraries(camera glfw
        -lpthread
        glfw
        ${OpenCV_LIBS}
        -lopencv_highgui
        -lopencv_highgui
        -lopencv_calib3d
        -lopencv_features2d
        -lopencv_flann
        -lopencv_imgproc
        -lopencv_core
        -lopencv_imgcodecs)
