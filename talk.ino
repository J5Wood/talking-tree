int strobePin = 12;
int resetPin = 13;
int audioOutputPin = A5;
int motorPwmOutputPin = 9;
int motorSignalOnePin = 7;
int motorSignalTwoPin = 8;
int level[7];

void setup() {
  Serial.begin(9600);
  
  // Define pin modes
  pinMode(motorPwmOutputPin, OUTPUT);
  pinMode(motorSignalOnePin, OUTPUT);
  pinMode(motorSignalTwoPin, OUTPUT);

  pinMode(strobePin, OUTPUT);
  pinMode(resetPin,  OUTPUT);
  pinMode(audioOutputPin,    INPUT);
 
  // Create an initial state for our pins
  digitalWrite(motorSignalOnePin, HIGH);
  digitalWrite(motorSignalTwoPin, HIGH);
  
  digitalWrite(resetPin,  LOW);
  digitalWrite(strobePin, LOW);
  delay(1);
 
  // Reset the MSGEQ7 as per the datasheet timing diagram
  digitalWrite(resetPin,  HIGH);
  delay(1);
  digitalWrite(resetPin,  LOW);
  digitalWrite(strobePin, HIGH); 
  delay(1);
}


void loop() {
  int pwmOutput = 255;
  analogWrite(motorPwmOutputPin, pwmOutput);

  extend(150);
  pause(500);
  retract(150);
  pause(500);
  

  // Cycle through each frequency band by pulsing the strobe.
  // for (int i = 0; i < 7; i++) {
  //   digitalWrite(strobePin, LOW);
  //   delayMicroseconds(100);                    // Delay necessary due to timing diagram
  //   level[i] = analogRead (audioOutputPin);
  //   digitalWrite(strobePin, HIGH);
  //   delayMicroseconds(100);                    // Delay necessary due to timing diagram  
  // }
 
  // for (int i = 0; i < 7; i++) {
  //   Serial.print(level[i]);
  //   Serial.print(" - ");
  // }
 
  // Serial.println();
  // Serial.println();
}

void extend(int ms) {
  digitalWrite(motorSignalOnePin, HIGH);
  digitalWrite(motorSignalTwoPin, LOW);
  delay(ms);
}

void retract(int ms) {
  digitalWrite(motorSignalOnePin, LOW);
  digitalWrite(motorSignalTwoPin, HIGH);
  delay(ms);
}

void pause(int ms) {
  digitalWrite(motorSignalOnePin, HIGH);
  digitalWrite(motorSignalTwoPin, HIGH);
  delay(ms);
}
