#define M1 4  //Motor left direction
#define E1 5  //Motor left speed
#define E2 6  //Motor right speed
#define M2 7  //Motor right direction
#define LS1 A0 //Sensor far left
#define LS2 A1 //Sensor left
#define LS3 A2 //Sensor right
#define LS4 A3 //Sensor far right

//------------- Constant variables -------------

const int turn = 400; //Test: time needed to turn 90  degrees.
const int black = 500;

//------------- Changing variables -------------

int LS1value;
int LS2value;
int LS3value;
int LS4value;
int cargo = 0;
char receivedChar;

//------------- Switches -------------

bool loaded = false;
bool sent = false;
bool on = false;
bool justTurned = false;
bool turned = false;
bool busy = false;
bool takeFirstTurn = cargo%2!=0;

void setup() {
  pinMode(E1, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  pinMode(LS3, INPUT);
  pinMode(LS4, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (on) {
    followLine();
  }
  delay(10);
  serialInput();
}


//------------- Motor controls -------------

//Left
void motor1(int PWM, boolean forward) {
  analogWrite(E1, PWM);
  if (forward) {
    digitalWrite(M1, HIGH);
  } else {
    digitalWrite(M1, LOW);
  }
}

//Right
void motor2(int PWM, boolean forward) {
  analogWrite(E2, PWM);
  if (forward) {
    digitalWrite(M2, HIGH);
  } else {
    digitalWrite(M2, LOW);
  }
}

void forward(int steps) {
  for (int i = 0; i < steps; i++) {
    serialInput();
    if (on) {
      motor1(255, true);
      motor2(255, true);
      delay(10);
    } else {
      break;
    }
  }
}

void forward() {
  motor1(255, true);
  motor2(255, true);
}

void backward(int steps) {
  for (int i = 0; i < steps; i++) {
    serialInput();
    if (on) {
      motor1(255, false);
      motor2(255, false);
      delay(10);
    } else {
      break;
    }
  }
}

void left(int steps) {
  forward(40);
  for (int i = 0; i < steps; i++) {
    serialInput();
    if (on) {
      motor1(255, false);
      motor2(255, true);
      delay(10);
    } else {
      break;
    }
  }
  justTurned = true;
  turned = true;
}

void right(int steps) {
  forward(40);
  for (int i = 0; i < steps; i++) {
    serialInput();
    if (on) {
      motor1(255, true);
      motor2(255, false);
      delay(10);
    } else {
      break;
    }
  }
  justTurned = true;
  turned = true;
}

void turnAround(int steps) {
  for (int i = 0; i < steps; i++) {
    serialInput();
    if (on) {
      motor1(255, true);
      motor2(255, false);
      delay(10);
    } else {
      break;
    }
  }
  justTurned = true;
}

void adjustRight() {
  motor1(150, true);
  motor2(255, true);
}

void adjustLeft() {
  motor1(255, true);
  motor2(150, true);
}

void stopMotors() {
  motor1(0, false);
  motor2(0, false);
}

void followLine() {
  if (!busy) {
    if (justTurned) {
      forward(100);
      justTurned = false;
    } else {
      readSensors();
      if (LS1value > black) {
        if (LS2value > black) {
          if (LS3value > black) {
            if (LS4value > black) {
              if (turned) {
                stopMotors();
                if (loaded) {
                  Serial.println('U');
                  busy = true;
                } else {
                  Serial.println('L');
                  busy = true;
                }
                turned = false;
              } else {
                right(turn);
              }
            } else {
              if (takeFirstTurn) {
                if (!turned) {
                  left(turn);
                }
              } else {
                forward(150);
              }
            }
          } else {
            adjustRight();
          }
        } else {
          adjustRight();
        }
      } else if (LS2value > black) {
        if (LS3value > black) {
          if (LS4value > black) {
            if (!turned) {
              right(turn);
            }
          } else {
            forward();
          }
        } else {
          adjustRight();
        }
      } else if (LS3value > black) {
        if (LS4value > black) {
          adjustLeft();
        } else {
          adjustLeft();
        }
      } else if (LS4value > black) {
        adjustLeft();
      }
    }
  }
}

//------------- Sensor functions -------------

void readSensors() {
  LS1value = analogRead(LS1);
  LS2value = analogRead(LS2);
  LS3value = analogRead(LS3);
  LS4value = analogRead(LS4);
}

//------------- Serial communication -------------

void serialInput() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    if (receivedChar == 'I') {
      on = true;
    }
    if (receivedChar == 'O') {
      stopMotors();
      loaded = false;
      sent = false;
      receivedChar = '\0';
      justTurned = false;
      turned = false;
      busy = false;
    }

    if (on) {
      if (receivedChar == 'L') {
        loaded = true;
        cargo++;
        sent = false;
        busy = false;
        turnAround(2 * turn);
      }
      if (receivedChar == 'U') {
        loaded = false;
        sent = false;
        busy = false;
        backward(100);
        turnAround(2 * turn);
      }

    }
  }
}
