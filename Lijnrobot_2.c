#define M3 4
#define E3 5
#define LDR A0
#define BUT 2 //ON/OFF


//------------- Constant variables -------------

const int sensor = 200; //Makkelijk bovenaan voor snelle aanpassing voor LDR gevoeligheid

//------------- Changing variables -------------

int LDRvalue;
int cargo = 0; 
char receivedChar;

//------------- Switches -------------

bool on = false;
bool pressed = false; // Zorgt dat aan/uit knop niet ingehouden kan worden voor continu aan/uit gaan.
bool reset = false;
bool loaded = false;
bool needAction = false; // Zorgt dat het in serialInput blijft wachten totdat de LDR iets ziet, voordat hij gaat laden.

void setup() {
  pinMode(LDR, INPUT);
  pinMode(BUT, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(E3, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUT), on_off, CHANGE);
  Serial.begin(9600);
}


void loop() {

  if (on) {
    multiplex(1);
    serialInput();
  } else {
    if (reset) {
      stopMotor();
      ledOff();
      cargo = 0;
      loaded = false;
      reset = false;
      needAction = false;
    }
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
  switch (tel) {
    case 1:
      one();
      break;
    case 2:
      two;
      break;
    default:
      zero();
      break;
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
    if (digitalRead(BUT) == LOW) {
      if (on) {
        on = false;
        reset = true;
        Serial.println('O');
      } else {
        on = true;
        Serial.println('I');
      }
      pressed = true;
    }
  } else {
    if (digitalRead(BUT) == HIGH) {
      pressed = false;
    }
  }

}

//------------- Serial communication -------------

void serialInput() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    needAction = true;
  }

  while (needAction) {
    if (on) {
      
      multiplex(1);
      
      if (receivedChar == 'L') {
        if (!loaded) {
          if (analogRead(LDR) < sensor) {
            load();
            needAction = false;
          }
        }
      }

      if (receivedChar == 'U') {
        if (loaded) {
          unload();
          needAction = false;
        }
      }
      
    }
  }
  
}
