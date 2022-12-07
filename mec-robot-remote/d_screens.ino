/*
  Mecanum Wheel Remote Control - TFT Display Screen Functions
  d_screens.ino
  Display screens used on remote control TFT display
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

void splashScreen(String messageString, bool errStat) {
  // Display a splash screen with a text message box
  // Background color depends upon error status
  if (errStat == HIGH) {
    // Fill the sprite with color & add rectangles
    sprite.fillSprite(displayColor6);

    // Text for top
    sprite.setTextDatum(4);
    sprite.setTextColor(displayColor1, displayColor6);
    sprite.drawString("Error", 114, 25, 4);
    sprite.drawString("Connecting", 114, 50, 4);

  } else {

    // Fill the sprite with color & add rectangles
    sprite.fillSprite(displayColor2b);

    // Text for top
    sprite.setTextDatum(4);
    sprite.setTextColor(displayColor1, displayColor2b);
    sprite.drawString("ESP-NOW", 114, 25, 4);
    sprite.drawString("Mecanum Car", 114, 50, 4);
  }

  // Box & text for status
  sprite.fillRoundRect(5, 70, 230, 40, 5, displayColor1);
  sprite.setTextColor(displayColor3, displayColor1);
  sprite.drawString(messageString, 114, 92, 4);

  // Paint display
  sprite.pushSprite(0, 0);
}

void controlInfo() {
// System information display


}

