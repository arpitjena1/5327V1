#pragma once
#include "ryanlib/api.hpp"
#include "okapi/api.hpp"
#include "globals.hpp"
#include "Drive.hpp"
using namespace okapi;

/**
 * @brief LRT AWP Auton - grabs the side mobile, then grabs a neutral mobile goal
 * 
 */
void AWP();

/**
 * @brief LRT High Branch Auton, drives back, loads the preload rings, then curves to the center mogo and deposit
 * 
 */
void highBranch();