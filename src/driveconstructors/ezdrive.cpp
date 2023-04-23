#include "main.h"


Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-2, -20}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{1, 11}

  // IMU Port
  ,10

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1.666

  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);

void ezdrive(){
    chassis.set_drive_brake(MOTOR_BRAKE_COAST);
    chassis.tank();
    while (true) {
        chassis.tank(); // Tank control
        printf("Gyro: %f \n", chassis.get_gyro());
        pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}

void ezinit(){
    chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
    chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
    chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
    default_constants(); // Set the drive to your own constants from autons.cpp!
    exit_condition_defaults(); // Set the exit conditions to your own constants from autons.cpp!
    chassis.initialize();
}