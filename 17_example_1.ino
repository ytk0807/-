#include <Servo.h>

// Arduino pin assignment
#define EMA_alpha 0.5
#define PIN_POTENTIOMETER 3 // Potentiometer at Pin A3
#define PIN_IR 0
#define PIN_SERVO 10
#define _DIST_MIN 100.0
#define _DIST_MAX 250.0
#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)
#define PIN_LED  9
#define LOOP_INTERVAL 20   // Loop Interval (unit: msec)
float EMA;
Servo myservo;
unsigned long last_loop_time;   // unit: msec

void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  pinMode(PIN_LED, OUTPUT);
  
  Serial.begin(57600);
}

void loop()
{
  float dist_raw;
  unsigned long time_curr = millis();
  int a_value, duty;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  //a_value = analogRead(PIN_POTENTIOMETER);
  a_value = analogRead(PIN_IR);
  
  
 dist_raw = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;

 

  if (dist_raw < _DIST_MIN) {
    dist_raw = _DIST_MIN - 10.0;    // Set Lower Value
    digitalWrite(PIN_LED, 1);       // LED OFF
  } else if (dist_raw > _DIST_MAX) {
    dist_raw = _DIST_MAX + 10.0;    // Set Higher Value
    digitalWrite(PIN_LED, 1);       // LED OFF
  } else {    // In desired Range
    digitalWrite(PIN_LED, 0);       // LED ON      
  }
 EMA=dist_raw*EMA_alpha+EMA*(1-EMA_alpha);


  // map distance into duty
  duty = (EMA-_DIST_MIN)/(_DIST_MAX - _DIST_MIN)*(_DUTY_MAX - _DUTY_MIN)+_DUTY_MIN;
  myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  
  Serial.print("IR sensor value: "); Serial.print(a_value);
  Serial.print(", dist: "); Serial.print(dist_raw);
  Serial.print(", servo: "); Serial.print(duty);
  Serial.print(", MIN: "); Serial.print(_DIST_MIN);
  Serial.print(", MAX: "); Serial.print(_DIST_MAX);
  Serial.print(", ema:"); Serial.print(EMA);
  Serial.println("");


}
