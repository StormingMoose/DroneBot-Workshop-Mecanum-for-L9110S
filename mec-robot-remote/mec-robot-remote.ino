/*
  4WD Mecanum Wheel Remote Control
  mec-robot-remote.ino
  Controls 4-wheel mecanum car base
  Uses ESP32 TTGO "T-Display" module with integrated TFT display and 2 pushbuttons 
  Uses ESP-NOW library
  Uses TFT_eSPI Library by Bodmer - https://github.com/Bodmer/TFT_eSPI
  Modify User_Setup.h file in library for TTGO-T-Display
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include Libraries for ESP-NOW Communications
#include <esp_now.h>
#include <WiFi.h>

// Include libraries for display
#include <TFT_eSPI.h>
#include <SPI.h>

// Define Joystick Connections (some joystick models reverse X & Y)
#define X_AXIS_PIN 33
#define Y_AXIS_PIN 32
#define SWITCH_PIN 27

// Define TTGO display built-in pushbuttons
#define BUTTON_GRAPH 35
#define BUTTON_SPEED 0

// Objects for display & sprites
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

// Display colors
#define displayColor1 0xFFFF  // White

#define displayColor2a 0x1E1E  // Cyan
#define displayColor2b 0x5566  // Green
#define displayColor2c 0xE3E3  // Orange
#define displayColor2d 0xFAFA  // Violet
#define displayColor2e 0xBEBE  // Light Blue
#define displayColor2f 0xE6E6  // Yellow

#define displayColor3 0x0000  // Black
#define displayColor4 0x2727  // Green Bar
#define displayColor5 0x1B1B  // Blue Bar
#define displayColor6 0xE8E8  // Red

// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0xC2, 0xCB, 0x38 };

// Define a data structure for received data
typedef struct struct_message_rcv {
  bool motorMode;
  int mecanumMode;
  int mtrRF_PWM;
  int mtrLF_PWM;
  int mtrRR_PWM;
  int mtrLR_PWM;
} struct_message_rcv;

// Create a structured object for received data
struct_message_rcv rcvData;

// Create a structured object for sent data
typedef struct struct_message_xmit {
  int xAxis;
  int yAxis;
  bool pbSwitch;
} struct_message_xmit;

// Create a structured object for sent data
struct_message_xmit xmitData;

// ESP-NOW Peer info
esp_now_peer_info_t peerInfo;

// Variable for Motor Mode
volatile byte motorModeValue = B00000000;

// Variable for Mecanum Mode
volatile int mecanumModeValue = 0;

// Variables for Motor PWM speeds
volatile int mtrRFpwmValue = 0;
volatile int mtrLFpwmValue = 0;
volatile int mtrRRpwmValue = 0;
volatile int mtrLRpwmValue = 0;

// Variables for Joystick values
int joyXaxis = 127;
int joyYaxis = 127;

// Variable for Joystick pushbutton state
bool joySwitchState = HIGH;

// Variable for connection error  - HIGH is error state
volatile bool connectError = LOW;

// Variable for connection status string
String connectStatus = "NO INFO";

// Variable for display selection - 0 = Graph, 1 = Speed Display
volatile int displaySelect = 0;

void IRAM_ATTR ISR_GRAPH() {
  // Graphics button was pressed
  displaySelect = 0;
}

void IRAM_ATTR ISR_SPEED() {
  // Speed button was pressed
  displaySelect = 1;
}

void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);

  // Set joystick pin as input with Pullup
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // Set built-in pushbuttons as inputs with pullups
  pinMode(BUTTON_GRAPH, INPUT_PULLUP);
  pinMode(BUTTON_SPEED, INPUT_PULLUP);

  // Attach interrupts to handlers
  attachInterrupt(BUTTON_GRAPH, ISR_GRAPH, FALLING);
  attachInterrupt(BUTTON_SPEED, ISR_SPEED, FALLING);

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Disable WiFi Sleep mode
  WiFi.setSleep(false);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    connectStatus = "ESP-NOW Error";
    connectError = HIGH;
    return;
  } else {
    connectStatus = "ESP-NOW OK";
    connectError = LOW;
  }

  // Register receive callback function
  esp_now_register_recv_cb(OnDataRecv);

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    connectStatus = "No peer added";
    connectError = HIGH;
    return;
  } else {
    connectStatus = "ESP-NOW Ready";
    connectError = LOW;
  }

  // Set A/D resolution to 12-bits
  analogReadResolution(12);

  // Initialize the display
  tft.init();
  tft.setRotation(1);

  // Create a sprite
  sprite.createSprite(320, 170);

  // Display a splash screen
  splashScreen(connectStatus, connectError);
  delay(2000);
  connectStatus = "Waiting for car";
  splashScreen(connectStatus, connectError);
  delay(2000);

  // Enter the Loop with connectError set HIGH to avoid intial display flicker
  connectError = HIGH;
}

void loop() {

  // Check connection status
  if (connectError == LOW) {

    // Select display
    if (displaySelect == 0) {
      // Display motor speed graph
      graphMotorSpeed(mecanumModeValue);
    } else {
      // Display motor speed "animation"
      displayMotorSpeed(mecanumModeValue);
    }

    // Get joystick values and convert them
    joyXaxis = convertJoystickValues(analogRead(X_AXIS_PIN), false);
    joyYaxis = convertJoystickValues(analogRead(Y_AXIS_PIN), false);

  } else {
    // Display splash screen
    splashScreen(connectStatus, HIGH);

    // Send "zero" values as joystick data
    joyXaxis = 127;
    joyYaxis = 127;
  }

  // Check and set switch status
  if (digitalRead(SWITCH_PIN) == LOW) {
    // Switch was pressed
    joySwitchState = true;
  } else {
    joySwitchState = false;
  }

  // Format structured data
  xmitData.xAxis = joyXaxis;
  xmitData.yAxis = joyYaxis;
  xmitData.pbSwitch = joySwitchState;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&xmitData, sizeof(xmitData));

  // If switch was pressed delay longer to debounce
  if (joySwitchState == true) {
    delay(200);
  } else {
    delay(50);
  }
}