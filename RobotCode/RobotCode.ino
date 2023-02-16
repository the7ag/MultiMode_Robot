// #define enA 5 //speed of M1
// #define enB 6  //speed of M2
#define in1 5 //if 1 then fwd M1
#define in2 6 //if 1 then bwd M1
#define in3 10 //if 1 then fwd M2
#define in4 11 //if 1 the bwd M2
/* ********************** */
#define S_R A0
#define S_L A3
/* ********************** */
char mode;  // mode = 2 --> Obstacle Avoider ; 1 -->Line Folower ; 0 --> Remote Controlled Car
char state;
bool Flag;
void setup() {
  Serial.begin(9600);
  pinMode(S_R,INPUT);
  pinMode(S_L,INPUT);
 // pinMode(enA,OUTPUT);
  //pinMode(enB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
}

void loop() {
  Stop();
  while(Serial.available()>0){
  mode = Serial.read();
  if (mode == 'V'){
    Flag = 1;
    while (Flag){
      state = Serial.read();
      switch (state)
      {
        case 'F':
          forward();
          delay(5);
          break;
        case 'L':
          right();
          delay(5);
          break;
        case 'R':
          left();
          delay(5);
          break;
        case 'B':
          reverse();
          delay(5);
          break;
        case 'I':
          F_Right();
          delay(5);
          break;
        case 'G':
          F_Left();
          delay(5);
          break;
          case 'H':
          B_Left();
          delay(5);
          break;
        case 'J':
          B_Right();
          delay(5);
          break;
        case 'S':
          Stop();
          delay(5);
          break;
        case 'W':
          Flag=0;
          break;
        case 'w':
          Flag=0;
          break;
      }
      //Stop();
    }
  }
  else if (mode == 'v' )
  {
    Flag = 1;
  while(Flag){
  if(digitalRead(S_R) == HIGH && digitalRead(S_L) == LOW){
    //Stop();
    //delay(5);
    right_LF();
    //delay(5);
  }
  else if(digitalRead(S_R) == LOW && digitalRead(S_L) == HIGH){
    //Stop();
    //delay(5);
    left_LF();
    //delay(5);
  }
  else if(digitalRead(S_R) == LOW && digitalRead(S_L) == LOW){
    forward_LF();
    //delay(5);
  }
  else if(digitalRead(S_R) == HIGH && digitalRead(S_L) ==HIGH){
    right_LF();
    //delay(5);
    }
  /*else if (mode =='2'){
    Obstacle();
  }*/
  char x = Serial.read();
    if (x=='W'){
      Flag = 0;
    }
    else if (x=='w'){
      Flag = 0;
    }
  }
  }
  }
}
void forward_LF(){  
  //analogWrite(enA,150);
  //analogWrite(enB,150);
  // analogWrite(in1,100);
  // analogWrite(in2,0);
  // analogWrite(in3,100);
  // analogWrite(in4,0);
  analogWrite(in1,100);
  analogWrite(in2, 0);
  analogWrite(in3, 100);
  analogWrite(in4, 0);
  
}
void right_LF(){
 // analogWrite(enA,150);
  //analogWrite(enB,150);
  // analogWrite(in1,0);
  // analogWrite(in2,0);
  // analogWrite(in3,100);
  // analogWrite(in4,0);
  // Turn Right
  analogWrite(in1,0);
  analogWrite(in2, 100);
  analogWrite(in3, 100);
  analogWrite(in4,0);

}
void left_LF(){
 // analogWrite(enA,150);
  //analogWrite(enB,150);
  // analogWrite(in1,100);
  // analogWrite(in2,0);
  // analogWrite(in3,0);
  // analogWrite(in4,0);
  analogWrite(in1,100);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 100);
}


void forward(){  
  //analogWrite(enA,150);
  //analogWrite(enB,150);
  analogWrite(in1,150);
  analogWrite(in2,0);
  analogWrite(in3,150);
  analogWrite(in4,0);
  
}
void right(){
 // analogWrite(enA,150);
  //analogWrite(enB,150);
  analogWrite(in1,0);
  analogWrite(in2,0);
  analogWrite(in3,150);
  analogWrite(in4,0);
}
void left(){
 // analogWrite(enA,150);
  //analogWrite(enB,150);
  analogWrite(in1,150);
  analogWrite(in2,0);
  analogWrite(in3,0);
  analogWrite(in4,0);
}
void reverse()
{
 // analogWrite(enA,150);
  //analogWrite(enB,150);
  analogWrite(in1,0);
  analogWrite(in2,150);
  analogWrite(in3,0);
  analogWrite(in4,150);
}
void Stop()
{
 // analogWrite(enA,0);
 // analogWrite(enB,0);
  analogWrite(in1,0);
  analogWrite(in2,0);
  analogWrite(in3,0);
  analogWrite(in4,0);
}
void B_Left(){
 // analogWrite(enA,255/2);
  //analogWrite(enB,255/2);
  analogWrite(in1,0);
  analogWrite(in2,150);
  analogWrite(in3,0);
  analogWrite(in4,150);
}
void B_Right(){
  //analogWrite(enA,255/2);
 // analogWrite(enB,255/2);
  analogWrite(in1,0);
  analogWrite(in2,150);
  analogWrite(in3,0);
  analogWrite(in4,150);
}
void F_Right(){
  //analogWrite(enA,255/2);
 // analogWrite(enB,255/2);
  analogWrite(in1,150);
  analogWrite(in2,0);
  analogWrite(in3,150);
  analogWrite(in4,0);
}
void F_Left(){
  //analogWrite(enA,255/2);
  //analogWrite(enB,255/2);
  analogWrite(in1,150);
  analogWrite(in2,0);
  analogWrite(in3,150);
  analogWrite(in4,0);
}