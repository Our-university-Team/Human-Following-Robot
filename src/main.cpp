//Human Following Robot
//BY: Mostafa Ayman 18105341
//    Shady Hisham  18104105

#include <Arduino.h>
#include<NewPing.h>           
#include<Servo.h>

//Definitions
#define Trigger PC14
#define Echo PC13
#define ServoPin PA1
#define Left_IR PA8
#define Right_IR PB7
#define Enable_Left PA7 // speed control for left motors
#define Enable_Right PA6 // speed control for right motors    
#define IN1 PA11   //left motors forward direction
#define IN2 PA12   //left motors backward direction
#define IN3 PA15   //right motors forward direction
#define IN4 PB3    //right motors backward direction
#define max_distance 200 //max ping distance

//Variale initialization
unsigned int distance = 0;    //to store ultrasonic sensor distance:
unsigned int Right_IR_Value = 0; //to store Right IR sensor value:
unsigned int Left__IR_value = 0;  //to store Left IR sensor value:
NewPing human_distance(Trigger,Echo,max_distance);//setup of max distance and pins for ping
Servo myservo;//creating servo object
int position=0;//to store servo position 


void setup() {
    
    myservo.attach(ServoPin);//servo is attached to servoPin(A1)

//Initially, servo starts at center(113). It goes from center(113)->left(180)->right(0)->center(113)


for(position = 113; position <= 180; position += 1){    // goes from center(113) to left(180)
  myservo.write(position);                   //tell servo to move
  delay(15);                            //wait 15ms for the servo to reach the position
  } 
for(position = 180; position >= 67; position-= 1) {     // goes from left(180) to right(0)
  myservo.write(position);                   //tell servo to move
  delay(15);                            //wait 15ms for the servo to reach the position
  }
for(position = 67; position<=113; position += 1) {       //goes from right(0) to center(113)
  myservo.write(position);                   //tell servo to move
  delay(15);                            //wait 15ms for the servo to reach the position
  }
  
//Input and Output Pins
pinMode(Right_IR,INPUT);
pinMode(Left_IR,INPUT);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
pinMode(Enable_Left,OUTPUT);
pinMode(Enable_Right,OUTPUT);

}

void loop() {

    delay(50);//wait 20ms between pings 
    distance=human_distance.ping_cm();//ping to get  in cm and store it in the variable "distance"

    //read ir sensors' values and store them in "Right_Value" and "Left_Value"
    Right_IR_Value=digitalRead(Right_IR);
    Left__IR_value=digitalRead(Left_IR);

    //move forward(1<distance<40)
    if(distance>12.5 && distance<35)
    {
        analogWrite(Enable_Left,120);//set speed for left motor
        digitalWrite(IN1,HIGH);//forward for left motor
        analogWrite(Enable_Right,120);//set speed for right motor
        digitalWrite(IN3,HIGH);//forward for right motor
        
        digitalWrite(IN2,LOW);//backward off for left motor
        digitalWrite(IN4,LOW);//backward off for right motor


        
    }

    //turn left(left ir=0)
    else if(Right_IR_Value==1 && Left__IR_value==0)
    {
        analogWrite(Enable_Left,100);//set speed for left motor
        digitalWrite(IN2,HIGH);//backward for left motor
        analogWrite(Enable_Right,100);//set speed for right motor
        digitalWrite(IN3,HIGH);//forward for right motor

        digitalWrite(IN1,LOW);//forward off for left motor
        digitalWrite(IN4,LOW);//backward off for right motor

        delay(150);
    }

    //turn right(right ir=0) 
    else if(Right_IR_Value==0 && Left__IR_value==1)  
    {
        analogWrite(Enable_Left,100);//set speed for left motor
        digitalWrite(IN1,HIGH);//forward for left motor
        analogWrite(Enable_Right,100);//set speed for right motor
        digitalWrite(IN4,HIGH);//backward for right motor

        digitalWrite(IN2,LOW);//backward off for left motor
        digitalWrite(IN3,LOW);//forward off for right motor


        delay(150);
    }


    //stop(very far distance>35)
    
    else if(distance>35)
    {
        analogWrite(Enable_Left,0);//set speed for left motor
        analogWrite(Enable_Right,0);//set speed for right motor
        digitalWrite(IN1,LOW);//forward off for left motor
        digitalWrite(IN2,LOW);//backward off for left motor
        digitalWrite(IN3,LOW);//forward off for right motor
        digitalWrite(IN4,LOW);//backward off for right motor

    }
    
}