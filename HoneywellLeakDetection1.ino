// Inspired by: https://forum.arduino.cc/t/interfacing-with-rope-leak-detector-cable/247230/13

// Pin Assignments
const int ledPin = LED_BUILTIN;
// These Analog-in pins are used to measure whether a Honeywell water-leak sensor cable is sensing water
// const int leakPins[sensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};
// A0 = Test
// A1 = Maxwell's shower
// A2 = North foundation
// A3 = East foundation
// A4 = Kitchen Refrigerator
// A5 = Kitchen Sink
const int leakPins[] = {A0, A1, A2, A3, A4, A5};
const int wetThreshold[] = {20, 30, 86, 140, 30, 30}; // Purely by observation; All haven't been tested yet, so I'm taking the highest observed dry level, and adding 10%
const int sensorCount = sizeof(leakPins) / sizeof(leakPins[0]);
// There is a piezo buzzer on this pin
const int buzzer = 9;  // digital out
// These pins are for operating HC-SR04 Time-of-Flight (distance) sensor, for measuring water depth in the sump
const int trigPin = 10;  
const int echoPin = 11; 
const int sumpThreshold = 49; // in cm, from the sensor to the top of the water; kinda reversed logic, here
// Some tunable variables for timeout
const int SAMPLE_COUNT = 20;
const int timeout = 100; // dwell time between sampling
// Set this to true, if you want serial output!
const bool DEBUG = true;

void setup() {
  // put your setup code here, to run once: 
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  if (DEBUG) {
    Serial.begin(19200);
    Serial.println("");
    Serial.println("=====================================");
    Serial.println("Initialized HoneywellleakDetection1...");
  }
  // Also setup pins for the HC-SR04 ToF sensor
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT);  
}

// When the cable is dry, over the course of about 3 seconds, the reading will cycle between 0 and 1023... sinusoidal?  (Capacitance?)
// When the cable is wet, the reading will be in the range of approximately 500-800
bool isLeakDetected (int leakPin, int threshold){
  int sampleCounter = 0;
  int currentSample;

  // collect samples
  if (DEBUG) {
    Serial.println("");
    Serial.print("Datapoints for sensor on pin "); 
    Serial.print(leakPin);
    Serial.print(" with threshold ");
    Serial.print(threshold);
    Serial.print(": ");
  }

  for (sampleCounter = 0; sampleCounter < SAMPLE_COUNT; sampleCounter++) {
    currentSample = analogRead(leakPin);
    if (DEBUG) {
      Serial.print(currentSample);
      Serial.print(", ");
    }
    if (currentSample < threshold) {
      return false;  // no leak
    }
    delay(timeout);   
  }
  triggerAlarm();
  return true;   // leak
}

bool isSumpFull (int threshold){
  // from https://projecthub.arduino.cc/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-7cabe1
  int duration = 0;
  int distance = 0;
  // Kick off the measuring process by tickling the "trigger" pin with particular timing delays; strobe the trigger!
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);  
  //
  duration=pulseIn(echoPin, HIGH);
  distance=(duration*.0343)/2;
  if (DEBUG) {
    Serial.print("Distance to the top of the water: ");
    Serial.println(distance);
  }
  if (distance > threshold) {
     return true;
  } else {
     return false;
  }
}

void triggerAlarm() {
  digitalWrite(ledPin, HIGH);
  tone(buzzer, 1000);
}

void cancelAlarm() {
  digitalWrite(ledPin, LOW);
  noTone(buzzer);
}

void loop() {
  bool leakDetected;
  leakDetected = false;

  //Check for water leaks
  for (int i = 0; i < sensorCount; i++) {
    if (isLeakDetected(leakPins[i], wetThreshold[i])) {
      leakDetected = true;
      if (DEBUG) Serial.print("Leak detected on sensor ");
      if (DEBUG) Serial.print(i);
    }
  }
  // Also check the depth of water in the sump
  if (isSumpFull(sumpThreshold)) {
      leakDetected = true;
      if (DEBUG) Serial.print("The sump is full above the threshold");
  }

  if (! leakDetected) cancelAlarm();
  if (DEBUG) Serial.println(); // visually mark the end of one round of testing all the sensors

  delay (6000);
}
