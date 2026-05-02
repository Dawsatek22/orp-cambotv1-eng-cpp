// this is a c++ code to stream on the raspberry pi camera(module 2 currently)
// with opencv,libcamera,lccv libraries
#include <iostream> // to use the input and output stream
#include <opencv2/opencv.hpp> // to use opencv functions
#include <libcamera_app.hpp> // to use libcamera functions
#include <lccv.hpp> // to use lccv functions
// namsapcec
// using namespace cv;
using namespace std;

int  main() {

uint32_t num_cams = LibcameraApp::GetNumberCameras(); // checks for camera number
	cout << "Found "<< num_cams << " cameras." << std::endl;
    uint32_t width = 640; // width is setup
  uint32_t height = 480; // height is setup

  
 cv::Mat frame = cv::Mat(height, width, CV_8UC3); // camera object
  
// below are the camera setup
lccv::PiCamera cam(0);
cam.options->video_width=width;
    cam.options->video_height=height;
    cam.options->framerate=30;
    cam.options->verbose=true;
  cam.startVideo();
while (true) {


// checks if camera is available
if (!cam.getVideoFrame(frame,1000)) {
cout << "frame not openend"<<'\n';

}
else {
    cv::imshow("webcam_test1",frame);
}
if (cv::waitKey(1) == 'q') { // if pressed q the while loop breaks and the camera closes
   

cam.stopVideo();
cv::destroyAllWindows();
break;
}
}}
