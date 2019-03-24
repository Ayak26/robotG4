#define M3 4
#define E3 5
#define LDRpin A0
#define KNOP 2 //ON/OFF

int LDRvalue = 0;
int cargo = 0; //Number of the cargo being moved
char receivedChar;
bool loaded = false;
bool on = false;
bool pressed = false;

void setup() {
  pinMode(LDRpin, INPUT);
  pinMode(KNOP, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(E3, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  on_off();

  if (on) {
    multiplex(1);
    serialInput();
  } else {
    stopMotor();
    ledOff();
    cargo = 0;
    loaded = false;
  }
}


//------------- Motor controls -------------

void motor(int PWM, boolean up) {
  analogWrite(E3, PWM);
  if (up) {
    digitalWrite(M3, HIGH);
  } else {
    digitalWrite(M3, LOW);
  }
}

void load() {
  motor(255, true);
  multiplex(1000);
  stopMotor();
  cargo++;
  loaded = true;
  Serial.println('L');
}

void unload() {
  motor(255, false);
  multiplex(850);
  stopMotor();
  loaded = false;
  Serial.println('U');
}

void stopMotor() {
  motor(0, true);
}

//------------- 7 segment display 1 -------------

void e() {
  digitalWrite(3, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

void l() {
  digitalWrite(3, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

void counter(int tel) {
  if (tel == 0) {
    zero();
  } else if (tel == 1) {
    one();
  } else if (tel == 2) {
    two();
  } else {
    zero();
  }
}

//------------- 7 segment display 2 -------------

void zero() {
  digitalWrite(3, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

void one() {
  digitalWrite(3, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

void two() {
  digitalWrite(3, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

void ledOff() {
  digitalWrite(3, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

//------------- 7 segment displays combined -------------

void multiplex(int steps) {
  for (int i = 0; i < steps; i++) {
    on_off();
    if (on) {
      if (loaded) {
        l();
        delay(2);
        counter(cargo);
        delay(2);
      } else {
        e();
        delay(2);
        counter(cargo);
        delay(2);
      }
    } else {
      break;
    }
  }
}

void on_off() {
  if (!pressed) {
    if (digitalRead(KNOP) == LOW) {
      if (on) {
        //Make proper reset
        on = false;
        Serial.println('O');
      } else {
        on = true;
        Serial.println('I');
      }
      pressed = true;
    }
  } else {
    if (digitalRead(KNOP) == HIGH) {
      pressed = false;
    }
  }

}

//------------- Serial communication -------------

void serialInput() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
  }
  if (on) {
    if (receivedChar == 'L') {
      if (!loaded) {
        load();
      }
    }
    if (receivedChar == 'U') {
      if (loaded) {
        unload();
      }
    }
  }
}
