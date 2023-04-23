#include "globals.hpp"
using namespace ryan;

// CONTROLLERS
Controller master(ControllerId::master);
Controller partner(ControllerId::partner);

// MOTORS
Motor leftFront(18, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees); 
Motor leftMiddle(9, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees); 
Motor leftBack(11, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees); 
Motor rightFront(16, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees); 
Motor rightMiddle(13, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightBack(6, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees); 

Motor intake(12, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

MotorGroup leftDrive({leftFront, leftMiddle, leftBack});
MotorGroup rightDrive({rightFront, rightMiddle, rightBack});
Motor liftBottom(6, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor liftTop(6, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor roller(10, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees); 
Motor topBranch(15, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees); 

MotorGroup lift({liftTop, liftBottom});

// SENSORS
IMU imu(8);
pros::Vision vision(16); 

// PNEUMATICS
Pneumatics clamp('F'); 
Pneumatics backClamp('C'); 
Pneumatics tilter('E'); 
Pneumatics leftNeedle('H'); 
Pneumatics rightNeedle('G'); 

// MOTION PROFILE CONSTANTS
ProfileConstraint moveLimit({3_ftps, 5_ftps2, 5_ftps2, 25_ftps3});
ProfileConstraint turnLimit({4.8_ftps, 17.5_ftps2, 17.5_ftps2, 25_ftps3});
FFVelocityController leftController(0.187, 0.04, 0.025, 4.35, 0.1); // TODO Tune for new chassis
FFVelocityController rightController(0.1915, 0.043, 0.02, 4, 0.1); // TODO Tune for new chassis

// SUBSYSTEM CONTROLLERS
std::shared_ptr<ChassisController> rchassis = ChassisControllerBuilder()
    .withMotors(leftDrive, rightDrive)
    .withDimensions({AbstractMotor::gearset::green, 5.0/7.0}, {{3.25_in, 1.294_ft}, imev5BlueTPR})
    .build();

std::shared_ptr<AsyncMotionProfiler> profiler = AsyncMotionProfilerBuilder()
    .withOutput(rchassis)
    .withProfiler(std::make_unique<SCurveMotionProfile>(moveLimit))
    .build();

std::shared_ptr<AsyncPositionController<double, double>> liftController = AsyncPosControllerBuilder()
    .withMotor(lift)
    .withGains({0.007, 0.0, 0.000075})
    .build();

std::shared_ptr<AsyncPositionController<double, double>> topBranchController = AsyncPosControllerBuilder()
    .withMotor(topBranch)
    .withMaxVelocity(0.5)
    .withGains({0.00685, 0.0, 0.000082})
    .build();

std::shared_ptr<IterativePosPIDController> turnPID = std::make_shared<IterativePosPIDController>(0.037, 0.0, 0.00065, 0, TimeUtilFactory::withSettledUtilParams(2, 2, 100_ms));

