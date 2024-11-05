// Inspired by: https://forum.arduino.cc/t/interfacing-with-rope-leak-detector-cable/247230/13

// Pin Assignments
const int ledPin = LED_BUILTIN;
// const int leakPins[sensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};
const int leakPins[sensorCount] = {A0, A1};
const int buzzer = 9;
// Some constants that might need adjusting, as I test the functionality
const int DRY_THRESHOLD_LOW = 300;
const int DRY_THRESHOLD_HIGH = 900;
const int SAMPLE_COUNT = 20;

const bool DEBUG = 1;
const int timeout = 100; // dwell time between sampling

void setup() {
  // put your setup code here, to run once: 
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  analogRead(leakPin);
  if (DEBUG) {
    Serial.begin(19200);
    Serial.println("Initialized HoneywellleakDetection1...");
  }
}

// When the cable is dry, over the course of about 3 seconds, the reading will cycle between 0 and 1023... sinusoidal?  (Capacitance?)
// When the cable is wet, the reading will be in the range of approximately 500-800
bool isLeakDetected (int leakPin){
  int sampleCounter = 0;
  int currentSample;

  // collect samples
  if (DEBUG) {
    Serial.print("Datapoints for sensor on pin "); 
    Serial.print(leakpin);
    Serial.print(": ");
  }

  for (sampleCounter = 0; sampleCounter < SAMPLE_COUNT; sampleCounter++) {
    currentSample = analogRead(leakPin);
    if (DEBUG) {
      Serial.print(currentSample);
      Serial.print(", ");
    }
    if (currentSample < DRY_THRESHOLD_LOW || currentSample > DRY_THRESHOLD_HIGH) {
      return false;  // no leak
    }
    delay(timeout);   
  }
  return true;   // leak
}

void triggerAlarm() }
  digitalWrite(ledPin, HIGH);
  tone(buzzer, 1000);
}

void cancelAlarm() }
  digitalWrite(ledPin, LOW);
  noTone(buzzer);
}

void loop() {
  //Check for water leaks
  for (int i = 0; i < sensorCount; i++) {
    if (isLeakDetected(leakPins[i])) {
      leakDetected = true;
      if (DEBUG) Serial.print("Leak detected on sensor ");
      if (DEBUG) Serial.println(i);
    }
  }
  if (DEBUG) Serial.println("");
  delay (6000);
}
