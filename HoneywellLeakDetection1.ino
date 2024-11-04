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

void setup() {
  // put your setup code here, to run once: 
  pinMode(ledPin, OUTPUT);
  analogRead(leakPin);
  if (DEBUG) {
    Serial.begin(19200);
    Serial.println("Initialized HoneywellleakDetection1...");
  }
}

void loop() {
  //Check for water leaks - we'll take 3 readings serially... seems to be some capacitance

  leak1 = analogRead(leakPin);
  for (counter=0; counter<1024; counter++) {
    
    delay(10);
  };
  leak2 = analogRead(leakPin);
  leak3 = analogRead(leakPin);
  if (DEBUG) {
    Serial.print("The value of leak entries is: ");
    Serial.print(leak1);
    Serial.print(", ");
    Serial.print(leak2);
    Serial.print(", ");
    Serial.print(leak3);
    Serial.print(", ");
  }
  if (leak1 > 100 && leak2 > 100 && leak3 > 100) {
    ledState = HIGH;
    if (DEBUG) {
      Serial.println("Leak detected!");
    }
  } else {
    ledState = LOW;
    if (DEBUG) {
      Serial.println("Normal - no leak detected.");
    }
  }
  // sleep(10);
  digitalWrite(ledPin, ledState);
}