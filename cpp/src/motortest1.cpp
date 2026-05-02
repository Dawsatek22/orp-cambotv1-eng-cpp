// this is a code to test the adeept robot hat v3
// to control motors with the pca9685 chip using
// the PiPCA9685 software(link is here: https://github.com/barulicm/PiPCA9685.git )
#include <PiPCA9685/PCA9685.h> // the header file for the  PiPCA9685
#include <iostream> // to use cout function
#include <unistd.h> // to use the sleep function


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


 // now the motors are tested

 pca.set_pwm_freq(50); // current frequency for the motors are set 50hz
// now the m1 and m2 motors are tested.

forwards();
sleep(3);
backward();
sleep(3);
left();
sleep(3);
right();
sleep(3);
stop();

 
 return 0;
}