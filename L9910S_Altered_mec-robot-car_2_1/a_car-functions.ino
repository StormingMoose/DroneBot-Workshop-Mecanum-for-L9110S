/*
  Mecanum Wheel Car - Functions
  a_car-functions.ino
  Functions for mecanum wheel robot car
  Used with mec-robot-car.ino
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

void moveMotors(int speedRF, int speedLF, int speedRR, int speedLR, byte dircontrol) {

  // Moves all 4 motors
  // Directions specified in direction byte

  // Right Front Motor
 
 if(bitRead(dircontrol, 7) == 1){ 
    digitalWrite(MF_AI1,0);
    ledcWrite(mtrRFpwmchannel, abs(speedRF));
  }
  else if (bitRead(dircontrol, 7) == 0) {
    digitalWrite(MF_AI1,1);
    ledcWrite(mtrRFpwmchannel, 255- abs(speedRF));}

  // Left Front Motor
  if(bitRead(dircontrol, 5) == 1){ 
    digitalWrite(MF_BI1,0);
    ledcWrite(mtrLFpwmchannel, abs(speedLF));
  }
  else if (bitRead(dircontrol, 5) == 0) {
    digitalWrite(MF_BI1,1);
    ledcWrite(mtrLFpwmchannel, 255 -abs(speedLF));
   }

  // Right Rear Motor
  if(bitRead(dircontrol, 3) == 1){ 
    digitalWrite(MR_AI1,0);
    ledcWrite(mtrRRpwmchannel, abs(speedRR));
  }
  else if (bitRead(dircontrol, 3) == 0) {
    digitalWrite(MR_AI1,1);
    ledcWrite(mtrRRpwmchannel,  255 - abs(speedRR));
  }

  // Left Rear Motor
  if(bitRead(dircontrol, 1) == 1){ 
    digitalWrite(MR_BI1,0);
    ledcWrite(mtrLRpwmchannel, abs(speedLR));
  }
  else if (bitRead(dircontrol, 1) == 0) {
    digitalWrite(MR_BI1,1);
    ledcWrite(mtrLRpwmchannel, 255 - abs(speedLR));
  }
}

void stopMotors() {

  // Stops all motors and motor controllers

  digitalWrite(MF_AI1, 0);
 // digitalWrite(MF_AI2, 0);
  digitalWrite(MF_BI1, 0);
  //digitalWrite(MF_BI2, 0);
  digitalWrite(MR_AI1, 0);
 // digitalWrite(MR_AI2, 0);
  digitalWrite(MR_BI1, 0);
//  digitalWrite(MR_BI2, 0);
     Serial.println("   KILROY ");
  ledcWrite(mtrRFpwmchannel, 0);
  ledcWrite(mtrLFpwmchannel, 0);
  ledcWrite(mtrRRpwmchannel, 0);
  ledcWrite(mtrLRpwmchannel, 0);
}

void ledMotorStatus(byte dircontrol) {

  // Sets status LEDs to indicate motor direction

  // Right front
  if ((bitRead(dircontrol, 7) == 1) && (bitRead(dircontrol, 6) == 0)) {
    // Motor moves forward
    // Turn Right Front NeoPixel BLUE
    strip.SetPixelColor(NEO_RF, blue);
  } else if ((bitRead(dircontrol, 7) == 0) && (bitRead(dircontrol, 6) == 1)) {
    // Motor moves in reverse
    // Turn Right Front NeoPixel GREEN
    strip.SetPixelColor(NEO_RF, green);
  } else {
    // Motor is stopped
    // Turn Right Front NeoPixel RED
    strip.SetPixelColor(NEO_RF, red);
  }

  // Left front
  if ((bitRead(dircontrol, 5) == 1) && (bitRead(dircontrol, 4) == 0)) {
    // Motor moves forward
    // Turn Left Front NeoPixel BLUE
    strip.SetPixelColor(NEO_LF, blue);
  } else if ((bitRead(dircontrol, 5) == 0) && (bitRead(dircontrol, 4) == 1)) {
    // Motor moves in reverse
    // Turn Left Front NeoPixel GREEN
    strip.SetPixelColor(NEO_LF, green);
  } else {
    // Motor is stopped
    // Turn left Front NeoPixel RED
    strip.SetPixelColor(NEO_LF, red);
  }

  // Right rear
  if ((bitRead(dircontrol, 3) == 1) && (bitRead(dircontrol, 2) == 0)) {
    // Motor moves forward
    // Turn Right Rear NeoPixel BLUE
    strip.SetPixelColor(NEO_RR, blue);
  } else if ((bitRead(dircontrol, 3) == 0) && (bitRead(dircontrol, 2) == 1)) {
    // Motor moves in reverse
    // Turn Right Rear NeoPixel GREEN
    strip.SetPixelColor(NEO_RR, green);
  } else {
    // Motor is stopped
    // Turn Right Rear NeoPixel RED
    strip.SetPixelColor(NEO_RR, red);
  }

  // Left rear
  if ((bitRead(dircontrol, 1) == 1) && (bitRead(dircontrol, 0) == 0)) {
    // Motor moves forward
    // Turn Left Rear NeoPixel BLUE
    strip.SetPixelColor(NEO_LR, blue);
  } else if ((bitRead(dircontrol, 1) == 0) && (bitRead(dircontrol, 0) == 1)) {
    // Motor moves in reverse
    // Turn Left Rear NeoPixel GREEN
    strip.SetPixelColor(NEO_LR, green);
  } else {
    // Motor is stopped
    // Turn Left Rear NeoPixel RED
    strip.SetPixelColor(NEO_LR, red);
  }

  // Update
  strip.Show();
}

void ledMotorTurnOff() {
  // Turn off all Motor NeoPixels
  strip.SetPixelColor(NEO_RF, black);
  strip.SetPixelColor(NEO_LF, black);
  strip.SetPixelColor(NEO_RR, black);
  strip.SetPixelColor(NEO_LR, black);
  strip.Show();
}

void ledAllTurnOff() {
  // Turn off all NeoPixels (including Status LED)
  strip.SetPixelColor(NEO_STATUS, black);
  strip.SetPixelColor(NEO_RF, black);
  strip.SetPixelColor(NEO_LF, black);
  strip.SetPixelColor(NEO_RR, black);
  strip.SetPixelColor(NEO_LR, black);
  strip.Show();
}

void ledAllStop() {
  // Turn all Motor NeoPixels RED
  strip.SetPixelColor(NEO_RF, red);
  strip.SetPixelColor(NEO_LF, red);
  strip.SetPixelColor(NEO_RR, red);
  strip.SetPixelColor(NEO_LR, red);
  strip.Show();
}

void ledError() {
  // Turn all Motor NeoPixels VIOLET
  strip.SetPixelColor(NEO_RF, violet);
  strip.SetPixelColor(NEO_LF, violet);
  strip.SetPixelColor(NEO_RR, violet);
  strip.SetPixelColor(NEO_LR, violet);
  // Turn Status NeoPixel RED
  strip.SetPixelColor(NEO_STATUS, red);
  strip.Show();
}

void setLedStatus(int statusVal) {
  // Set LED color based upon Mecanum Mode value
  if (statusVal == 0) {  // Cyan - Standard Mode
    strip.SetPixelColor(NEO_STATUS, cyan);
  } else if (statusVal == 1) {  // Green - Rotate Mode
    strip.SetPixelColor(NEO_STATUS, green);
  } else if (statusVal == 2) {  // Orange - Pivot Right Mode
    strip.SetPixelColor(NEO_STATUS, orange);
  } else if (statusVal == 3) {  // Violet - Pivot Left Mode
    strip.SetPixelColor(NEO_STATUS, violet);
  } else if (statusVal == 4) {  // Light Blue - Pivot Front mode
    strip.SetPixelColor(NEO_STATUS, lightblue);
  } else if (statusVal == 5) {  // Yellow - Pivot Rear Mode
    strip.SetPixelColor(NEO_STATUS, yellow);
  } else {  // Off (black) - Undefined Mode
    strip.SetPixelColor(NEO_STATUS, black);
  }
  strip.Show();
}