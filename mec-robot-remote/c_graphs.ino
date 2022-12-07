/*
  Mecanum Wheel Remote Control - TFT Display Graph Functions
  c_graphs.ino
  Graphs used on remote control TFT display
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

void graphMotorSpeed(int opMode) {
  // Display motor speeds as bargarph
  // Background color changes with operating mode
  // Graph colors change with motor direction

  int backColor;
  String headerText;

  if (opMode == 0) {
    backColor = displayColor2a;
    headerText = "Standard Mecanum Mode";
  } else if (opMode == 1) {
    backColor = displayColor2b;
    headerText = "Rotate Mode";
  } else if (opMode == 2) {
    backColor = displayColor2c;
    headerText = "Pivot Right Mode";
  } else if (opMode == 3) {
    backColor = displayColor2d;
    headerText = "Pivot Left Mode";
  } else if (opMode == 4) {
    backColor = displayColor2e;
    headerText = "Pivot Front Mode";
  } else if (opMode == 5) {
    backColor = displayColor2f;
    headerText = "Pivot Rear Mode";
  } else {
    backColor = displayColor2f;
    headerText = "Standard Mecanum Mode";
  }


  // Fill the sprite with color & add rectangles
  sprite.fillSprite(displayColor3);
  sprite.fillRect(0, 0, 300, 160, displayColor1);
  sprite.fillRoundRect(5, 20, 230, 110, 5, backColor);
  sprite.fillRect(40, 30, 2, 80, displayColor1);
  sprite.fillRect(40, 110, 190, 2, displayColor1);

  // Text for top
  sprite.setTextDatum(4);
  sprite.setTextColor(displayColor3, displayColor1);
  sprite.drawString(headerText, 114, 10, 2);

  // Text for left sidebar (increment lables)
  sprite.setTextColor(displayColor1, backColor);
  for (int i = 2; i < 8; i = i + 2) {
    sprite.drawString(String(i * 40), 22, 105 - (i * 10));
    for (int j = 0; j < 197; j = j + 5)
      sprite.drawPixel(40 + j, 105 - (i * 10), displayColor1);
  }

  // Text for bottom
  sprite.drawString("RF", 70, 121, 2);
  sprite.drawString("LF", 115, 121, 2);
  sprite.drawString("RR", 160, 121, 2);
  sprite.drawString("LR", 205, 121, 2);

  // Bargraph values

  byte barMotorMode = motorModeValue;

  int barvalueRF = abs(mtrRFpwmValue);
  int barvalueLF = abs(mtrLFpwmValue);
  int barvalueRR = abs(mtrRRpwmValue);
  int barvalueLR = abs(mtrLRpwmValue);

  // Map results to bargraph range
  barvalueRF = map(barvalueRF, 0, 255, 0, 75);
  barvalueLF = map(barvalueLF, 0, 255, 0, 75);
  barvalueRR = map(barvalueRR, 0, 255, 0, 75);
  barvalueLR = map(barvalueLR, 0, 255, 0, 75);

  // Set bargraph colors by motor direction
  if ((bitRead(barMotorMode, 7) == 1) && (bitRead(barMotorMode, 6) == 0)) {
    sprite.fillRect(60, 110 - barvalueRF, 16, barvalueRF, displayColor5);
  } else if ((bitRead(barMotorMode, 7) == 0) && (bitRead(barMotorMode, 6) == 1)) {
    sprite.fillRect(60, 110 - barvalueRF, 16, barvalueRF, displayColor4);
  }

  if ((bitRead(barMotorMode, 5) == 1) && (bitRead(barMotorMode, 4) == 0)) {
    sprite.fillRect(105, 110 - barvalueLF, 16, barvalueLF, displayColor5);
  } else if ((bitRead(barMotorMode, 5) == 0) && (bitRead(barMotorMode, 4) == 1)) {
    sprite.fillRect(105, 110 - barvalueLF, 16, barvalueLF, displayColor4);
  }

  if ((bitRead(barMotorMode, 3) == 1) && (bitRead(barMotorMode, 2) == 0)) {
    sprite.fillRect(150, 110 - barvalueRR, 16, barvalueRR, displayColor5);
  } else if ((bitRead(barMotorMode, 3) == 0) && (bitRead(barMotorMode, 2) == 1)) {
    sprite.fillRect(150, 110 - barvalueRR, 16, barvalueRR, displayColor4);
  }

  if ((bitRead(barMotorMode, 1) == 1) && (bitRead(barMotorMode, 0) == 0)) {
    sprite.fillRect(195, 110 - barvalueLR, 16, barvalueLR, displayColor5);
  } else if ((bitRead(barMotorMode, 1) == 0) && (bitRead(barMotorMode, 0) == 1)) {
    sprite.fillRect(195, 110 - barvalueLR, 16, barvalueLR, displayColor4);
  }

  // Paint display
  sprite.pushSprite(0, 0);
}

void displayMotorSpeed(int opMode) {
  // Display of speed and directon of all motors

  int backColor;
  String headerText;

  if (opMode == 0) {
    backColor = displayColor2a;
    headerText = "Standard Mecanum Mode";
  } else if (opMode == 1) {
    backColor = displayColor2b;
    headerText = "Rotate Mode";
  } else if (opMode == 2) {
    backColor = displayColor2c;
    headerText = "Pivot Right Mode";
  } else if (opMode == 3) {
    backColor = displayColor2d;
    headerText = "Pivot Left Mode";
  } else if (opMode == 4) {
    backColor = displayColor2e;
    headerText = "Pivot Front Mode";
  } else if (opMode == 5) {
    backColor = displayColor2f;
    headerText = "Pivot Rear Mode";
  } else {
    backColor = displayColor2f;
    headerText = "Standard Mecanum Mode";
  }

  // Fill the sprite with color & add "car" rectangle
  sprite.fillSprite(backColor);
  sprite.fillRect(85, 30, 70, 90, displayColor1);

  // Text for top
  sprite.setTextDatum(4);
  sprite.setTextColor(displayColor3, backColor);
  sprite.drawString(headerText, 114, 10, 2);

  // Speed values
  byte speedMotorMode = motorModeValue;

  String speedvalueRF = String(abs(mtrRFpwmValue));
  String speedvalueLF = String(abs(mtrLFpwmValue));
  String speedvalueRR = String(abs(mtrRRpwmValue));
  String speedvalueLR = String(abs(mtrLRpwmValue));

  // Set "wheel" colors by motor direction
  // Right Front
  if ((bitRead(speedMotorMode, 7) == 1) && (bitRead(speedMotorMode, 6) == 0)) {
    sprite.fillRoundRect(145, 35, 20, 30, 2, displayColor5);
  } else if ((bitRead(speedMotorMode, 7) == 0) && (bitRead(speedMotorMode, 6) == 1)) {
    sprite.fillRoundRect(145, 35, 20, 30, 2, displayColor4);
  } else {
    sprite.fillRoundRect(145, 35, 20, 30, 2, displayColor6);
    speedvalueRF = "OFF";
  }

  // Left Front
  if ((bitRead(speedMotorMode, 5) == 1) && (bitRead(speedMotorMode, 4) == 0)) {
    sprite.fillRoundRect(75, 35, 20, 30, 2, displayColor5);
  } else if ((bitRead(speedMotorMode, 5) == 0) && (bitRead(speedMotorMode, 4) == 1)) {
    sprite.fillRoundRect(75, 35, 20, 30, 2, displayColor4);
  } else {
    sprite.fillRoundRect(75, 35, 20, 30, 2, displayColor6);
    speedvalueLF = "OFF";
  }

  // Right Rear
  if ((bitRead(speedMotorMode, 3) == 1) && (bitRead(speedMotorMode, 2) == 0)) {
    sprite.fillRoundRect(145, 85, 20, 30, 2, displayColor5);
  } else if ((bitRead(speedMotorMode, 3) == 0) && (bitRead(speedMotorMode, 2) == 1)) {
    sprite.fillRoundRect(145, 85, 20, 30, 2, displayColor4);
  } else {
    sprite.fillRoundRect(145, 85, 20, 30, 2, displayColor6);
    speedvalueRR = "OFF";
  }

  // Left Rear
  if ((bitRead(speedMotorMode, 1) == 1) && (bitRead(speedMotorMode, 0) == 0)) {
    sprite.fillRoundRect(75, 85, 20, 30, 2, displayColor5);
  } else if ((bitRead(speedMotorMode, 1) == 0) && (bitRead(speedMotorMode, 0) == 1)) {
    sprite.fillRoundRect(75, 85, 20, 30, 2, displayColor4);
  } else {
    sprite.fillRoundRect(75, 85, 20, 30, 2, displayColor6);
    speedvalueLR = "OFF";
  }

  // Display speed values
  sprite.drawString(speedvalueRF, 195, 50, 4);
  sprite.drawString(speedvalueLF, 40, 50, 4);
  sprite.drawString(speedvalueRR, 195, 100, 4);
  sprite.drawString(speedvalueLR, 40, 100, 4);

  // Paint display
  sprite.pushSprite(0, 0);
}