#define M1 4  //Motor rechts richting
#define E1 5  //Motor rechts snelheid
#define E2 6  //Motor links snelheid
#define M2 7  //Motor links richting
#define KNOP 2 //Aan/uit knop
#define LS1 A0 //Ver links
#define LS2 A1 //Midden links
#define LS3 A2 //Midden rechts
#define LS4 A3 //Ver rechts
#define LS5 A4 //Voorkant

void setup() {
  pinMode(E1, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(KNOP, INPUT_PULLUP);
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  pinMode(LS3, INPUT);
  pinMode(LS4, INPUT);
  pinMode(LS5, INPUT);
  Serial.begin(9600);
}

boolean on = false;
boolean bruikbaar = true;
int draai = 2000; //testen hoelang het duurt om 90 graden te draaien.
int zwart = 800;
int lospunt = 0;
void loop() {
  if (digitalRead(KNOP) == LOW && bruikbaar) {
    on = !on;
    bruikbaar = !bruikbaar;
  }
  while (on) {
    if (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart && analogRead(LS3) >= zwart && analogRead(LS4) >= zwart) {
      stopMotors();
      Serial.write(1);
    }
    vooruit();
    delay(2000);
    if (analogRead(LS4) >= zwart) {
      rechts();
    }
    vooruit();
    if (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart && analogRead(LS3) >= zwart && analogRead(LS4) >= zwart) {
      stopMotors();
      Serial.write(1);
    }
    vooruit();
    if (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart && analogRead(LS3) >= zwart && analogRead(LS4) >= zwart) {
      links();
    }
    vooruit();
    if (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart && analogRead(LS3) >= zwart && analogRead(LS4) >= zwart) {
      stopMotors();
      Serial.write(1);
    }
    vooruit();
    delay(2000):
      if (analogRead(LS4) >= zwart && analogRead(LS5) >= zwart {
    rechts();
    }
    vooruit();
    if (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart && analogRead(LS3) >= zwart && analogRead(LS4) >= zwart) {
    stopMotors();
      Serial.write(1);
    }
    vooruit();
    if   (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart && analogRead(LS3) >= zwart) {
    links();
    }
    vooruit();
    if (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart && analogRead(LS3) >= zwart && analogRead(LS4) >= zwart) {
    stopMotors();
      Serial.write(1);
    }


    if (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart && analogRead(LS3) >= zwart && analogRead(LS4) >= zwart && analogRead(LS5) >= zwart) {
    links();
    } else if (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart && analogRead(LS3) >= zwart && analogRead(LS4) >= zwart) {
    stopMotors();
      Serial.write(1);
    } else if (analogRead(LS2) >= zwart && analogRead(LS3) >= zwart && analogRead(LS4) >= zwart && analogRead(LS5) >= zwart && lospunt % 2 != 0) {
    rechts();
    } else if (analogRead(LS2) >= zwart && analogRead(LS3) >= zwart && analogRead(LS4) >= zwart) {
    rechts();
    } else if (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart && analogRead(LS3) >= zwart) {
    links();
    } else if (analogRead(LS2) >= zwart && analogRead(LS3) >= zwart) {
    vooruit();
    } else if (analogRead(LS3) >= zwart && analogRead(LS4) >= zwart) {
    bijstellenRechts();
    } else if (analogRead(LS1) >= zwart && analogRead(LS2) >= zwart) {
    bijstellenLinks();
    }
  }
}

void motor1(int PWM, boolean vooruit) {
  analogWrite(E1, PWM);
  if (vooruit) {
    digitalWrite(M1, HIGH);
  } else {
    digitalWrite(M1, LOW);
  }
}

void motor2(int PWM, boolean vooruit) {
  analogWrite(E2, PWM);
  if (vooruit) {
    digitalWrite(M2, HIGH);
  } else {
    digitalWrite(M2, LOW);
  }
}

void vooruit() {
  motor1(255, true);
  motor2(255, true);
}

void achteruit() {
  motor1(255, false);
  motor2(255, false);
}

void rechts() {
  motor1(255, false);
  motor2(255, true);
  delay(draai);
}

void links() {
  motor1(255, true);
  motor2(255, false);
  delay(draai);
}

void bijstellenRechts() {
  motor1(240, true);
  motor2(255, true);
}

void bijstellenLinks() {
  motor1(255, true);
  motor2(240, true);
}

void omdraaien() {
  motor1(255, false);
  motor2(255, true);
  delay(2 * draai);
}

void stopMotors() {
  motor1(0, false);
  motor2(0, false);
}

void serialEvent() {
  byte byteIn = Serial.read();
  if (byteIn == 1) {
    lospunt++;
    omdraaien();
  } else if (byteIn == 2) {
    achteruit();
    delay(200); //testen
    omdraaien();
  }
}