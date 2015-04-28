#include <SoftwareSerial.h>
#include <Servo.h>

// Led for car
#define LED 7

// Manage Motor
// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define CW  0
#define CCW 1
#define MOTOR_A 0
#define MOTOR_B 1
#define SERVO_A 6

// Don't change these! These pins are statically defined by shield layout
const byte PWMA = 3;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B

//Manage bluetooth
SoftwareSerial bluetooth(9, 10); // RX, TX

void setup (){
  pinMode(LED, OUTPUT);
  //Serial.begin(9600);
  setupArdumoto();
  bluetooth.begin(9600);
  bluetooth.println("Bluetooth On");
}

void loop (){
  if (bluetooth.available()){
    char data = bluetooth.read();
    if (data == 'o'){
      digitalWrite(LED, HIGH);
    }
    
    else if (data == 'n'){
      digitalWrite(LED, LOW);
    }
    
    else if (data == 'f'){
       // Set motor A to CCW at max, forward
       driveArdumoto(MOTOR_A, CW, 255); 
       driveArdumoto(MOTOR_B, CW, 255);
    }
    else if (data == 'b'){
      // Set motor A to CW at at, backward
      driveArdumoto(MOTOR_A, CCW, 255); 
      driveArdumoto(MOTOR_B, CCW, 255);  
    }
    
    else if (data == 's'){
      driveArdumoto(MOTOR_A, CCW, 0); 
      driveArdumoto(MOTOR_B, CCW, 0);
    }
    
    else if (data == 'l'){
      driveArdumoto(MOTOR_B, CCW, 0); 
      driveArdumoto(MOTOR_A, CCW, 255);
    }
    
    else if (data == 'r'){
      driveArdumoto(MOTOR_B, CCW, 255); 
      driveArdumoto(MOTOR_A, CCW, 0);
    }
  }
}

// setupArdumoto initialize all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  // Second motor
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}
