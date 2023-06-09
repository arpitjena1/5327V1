#pragma once
#include "ryanlib/api.hpp"
#include "okapi/api.hpp"
using namespace okapi;

#define LVGL_SCREEN_WIDTH 480
#define LVGL_SCREEN_HEIGHT 240

// CONSTANTS
const double DEADBAND = 0.0500;

namespace LiftPosition{
    const int MINHEIGHT = 0;
    const int LOADINGHEIGHT = 255;
    const int LOWBRANCH = 0; // TODO TUNE READING
    const int TOPBRANCH = 555; 
    const int MAXHEIGHT = 755;
};

namespace TopBranchPosition{
    const int STOWED = 0; 
    const int REST = -160;
    const int LOADINGHEIGHT = -830; 
    const int LOWBRANCH = 0; // TODO TUNE READING
    const int TOPBRANCH = -263; 
}

// CONTROLLER
extern Controller master;
extern Controller partner;

// MOTORS
extern MotorGroup leftDrive;
extern MotorGroup rightDrive;
extern MotorGroup lift;
extern Motor topBranch;
extern Motor roller;

// SENSORS
extern IMU imu; 
extern pros::Vision vision;

// PNEUMATICS
extern Pneumatics clamp;
extern Pneumatics backClamp;
extern Pneumatics tilter;
extern Pneumatics leftNeedle;
extern Pneumatics rightNeedle;

// MOTION PROFILE CONSTANTS
extern ProfileConstraint moveLimit;
extern ProfileConstraint turnLimit;
extern FFVelocityController leftController;
extern FFVelocityController rightController;

// SUBSYSTEM CONTROLLERS
extern std::shared_ptr<ChassisController> chassis;
extern std::shared_ptr<AsyncMotionProfiler> profiler;
extern std::shared_ptr<AsyncPositionController<double, double>> liftController;
extern std::shared_ptr<AsyncPositionController<double, double>> topBranchController;
extern std::shared_ptr<IterativePosPIDController> turnPID;

