/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Joey0                                                     */
/*    Created:      1/12/2026, 7:43:30 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor leftMotorA = motor(PORT5, ratio18_1, false);
motor leftMotorB = motor(PORT7, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT6, ratio18_1, true);
motor rightMotorB = motor(PORT8, ratio18_1, true);
motor cluster1 = motor(PORT11, ratio18_1, false);
motor cluster2 = motor(PORT12, ratio18_1, false);
motor cluster3 = motor(PORT13, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
controller ControllerDtrain = controller(primary);
controller ControllerMech = controller(partner);
//mech is slave

motor dtrainMotors[4] = {leftMotorA, leftMotorB, rightMotorA, rightMotorB};
//master motor group

// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
// void playVexcodeSound(const char *soundName) {
//   std::cout << "VEXPlaySound" << soundName;
//   wait(5, msec);
// }



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
#pragma endregion VEXcode Generated Robot Configuration

#include <vex.h>
using namespace vex;

// A global instance of competition
competition Competition;

int axis3Pos;
int axis1Pos;
int axis4Pos;

void option1()
{
//X was pressed
  cluster1.spin(forward);
  cluster2.spin(forward);
  cluster3.spin(forward);
}

void option2()
{
  //A was pressed
  cluster1.spin(reverse);
  cluster2.spin(forward);
  cluster3.spin(forward);
}

void option3()
{
  //B was pressed
  cluster1.spin(forward);
  cluster2.spin(reverse);
  cluster3.spin(forward);
}

void option4()
{
  //Y was pressed
  cluster1.spin(forward);
  cluster2.spin(forward);
  cluster3.spin(reverse);
}

void option5()
{
  //Up was pressed
  cluster1.spin(reverse);
  cluster2.spin(forward);
  cluster3.spin(reverse);
}

void option6()
{
  //right was pressed
  cluster1.spin(forward);
  cluster2.spin(reverse);
  cluster3.spin(reverse);
}

void option7()
{
  //down was pressed
  cluster1.spin(reverse);
  cluster2.spin(reverse);
  cluster3.spin(forward);
}

void option8()
{
  //left was pressed
  cluster1.spin(reverse);
  cluster2.spin(reverse);
  cluster3.spin(reverse);
}

void r1WasPressed()
{
  cluster1.stop();
  cluster2.stop();
  cluster3.stop();
}

void Drive(int speed, int dir[4])
{
  int fixedSpeed = abs(speed);
  for(int i = 0; i < 4; i++)
  {
    dtrainMotors[i].setVelocity(fixedSpeed,percent);

    switch(dir[i])
    {
      case 0:
      dtrainMotors[i].spin(forward);
      break;

      case 1:
      dtrainMotors[i].spin(reverse);
      break;

      default:
      //shit broke, too high a num
      break;
    }
  }
}


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  leftMotorA.setMaxTorque(100,percent);
  leftMotorB.setMaxTorque(100,percent);
  rightMotorA.setMaxTorque(100,percent);
  rightMotorB.setMaxTorque(100,percent);

  cluster1.setMaxTorque(100,percent);
  cluster2.setMaxTorque(100,percent);
  cluster3.setMaxTorque(100,percent);

  cluster1.setVelocity(100,percent);
  cluster2.setVelocity(100,percent);
  cluster3.setVelocity(100,percent);
  
  //return void;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}
//meowffd
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    axis3Pos = ControllerDtrain.Axis3.position();
    axis1Pos = ControllerDtrain.Axis1.position();
    axis4Pos = ControllerDtrain.Axis4.position();
    //get controller inputs

    if(axis3Pos == 0 && axis1Pos == 0 && axis4Pos == 0)
    {
      leftMotorA.stop();
      leftMotorB.stop();
      rightMotorA.stop();
      rightMotorB.stop();

      leftMotorA.setVelocity(0,percent);
      leftMotorB.setVelocity(0,percent);
      rightMotorA.setVelocity(0,percent);
      rightMotorB.setVelocity(0,percent);
    }
    //no input so bot is stopped

    else 
    {
      if(axis3Pos > 0)
      {
       Drive(axis3Pos, (int[4]){0,0,0,0});
      }
      //drive straight forward
      if(axis3Pos < 0)
      {
        Drive(axis3Pos, (int[4]){1,1,1,1});
      }
      //drive straight backward

      if(axis1Pos > 0)
      {
      Drive(axis1Pos, (int[4]){0,0,1,1});
      }
      //right turn

      if(axis1Pos < 0)
      {
        Drive(axis1Pos, (int[4]){1,1,0,0});
      }
      //left turn

      if(axis4Pos > 0)
      {
        Drive(axis4Pos, (int[4]){0,1,1,0});
      }
      //strafe right

      if(axis4Pos < 0)
      {
        Drive(axis4Pos,(int[4]){1,0,0,1});
      }

    
  }

  ControllerMech.ButtonX.pressed(option1);
  ControllerMech.ButtonA.pressed(option2);
  ControllerMech.ButtonB.pressed(option3);
  ControllerMech.ButtonY.pressed(option4);

  ControllerMech.ButtonUp.pressed(option5);
  ControllerMech.ButtonRight.pressed(option6);
  ControllerMech.ButtonDown.pressed(option7);
  ControllerMech.ButtonLeft.pressed(option8);

  ControllerMech.ButtonR1.pressed(r1WasPressed);

  wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
} 
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  vexcodeInit();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  


  }

