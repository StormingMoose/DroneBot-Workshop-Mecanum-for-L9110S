/*
  Mecanum Wheel Car - Mecanum driving functions
  c_mecanum-functions.ino
  Motor control and steering functions
  Used with mec-robot-car.ino
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

void toggleMecanumMode() {
  // Toggle Mecanum Mode value from 0 to 5
  int currentMecMode = mecanumModeValue;
  if (currentMecMode == 5) {
    mecanumModeValue = 0;
  } else {
    mecanumModeValue = currentMecMode + 1;
  }
}

void driveMecanumMode() {

  // Pass control to proper Mecanum Mode function
  switch (mecanumModeValue) {

    case 0:
      // Standard driving mode, controlled by joystick
      // Pass joystick values to motorControlMode0 function
      motorControlMode0(joyXaxis, joyYaxis);

      break;

    case 1:
      // Rotate mode, controlled by joystick Y Axis only
      // Pass joystick values to motorControlMode0 function
      motorControlMode1(joyYaxis);

      break;

    case 2:
      // Pivot Right mode, controlled by joystick Y Axis only
      // Pass joystick values to motorControlMode0 function
      motorControlMode2(joyYaxis);

      break;

    case 3:
      // Pivot Left mode, controlled by joystick Y Axis only
      // Pass joystick values to motorControlMode0 function
      motorControlMode3(joyYaxis);

      break;

    case 4:
      // Pivot Front mode, controlled by joystick Y Axis only
      // Pass joystick values to motorControlMode0 function
      motorControlMode4(joyYaxis);

      break;

    case 5:
      // Pivot Rear mode, controlled by joystick Y Axis only
      // Pass joystick values to motorControlMode0 function
      motorControlMode5(joyYaxis);

      break;
  }
}