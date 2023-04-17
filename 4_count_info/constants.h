#define AF_M1_0 10 // Auto Focus Motor (PWM Pins)
#define AF_M1_1 11 // Auto Focus Motor (PWM Pins)
#define AF_ENCODER 2 // Auto Focus Encoder
#define AF_MIN_RANGE 0 // Auto Focus min. range in encoder steps
#define AF_MAX_RANGE 40000 // Auto Focus Max. range in encoder steps

unsigned long int pulses = 0;
volatile unsigned long int AF_ENCODER_COUNT = 0;
volatile unsigned long int CURRENT_POSITION = 0;
unsigned int move_direction = -1; // 0: forward, 1:backward
