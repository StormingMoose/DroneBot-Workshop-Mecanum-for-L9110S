/*
  Mecanum Wheel Car - Modes 2 - 5 (Pivots) driving functions
  e_mode-2-5.ino
  Allows control with joystick on remote control
  Used with mec-robot-car.ino
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Function to control motors with joystick values - Pivot Right Mode
void motorControlMode2(int yjoystick) {

  // Variables to hold mode byte and speed values
  byte motorCtlMode = B00000000;
  int rf_speed = 0;
  int lf_speed = 0;
  int rr_speed = 0;
  int lr_speed = 0;

  // Define variables and map Y joystick values to ranges from -255 to +255
  int yaxis = map(yjoystick, 0, 254, -255, 255);

  // Determine if forward or reverse
  if (yaxis > 0) {
    // Forward
    motorCtlMode = MEC_PIVOT_RIGHT_FORWARD;
    lf_speed = yaxis;
    lr_speed = yaxis;
  } else if (yaxis < 0) {
    // Reverse
    motorCtlMode = MEC_PIVOT_RIGHT_BACKWARD;
    lf_speed = yaxis;
    lr_speed = yaxis;
  } else {
    // Stopped
    motorCtlMode = B00000000;
    rf_speed = 0;
    lf_speed = 0;
    rr_speed = 0;
    lr_speed = 0;
  }

  // Drive motors & set LED colors (moveMotors will correct any negative speed values)
  moveMotors(rf_speed, lf_speed, rr_speed, lr_speed, motorCtlMode);
  ledMotorStatus(motorCtlMode);

  // Update values to send to remote
  motorModeValue = motorCtlMode;
  mtrRFpwmValue = rf_speed;
  mtrLFpwmValue = lf_speed;
  mtrRRpwmValue = rr_speed;
  mtrLRpwmValue = lr_speed;
}

// Function to control motors with joystick values - Pivot Left Mode
void motorControlMode3(int yjoystick) {

  // Variables to hold mode byte and speed values
  byte motorCtlMode = B00000000;
  int rf_speed = 0;
  int lf_speed = 0;
  int rr_speed = 0;
  int lr_speed = 0;

  // Define variables and map Y joystick values to ranges from -255 to +255
  int yaxis = map(yjoystick, 0, 254, -255, 255);

  // Determine if forward or reverse
  if (yaxis > 0) {
    // Forward
    motorCtlMode = MEC_PIVOT_LEFT_FORWARD;
    rf_speed = yaxis;
    rr_speed = yaxis;
  } else if (yaxis < 0) {
    // Reverse
    motorCtlMode = MEC_PIVOT_LEFT_BACKWARD;
    rf_speed = yaxis;
    rr_speed = yaxis;
  } else {
    // Stopped
    motorCtlMode = B00000000;
    rf_speed = 0;
    lf_speed = 0;
    rr_speed = 0;
    lr_speed = 0;
  }

  // Drive motors & set LED colors (moveMotors will correct any negative speed values)
  moveMotors(rf_speed, lf_speed, rr_speed, lr_speed, motorCtlMode);
  ledMotorStatus(motorCtlMode);

  // Update values to send to remote
  motorModeValue = motorCtlMode;
  mtrRFpwmValue = rf_speed;
  mtrLFpwmValue = lf_speed;
  mtrRRpwmValue = rr_speed;
  mtrLRpwmValue = lr_speed;
}

// Function to control motors with joystick values - Pivot Front Mode
void motorControlMode4(int yjoystick) {

  // Variables to hold mode byte and speed values
  byte motorCtlMode = B00000000;
  int rf_speed = 0;
  int lf_speed = 0;
  int rr_speed = 0;
  int lr_speed = 0;

  // Define variables and map Y joystick values to ranges from -255 to +255
  int yaxis = map(yjoystick, 0, 254, -255, 255);

  // Determine if forward or reverse
  if (yaxis > 0) {
    // Forward
    motorCtlMode = MEC_PIVOT_SIDEWAYS_FRONT_RIGHT;
    rf_speed = yaxis;
    lf_speed = yaxis;
  } else if (yaxis < 0) {
    // Reverse
    motorCtlMode = MEC_PIVOT_SIDEWAYS_FRONT_LEFT;
    rf_speed = yaxis;
    lf_speed = yaxis;
  } else {
    // Stopped
    motorCtlMode = B00000000;
    rf_speed = 0;
    lf_speed = 0;
    rr_speed = 0;
    lr_speed = 0;
  }

  // Drive motors & set LED colors (moveMotors will correct any negative speed values)
  moveMotors(rf_speed, lf_speed, rr_speed, lr_speed, motorCtlMode);
  ledMotorStatus(motorCtlMode);

  // Update values to send to remote
  motorModeValue = motorCtlMode;
  mtrRFpwmValue = rf_speed;
  mtrLFpwmValue = lf_speed;
  mtrRRpwmValue = rr_speed;
  mtrLRpwmValue = lr_speed;
}

// Function to control motors with joystick values - Pivot Rear Mode
void motorControlMode5(int yjoystick) {

  // Variables to hold mode byte and speed values
  byte motorCtlMode = B00000000;
  int rf_speed = 0;
  int lf_speed = 0;
  int rr_speed = 0;
  int lr_speed = 0;

  // Define variables and map Y joystick values to ranges from -255 to +255
  int yaxis = map(yjoystick, 0, 254, -255, 255);

  // Determine if forward or reverse
  if (yaxis > 0) {
    // Forward
    motorCtlMode = MEC_PIVOT_SIDEWAYS_REAR_RIGHT;
    rr_speed = yaxis;
    lr_speed = yaxis;
  } else if (yaxis < 0) {
    // Reverse
    motorCtlMode = MEC_PIVOT_SIDEWAYS_REAR_LEFT;
    rr_speed = yaxis;
    lr_speed = yaxis;
  } else {
    // Stopped
    motorCtlMode = B00000000;
    rf_speed = 0;
    lf_speed = 0;
    rr_speed = 0;
    lr_speed = 0;
  }

  // Drive motors & set LED colors (moveMotors will correct any negative speed values)
  moveMotors(rf_speed, lf_speed, rr_speed, lr_speed, motorCtlMode);
  ledMotorStatus(motorCtlMode);

  // Update values to send to remote
  motorModeValue = motorCtlMode;
  mtrRFpwmValue = rf_speed;
  mtrLFpwmValue = lf_speed;
  mtrRRpwmValue = rr_speed;
  mtrLRpwmValue = lr_speed;
}