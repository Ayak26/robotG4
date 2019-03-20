#define E3 4
#define M3 5
#define LDRpin A0

int LDRValue = 0;     // result of reading the analog pin
int lading = 0;
boolean geladen = false;

void setup() {
  pinMode(2, OUTPUT);
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
  Serial.begin(9600);
}

void loop() {
  LDRvalue = analogRead(A0);
  if (geladen) {
    l();
    teller(lading);
  }else {
    e();
    teller(lading);
  }
}

void motor(int PWM, boolean omhoog) {
  analogWrite(E3, PWM);
  if (omhoog) {
    digitalWrite(M3, HIGH);
  } else {
    digitalWrite(M3, LOW);
  }
}

void laad() {
  motor(200, true);
  delay(200); //preciese delay testen
  motor(0, false);
  lading++;
  geladen = !geladen;
  Serial.write(1);
}

void los() {
  motor(200, false);
  delay(200); //preciese delay testen
  motor(0, true);
  geladen = !geladen;
  Serial.write(2);
}

void e() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}

void l() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
}

void teller(int tel) {
  if (tel==0) {
    nul();
  } else if (tel==1) {
    een();
  } else if (tel==2) {
    twee();
  }
}

void nul() {
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}

void een() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}

void twee() {
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}

void serialEvent() {
  byte byteIn = Serial.read();
  if (byteIn == 1 && !geladen && LDRvalue < 10) {
    laad();
  } else if (byteIn == 1 && geladen) {
    los();
  }
}