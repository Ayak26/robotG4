#define M1 4  //Motor left direction
#define E1 5  //Motor left speed
#define E2 6  //Motor right speed
#define M2 7  //Motor right direction
#define LS1 A0 //Sensor far left
#define LS3 A1 //Sensor left
#define LS2 A2 //Sensor right
#define LS4 A3 //Sensor far right

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


int val1;
int val2;
int val3;
int val4;
int turn = 4000; //Test: time needed to turn 90  degrees.
const int black = 500;
char receivedChar;
bool loaded = false;
bool sent = false;
bool on = false;

void loop() {
  if (on) {
    //Infinite loop to test communication
    if (!sent) {
      if (loaded) {
        serialOutput('U');
      } else {
        serialOutput('L');
      }
    }
  } else {
    //Make proper reset
    stopMotors();
    loaded = false;
    sent = false;
  }

  serialInput();

}

//------------- Motor controls -------------

void motor1(int PWM, boolean forward) {
  analogWrite(E1, PWM);
  if (forward) {
    digitalWrite(M1, HIGH);
  } else {
    digitalWrite(M1, LOW);
  }
}

void motor2(int PWM, boolean forward) {
  analogWrite(E2, PWM);
  if (forward) {
    digitalWrite(M2, LOW);
  } else {
    digitalWrite(M2, HIGH);
  }
}

void forward() {
  motor1(255, true);
  motor2(255, true);
}

void backwards() {
  motor1(255, false);
  motor2(255, false);
}

void left() {
  motor1(255, false);
  motor2(255, true);
}

void right() {
  motor1(255, true);
  motor2(255, false);
}

void adjustLeft() {
  motor1(180, true);
  motor2(240, true);
}

void adjustRight() {
  motor1(240, true);
  motor2(180, true);
}

void turnAround() {
  motor1(255, false);
  motor2(255, true);
}

void stopMotors() {
  motor1(0, false);
  motor2(0, false);
}

//------------- Serial communication -------------

void serialInput() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    if (receivedChar == 'I') {
      on = true;
    }
    if (receivedChar == 'O') {
      on = false;
    }

    if (on) {
      if (receivedChar == 'L') {
        loaded = true;
        sent = false;
      }
      if (receivedChar == 'U') {
        loaded = false;
        sent = false;
      }

    }
  }
}

void serialOutput(char output) {
  Serial.println(output);
  sent = true;
}