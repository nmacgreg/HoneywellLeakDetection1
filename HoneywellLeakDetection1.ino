// Inspired by: https://forum.arduino.cc/t/interfacing-with-rope-leak-detector-cable/247230/13

const int ledPin = LED_BUILTIN;
int leakPin = A0;
int ledState = LOW;
unsigned long previousMillis = 0;
int leak1 = 0;
int leak2 = 0;
int leak3 = 0; 
int counter = 0;
int DEBUG = 1;
int timeout = 100;

void setup() {
  // put your setup code here, to run once: 
  pinMode(ledPin, OUTPUT);
  analogRead(leakPin);
  if (DEBUG) {
    Serial.begin(19200);
    Serial.println("Initialized HoneywellleakDetection1...");
  }
}

// When the cable is dry, over the course of about 3 seconds, the reading will cycle between 0 and 1023... sinusoidal?  (Capacitance?)
// When the cable is wet, the reading will be in the range of approximately 500-800
int dataSample (){
  int sampleCounter = 0;
  int currentSample = 0;
  // collect 20 samples
  if (DEBUG) {
    Serial.print("Datapoints: ");
  }
  for (sampleCounter = 0; sampleCounter<20; sampleCounter++) {
    currentSample = analogRead(leakPin);
    if (DEBUG) {
      Serial.print(currentSample);
      Serial.print(", ");
    }
    delay(timeout);   
    if (currentSample < 300 || currentSample > 900) {
      return false;  // no leak
    }
  }
  return true;   // leak
}

void loop() {
  //Check for water leaks
  if (dataSample()) {
    ledState = HIGH;  // a leak has been detected
  } else {
    ledState = LOW;  // no leak 
  }
  digitalWrite(ledPin, ledState);
  if (DEBUG) {
    Serial.println("");
  }
  delay (6000);
}