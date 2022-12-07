/*
  Mecanum Wheel Remote Control - functions
  a_remote-functions.ino
  Functions for remote control
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/
// Map 12-bit A/D values to 8-bit PWM values
// Allow for gap in center to account for joystick inaccuracies
int convertJoystickValues(int value, bool reverse) {
  if (value >= 2200) {
    // Joystick pushed forward
    value = map(value, 2200, 4095, 127, 254);
  } else if (value <= 1800) {
    // Joystick pulled back
    value = map(value, 1800, 0, 127, 0);
  } else {
    // Joystick in center
    value = 127;
  }

  // Check direction
  if (reverse) {
    value = 254 - value;
  }
  return value;
}