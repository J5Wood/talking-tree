int audioStrobePin = 12;
int audioResetPin = 13;
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

  pinMode(audioStrobePin, OUTPUT);
  pinMode(audioResetPin,  OUTPUT);
  pinMode(audioOutputPin,    INPUT);
 
  // Create an initial state for our pins
  digitalWrite(motorSignalOnePin, HIGH);
  digitalWrite(motorSignalTwoPin, HIGH);
  
  digitalWrite(audioResetPin,  LOW);
  digitalWrite(audioStrobePin, LOW);
  delay(1);
 
  // Reset the MSGEQ7 as per the datasheet timing diagram
  digitalWrite(audioResetPin,  HIGH);
  delay(1);
  digitalWrite(audioResetPin,  LOW);
  digitalWrite(audioStrobePin, HIGH); 
  delay(1);
}


// int counter = 0;
// int sum = 0;

// int max = 0;
// int min = 9999;

void loop() {
  // Speed of actuator motor
  int pwmOutput = 150;
  analogWrite(motorPwmOutputPin, pwmOutput);

  // * Check if audio input is above threshold

  measureAudioSignals();
  bool talking = checkAudio();

  // If so, check if audio is high or low?

  // * If so, move mouth
  // * If not, make sure mouth is closed
  if(talking){
    extend(200);
    retract(200);
  } else {
    retract(200);
  }
}

void measureAudioSignals(){
  for (int i = 0; i < 7; i++) {
    digitalWrite(audioStrobePin, LOW);
    delayMicroseconds(100);                    // Delay necessary due to timing diagram
    level[i] = analogRead (audioOutputPin);
    digitalWrite(audioStrobePin, HIGH);
    delayMicroseconds(100);                    // Delay necessary due to timing diagram  
  }
    Serial.println("");
    Serial.print(level[0]);
    Serial.print(" - ");
    Serial.print(level[1]);
    Serial.print(" - ");
    Serial.print(level[2]);
    Serial.print(" - ");
    Serial.print(level[3]);
    Serial.print(" - ");
    Serial.print(level[4]);
    Serial.print(" - ");
    Serial.print(level[5]);
    Serial.print(" - ");
    Serial.println(level[6]);
    Serial.println("");
}

// * Loop through each list of frequncies.
// * If average of the readings are at least ~50 over average, start moving mouth.
// * If none are above averages, return false to stop sound

// ? Baselines for 7 channels
// *1   Average: 49
// *2   Average: 63
// *3   Average: 57
// *4   Average: 70
// *5   Average: 90
// *6   Average: 110
// *7   Average: 139

int dict[7][6] =  { {0,0,0,0,0,0},  {0,0,0,0,0,0},  {0,0,0,0,0,0},  {0,0,0,0,0,0},  {0,0,0,0,0,0},  {0,0,0,0,0,0},  {0,0,0,0,0,0}};
int keys[7] = {100, 115, 115, 120, 140, 160, 190};
int index = 0;

bool checkAudio() {  
  for (int i = 0; i < 7; i++) {
    dict[i][index] = level[i];

    int sum = 0;
    for(int j = 0; j < 6; j++){
      sum = sum + dict[i][j];
    }

    int avg = sum / 6; 

    if(avg > keys[i]){
      if(index > 4) {
        index = 0;
      } else {
        index = index + 1;
      }
      return true;
    }

  }
  if(index > 4) {
    index = 0;
  } else {
    index = index + 1;
  }
  


  // * Loop through each list of frequncies.
  // * If average of the readings are at least ~50 over average, start moving mouth.
  // * If none are above averages, return false to stop sound

  // ? Baselines for 7 channels
  // *1   Average: 49
  // *2   Average: 63
  // *3   Average: 57
  // *4   Average: 70
  // *5   Average: 90
  // *6   Average: 110
  // *7   Average: 139

  return false;
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