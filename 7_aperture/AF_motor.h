// AF_Motor Stop
void AF_stop(void)
{
  digitalWrite(AF_M1_0, LOW);
  digitalWrite(AF_M1_1, LOW);
}

// Move motor to limit switch and reset position
void AF_home(void)
{
  int temp = 0;
  AF_PWM_backward(100);
  delay(300);
  while(temp == 0)
  {
    temp = digitalRead(AF_LIMIT_SW);
  }
  AF_PWM_forward(100);
  AF_stop();
  Serial.println("AF_home;");
  AF_current_pos = 0;
}

// PWM AF_Motor Forward
void AF_PWM_forward(int PWM_VAL)
{
  analogWrite(AF_M1_0, PWM_VAL);
  digitalWrite(AF_M1_1, LOW);
}

// PWM AF_Motor Backward
void AF_PWM_backward(int PWM_VAL)
{
  digitalWrite(AF_M1_0, LOW);
  analogWrite(AF_M1_1, PWM_VAL);
}

//RUN AF motor for specific pulses
void AF_run_motor_forward(char* pulse_info)
{
  int pwm_val;
  AF_pulses = 0;
  pwm_val = atoi(strtok_r(pulse_info,";",&pulse_info));
  AF_pulses = strtol(strtok_r(pulse_info,";",&pulse_info),NULL, 0);
  //Serial.print("PWM: "); Serial.print(pwm_val);
  //Serial.print(", Pulse to move forward: "); Serial.println(AF_pulses);
  AF_encoder_count = 0;
  AF_active = 1;
  AF_PWM_forward(pwm_val); // AF motor forward direction specific PWM
}

//RUN AF motor for specific pulses
void AF_run_motor_backward(char* pulse_info)
{
  int pwm_val;
  AF_pulses = 0;
  pwm_val = atoi(strtok_r(pulse_info,";",&pulse_info));
  AF_pulses = strtol(strtok_r(pulse_info,";",&pulse_info),NULL, 0);
  //Serial.print("PWM: "); Serial.print(pwm_val);
  //Serial.print(", Pulse to move backward: "); Serial.println(AF_pulses);
  AF_encoder_count = 0;
  AF_active = 1;
  AF_PWM_backward(pwm_val); // AF motor backward direction specific PWM
}

// move motor to an absolute position
void AF_abs_move(char *pos_info)
{
  int pwm_val;
  unsigned long int abs_pos = 0;
  pwm_val = atoi(strtok_r(pos_info,";",&pos_info));
  abs_pos = strtol(strtok_r(pos_info,";",&pos_info),NULL, 0);

  if((abs_pos > AF_MAX_RANGE) || (abs_pos < AF_MIN_RANGE))
  {
   // Serial.println("Invalid Position");
  }
  else
  {
    if(abs_pos > AF_current_pos)
    {
      AF_pulses = abs_pos - AF_current_pos;
      AF_encoder_count = 0;
      AF_active = 1;
      AF_PWM_forward(pwm_val); // AF motor forward direction specific PWM
    }
    else if(abs_pos < AF_current_pos)
    {
      AF_pulses = AF_current_pos - abs_pos;
      AF_encoder_count = 0;
      AF_active = 1;
      AF_PWM_backward(pwm_val); // AF motor backward direction specific PWM
    }
  }
}
