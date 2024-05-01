/*
  ELEC1100 earlydemo

  Group No. (number of your project box):  5
  Group Member 1 (name & SID): Wu Chun Fei Gabriel 20985696
  Group Member 2 (name & SID): TAI Wing Kuen 2098393
  
*/

// assign meaningful names to those pins that will be used

const int pinL_Sensor = A5;      //pin A5: left sensor 
const int pinB_Sensor = A4;      //pin A4: bumper sensor
const int pinR_Sensor = A3;      //pin A3: right sensor 

const int pinL_PWM = 9;          //pin D9: left motor speed
const int pinL_DIR = 10;         //pin D10: left motor direction

const int pinR_PWM = 11;         //pin D11: right motor speed
const int pinR_DIR = 12;         //pin D12: right motor direction

//define variables to be used in script

int bumperSensor = 1;  // not sensing white
int leftSensor = 1;    // not sensing white
int rightSensor = 1;   // not sensing white

int countBumper = 0;   // bumper sensor not triggered yet
int countTjunction = 0; // for detecting T-junctions
int count360=0;
int countStop=0;

// the setup function runs once when you press reset or power the board

void setup ()
{
  // define pins as input and output
  pinMode(pinB_Sensor, INPUT);
  pinMode(pinL_Sensor, INPUT);
  pinMode(pinR_Sensor, INPUT);
  
  pinMode(pinL_DIR, OUTPUT);
  pinMode(pinR_DIR, OUTPUT);
  
  pinMode(pinL_PWM, OUTPUT);
  pinMode(pinR_PWM, OUTPUT);
  
  // initialize output pins
  digitalWrite(pinL_DIR, HIGH);   //forward direction    
  digitalWrite(pinR_DIR, HIGH);   //forward direction
  analogWrite(pinL_PWM, 0);       //stop at the start position 
  analogWrite(pinR_PWM, 0);       //stop at the start position 
}

// the loop function runs over and over again forever

void loop() {

  // Arduino is reading the sensor measurements
  bumperSensor = digitalRead(pinB_Sensor);
  leftSensor = digitalRead(pinL_Sensor);
  rightSensor = digitalRead(pinR_Sensor);
  
  // car stops at the start position when bumper sensor no trigger
  if ( bumperSensor && countBumper == 0 ) {
    analogWrite(pinL_PWM, 0);
    analogWrite(pinR_PWM, 0);
  }

  // bumper sensor is triggered at the start position for the 1st time
  else if ( !bumperSensor && countBumper == 0) {
    analogWrite(pinL_PWM, 150);
    analogWrite(pinR_PWM, 150);
    countBumper = countBumper + 1;
    delay(350);     //to let the car leave the start position with no miscount
  }
  
  // car is tracking on the white line
  else if ( bumperSensor && countBumper == 1&&countStop==0) 
  { 
    if ( !leftSensor && !rightSensor &&countTjunction==0) {
      // Turn right
        analogWrite(pinL_PWM, 150);
        analogWrite(pinR_PWM, 150);
        digitalWrite(pinL_DIR, HIGH);
        digitalWrite(pinR_DIR, 0); 
        delay(300);
        //if(leftSensor || rightSensor){
        countTjunction+=1;
        //}
      }
    else if(countTjunction==2&&count360==0) {
        analogWrite(pinL_PWM, 200);
        analogWrite(pinR_PWM, 200);
        digitalWrite(pinL_DIR, LOW);
        digitalWrite(pinR_DIR, 1); 
        delay(1200);
        count360 += 1;
        countTjunction+=1;
    }
    else if(countTjunction==4)
    {
      countStop=1;
    }
    else if ( !leftSensor && !rightSensor ) {
        countTjunction+=1;  
    } 
    //follow straight line
    if ( !leftSensor && rightSensor ) {
      // Turn left
        analogWrite(pinL_PWM, 150);
        analogWrite(pinR_PWM, 150);
        digitalWrite(pinL_DIR, 0);
        digitalWrite(pinR_DIR, HIGH);
      }
    
    if ( leftSensor && !rightSensor ) {
      // Turn right
        analogWrite(pinL_PWM, 150);
        analogWrite(pinR_PWM, 150);
        digitalWrite(pinL_DIR, HIGH);
        digitalWrite(pinR_DIR, 0);  
      }
    
    if ( leftSensor && rightSensor ) {
      // Move straight
        analogWrite(pinL_PWM, 150);
        analogWrite(pinR_PWM, 150);
        digitalWrite(pinL_DIR, HIGH);
        digitalWrite(pinR_DIR, HIGH);  
      }
    if(countStop==1)
    {
      analogWrite(pinL_PWM, 0);
      analogWrite(pinR_PWM, 0);      
    }
  }
  }
