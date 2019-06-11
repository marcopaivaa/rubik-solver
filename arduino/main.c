//libraries
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <time.h>
#include <stdlib.h>

void left(int direction);
void right(int direction);
void front(int direction);
void back(int direction);
void top(int direction);
void down(int direction);
void rotate(int deg, int pin, int min, int max);
void init_servos();

#define LEFT_ARM_PIN            6
#define LEFT_ARM_MIN            121
#define LEFT_ARM_MAX            572
#define LEFT_TRAIL_PIN          4
#define LEFT_TRAIL_MIN          121
#define LEFT_TRAIL_MAX          580
        
#define RIGHT_ARM_PIN           14 
#define RIGHT_ARM_MIN           123 
#define RIGHT_ARM_MAX           571 
#define RIGHT_TRAIL_PIN         12
#define RIGHT_TRAIL_MIN         123 
#define RIGHT_TRAIL_MAX         580 
        
#define FRONT_ARM_PIN           2 
#define FRONT_ARM_MIN           122 
#define FRONT_ARM_MAX           575 
#define FRONT_TRAIL_PIN         0  
#define FRONT_TRAIL_MIN         120 
#define FRONT_TRAIL_MAX         580 
        
#define BACK_ARM_PIN            10
#define BACK_ARM_MIN            121
#define BACK_ARM_MAX            572
#define BACK_TRAIL_PIN          8
#define BACK_TRAIL_MIN          132
#define BACK_TRAIL_MAX          589

#define ARM_DEFAULT_DEGREE      90
#define ARM_MAX_DEGREE          0
#define ARM_MIN_DEGREE          180

#define TRAIL_MAX_DEGREE        108
#define TRAIL_MIN_DEGREE        0

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
String commands[] = {"L", "R", "F", "B", "T", "D", "L'", "R'", "F'", "B'", "T'", "D'"};

void setup() {
  Serial.begin(9600);
  Serial.println("[*] INITIAL CONFIG...!");
  pwm.begin();
  pwm.setPWMFreq(60); 
  delay(10);
  srand(time(NULL));
  init_servos();
}

void loop() {
    int r = rand() % 12;
    //Serial.println("[*] Running: %s", commands[r]);
    switch (r)
    {
        case 0:
            left(1); break;
        case 1:
            right(1); break;
        case 2:
            front(1); break;
        case 3:
            back(1); break;
        case 4:
            top(1); break;
        case 5:
            down(1); break;
        case 6:
            left(-1); break;
        case 7:
            right(-1); break;
        case 8:
            front(-1); break;
        case 9:
            back(-1); break;
        case 10:
            top(-1); break;
        case 11:
            down(-1); break;
    }
}


/** FUNCTIONS */

void left(int direction){
    int degree = direction > 0 ? ARM_MAX_DEGREE : ARM_MIN_DEGREE;
    rotate(degree, LEFT_ARM_PIN, LEFT_ARM_MIN, LEFT_ARM_MAX, 1);
    rotate(TRAIL_MIN_DEGREE, LEFT_TRAIL_PIN, LEFT_TRAIL_MIN, LEFT_TRAIL_MAX, 1);
    rotate(ARM_DEFAULT_DEGREE, LEFT_ARM_PIN, LEFT_ARM_MIN, LEFT_ARM_MAX, 1);
    rotate(TRAIL_MAX_DEGREE, LEFT_TRAIL_PIN, LEFT_TRAIL_MIN, LEFT_TRAIL_MAX, 1);
}


void right(int direction){
    int degree = direction > 0 ? ARM_MAX_DEGREE : ARM_MIN_DEGREE;
    rotate(degree, RIGHT_ARM_PIN, RIGHT_ARM_MIN, RIGHT_ARM_MAX, 1);
    rotate(TRAIL_MIN_DEGREE, RIGHT_TRAIL_PIN, RIGHT_TRAIL_MIN, RIGHT_TRAIL_MAX, 1);
    rotate(ARM_DEFAULT_DEGREE, RIGHT_ARM_PIN, RIGHT_ARM_MIN, RIGHT_ARM_MAX, 1);
    rotate(TRAIL_MAX_DEGREE, RIGHT_TRAIL_PIN, RIGHT_TRAIL_MIN, RIGHT_TRAIL_MAX, 1);
}


void front(int direction){
    int degree = direction > 0 ? ARM_MAX_DEGREE : ARM_MIN_DEGREE;
    rotate(degree, FRONT_ARM_PIN, FRONT_ARM_MIN, FRONT_ARM_MAX, 1);
    rotate(TRAIL_MIN_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 1);
    rotate(ARM_DEFAULT_DEGREE, FRONT_ARM_PIN, FRONT_ARM_MIN, FRONT_ARM_MAX, 1);
    rotate(TRAIL_MAX_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 1);
}


void back(int direction){
    int degree = direction > 0 ? ARM_MAX_DEGREE : ARM_MIN_DEGREE;
    rotate(degree, BACK_ARM_PIN, BACK_ARM_MIN, BACK_ARM_MAX, 1);
    rotate(TRAIL_MIN_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 1);
    rotate(ARM_DEFAULT_DEGREE, BACK_ARM_PIN, BACK_ARM_MIN, BACK_ARM_MAX, 1);
    rotate(TRAIL_MAX_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 1);
}


void top(int direction){
    rotate(TRAIL_MIN_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 0);
    rotate(TRAIL_MIN_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 0);

    rotate(ARM_MIN_DEGREE, LEFT_ARM_PIN, LEFT_ARM_MIN, LEFT_ARM_MAX, 0);
    rotate(ARM_MIN_DEGREE, RIGHT_ARM_PIN, RIGHT_ARM_MIN, RIGHT_ARM_MAX, 0);

    rotate(TRAIL_MAX_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 0);
    rotate(TRAIL_MAX_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 0);

    front(direction);

    rotate(TRAIL_MIN_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 0);
    rotate(TRAIL_MIN_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 0);

    rotate(ARM_DEFAULT_DEGREE, LEFT_ARM_PIN, LEFT_ARM_MIN, LEFT_ARM_MAX, 0);
    rotate(ARM_DEFAULT_DEGREE, RIGHT_ARM_PIN, RIGHT_ARM_MIN, RIGHT_ARM_MAX, 0);

    rotate(TRAIL_MAX_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 0);
    rotate(TRAIL_MAX_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 0);
    
}


void down(int direction){
    rotate(TRAIL_MIN_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 0);
    rotate(TRAIL_MIN_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 0);

    rotate(ARM_MIN_DEGREE, LEFT_ARM_PIN, LEFT_ARM_MIN, LEFT_ARM_MAX, 0);
    rotate(ARM_MIN_DEGREE, RIGHT_ARM_PIN, RIGHT_ARM_MIN, RIGHT_ARM_MAX, 0);

    rotate(TRAIL_MAX_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 0);
    rotate(TRAIL_MAX_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 0);

    back(direction);

    rotate(TRAIL_MIN_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 0);
    rotate(TRAIL_MIN_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 0);

    rotate(ARM_DEFAULT_DEGREE, LEFT_ARM_PIN, LEFT_ARM_MIN, LEFT_ARM_MAX, 0);
    rotate(ARM_DEFAULT_DEGREE, RIGHT_ARM_PIN, RIGHT_ARM_MIN, RIGHT_ARM_MAX, 0);

    rotate(TRAIL_MAX_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 0);
    rotate(TRAIL_MAX_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 0);
}


void rotate(int deg, int pin, int min, int max, int delay_bit){
    uint16_t pulse = map(deg, 0, 180, min, max);
    pwm.setPWM(pin, 0, pulse);
    if(delay_bit == 1){
        delay(1000);
    }
}

void init_servos(){
    rotate(TRAIL_MIN_DEGREE, LEFT_TRAIL_PIN, LEFT_TRAIL_MIN, LEFT_TRAIL_MAX, 0);
    rotate(TRAIL_MIN_DEGREE, RIGHT_TRAIL_PIN, RIGHT_TRAIL_MIN, RIGHT_TRAIL_MAX, 0);
    rotate(TRAIL_MIN_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 0);
    rotate(TRAIL_MIN_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 0);

    delay(2500);

    rotate(ARM_DEFAULT_DEGREE, LEFT_ARM_PIN, LEFT_ARM_MIN, LEFT_ARM_MAX, 0);
    rotate(ARM_DEFAULT_DEGREE, RIGHT_ARM_PIN, RIGHT_ARM_MIN, RIGHT_ARM_MAX, 0);
    rotate(ARM_DEFAULT_DEGREE, FRONT_ARM_PIN, FRONT_ARM_MIN, FRONT_ARM_MAX, 0);
    rotate(ARM_DEFAULT_DEGREE, BACK_ARM_PIN, BACK_ARM_MIN, BACK_ARM_MAX, 0);

    delay(2500);

    rotate(TRAIL_MAX_DEGREE, LEFT_TRAIL_PIN, LEFT_TRAIL_MIN, LEFT_TRAIL_MAX, 0);
    rotate(TRAIL_MAX_DEGREE, RIGHT_TRAIL_PIN, RIGHT_TRAIL_MIN, RIGHT_TRAIL_MAX, 0);
    rotate(TRAIL_MAX_DEGREE, FRONT_TRAIL_PIN, FRONT_TRAIL_MIN, FRONT_TRAIL_MAX, 0);
    rotate(TRAIL_MAX_DEGREE, BACK_TRAIL_PIN, BACK_TRAIL_MIN, BACK_TRAIL_MAX, 0);
}