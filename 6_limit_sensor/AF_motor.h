/*
 * In this firmware, I have assumed that motor will run backward till it got to home position. After that it will run in forward or 
 * backward direction.
 */

// AF_Motor Pins initialization
void AF_motor_init(void)
{
  pinMode(AF_M1_0, OUTPUT);
  pinMode(AF_M1_1, OUTPUT);
}

// limit switch Pins initialization
void limit_switch_init(void)
{
  pinMode(LIMIT_SWITCH, INPUT_PULLUP);
}

// AF_Motor Forward
void AF_forward(void)
{
  digitalWrite(AF_M1_0, HIGH);
  digitalWrite(AF_M1_1, LOW);
}

// AF_Motor Backward
void AF_backward(void)
{
  digitalWrite(AF_M1_0, LOW);
  digitalWrite(AF_M1_1, HIGH);
}

// AF_Motor Stop
void AF_stop(void)
{
  digitalWrite(AF_M1_0, LOW);
  digitalWrite(AF_M1_1, LOW);
}

// 
void AF_home(void)
{
  int temp = 0;
  // Move motor backward till we hit the optical sensor
//  Serial.println("Going to Home");
  AF_backward();
//  while(digitalRead(LIMIT_SWITCH) == 0)
  while(temp == 0)
  {
    temp = digitalRead(LIMIT_SWITCH);
//    Serial.println(temp);
  }
//  Serial.print("Limit Switch: ");Serial.println(digitalRead(LIMIT_SWITCH));
  AF_forward();
  AF_stop();
//  Serial.println("Reached Home Position");
  Serial.println("home;");
  // set cur_position to 0
  CURRENT_POSITION = 0;
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
  pulses = 0;
  pwm_val = atoi(strtok_r(pulse_info,";",&pulse_info));
  pulses = strtol(strtok_r(pulse_info,";",&pulse_info),NULL, 0); // to convert into long int
  Serial.print("PWM: "); Serial.print(pwm_val);Serial.print(", Pulse to move forward: "); Serial.println(pulses);
  AF_ENCODER_COUNT = 0;
  AF_PWM_forward(pwm_val); // start AF motor in forward direction with specific PWM
  attachInterrupt(digitalPinToInterrupt(AF_ENCODER), AF_ENCODER_ISR, RISING);
}

//RUN AF motor for specific pulses
void AF_run_motor_backward(char* pulse_info)
{
  int pwm_val;
  pulses = 0;
  pwm_val = atoi(strtok_r(pulse_info,";",&pulse_info));
  pulses = strtol(strtok_r(pulse_info,";",&pulse_info),NULL, 0); // to convert into long int
  Serial.print("PWM: "); Serial.print(pwm_val);Serial.print(", Pulse to move backward: "); Serial.println(pulses);
  AF_ENCODER_COUNT = 0;
  AF_PWM_backward(pwm_val); // start AF motor in backward direction with specific PWM
  attachInterrupt(digitalPinToInterrupt(AF_ENCODER), AF_ENCODER_ISR, RISING);
}

// find motor direction to run
void AF_find_dir(char *pos_info)
{
  int pwm_val;
  unsigned long int abs_pos = 0;
  pwm_val = atoi(strtok_r(pos_info,";",&pos_info));
  abs_pos = strtol(strtok_r(pos_info,";",&pos_info),NULL, 0);

  if((abs_pos > AF_MAX_RANGE) || (abs_pos < AF_MIN_RANGE))
  {
    Serial.println("Invalid Position");
    detachInterrupt(digitalPinToInterrupt(AF_ENCODER));
  }
  else
  {
    if(abs_pos > CURRENT_POSITION)
    {
      pulses = abs_pos - CURRENT_POSITION;
      move_direction = 0; //forward
      AF_ENCODER_COUNT = 0;
      AF_PWM_forward(pwm_val); // start AF motor in forward direction with specific PWM
      attachInterrupt(digitalPinToInterrupt(AF_ENCODER), AF_ENCODER_ISR, RISING);
    }
    else if(abs_pos < CURRENT_POSITION)
    {
      pulses = CURRENT_POSITION - abs_pos;
      move_direction = 1; //Backward
      AF_ENCODER_COUNT = 0;
      AF_PWM_backward(pwm_val); // start AF motor in backward direction with specific PWM
      attachInterrupt(digitalPinToInterrupt(AF_ENCODER), AF_ENCODER_ISR, RISING);
    }
    else
    {}
  }
}
