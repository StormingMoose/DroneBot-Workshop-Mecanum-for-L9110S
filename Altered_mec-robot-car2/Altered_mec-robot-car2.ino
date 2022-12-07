/*
  4WD Mecanum Wheel Robot Car Base
  mec-robot-car.ino
  Drives 4-wheel mecanum car base
  Uses ESP32 DevKitC (other ESP32 boards will work)
  Uses 2 TB6612FNG Motor Drivers, also compatible with L298N
  Uses WiFi & ESP-NOW library
  Uses NeoPixelBus Library by Michael C. Miller - https://github.com/Makuna/NeoPixelBus
  
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include Libraries
#include <NeoPixelBus.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_task_wdt.h>

// Watchdog timer period in seconds
#define WDT_TIMEOUT 3

// Define Motor Connections
// Right Front Motor
#define MF_PWMA 32
#define MF_AI1 33
//#define MF_AI2 23

// Left Front Motor
#define MF_PWMB 13
#define MF_BI1 12
//#define MF_BI2 25

// Right Rear Motor
#define MR_PWMA 26
#define MR_AI1 25
//#define MR_AI2 14

// Left Rear Motor
#define MR_PWMB 14
#define MR_BI1 27
//#define MR_BI2 2

// PWM Parameters for motor control
// PWM Frequency = 1KHz
const int mtrPWMFreq = 1000;
// PWM Resolution
const int mtrPWMResolution = 8;
// Define PWM channels for each motor
const int mtrRFpwmchannel = 4;
const int mtrLFpwmchannel = 5;
const int mtrRRpwmchannel = 6;
const int mtrLRpwmchannel = 7;

// Number of NeoPixels
const uint16_t PixelCount = 5;
// NeoPixel Pin
const uint8_t PixelPin = 5;

// Name each LED for easier reference
#define NEO_STATUS 0
#define NEO_RF 1
#define NEO_LF 2
#define NEO_RR 3
#define NEO_LR 4

// Colors for NeoPixels (black is off)
RgbColor red(255, 0, 0);
RgbColor green(0, 255, 0);
RgbColor blue(0, 0, 255);
RgbColor yellow(255, 191, 0);
RgbColor violet(255, 0, 255);
RgbColor cyan(0, 255, 255);
RgbColor white(255, 255, 255);
RgbColor orange(255, 69, 0);
RgbColor lightblue(173, 216, 230);
RgbColor lightgreen(144, 238, 144);
RgbColor black(0);

// Create "strip" object representing NeoPixel string
NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {  0x24, 0x6F, 0x28, 0x96, 0x77, 0x44 };

// Define a data structure for received data
typedef struct struct_message_rcv {
  int xAxis;
  int yAxis;
  bool pbSwitch;
} struct_message_rcv;

// Create a structured object for received data
struct_message_rcv rcvData;

// Define a data structure for sent data
typedef struct struct_message_xmit {
  byte motorMode;
  int mecanumMode;
  int mtrRF_PWM;
  int mtrLF_PWM;
  int mtrRR_PWM;
  int mtrLR_PWM;
} struct_message_xmit;

// Create a structured object for sent data
struct_message_xmit xmitData;

// ESP-NOW Peer info
esp_now_peer_info_t peerInfo;

// Define ESP-NOW timeout value
#define SIGNAL_TIMEOUT 500
// Last Receive time
unsigned long lastRecvTime = 0;

// Define Bytes to represent Mecanum Wheel Modes
// Individual bits define TB6612FNG motor driver module input states
// B7 = MF_AI1, B6 = MF_AI2, B5 = MF_BI1, B4 = MF_BI2, B3 = MR_AI1, B2 = MR_AI2, B1 = MR_BI1, B0 = MR_BI2
const byte MEC_STRAIGHT_FORWARD = B10101010;
const byte MEC_STRAIGHT_BACKWARD = B01010101;
const byte MEC_SIDEWAYS_RIGHT = B01101001;
const byte MEC_SIDEWAYS_LEFT = B10010110;
const byte MEC_DIAGONAL_45 = B00101000;
const byte MEC_DIAGONAL_135 = B10000010;
const byte MEC_DIAGONAL_225 = B00010100;
const byte MEC_DIAGONAL_315 = B01000001;
const byte MEC_PIVOT_RIGHT_FORWARD = B00100010;
const byte MEC_PIVOT_RIGHT_BACKWARD = B00010001;
const byte MEC_PIVOT_LEFT_FORWARD = B10001000;
const byte MEC_PIVOT_LEFT_BACKWARD = B01000100;
const byte MEC_ROTATE_CLOCKWISE = B01100110;
const byte MEC_ROTATE_COUNTERCLOCKWISE = B10011001;
const byte MEC_PIVOT_SIDEWAYS_FRONT_RIGHT = B01100000;
const byte MEC_PIVOT_SIDEWAYS_FRONT_LEFT = B10010000;
const byte MEC_PIVOT_SIDEWAYS_REAR_RIGHT = B00001001;
const byte MEC_PIVOT_SIDEWAYS_REAR_LEFT = B00000110;
const byte MEC_STOPPED = B00000000;                      //////////////////////////////////

// Variable for Motor Mode
byte motorModeValue = B00000000;

// Variable for Mecanum Mode
// 0 = Standard, 1 = Rotate, 2 = Pivot Right, 4 = Pivot Left, 5 = Pivot Front, 6 = Pivot Rear
int mecanumModeValue = 0;

// Variables for Motor PWM speeds
int mtrRFpwmValue = 0;
int mtrLFpwmValue = 0;
int mtrRRpwmValue = 0;
int mtrLRpwmValue = 0;

// Variables for Joystick values
volatile int joyXaxis = 127;
volatile int joyYaxis = 127;

// Variable for Joystick pushbutton state
volatile bool joySwitchState = true;

void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Disable WiFi sleep mode
  WiFi.setSleep(false);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    return;
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
    return;
  }

  // Set all connections as outputs
  pinMode(MF_PWMA, OUTPUT);
  pinMode(MF_AI1, OUTPUT);
 // pinMode(MF_AI2, OUTPUT);
  pinMode(MF_PWMB, OUTPUT);
  pinMode(MF_BI1, OUTPUT);
  //pinMode(MF_BI2, OUTPUT);
  pinMode(MR_PWMA, OUTPUT);
  pinMode(MR_AI1, OUTPUT);
 // pinMode(MR_AI2, OUTPUT);
  pinMode(MR_PWMB, OUTPUT);
  pinMode(MR_BI1, OUTPUT);
  //pinMode(MR_BI2, OUTPUT);

  //Set up PWM channels with frequency and resolution
  ledcSetup(mtrRFpwmchannel, mtrPWMFreq, mtrPWMResolution);
  ledcSetup(mtrLFpwmchannel, mtrPWMFreq, mtrPWMResolution);
  ledcSetup(mtrRRpwmchannel, mtrPWMFreq, mtrPWMResolution);
  ledcSetup(mtrLRpwmchannel, mtrPWMFreq, mtrPWMResolution);

  // Attach channels to PWM output pins
  ledcAttachPin(MF_PWMA, mtrRFpwmchannel);
  ledcAttachPin(MF_PWMB, mtrLFpwmchannel);
  ledcAttachPin(MR_PWMA, mtrRRpwmchannel);
  ledcAttachPin(MR_PWMB, mtrLRpwmchannel);

  // Enable watchdog timer - true is "panic mode" to restart
  esp_task_wdt_init(WDT_TIMEOUT, true);
  // Add current thread to watchdog timer
  esp_task_wdt_add(NULL);

  // Reset all the neopixels to an off state
  strip.Begin();
  strip.Show();

  delay(1000);

  // Turn all Motor LEDs red
  ledAllStop();

  // Stop all motors
  stopMotors();

  delay(1000);
}

void loop() {

  //Check timer to see if signal is lost
  unsigned long now = millis();

  if (now - lastRecvTime > SIGNAL_TIMEOUT)
  // Signal is lost
  {

    // Stop all motors
    stopMotors();

    // Put LEDs into Error mode
    ledError();

    // Set controller values to default
    joyXaxis = 127;
    joyYaxis = 127;
    joySwitchState = true;

  } else {

    // Set LED color based upon mode
    setLedStatus(mecanumModeValue);

    // Drive car using current mode
    driveMecanumMode();

    // Format structured data to send back to controller
    xmitData.motorMode = motorModeValue;
    xmitData.mecanumMode = mecanumModeValue;
    xmitData.mtrRF_PWM = mtrRFpwmValue;
    xmitData.mtrLF_PWM = mtrLFpwmValue;
    xmitData.mtrRR_PWM = mtrRRpwmValue;
    xmitData.mtrLR_PWM = mtrLRpwmValue;

    // Send message via ESP-NOW
    esp_err_t result2 = esp_now_send(broadcastAddress, (uint8_t *)&xmitData, sizeof(xmitData));
  }

  // Reset watchdog timer
  esp_task_wdt_reset();

  // Short delay
  delay(50);
}