
// AF_Motor Pins initialization
void AF_motor_init(void)
{
  pinMode(AF_M1_0, OUTPUT);
  pinMode(AF_M1_1, OUTPUT);
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
}
