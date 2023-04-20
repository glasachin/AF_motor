#define AF_M1_0 10 // Auto Focus Motor (PWM Pins)
#define AF_M1_1 11 // Auto Focus Motor (PWM Pins)
#define AF_ENCODER 2 // Auto Focus Encoder
#define AF_MIN_RANGE 0 // Auto Focus min. range in encoder steps
#define AF_MAX_RANGE 40000 // Auto Focus Max. range in encoder steps
#define LIMIT_SWITCH 4 // Pin at which limit switch is connected

unsigned long int pulses = 0;
volatile long int AF_ENCODER_COUNT = 0; // to store the required pulse move information
volatile long int CURRENT_POSITION = 0;
unsigned int move_direction = -1; // 0: forward, 1:backward

void AF_motor_init(void);
void limit_switch_init(void);
void AF_forward(void);
void AF_backward(void);
void AF_stop(void);
void AF_home(void);
void AF_PWM_forward(int);
void AF_PWM_backward(int);
void AF_run_motor_forward(char*);
void AF_run_motor_backward(char*);
void AF_find_dir(char*);
void AF_ENCODER_INIT(void);
void AF_ENCODER_ISR(void);
