// Jawad Mehmood Butt : Low-Level Code for active foldable quadrotors
// PWM MAIN MOTORS 400 Hz
// PWM Servo Motors 50 Hz
// You may use Arduino for this motor controls for the 4 motors of active foldable quadrotors. It can receive the motor commands from the ROS 
// motion control node running on the raspberry pi 4b

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif
#include <ros.h>
#include <ArduinoHardware.h>
#include <std_msgs/Int16.h>
#include <Servo.h> 
unsigned long timd = 0;
// Esc min-max in micro-sec
#define esc_min 2000
#define esc_max 4000


// ros handle
ros::NodeHandle nh;

#define servo1_pin 11 //45
#define servo2_pin 12 //11
#define servo3_pin 13 //12
#define servo4_pin 45 //13
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// MOtors and Servos
#define m2 OCR4A // motor2 Pin 6
int m_val2 = 0;
unsigned long newMills2;
unsigned long oldMills2;

#define m1 OCR4B // motor1 Pin 7
int m_val1 = 0;
unsigned long newMills1;
unsigned long oldMills1;

#define m3 OCR3A // motor3 Pin 5
int m_val3 = 0;
unsigned long newMills3;
unsigned long oldMills3;

#define m4 OCR3C // motor4 Pin 3
int m_val4 = 0;
unsigned long newMills4;

unsigned long oldMills4;

void motor1_cb( const std_msgs::Int16& msg)
{
  newMills1 = millis();
  if (newMills1 - oldMills1 >= 10)
  {

    m_val1 = msg.data;

    if (m_val1 <= esc_min)
    {
      m_val1 = esc_min;
    }

    if (m_val1 >= esc_max)
    {
      m_val1 = esc_max;
    }

    m1 = m_val1;
    oldMills1 = newMills1;
  }
}


void motor2_cb( const std_msgs::Int16& msg)
{
  newMills2 = millis();
  if (newMills2 - oldMills2 >= 10)
  {

    m_val2 = msg.data;

    if (m_val2 <= esc_min)
    {
      m_val2 = esc_min;
    }

    if (m_val2 >= esc_max)
    {
      m_val2 = esc_max;
    }

    m2 = m_val2;
    oldMills2 = newMills2;
  }
}

void motor3_cb( const std_msgs::Int16& msg)
{
  newMills3 = millis();
  if (newMills3 - oldMills3 >= 10)
  {

    m_val3 = msg.data;

    if (m_val3 <= esc_min)
    {
      m_val3 = esc_min;
    }

    if (m_val3 >= esc_max)
    {
      m_val3 = esc_max;
    }

    m3 = m_val3;
    oldMills3 = newMills3;
  }
}

void motor4_cb( const std_msgs::Int16& msg)
{
  newMills4 = millis();
  if (newMills4 - oldMills4 >= 10)
  {

    m_val4 = msg.data;

    if (m_val4 <= esc_min)
    {
      m_val4 = esc_min;
    }

    if (m_val4 >= esc_max)
    {
      m_val4 = esc_max;
    }

    m4 = m_val4;
    oldMills4 = newMills4;
  }
}

// servo callbacks
void servo1_cb( const std_msgs::Int16& msg)
{
 servo1.write(msg.data); //set servo angle, should be from 0-180
}

void servo2_cb( const std_msgs::Int16& msg)
{
 servo2.write(msg.data); //set servo angle, should be from 0-180
}

void servo3_cb( const std_msgs::Int16& msg)
{
 servo3.write(msg.data); //set servo angle, should be from 0-180
}

void servo4_cb( const std_msgs::Int16& msg)
{
 servo4.write(msg.data); //set servo angle, should be from 0-180
}

// servo subscribers
ros::Subscriber<std_msgs::Int16> sub_servo1("servo1", servo1_cb);
ros::Subscriber<std_msgs::Int16> sub_servo2("servo2", servo2_cb);
ros::Subscriber<std_msgs::Int16> sub_servo3("servo3", servo3_cb);
ros::Subscriber<std_msgs::Int16> sub_servo4("servo4", servo4_cb);
ros::Subscriber<std_msgs::Int16> sub_motor1("motor1", motor1_cb);
ros::Subscriber<std_msgs::Int16> sub_motor2("motor2", motor2_cb);
ros::Subscriber<std_msgs::Int16> sub_motor3("motor3", motor3_cb);
ros::Subscriber<std_msgs::Int16> sub_motor4("motor4", motor4_cb);


void setup() {
  // ============== init, sub, and pub===============
    nh.getHardware()->setBaud(115200);
    nh.initNode();
    nh.subscribe(sub_servo1);
    nh.subscribe(sub_servo2);
    nh.subscribe(sub_servo3);
    nh.subscribe(sub_servo4);
    nh.subscribe(sub_motor1);
    nh.subscribe(sub_motor2);
    nh.subscribe(sub_motor3);
    nh.subscribe(sub_motor4);

    // attachings servos
    servo1.attach(servo1_pin); //attach servo 1 to pin45
    servo2.attach(servo2_pin); //attach servo 1 to pin11 
    servo3.attach(servo3_pin); //attach servo 1 to pin12 
    servo4.attach(servo4_pin); //attach servo 1 to pin13 
    servo1.write(140);
    servo2.write(125);
    servo3.write(130);
    servo4.write(90);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
    // 400HZ
  ICR4 = 0X1387;
  TCCR4A = 0b10101010;
  TCCR4B = 0b00011010;
  // init motors on timer 3
  m2 = esc_min; m1 = esc_min; 

  // 400HZ
  ICR3 = 0X1387;
  TCCR3A = 0b10101010;
  TCCR3B = 0b00011010;

  m3 = esc_min; m4 = esc_min; 
}

void loop() 
{
   if(millis() - timd >= 10){
    timd = millis();
    nh.spinOnce(); 
   }
}
  
