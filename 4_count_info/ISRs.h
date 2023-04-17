#include"AF_motor.h"


void AF_ENCODER_INIT()
{
  pinMode(AF_ENCODER, INPUT_PULLUP);
}

void AF_ENCODER_ISR()
{
  AF_ENCODER_COUNT +=1;

  //update current position
  if(move_direction == 0)
  {
    CURRENT_POSITION += 1;
  }
  else if(move_direction == 1)
  {
    CURRENT_POSITION -= 1;
  }
  else
  { }
  
  // stop motor when encoder count are greater than requested count
  if(AF_ENCODER_COUNT >= pulses)
  {
    AF_stop(); // Stop motor
    detachInterrupt(digitalPinToInterrupt(AF_ENCODER));
    Serial.print("Pulse Count: "); Serial.println(AF_ENCODER_COUNT);
    AF_ENCODER_COUNT = 0;
  }
}
