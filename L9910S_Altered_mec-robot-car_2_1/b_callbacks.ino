/*
  Mecanum Wheel Car - Callback Functions
  b_callbacks.ino
  ESP-NOW callback functions for mecanum wheel robot car
  Used with mec-robot-car.ino
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  
}

// Callback function executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {

  if (len == 0) {
    // No data received, error condition
    // Stop all motors
    stopMotors();

    // Put LEDs into Error mode
    ledError();

    // Set controller values to default
    joyXaxis = 127;
    joyYaxis = 127;
    joySwitchState = true;
    return;
  }

  memcpy(&rcvData, incomingData, sizeof(rcvData));

  //Serial.print("X = ");
  //Serial.print(rcvData.xAxis);
  //Serial.print(", Y = ");
  //Serial.print(rcvData.yAxis);
  //Serial.print(", SW = ");
  //Serial.println(rcvData.pbSwitch);

  // Pass received values to local variables
  joyXaxis = rcvData.xAxis;
  joyYaxis = rcvData.yAxis;
  joySwitchState = rcvData.pbSwitch;

  // Check to see if we are changing Mecanum mode
  if (joySwitchState == true) {
    // Switch was pressed, toggle mecanum mode
    toggleMecanumMode();
  }

  // Update last received time counter
  lastRecvTime = millis();
}