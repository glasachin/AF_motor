#define AF_M1_0 9 // Auto Focus Motor (PWM Pins)
#define AF_M1_1 6 // Auto Focus Motor (PWM Pins)
#define AF_ENCODER 3 // Auto Focus Encoder
#define AF_MIN_RANGE 0 // Auto Focus min. range in encoder steps
#define AF_MAX_RANGE 40000 // Auto Focus Max. range in encoder steps
#define AF_LIMIT_SWITCH 5 // Pin at which Auto Focus motor limit switch is connected

#define AA_M1_0 10 // Auto Aperture Motor (PWM Pins)
#define AA_M1_1 11 // Auto Aperture Motor (PWM Pins)
#define AA_ENCODER 2 // Auto Aperture Encoder
#define AA_MIN_RANGE 0 // Auto Aperture min. range in encoder steps
#define AA_MAX_RANGE 40000 // Auto Aperture Max. range in encoder steps
#define AA_LIMIT_SWITCH 4 // Pin at which limit switch is connected

unsigned long int AF_pulses = 0;
volatile long int AF_ENCODER_COUNT = 0; // to store the required pulse move information
volatile long int AF_CURRENT_POSITION = 0;
unsigned int AF_move_direction = -1; // 0: forward, 1:backward

unsigned long int AA_pulses = 0;
volatile long int AA_ENCODER_COUNT = 0; // to store the required pulse move information
volatile long int AA_CURRENT_POSITION = 0;
unsigned int AA_move_direction = -1; // 0: forward, 1:backward

void AF_limit_switch_init(void);
void AF_motor_init(void);
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

void AA_limit_switch_init(void);
void AA_motor_init(void);
void AA_forward(void);
void AA_backward(void);
void AA_stop(void);
void AA_home(void);
void AA_PWM_forward(int);
void AA_PWM_backward(int);
void AA_run_motor_forward(char*);
void AA_run_motor_backward(char*);
void AA_find_dir(char*);
void AA_ENCODER_INIT(void);
void AA_ENCODER_ISR(void);
