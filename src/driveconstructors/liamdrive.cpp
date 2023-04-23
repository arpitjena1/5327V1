#include "main.h"

// drivetrain motors
pros::Motor left_front_motor(2, pros::E_MOTOR_GEARSET_18, false); // port 1, blue gearbox, not reversed
pros::Motor left_back_motor(1, pros::E_MOTOR_GEARSET_18, false); // port 2, green gearbox, not reversed
pros::Motor right_front_motor(3, pros::E_MOTOR_GEARSET_18, true); // port 3, red gearbox, reversed
pros::Motor right_back_motor(11, pros::E_MOTOR_GEARSET_18, true); // port 4, red gearbox, reversed
 
// drivetrain motor groups
pros::MotorGroup left_side_motors({left_front_motor, left_back_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_back_motor});
 
lemlib::Drivetrain_t drivetrain {
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    11.5, // track width
    3.25, // wheel diameter
    200 // wheel rpm
};
 
// left tracking wheel encoder
pros::ADIEncoder left_enc('C', 'D', true); // ports A and B, reversed
// right tracking wheel encoder
pros::ADIEncoder right_enc('G', 'H', false); // port 1, not reversed
// back tracking wheel encoder
pros::ADIEncoder back_enc('A', 'B', true); // ports C and D, not reversed
 
// left tracking wheel
lemlib::TrackingWheel left_tracking_wheel(&left_enc, 2.75, -2.5); // 2.75" wheel diameter, -4.6" offset from tracking center
// right tracking wheel
lemlib::TrackingWheel right_tracking_wheel(&right_enc, 2.75, 2.5); // 2.75" wheel diameter, 1.7" offset from tracking center
lemlib::TrackingWheel back_tracking_wheel(&back_enc, 2.75, -4.75); // 2.75" wheel diameter, 4.5" offset from tracking center
 
// inertial sensor
pros::Imu inertial_sensor(10); // port 2
 
// odometry struct
lemlib::OdomSensors_t sensors {
    &left_tracking_wheel, // vertical tracking wheel 1
    &right_tracking_wheel, // vertical tracking wheel 2
    &back_tracking_wheel, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};
 
// forward/backward PID
lemlib::ChassisController_t lateralController {
    25, // kP
    10, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    25, // kP
    10, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};
 
 
// create the chassis
lemlib::Chassis lemchassis(drivetrain, lateralController, angularController, sensors);

void screen() {
    // loop forever
    while (true) {
        lemlib::Pose pose = lemchassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}


void leminit(){
    lemchassis.calibrate(); // calibrate the chassis
    lemchassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0
	pros::Task screenTask(screen);
}