
// this is a code to test the motors with joystick controls
#include <fcntl.h>
#include <libevdev/libevdev.h>
#include <stdio.h>
#include <cstdlib>
#include <errno.h>
#include <error.h>
#include <string.h>
#include <iostream>
#include <PiPCA9685/PCA9685.h>


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
 PiPCA9685::PCA9685 pca{"/dev/i2c-1", 0x5f}; // 0x5f is the robot hat default adress

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

struct libevdev *dev = NULL;
int fd;
int rc = 1;
// button values for  xbox one game pad
 
 int a_btn = BTN_SOUTH; // A button
 int b_btn = BTN_EAST; // B button
 int x_btn = BTN_NORTH; // X button 
 int y_btn = BTN_WEST; // Y button 
 int lb_Btn = BTN_TL ; // LB button 
 int lt_btn = ABS_BRAKE; // LT button
 int rb_btn = BTN_TR; // RB button
 int rt_btn = ABS_GAS; // RT button
 int select_btn = BTN_SELECT; // select button
 int start_btn = BTN_START; // start button
 int lstick_btn = BTN_THUMBL; // left joystick button 
 int rstick_btn = BTN_THUMBR; // right joystick button 
int y_arrow = ABS_HAT0Y; // up and down arrow button
int x_arrow = ABS_HAT0X; // left and right arrow button
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


   




          

            }}