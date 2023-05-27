#include <NewPing.h>
#include <Servo.h>

int distance;
// UltraSonic Configurations
#define Echo A1
#define Trigger A0
#define MAX_DISTANCE 250   // Max Range
NewPing Sonar(Trigger,Echo,MAX_DISTANCE);

// boolean Forward lllb=c false;
#define white LOW
#define black HIGH

// Servo Configurations
#define SERVO_PIN 10
Servo myServo;


// L298 Driver
// Right Motor
#define IN1 13
#define IN2 12
#define ENA 11
// Left Motor
#define IN3 9
#define IN4 8
#define ENB 6

// Middle Sensor
#define IR_Input_M 7 
// Right Sensor
#define IR_Input_R 4 
// Left Sensor
#define IR_Input_L 2

// Reading the sensors value
  // int sensorState_M = digitalRead(IR_Input_M);
  // int sensorState_R = digitalRead(IR_Input_R);
  // int sensorState_L = digitalRead(IR_Input_L);



// Turning all Motors in forward direction
void Forward_dir(){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
}

void Forward_dir_Slow(){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENB,150);
    analogWrite(ENA,150);
}

// Turning all Motors in backward direction
void Backward_dir(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

// Stop all motors
void Stop_motors(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

// Turning Right
void Right_dir(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void Right_dir_Slow(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(ENB,120);
  // analogWrite(ENA,120);
}

void R_Right_dir(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENB,100);
  analogWrite(ENA,100);
}

void S_R_Right_dir_Slow(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENB,120);
  analogWrite(ENA,190);

}

// Turning Left
void Left_dir(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}
void R_Left_dir(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENB,100);
  analogWrite(ENA,100);
}

void S_R_Left_dir_Slow(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENA,120);
  analogWrite(ENB,190);
}


//servo configrations

int readSensor(){
  delay(70);
  int readingCm = Sonar.ping_cm();
  if (readingCm == 0){
    readingCm = 250;
  }
  return readingCm;
}


// Checker Function To Check If The Car Is Still On Track 
// bool Line_Status;
// bool checkTrack_LF() 
// {
//   if(sensorState_L == HIGH && sensorState_R == HIGH && sensorState_M == HIGH){  // If all sensors are not on the black line
//     delay(1500);
//     if(sensorState_L == HIGH && sensorState_R == HIGH && sensorState_M == HIGH)
//     {
//       Line_Status = false;
//     }else
//     {
//       Line_Status = true;
//     }
    
//   }
//   return Line_Status;
// }



// Servo Look Right -
int lookRight(){
  myServo.write(85);            // First Angle
  delay(600);
  int distance_1 = readSensor();
  
  myServo.write(50);            // Second Angle
  delay(600);
  int distance_2 = readSensor();
  delay(100);
  int distacne = distance_1 + distance_2;

  myServo.write(120);                        // setting servo back to center
  return distance;
}

// Servo Look Left -
int lookLeft(){
  myServo.write(150);            // First Angle
  delay(600);
  int distance_1 = readSensor();
  
  myServo.write(180);            // Second Angle
  delay(600);
  int distance_2 = readSensor();
  delay(100);
  int distacne = distance_1 + distance_2;
  
  myServo.write(120);                        // setting servo back to center
  return distance;
}

int distanceRight;
int distanceLeft;


void Collision_Avoidance(){
  delay(50);
  

  if(distance<=16){
    Stop_motors();
    delay(300);
    Backward_dir();
    delay(250);
    Stop_motors();
    delay(50);
    distanceRight = lookRight();
    delay(50);
    distanceLeft = lookLeft();
    delay(50);

    if (distance >= distanceLeft)    // If There Is Obstacle At Left Direction
    {
      Right_dir();
      delay(600);
      Stop_motors();
      delay(50);
      Forward_dir();
      delay(1200);
      Stop_motors();
      delay(50);
      Left_dir();
      delay(600);
    }

    else if(distance <= distanceLeft) // If There Is Obstacle At Right Direction
    {
      Left_dir();
      delay(600);
      Stop_motors();
      delay(50);
      Forward_dir();
      delay(1200);
      Stop_motors();
      delay(50);
      Right_dir();
      delay(600);
    }
  }
  // else
  // {
  //   while(sensorState_L == HIGH || sensorState_R == HIGH || sensorState_M == HIGH)
  //   {
  //     Forward_dir();
  //   }
  //   LineFollowerMode();
  // }
  // distance = readSensor();
}

  // // Reading the sensors value


void LineFollowerMode(){

  int sensorState_M = digitalRead(IR_Input_M);
  int sensorState_R = digitalRead(IR_Input_R);
  int sensorState_L = digitalRead(IR_Input_L);

  if(sensorState_L == 0 && sensorState_R == 0){       // Both sensors are on white surface
    Forward_dir_Slow();
  }
  else if(sensorState_L == 1 && sensorState_R == 0){       // If the left sensor on the black line
    // analogWrite(ENA,255);
    // analogWrite(ENB,255);
    R_Left_dir();
  }
  else if(sensorState_L == 0 && sensorState_R == 1){       // If the right sensor on the black line
    // analogWrite(ENA,255);
    // analogWrite(ENB,255);
    R_Right_dir();
  }
  else if(sensorState_L == 0 && sensorState_R == 0 && sensorState_M == 0){  // If all sensors are not on the black line
    delay(1100);
    if(sensorState_L == 0 && sensorState_R == 0 && sensorState_M == 0)
    {
    Stop_motors();
    delay(50);
    Backward_dir();
    delay(900);
    }
  }
}

void LineFollowerMode_v2(){
  // Reading the sensors value
  int sensorState_R = digitalRead(IR_Input_R);
  int sensorState_L = digitalRead(IR_Input_L);
  int sensorState_M = digitalRead(IR_Input_M);

  if(sensorState_L == 0 && sensorState_R == 0){             // Both sensors are on white surface
    Forward_dir_Slow();
  }else if(sensorState_L == 1 && sensorState_R == 0){       // If the left sensor on the black surface
    R_Left_dir();
  }else if(sensorState_L == 0 && sensorState_R == 1){       // If the right sensor on the black surface
    R_Right_dir();
  // }else if(sensorState_L == white && sensorState_R == white && sensorState_M == white)
  // {
  //   Backward_dir();
  //   delay(500);
  // }
}
}
// 55555 white reads LOW   0
// 55555 black reads HIGH  1





void setup() {

  myServo.attach(SERVO_PIN);

  // Motors Configurations
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);


  // IR Configurations
  pinMode(IR_Input_M,INPUT);
  pinMode(IR_Input_R,INPUT);
  pinMode(IR_Input_L,INPUT);

  // Collison Configurations
  myServo.write(120);
  delay(2000);
  distance = readSensor();
  delay(100);
  distance = readSensor();
  delay(100);
  distance = readSensor();
  delay(100);
  distance = readSensor();
  delay(100);

}


void loop() {
  // while(distance>=16)
  // {
  //   LineFollowerMode();
  // }
  // else
  // {
  //   Collision_Avoidance();
  // }
  // Forward_dir_Slow();
  LineFollowerMode_v2();
  // Right_dir();
  // delay(2000);
  // Right_dir_Slow();
}






