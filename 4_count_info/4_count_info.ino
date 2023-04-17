#include"constants.h"
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
  Serial.begin(115200);
  Serial.println("Running");

  // Initialize Motor Pins
  AF_motor_init();

  // Attach encoder to Interrupt pin
  attachInterrupt(digitalPinToInterrupt(AF_ENCODER), AF_ENCODER_ISR, RISING);

  // Start motor forward
  AF_stop();
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
      attachInterrupt(digitalPinToInterrupt(AF_ENCODER), AF_ENCODER_ISR, RISING);
      move_direction = 0; //forward
      AF_run_motor_forward(rest);
    }
    else if(op_cmd == "af_run_backward")
    {
      attachInterrupt(digitalPinToInterrupt(AF_ENCODER), AF_ENCODER_ISR, RISING);
      move_direction = 1; // backward
      AF_run_motor_backward(rest);
    }
    else if(op_cmd == "af_position")
    {
      Serial.print("af_pos;");Serial.print(CURRENT_POSITION);Serial.println(";");
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
    else if(op_cmd == "reset")
    {
      CURRENT_POSITION = 0;
    }
  }
  
  delay(10);
}
