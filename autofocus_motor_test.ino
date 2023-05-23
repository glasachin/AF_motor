#include"constants.h"
#include"AF_motor.h"
#include"ISRs.h"

unsigned long int current_count = 0;
unsigned long int prev_count = 0;
int diff_count = 0;
unsigned long int cur_time = 0;
unsigned long int prev_time = 0;
char buf[100];
String sr_data;
char* rest;
String op_cmd;

void setup() {
  // Initializing serial communication
  Serial.begin(9600);
  while(!Serial){};
  Serial.println("Running");

  // Initialize Motor Pins
  motor_init();
  Serial.println("Motor Initialized");
  limit_switch_init();
  Serial.println("Limit Switch Initialized");

  // Go to home position or 0 position
  Serial.println("Homing");
  AF_home();
  attachInterrupt(digitalPinToInterrupt(AF_ENCODER_A), AF_ENCODER_ISR, RISING);
  
}

void loop() {
  
  if(Serial.available() > 2){

    rest = buf;
    sr_data = Serial.readString();
    sr_data.toCharArray(buf, sizeof(buf));

    op_cmd = String(strtok_r(rest,";",&rest));

    if(op_cmd == "af_run_forward")
    {
      //move_direction = 0; //forward
      AF_run_motor_forward(rest);
    }
    
    else if(op_cmd == "af_run_backward")
    {
      //move_direction = 1; // backward
      AF_run_motor_backward(rest);
    }
    
    else if(op_cmd == "af_move")
    {
      AF_ABS_move(rest); // Find AF motor's moving direction
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
      detachInterrupt(digitalPinToInterrupt(AF_ENCODER_A));
      AF_home(); // move motor to home position
      attachInterrupt(digitalPinToInterrupt(AF_ENCODER_A), AF_ENCODER_ISR, RISING);
    }

    else
    {
      Serial.println("INVALID COMMAND");
    }

  }
  Serial.print(AF_move_dir);
  Serial.print("   ");
  Serial.println(AF_CURRENT_POSITION);
  
  delay(500);
}
