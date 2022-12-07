/*
  Mecanum Wheel Remote Control - ESP-NOW Callbacks
  b_callbacks.ino
  Callbacks for communication with mecanum wheel robot car
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/
// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {

  if (status == ESP_NOW_SEND_SUCCESS) {
    connectStatus = "Car found";
    connectError = LOW;
  } else {
    connectStatus = "Car not found";
    connectError = HIGH;
  }
}

// Callback function executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {

  // Get receievd data
  memcpy(&rcvData, incomingData, sizeof(rcvData));

  // Pass received values to local variables
  motorModeValue = rcvData.motorMode;
  mecanumModeValue = rcvData.mecanumMode;
  mtrRFpwmValue = rcvData.mtrRF_PWM;
  mtrLFpwmValue = rcvData.mtrLF_PWM;
  mtrRRpwmValue = rcvData.mtrRR_PWM;
  mtrLRpwmValue = rcvData.mtrLR_PWM;

  //Serial.println(mecanumModeValue);
}