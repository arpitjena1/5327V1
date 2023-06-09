#include "customauton.hpp"
void AWP(){
    // Grab right alliance mogo
    profiler->setTarget(10_in, true);
    profiler->waitUntilSettled();
    turnToAngle(-45_deg);
    
}

void highBranch(){
    // Push neutral mogo back & collect rings
    profiler->setTarget(-2.5_ft, true);
    topBranchController->setTarget(TopBranchPosition::LOADINGHEIGHT);
    pros::delay(250);
    liftController->setTarget(LiftPosition::LOADINGHEIGHT);
    pros::delay(750);
    profiler->setTarget(26_in, true);
    leftNeedle.set(true); rightNeedle.set(true);

    // Align with tall neutral mogo 
    liftController->setTarget(LiftPosition::TOPBRANCH);
    //profiler->setTarget(curveToTallMogo, true);
    turnToAngle(0_deg);
    profiler->setTarget(0.405_ft, true);
    turnToAngle(270_deg);
    leftDrive.moveVoltage(-4500); rightDrive.moveVoltage(-4500); pros::delay(800); leftDrive.moveVoltage(0); rightDrive.moveVoltage(0);
    
    // Deploy rings
    backClamp.set(true); pros::delay(250); tilter.set(true);
    topBranchController->setTarget(TopBranchPosition::TOPBRANCH);
    pros::delay(2000);
    leftNeedle.set(false); rightNeedle.set(false);

    pros::delay(400);
    
    // Oscillate
    for(int i = 0; i < 6; i++) {
        leftDrive.moveVoltage(8000); rightDrive.moveVoltage(-8000);
        pros::delay(700);
        leftDrive.moveVoltage(-8000); rightDrive.moveVoltage(8000);
        pros::delay(700);
    }
    leftDrive.moveVoltage(0); rightDrive.moveVoltage(0);
}