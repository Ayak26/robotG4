//#include "SevSeg.h"
#define LDRpin A0
  int LDRValue = 0;     // result of reading the analog pin
   int i = 0;
//
//SevSeg sevseg; 
void setup(){
    pinMode(2, OUTPUT); 
    pinMode(3, OUTPUT); 
    pinMode(4, OUTPUT); 
    pinMode(5, OUTPUT); 
    pinMode(6, OUTPUT); 

    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
  Serial.begin(9600); // sets serial port for communication
}


  void teller(int tel){
    if(tel == 1){
            digitalWrite(8, HIGH);  
  //  digitalWrite(9, HIGH);  
  //digitalWrite(10, HIGH);  
  digitalWrite(11, HIGH);  
  //digitalWrite(12, HIGH); 
 // digitalWrite(13, HIGH);
    } else if(tel == 2){
                  digitalWrite(8, HIGH);  
    digitalWrite(9, HIGH);  
  digitalWrite(10, HIGH);  
  digitalWrite(11, LOW);  
  digitalWrite(12, HIGH); 
  digitalWrite(13, HIGH);
    }
  }
  
void loop(){


  LDRValue = analogRead(LDRpin); // read the value from the LDR
  Serial.println(LDRValue);      // print the value to the serial port
  delay(1000);
 

 
  if(LDRValue < 40) {
        digitalWrite(2, LOW);  
    digitalWrite(3, LOW);  
  digitalWrite(4, HIGH);  
  digitalWrite(5, HIGH);  
  digitalWrite(6, HIGH); 
  Serial.println(i);
  i++;
  teller(i);
  } else if(LDRValue > 40){
      digitalWrite(2, HIGH);  
    digitalWrite(3, HIGH);  
  digitalWrite(4, HIGH);  
  digitalWrite(5, HIGH);  
  digitalWrite(6, HIGH);  
  }

  
  }
              