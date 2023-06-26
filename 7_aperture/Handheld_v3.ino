#include"constants.h"
#include"AF_motor.h"
#include"AA_motor.h"
#include"ISRs.h"

char buf[25];
String sr_data;
char* rest;
String op_cmd;
//long int STEP = 0;

void setup() 
{
  // Initializing serial communication
  Serial.begin(115200);
  while(!Serial);
  //Serial.println("Running");

  // Initialize Motor pins & Limit Switch pins
  motor_init();
  limit_switch_init();
  encoder_init();
  
  // Go to home position or 0 position
  Serial.println("Homing");
  AF_home();
  delay(500);
  AA_home();

  // attach interrupts and start counting
  attachInterrupt(digitalPinToInterrupt(AF_ENCODER_A), AF_encoder_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(AA_ENCODER_A), AA_encoder_isr, RISING);
}

void loop() 
{
  if(Serial.available() > 6)
  {
    rest = buf;
    sr_data = Serial.readStringUntil('\n');
    sr_data.toCharArray(buf, sizeof(buf));
    op_cmd = String(strtok_r(rest,";",&rest));
    
    //________________________________________________________________________________
    if(op_cmd == "af_run_forward")
    {
      AF_run_motor_forward(rest);
    }
    
    else if(op_cmd == "af_run_backward")
    {
      AF_run_motor_backward(rest);
    }
    
    else if(op_cmd == "af_move")
    {
      AF_abs_move(rest); // Find AF motor's moving direction
    }
        
    else if(op_cmd == "af_stop")
    {
      AF_stop(); // Stop motor
    }
        
    else if(op_cmd == "af_reset")
    {
      detachInterrupt(digitalPinToInterrupt(AF_ENCODER_A));
      AF_home(); // move motor to home position
      attachInterrupt(digitalPinToInterrupt(AF_ENCODER_A), AF_encoder_isr, RISING);
    }
    
    else if(op_cmd == "af_position")
    {
      Serial.print("af_pos;");Serial.print(AF_current_pos);Serial.println(";");
    }

    else if(op_cmd == "af_range")
    {
      Serial.print("af_min;");Serial.print(AF_MIN_RANGE);Serial.print(";");
      Serial.print("af_max;");Serial.print(AF_MAX_RANGE);Serial.println(";"); 
    }

    //________________________________________________________________________________
    else if(op_cmd == "aa_run_forward")
    {
      AA_run_motor_forward(rest);
    }
    
    else if(op_cmd == "aa_run_backward")
    {
      AA_run_motor_backward(rest);
    }
    
    else if(op_cmd == "aa_move")
    {
      AA_abs_move(rest); // Find AF motor's moving direction
    }
        
    else if(op_cmd == "aa_stop")
    {
      AA_stop(); // Stop motor
    }
    
    else if(op_cmd == "aa_reset")
    {
      detachInterrupt(digitalPinToInterrupt(AA_ENCODER_A));
      AA_home(); // move motor to home position
      attachInterrupt(digitalPinToInterrupt(AA_ENCODER_A), AA_encoder_isr, RISING);
    }
    
    else if(op_cmd == "aa_position")
    {
      Serial.print("aa_pos;");Serial.print(AA_current_pos);Serial.println(";");
    }
    
    else if(op_cmd == "aa_range")
    {
      Serial.print("aa_min;");Serial.print(AA_MIN_RANGE);Serial.print(";");
      Serial.print("aa_max;");Serial.print(AA_MAX_RANGE);Serial.println(";"); 
    }

    else Serial.println("INVALID COMMAND");
  }
      
  // stop motor when encoder count are greater than requested count
  if((AF_encoder_count >= AF_pulses) && (AF_active == 1))
  {
    AF_stop(); // Stop motor
    AF_encoder_count = 0;  //reset Encoder count
    AF_active = 0;  //reset active flag
    //Serial.print("Pulse Count: "); Serial.print(AF_encoder_count);
    //Serial.print("Current Position: "); Serial.println(AF_current_pos);
  }
  
  // stop motor when current position is out of range  
  if((AF_current_pos < AF_MIN_RANGE)||(AF_current_pos > AF_MAX_RANGE))
  {
    AF_stop(); // Stop motor
    //Serial.println("AF Out of Range!");
    AF_encoder_count = 0;
    if(AF_current_pos < AF_MIN_RANGE)
      AF_current_pos = 0;
    if(AF_current_pos > AF_MAX_RANGE)
      AF_current_pos = AF_MAX_RANGE;
  }

  // stop motor when encoder count are greater than requested count
  if((AA_encoder_count >= AA_pulses) && (AA_active == 1))
  {
    AA_stop(); // Stop motor
    AA_encoder_count = 0;  //reset Encoder count
    AA_active = 0;  //reset active flag
   // Serial.print("Pulse Count: "); Serial.print(AA_encoder_count);
   // Serial.print("Current Position: "); Serial.println(AA_current_pos);
  }
  
  // stop motor when current position is out of range  
  if((AA_current_pos < AA_MIN_RANGE)||(AA_current_pos > AA_MAX_RANGE))
  {
    AA_stop(); // Stop motor
    //Serial.println("AA Out of Range!");
    AA_encoder_count = 0;
    if(AA_current_pos < AA_MIN_RANGE)
      AA_current_pos = 0;
    if(AA_current_pos > AA_MAX_RANGE)
      AA_current_pos = AA_MAX_RANGE;
  }
  
  //if(STEP >= 2000)
  //{
   // Serial.print(AF_current_pos);
   // Serial.print("   ");
   // Serial.println(AA_current_pos);
  //  STEP=0;
 // }
 // else STEP++;

  delay(1);
}
