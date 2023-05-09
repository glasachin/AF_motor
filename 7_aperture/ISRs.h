
void AF_ENCODER_INIT(void)
{
  pinMode(AF_ENCODER, INPUT_PULLUP);
}

void AA_ENCODER_INIT(void)
{
  pinMode(AA_ENCODER, INPUT_PULLUP);
}

void AF_ENCODER_ISR()
{
  AF_ENCODER_COUNT +=1;
  //update current position
  if(AF_move_direction == 0)
  {
    AF_CURRENT_POSITION += 1;
  }
  else if(AF_move_direction == 1)
  {
    AF_CURRENT_POSITION -= 1;
  }
  else
  { }
  
  // stop motor when encoder count are greater than requested count
  if((AF_ENCODER_COUNT >= AF_pulses)||(AF_CURRENT_POSITION < AF_MIN_RANGE)||(AF_CURRENT_POSITION > AF_MAX_RANGE))
  {
    AF_stop(); // Stop motor
    detachInterrupt(digitalPinToInterrupt(AF_ENCODER));
    Serial.print("Pulse Count: "); Serial.println(AF_ENCODER_COUNT);
    Serial.print("Current Position: "); Serial.println(AF_CURRENT_POSITION);
    AF_ENCODER_COUNT = 0;
    if(AF_CURRENT_POSITION < AF_MIN_RANGE)
      AF_CURRENT_POSITION = 0;
    if(AF_CURRENT_POSITION > AF_MAX_RANGE)
      AF_CURRENT_POSITION = AF_MAX_RANGE;
  }
}

void AA_ENCODER_ISR()
{
  AA_ENCODER_COUNT +=1;
  //update current position
  if(AA_move_direction == 0)
  {
    AA_CURRENT_POSITION += 1;
  }
  else if(AA_move_direction == 1)
  {
    AA_CURRENT_POSITION -= 1;
  }
  else
  { }
  
  // stop motor when encoder count are greater than requested count
  if((AA_ENCODER_COUNT >= AA_pulses)||(AA_CURRENT_POSITION < AA_MIN_RANGE)||(AA_CURRENT_POSITION > AA_MAX_RANGE))
  {
    AA_stop(); // Stop motor
    detachInterrupt(digitalPinToInterrupt(AA_ENCODER));
    Serial.print("Pulse Count: "); Serial.println(AA_ENCODER_COUNT);
    Serial.print("Current Position: "); Serial.println(AA_CURRENT_POSITION);
    AA_ENCODER_COUNT = 0;
    if(AA_CURRENT_POSITION < AA_MIN_RANGE)
      AA_CURRENT_POSITION = 0;
    if(AA_CURRENT_POSITION > AA_MAX_RANGE)
      AA_CURRENT_POSITION = AA_MAX_RANGE;
  }
}
