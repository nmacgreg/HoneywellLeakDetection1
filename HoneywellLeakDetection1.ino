// Inspired by: https://forum.arduino.cc/t/interfacing-with-rope-leak-detector-cable/247230/13

// Pin Assignments
const int ledPin = LED_BUILTIN;
// const int leakPins[sensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};
const int leakPins[] = {A0, A1, A2, A3};
const int wetThreshold[] = {20, 30, 86, 140}; // Purely by observation; All haven't been tested yet, so I'm taking the highest observed dry level, and adding 10%
const int sensorCount = sizeof(leakPins) / sizeof(leakPins[0]);
const int buzzer = 9;
// Some constants that might need adjusting, as I test the functionality
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

  if (! leakDetected) cancelAlarm();
  if (DEBUG) Serial.println(); // visually mark the end of one round of testing all the sensors

  delay (6000);
}
