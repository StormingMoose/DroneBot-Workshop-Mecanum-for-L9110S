/*
  Mecanum Wheel Car - Mode 0 (Standard) driving functions
  d_mode-0.ino
  Allows control with joystick on remote control
  Used with mec-robot-car.ino
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Function to control motors with joystick values - Standard Mode
void motorControlMode0(int xjoystick, int yjoystick) {

  // Variables to hold mode byte and speed values
  byte motorCtlMode = B00000000;
  int rf_speed = 0;
  int lf_speed = 0;
  int rr_speed = 0;
  int lr_speed = 0;
 
  // Define variables and map joystick values to ranges from -255 to +255
  int xaxis = map(xjoystick, 0, 254, -255, 255);
  int yaxis = map(yjoystick, 0, 254, -255, 255);
 /* Serial.print("xaxis ");
     Serial.print(xaxis);
       Serial.print("    yaxis ");
         Serial.print(yaxis);
  */
  // Determine Wheel Mode byte and speed values
  if ((xaxis == 0) && (yaxis > 0)) {
    //Straight Forward
    motorCtlMode = MEC_STRAIGHT_FORWARD;
    rf_speed = yaxis;
    lf_speed = yaxis;
    rr_speed = yaxis;
    lr_speed = yaxis;
  } else if ((xaxis == 0) && (yaxis < 0)) {
    //Straight Backward
    motorCtlMode = MEC_STRAIGHT_BACKWARD;
    rf_speed = yaxis;
    lf_speed = yaxis;
    rr_speed = yaxis;
    lr_speed = yaxis;
  } else if ((xaxis < 0) && (yaxis == 0)) {
    //Sideways Right
    motorCtlMode = MEC_SIDEWAYS_RIGHT;
    rf_speed = xaxis;
    lf_speed = xaxis;
    rr_speed = xaxis;
    lr_speed = xaxis;
  } else if ((xaxis > 0) && (yaxis == 0)) {
    //Sideways Left
    motorCtlMode = MEC_SIDEWAYS_LEFT;
    rf_speed = xaxis;
    lf_speed = xaxis;
    rr_speed = xaxis;
    lr_speed = xaxis;
  } else if ((xaxis > 0) && (yaxis > 0)) {
    //Diagonal 45 Degrees
    motorCtlMode = MEC_DIAGONAL_45;
    rf_speed = 0;
    lf_speed = xaxis;
    rr_speed = yaxis;
    lr_speed = 0;
  } else if ((xaxis < 0) && (yaxis > 0)) {
    //Diagonal 135 Degrees
    motorCtlMode = MEC_DIAGONAL_135;
    rf_speed = xaxis;
    lf_speed = 0;
    rr_speed = 0;
    lr_speed = yaxis;
  } else if ((xaxis < 0) && (yaxis < 0)) {
    //Diagonal 225 Degrees
    motorCtlMode = MEC_DIAGONAL_225;
    rf_speed = 0;
    lf_speed = yaxis;
    rr_speed = xaxis;
    lr_speed = 0;
  } else if ((xaxis > 0) && (yaxis < 0)) {
    //Diagonal 315 Degrees
    motorCtlMode = MEC_DIAGONAL_315;
    rf_speed = yaxis;
    lf_speed = 0;
    rr_speed = 0;
    lr_speed = xaxis;
  } else if ((xaxis == 0) && (yaxis == 0)) {
    //Stop all motors
    motorCtlMode = MEC_STOPPED;
    rf_speed = 0;
    lf_speed = 0;
    rr_speed = 0;
    lr_speed = 0;
  }

  // Drive motors & set LED colors (moveMotors will correct any negative speed values)
  moveMotors(rf_speed, lf_speed, rr_speed, lr_speed, motorCtlMode);
  ledMotorStatus(motorCtlMode);

  /* Update values to send to remote
  Serial.print("rf_speed ");
     Serial.print(rf_speed);
       Serial.print("   lf_speed ");
         Serial.print(lf_speed);
  Serial.print("rr_speed ");
     Serial.print(rr_speed);
       Serial.print("   lr_speed ");
         Serial.println(lr_speed);
 
 */
  motorModeValue = motorCtlMode;
  mtrRFpwmValue = rf_speed;
  mtrLFpwmValue = lf_speed;
  mtrRRpwmValue = rr_speed;
  mtrLRpwmValue = lr_speed;
}