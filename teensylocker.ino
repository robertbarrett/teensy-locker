//IR Sensor will detect something in front of it up to approx 16in

int sensorPin = 0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int awayCount = 0;    // variable to count the interval between detections
int lockTimer = 20;   // max time to wait before locking the system.
boolean lockToggle = false; // toggles if locked, so keystrokes aren't sent repeatedly

int detected = 0;     // IR Sensor returns a 0 if something is detected
int notDetected = 1;  // IR Sensor returns a 1 if nothing is detected

void setup() {
  // declare the ledPin as an OUTPUT:
  // Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  // read the value from the sensor:
  sensorValue = digitalRead(sensorPin);
  // sensorValue will read the value of the IR sensor.
  // it will record a 0 if something is detected
  // it will record a 1 if something is not detected

  if (lockToggle)
  {
  // if system was locked, only check if someone is back, so WinL keystrokes aren't sent repeatedly
    if (sensorValue==detected)
      lockToggle = false;
  }
  else if (sensorValue==notDetected)  // nothing detected. increment the awayCount
    awayCount = awayCount + 1; 
  else  // something detected. reset the awayCount
    awayCount = 0;
    
  if (awayCount>=lockTimer)
  {
    // set Windows Key to be pressed
    Keyboard.set_modifier(MODIFIERKEY_GUI);
    Keyboard.send_now();
    // set L key to be pressed
    Keyboard.set_key1(KEY_L);
    Keyboard.send_now();
    
    // release all the keys at the same instant
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    // Serial.println("=============IT LOCK TIME================");
    
    awayCount = 0;
    
    lockToggle = true;

  }
  
  // Serial.print("sensorValue: ");
  // Serial.println(sensorValue);
  // Serial.print("awayCount: ");
  // Serial.println(awayCount);
  delay(1000);  
}
