#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  4, 0,                  // Button Count, Hat Switch Count
  true, true, true,     // X ,Y and Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle (MSFS does not work well with this rudder / throttle control)
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // open the serial port at 9600 bps.
  // Uncomment only when debugging.
  // this is useful to log debug messages to the console using Serial.println()
  // Serial.begin(9600);

  // Initialize Joystick Library
  // 6,7,12,13 are the inputs where i connected the wires in the arduino.
  // This can change if you decide to plug the your wires into other inputs
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  Joystick.begin();

}

int throttle = 0;
int prop = 0;
int mixture = 0;
// Again:
// 6,7,12,13 are the inputs where i connected the wires in the arduino.
// This can change if you decide to plug the your wires into other inputs
int btnStates[4] = {0,0,0,0};
int btnPins[4] = {6,7,12,13};



void loop() {
  // Same for 1,3 and 5: i'm using the analog inputs 1,3 and 5 in the board
  // modify that to reflect your wiring
  throttle = analogRead(1);
  prop = analogRead(3);
  mixture = analogRead(5);
  // Serial.println("Throttle: "+String(throttle)+" / Propeller: "+String(prop)+" / Mixture: "+ String(mixture));
  Joystick.setXAxis(throttle);
  Joystick.setYAxis(prop);
  Joystick.setZAxis(mixture);

  for(byte i = 0; i < 4 ; i++){
    // Setup buttons (using them for Flap up, Flap down, Toggle Landing Gear, Parking Breaks)
    int lastState = btnStates[i];
    int btnState = !digitalRead(btnPins[i]);

    if(btnState != lastState){
      Joystick.setButton(i, btnState);
      btnStates[i] = btnState;
    }
  }
}
