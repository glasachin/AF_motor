#include"constants.h"
#include"AF_motor.h"
#include"AA_motor.h"
#include"ISRs.h"

unsigned long int AF_current_count = 0;
unsigned long int AF_prev_count = 0;
int AF_diff_count = 0;
unsigned long int AA_current_count = 0;
unsigned long int AA_prev_count = 0;
int AA_diff_count = 0;
//unsigned long int AF_cur_time = 0;
//unsigned long int AF_prev_time = 0;
char buf[100];
String sr_data;
char* rest;
String op_cmd;

void setup() {
  // Initializing serial communication
  Serial.begin(115200);
  Serial.println("Running");

  // Initialize Motor Pins
  AF_motor_init();
  AF_limit_switch_init();
  AA_motor_init();
  AA_limit_switch_init();

  // Go to home position or 0 position
  AF_home();
  AA_home();
}

void loop() {
  
  if(Serial.available() > 2){

    rest = buf;
    sr_data = Serial.readString();
    sr_data.toCharArray(buf, sizeof(buf));
//    Serial.println(buf);

    op_cmd = String(strtok_r(rest,";",&rest));
    if(op_cmd == "af_run_forward")
    {
      AF_move_direction = 0; //forward
      AF_run_motor_forward(rest);
    }
    else if(op_cmd == "af_run_backward")
    {
      AF_move_direction = 1; // backward
      AF_run_motor_backward(rest);
    }
    else if(op_cmd == "af_move")
    {
      AF_find_dir(rest); // Find AF motor's moving direction
    }
    else if(op_cmd == "af_position")
    {
      Serial.print("af_pos;");Serial.print(AF_CURRENT_POSITION);Serial.println(";");
    }
    else if(op_cmd == "af_stop")
    {
      AF_stop(); // Stop motor
    }
    else if(op_cmd == "af_range")
    {
      Serial.print("af_min;");Serial.print(AF_MIN_RANGE);Serial.println(";"); // Send min range
      Serial.print("af_max;");Serial.print(AF_MAX_RANGE);Serial.println(";");// Send min range 
    }
    else if(op_cmd == "af_reset")
    {
      detachInterrupt(digitalPinToInterrupt(AF_ENCODER));
      AF_home(); // move motor to home position
    }



    if(op_cmd == "aa_run_forward")
    {
      AA_move_direction = 0; //forward
      AA_run_motor_forward(rest);
    }
    else if(op_cmd == "aa_run_backward")
    {
      AA_move_direction = 1; // backward
      AA_run_motor_backward(rest);
    }
    else if(op_cmd == "aa_move")
    {
      AA_find_dir(rest); // Find AF motor's moving direction
    }
    else if(op_cmd == "aa_position")
    {
      Serial.print("aa_pos;");Serial.print(AA_CURRENT_POSITION);Serial.println(";");
    }
    else if(op_cmd == "aa_stop")
    {
      AA_stop(); // Stop motor
    }
    else if(op_cmd == "aa_range")
    {
      Serial.print("aa_min;");Serial.print(AA_MIN_RANGE);Serial.println(";"); // Send min range
      Serial.print("aa_max;");Serial.print(AA_MAX_RANGE);Serial.println(";");// Send min range 
    }
    else if(op_cmd == "aa_reset")
    {
      detachInterrupt(digitalPinToInterrupt(AA_ENCODER));
      AA_home(); // move motor to home position
    }
  }
  delay(10);
}
