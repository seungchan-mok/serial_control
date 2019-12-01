#include <Servo.h>
char data[] = "V+000A+00";
//             0123456789
Servo myservo;
int pos = 0;
int vel = 0;
const int servo_pin = 9;
const int dc_pwm_pin = 6;
const int dc_dir_pin = 7;
void setup() {
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {
  bool communication_success = true;
  if(Serial.available()>0)
  {
    Serial.readBytes(data,10);
    
    if(data[0] == 'M')
    {
      if(data[1] == '+')
      {
        vel = (int)(data[2] - '0')*100 + (int)(data[3] - '0')*10 + (int)(data[4] - '0');
      }
      else if(data[1] == '-')
      {
        vel = -((int)(data[2] - '0')*100 + (int)(data[3] - '0')*10 + (int)(data[4] - '0'));
      }
      else
      {
        communication_success = false;
      }
      if(data[5] == 'A')
      {
        if(data[6] == '+')
        {
          pos = (int)(data[7] - '0')*10 + (int)(data[8] - '0') + 90;
        }
        else if(data[6] == '-')
        {
          pos = 90 - ((int)(data[7] - '0')*10 + (int)(data[8] - '0'));
        }
        else
        {
          communication_success = false;
        }
      }
      else
      {
        communication_success = false;
      }
    }
    else
    {
      communication_success = false;
    }
  }
  if(communication_success)
  {
    if(pos > 180)
    {
      pos = 180;
    }
    if(pos < 0)
    {
        pos = 0;
    }
    if(vel > 255)
    {
      vel = 255;
    }
    if(vel < -255)
    {
      vel = -255;
    }
    myservo.write(pos);
    if(vel > 0)
    {
      digitalWrite(dc_dir_pin,HIGH);
      analogWrite(dc_pwm_pin,vel);
    }
    else
    {
      digitalWrite(dc_dir_pin,LOW);
      analogWrite(dc_pwm_pin,vel);
    }
    delay(10); 
  }
}