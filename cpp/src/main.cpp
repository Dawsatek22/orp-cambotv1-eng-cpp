// this is the main code for the orp-cambotv1
// it uses a combination of all the testcode executables

#include <fcntl.h>
#include <libevdev/libevdev.h>
#include <stdio.h>
#include <cstdlib>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <iostream>
#include <PiPCA9685/PCA9685.h>

#include <opencv2/opencv.hpp> 
#include <libcamera_app.hpp> 
#include <lccv.hpp>

using namespace std;

/* // below are the pin values for the M1 and m4 motors channels
the pin for the motor drivers
you can switch the pin numbers if the motors are not driving
in the right diretion
*/
// pins for the m1 motor channel
int m1_ch1 = 15; 
int m1_ch2 = 14;

// pins for the m2 motor channel
int m2_ch1 = 8;
int m2_ch2 = 9;

// the PCA9685 class instance is made
 PiPCA9685::PCA9685 pca{"/dev/i2c-1", 0x5f};


// the motor direction functions are made 

void left() {


 pca.set_pwm(m1_ch1,0,0);
 pca.set_pwm(m1_ch2,0,1000);
 

pca.set_pwm(m2_ch1,0,0);
 pca.set_pwm(m2_ch2,0,0);
 
std::cout<<"motor goes left"<< std::endl;

}

void right() {


 pca.set_pwm(m1_ch1,0,0);
 pca.set_pwm(m1_ch2,0,0);
 

pca.set_pwm(m2_ch1,0,0);
 pca.set_pwm(m2_ch2,0,1000);
 
std::cout<<"motor  goes right"<< std::endl;

}

// the motor direction functions are made 
void backward() {


 pca.set_pwm(m1_ch1,0,1000);
 pca.set_pwm(m1_ch2,0,0);
 

pca.set_pwm(m2_ch1,0,1000);
 pca.set_pwm(m2_ch2,0,0);
 
std::cout<<"motor  goes backwards"<< std::endl;

}



void stop() {
 pca.set_pwm(m1_ch1,0,0);
 pca.set_pwm(m1_ch2,0,0);




pca.set_pwm(m2_ch1,0,0);
 pca.set_pwm(m2_ch2,0,0);
 
 std::cout<<"motor  stopped"<< std::endl;

}

void forwards() {


 pca.set_pwm(m1_ch1,0,0);
 pca.set_pwm(m1_ch2,0,1000);


 pca.set_pwm(m2_ch1,0,0);
 pca.set_pwm(m2_ch2,0,1000);
  std::cout<<"motor forward "<< std::endl;
}




int main() {


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

struct libevdev *dev = NULL;
int fd;
int rc = 1;
// button values for a xbox one game pad

 int a_btn = BTN_SOUTH; // A button
 int b_btn = BTN_EAST; // B button
 int x_btn = BTN_NORTH; // X button 
 int y_btn = BTN_WEST; // Y button 
 int lb_Btn = BTN_TL ; // LB button 

 int rb_btn = BTN_TR; // RB button
 
fd = open("/dev/input/event4", O_RDONLY|O_NONBLOCK); 
rc = libevdev_new_from_fd(fd, &dev);
if (rc < 0) {
        fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
        exit(1);
}
printf("Input device name: \"%s\"\n", libevdev_get_name(dev));
printf("Input device ID: bus %#x vendor %#x product %#x\n",
       libevdev_get_id_bustype(dev),
       libevdev_get_id_vendor(dev),
       libevdev_get_id_product(dev));
// checks if gamepad is available
if (!libevdev_has_event_type(dev, EV_SYN) ||
    !libevdev_has_event_code(dev, EV_KEY,a_btn)) {
        printf("This device does not look like a gamepad\n");
        exit(1);
}
 
while (true) {
        struct input_event ev;
        rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);

       
                
if (!cam.getVideoFrame(frame,1000)) {
cout << "frame not openend"<<'\n';

}
else {
    imshow("webcam_test1",frame);
}

              // here are the button presses printed 
              // here are the button events(some code is removed to make the code shorter and readable)
              if (ev.code == x_btn)  {
                 stop();
                  printf("X was pressed.");
              }
            
                  if (ev.code == a_btn)  {
                 backward();
                  printf("A was pressed.");
                 
                  }
                
                     if (ev.code == y_btn)  {
                 forwards();
                  printf("Y was pressed.");
            
                  }
                        if (ev.code == lb_Btn)  {
                  left();
                  printf("LB was pressed.");
                 
                  }


                           if (ev.code == rb_btn)  {
                  right();
                  printf("RB was pressed.");
                  
                  }
if (cv::waitKey(1) == 'q') {
   

cam.stopVideo();
cv::destroyAllWindows();
break;
}
          

            }}