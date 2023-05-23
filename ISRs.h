
void AF_ENCODER_INIT(void)
{
  pinMode(AF_ENCODER_A, INPUT_PULLUP);
  pinMode(AF_ENCODER_B, INPUT_PULLUP);
}

void AF_ENCODER_ISR()
{
  AF_move_dir = digitalRead(AF_ENCODER_B);
  if(AF_move_dir == 0)
  {
    AF_CURRENT_POSITION += 1;
  }
  else if(AF_move_dir == 1)
  {
    AF_CURRENT_POSITION -= 1;
  }
  
  if(AF_active == 1)
  {
    AF_ENCODER_COUNT +=1;   //update Encoder count

    // stop motor when encoder count are greater than requested count
    if(AF_ENCODER_COUNT >= AF_pulses)
    {
      AF_stop(); // Stop motor
      AF_ENCODER_COUNT = 0;  //reset Encoder count
      AF_active = 0;  //reset active flag
      Serial.print("Pulse Count: "); Serial.println(AF_ENCODER_COUNT);
      Serial.print("Current Position: "); Serial.println(AF_CURRENT_POSITION);
    }
  }

  // stop motor when current position is out of range  
  if((AF_CURRENT_POSITION < AF_MIN_RANGE)||(AF_CURRENT_POSITION > AF_MAX_RANGE))
  {
    AF_stop(); // Stop motor
    Serial.print("Pulse Count: "); Serial.println(AF_ENCODER_COUNT);
    Serial.print("Current Position: "); Serial.println(AF_CURRENT_POSITION);
    AF_ENCODER_COUNT = 0;
    if(AF_CURRENT_POSITION < AF_MIN_RANGE)
      AF_CURRENT_POSITION = 0;
    if(AF_CURRENT_POSITION > AF_MAX_RANGE)
      AF_CURRENT_POSITION = AF_MAX_RANGE;
  }
}
