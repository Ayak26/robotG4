int E1 = 5;
int M1 = 4;
int E2 = 6;
int M2 = 7;
int snelheidM1 = 0; //set snelheid van motor 1, motor 1 is de linker rupsband
int snelheidM2 = 0; // set snelheid van motor 2, motor 2 is de rechter rupsband

void draaiL() {
  int M1 = -250;
  int M2 = 250;
  links(M1);
  rechts(M2);
}
void draaiLinker(){
  int M1 = 250;
  int M2 = 0;
  links(M1);
  rechts(M2);
}
void draaiRechter(){
  int M1 = 0;
  int M2 = 250;
  links(M1);
  rechts(M2);
}
void draaiR() {
  int M1 = 250;
  int M2 = -250;
  links(M1);
  rechts(M2);
}
void rechtdoor() {
  int M1 = 250;
  int M2 = 250;
  links(M1);
  rechts(M2);
}
int links(int i) {
  snelheidM1 = i;
}

int rechts (int i) {
  snelheidM2 = i;
}

void setup()
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void loop()
{
  draaiL();
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, snelheidM1);   //PWM Speed Control
  analogWrite(E2, snelheidM1);   //PWM Speed Control
}