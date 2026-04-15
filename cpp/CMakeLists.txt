cmake_minimum_required(VERSION 3.25.1 ) # the current version used
project(orp-cambotv1-eng)


set(CMAKE_CXX STANDARD 23) # the current set c++ standard
#below are the required pkgs
find_package(PiPCA9685 REQUIRED) #PCA9685 setup
find_package(OpenCV REQUIRED) # opencv pkg setup
find_package(PkgConfig REQUIRED) # pkg config setup
pkg_search_module(LIBEVDEV REQUIRED libevdev) # libevdev setup

pkg_check_modules(LIBCAMERA REQUIRED libcamera)
include_directories(${LIBCAMERA_INCLUDE_DIRS} ${OPENCV_INCLUDE_DIRS})

add_executable(mtest1 src/motortest1.cpp)
add_executable(joy src/joytest.cpp)
add_executable(joydrive src/joy_drivetest.cpp )
add_executable(camera_test1 src/cam_test.cpp)
add_executable(main src/main.cpp)
# below are the executable linked to the library
target_link_libraries(mtest1 PiPCA9685::PiPCA9685)
target_link_libraries(camera_test1 -llccv ${OpenCV_LIBS})
target_link_libraries(main  PRIVATE ${LIBEVDEV_LIBRARIES} -llccv ${OpenCV_LIBS} PiPCA9685::PiPCA9685)
target_link_libraries(joydrive PRIVATE ${LIBEVDEV_LIBRARIES}  PiPCA9685::PiPCA9685)
target_link_libraries(joy PRIVATE ${LIBEVDEV_LIBRARIES})
#below are the diretctories included to the executabels
target_include_directories(joy PRIVATE  ${LIBEVDEV_INCLUDE_DIRS})
target_include_directories(joydrive PRIVATE  ${LIBEVDEV_INCLUDE_DIRS})
target_include_directories(main  PRIVATE  ${LIBEVDEV_INCLUDE_DIRS})