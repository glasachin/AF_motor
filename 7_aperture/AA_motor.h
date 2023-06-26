// AA_Motor Stop
void AA_stop(void)
{
  digitalWrite(AA_M1_0, LOW);
  digitalWrite(AA_M1_1, LOW);
}

// Move motor to limit switch and reset position
void AA_home(void)
{
  int temp = 0;
  AA_PWM_backward(100);
  delay(300);
  while(temp == 0)
  {
    temp = digitalRead(AA_LIMIT_SW);
  }
  AA_PWM_forward(100);
  AA_stop();
  Serial.println("AA_home;");
  AA_current_pos = 0;
}

// PWM AA_Motor Forward
void AA_PWM_forward(int PWM_VAL)
{
  digitalWrite(AA_M1_0, LOW);
  analogWrite(AA_M1_1, PWM_VAL);
}

// PWM AA_Motor Backward
void AA_PWM_backward(int PWM_VAL)
{
  analogWrite(AA_M1_0, PWM_VAL);
  digitalWrite(AA_M1_1, LOW);
}

//RUN AA motor for specific pulses
void AA_run_motor_forward(char* pulse_info)
{
  int pwm_val;
  AA_pulses = 0;
  pwm_val = atoi(strtok_r(pulse_info,";",&pulse_info));
  AA_pulses = strtol(strtok_r(pulse_info,";",&pulse_info),NULL, 0);
  //Serial.print("PWM: "); Serial.print(pwm_val);
 // Serial.print(", Pulse to move forward: "); Serial.println(AA_pulses);
  AA_encoder_count = 0;
  AA_active = 1;
  AA_PWM_forward(pwm_val); // AA motor forward direction specific PWM
}

//RUN AA motor for specific pulses
void AA_run_motor_backward(char* pulse_info)
{
  int pwm_val;
  AA_pulses = 0;
  pwm_val = atoi(strtok_r(pulse_info,";",&pulse_info));
  AA_pulses = strtol(strtok_r(pulse_info,";",&pulse_info),NULL, 0);
  //Serial.print("PWM: "); Serial.print(pwm_val);
  //Serial.print(", Pulse to move backward: "); Serial.println(AA_pulses);
  AA_encoder_count = 0;
  AA_active = 1;
  AA_PWM_backward(pwm_val); // AA motor backward direction specific PWM
}

// move motor to an absolute position
void AA_abs_move(char *pos_info)
{
  int pwm_val;
  unsigned long int abs_pos = 0;
  pwm_val = atoi(strtok_r(pos_info,";",&pos_info));
  abs_pos = strtol(strtok_r(pos_info,";",&pos_info),NULL, 0);

  if((abs_pos > AA_MAX_RANGE) || (abs_pos < AA_MIN_RANGE))
  {
   // Serial.println("Invalid Position");
  }
  else
  {
    if(abs_pos > AA_current_pos)
    {
      AA_pulses = abs_pos - AA_current_pos;
      AA_encoder_count = 0;
      AA_active = 1;
      AA_PWM_forward(pwm_val); // AA motor forward direction specific PWM
    }
    else if(abs_pos < AA_current_pos)
    {
      AA_pulses = AA_current_pos - abs_pos;
      AA_encoder_count = 0;
      AA_active = 1;
      AA_PWM_backward(pwm_val); // AA motor backward direction specific PWM
    }
  }
}
