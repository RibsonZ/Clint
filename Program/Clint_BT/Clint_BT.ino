#include "Servo.h"
#define RX 0
#define TX 1
#define SERVO 3
#define BUFFER_SIZE 63
#define CENTER_POS 100
#define LEFT_POS 50
#define RIGHT_POS 150

void pan_to(String buff);

const String Left = "left\n";
const String Center = "center\n";
const String Right = "right\n";

String buff = Center;
Servo CamPan;

void setup() {
  pinMode(RX, INPUT);
  pinMode(TX, OUTPUT);
  pinMode(SERVO, OUTPUT);
  CamPan.attach(SERVO);
  Serial.begin(9600);
//  Serial.println("Hello boss!");
  CamPan.write(CENTER_POS);
}

void loop() {
  if (Serial.available()) {
    buff = Serial.readString();
//    Serial.println(buff);
  }
  pan_to();
}

void pan_to() {
  static unsigned char pos = CENTER_POS, new_pos = CENTER_POS;
  static String old_buff = Center;
  if(old_buff != buff){
    if(Left == buff) {
      new_pos = LEFT_POS;
//      Serial.println("To the left, boss!");
    }
    else if(Center == buff) {
      new_pos = CENTER_POS;
//      Serial.println("To the center, boss!");
    }
    else if(Right == buff) {
      new_pos = RIGHT_POS;
//      Serial.println("To the right, boss!");
    }
    old_buff = buff;
  }
  
  for(;new_pos > pos; pos++) {
    CamPan.write(pos);
    delay(5);
  }

  for(;new_pos < pos; pos--) {
    CamPan.write(pos);
    delay(5);
  }
}
