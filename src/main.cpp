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
  gps GPS = gps(PORT19, offsetx, offsety, mm, 180);
digital_out extendTrapdoor = digital_out(Brain.ThreeWirePort.G); 
digital_out extendGate = digital_out(Brain.ThreeWirePort.H);
digital_out retractGate = digital_out(Brain.ThreeWirePort.F)
//only need to extend it as of 2/21/26
motor leftMotorA = motor(PORT5, ratio18_1, false);
motor leftMotorB = motor(PORT3, ratio18_1, false);
motor rightMotorA = motor(PORT6, ratio18_1, true);
motor rightMotorB = motor(PORT8, ratio18_1, true);
motor cluster1 = motor(PORT11, ratio18_1, false);
motor cluster2 = motor(PORT12, ratio18_1, false);
motor cluster3 = motor(PORT13, ratio18_1, false);
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

int autonVer = 0;

void toHopper()
{
  //A was pressed
  //intake to hopper
  //make cluster3 slightly less aggressive for this
  cluster1.spin(reverse);
  cluster2.spin(forward);
  cluster3.spin(forward);
}

void toHighG()
{
  //X was pressed
  //hopper to highG and intake to highG
  cluster1.spin(reverse);
  cluster2.spin(forward);
  cluster3.spin(reverse);
}


void toLowG()
{
  //B was pressed
  //hoper to lowG
  cluster1.spin(reverse);
  cluster2.spin(reverse);
  cluster3.spin(forward);
}

void stopCluster()
{
  cluster1.stop();
  cluster2.stop();
  cluster3.stop();
}


void extendGateToggle()
{
    retractGate.set(false);
    extendGate.set(true);
}

void retractGateToggle()
{
  extendGate.set(false);
  retractGate.set(true);
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

  wait(0.5, seconds);

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

  GPS.calibrate();
  
  GPS.setLocation();

  extendGate.set(false);
  retractGate.set(true);

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
//   // ..........................................................................
  if(GPS.isCalibrating() == false)
  {

  switch(autonVer)
  {
    case 0:
    //comp starting on left/alpha side

    break;
    
    case 1:
    //comp starting on right/beta side
    
    break;
  }
}

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
  ControllerMech.ButtonA.pressed(toHopper);
  ControllerMech.ButtonX.pressed(toHighG);
  ControllerMech.ButtonB.pressed(toLowG);
  ControllerMech.ButtonY.pressed(stopCluster);

  ControllerMech.ButtonR1.pressed(extendGateToggle);
  ControllerMech.ButtonL1.pressed(retractGateToggle);

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
      Drive(axis1Pos, (int[4]){1,1,0,0});
      }
      //right turn

      if(axis1Pos < 0)
      {
        Drive(axis1Pos, (int[4]){0,0,1,1});
      }
      //left turn

      if(axis4Pos > 0)
      {
        Drive(axis4Pos, (int[4]){1,0,0,1});
      }
      //strafe right

      if(axis4Pos < 0)
      {
        Drive(axis4Pos,(int[4]){0,1,1,0});
      }

    
  }

 

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

