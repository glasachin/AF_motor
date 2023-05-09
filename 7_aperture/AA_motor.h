/*
 * In this firmware, I have assumed that motor will run backward till it got to home position. After that it will run in forward or 
 * backward direction.
 */

// AA_Motor Pins initialization
void AA_motor_init(void)
{
  pinMode(AA_M1_0, OUTPUT);
  pinMode(AA_M1_1, OUTPUT);
}

// limit switch Pins initialization
void AA_limit_switch_init(void)
{
  pinMode(AA_LIMIT_SWITCH, INPUT_PULLUP);
}

// AA_Motor Forward
void AA_forward(void)
{
  digitalWrite(AA_M1_0, HIGH);
  digitalWrite(AA_M1_1, LOW);
}

// AA_Motor Backward
void AA_backward(void)
{
  digitalWrite(AA_M1_0, LOW);
  digitalWrite(AA_M1_1, HIGH);
}

// AA_Motor Stop
void AA_stop(void)
{
  digitalWrite(AA_M1_0, LOW);
  digitalWrite(AA_M1_1, LOW);
}

// 
void AA_home(void)
{
  int temp = 0;
  // Move motor backward till we hit the optical sensor
//  Serial.println("Going to Home");
  AA_backward();
//  while(digitalRead(LIMIT_SWITCH) == 0)
  while(temp == 0)
  {
    temp = digitalRead(AA_LIMIT_SWITCH);
  }
//  Serial.print("Limit Switch: ");Serial.println(digitalRead(LIMIT_SWITCH));
  AA_forward();
  AA_stop();
//  Serial.println("Reached Home Position");
  Serial.println("AA_home;");
  // set cur_position to 0
  AA_CURRENT_POSITION = 0;
}

// PWM AA_Motor Forward
void AA_PWM_forward(int PWM_VAL)
{
  analogWrite(AA_M1_0, PWM_VAL);
  digitalWrite(AA_M1_1, LOW);
}

// PWM AA_Motor Backward
void AA_PWM_backward(int PWM_VAL)
{
  digitalWrite(AA_M1_0, LOW);
  analogWrite(AA_M1_1, PWM_VAL);
}

//RUN AA motor for specific pulses
void AA_run_motor_forward(char* pulse_info)
{
  int pwm_val;
  AA_pulses = 0;
  pwm_val = atoi(strtok_r(pulse_info,";",&pulse_info));
  AA_pulses = strtol(strtok_r(pulse_info,";",&pulse_info),NULL, 0); // to convert into long int
  Serial.print("PWM: "); Serial.print(pwm_val);Serial.print(", Pulse to move forward: "); Serial.println(AA_pulses);
  AA_ENCODER_COUNT = 0;
  AA_PWM_forward(pwm_val); // start AF motor in forward direction with specific PWM
  attachInterrupt(digitalPinToInterrupt(AA_ENCODER), AA_ENCODER_ISR, RISING);
}

//RUN AA motor for specific pulses
void AA_run_motor_backward(char* pulse_info)
{
  int pwm_val;
  AA_pulses = 0;
  pwm_val = atoi(strtok_r(pulse_info,";",&pulse_info));
  AA_pulses = strtol(strtok_r(pulse_info,";",&pulse_info),NULL, 0); // to convert into long int
  Serial.print("PWM: "); Serial.print(pwm_val);Serial.print(", Pulse to move backward: "); Serial.println(AA_pulses);
  AA_ENCODER_COUNT = 0;
  AA_PWM_backward(pwm_val); // start AF motor in backward direction with specific PWM
  attachInterrupt(digitalPinToInterrupt(AA_ENCODER), AA_ENCODER_ISR, RISING);
}

// find motor direction to run
void AA_find_dir(char *pos_info)
{
  int pwm_val;
  unsigned long int abs_pos = 0;
  pwm_val = atoi(strtok_r(pos_info,";",&pos_info));
  abs_pos = strtol(strtok_r(pos_info,";",&pos_info),NULL, 0);

  if((abs_pos > AA_MAX_RANGE) || (abs_pos < AA_MIN_RANGE))
  {
    Serial.println("Invalid Position");
    detachInterrupt(digitalPinToInterrupt(AA_ENCODER));
  }
  else
  {
    if(abs_pos > AA_CURRENT_POSITION)
    {
      AA_pulses = abs_pos - AA_CURRENT_POSITION;
      AA_move_direction = 0; //forward
      AA_ENCODER_COUNT = 0;
      AA_PWM_forward(pwm_val); // start AA motor in forward direction with specific PWM
      attachInterrupt(digitalPinToInterrupt(AA_ENCODER), AA_ENCODER_ISR, RISING);
    }
    else if(abs_pos < AA_CURRENT_POSITION)
    {
      AA_pulses = AA_CURRENT_POSITION - abs_pos;
      AA_move_direction = 1; //Backward
      AA_ENCODER_COUNT = 0;
      AA_PWM_backward(pwm_val); // start AA motor in backward direction with specific PWM
      attachInterrupt(digitalPinToInterrupt(AA_ENCODER), AA_ENCODER_ISR, RISING);
    }
    else
    {}
  }
}
