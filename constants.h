#define AF_M1_0 9// Auto Focus Motor (PWM Pins)
#define AF_M1_1 10 // Auto Focus Motor (PWM Pins)
#define AA_M2_0 5 // Auto Aperture Motor (PWM Pins)
#define AA_M2_1 6 // Auto Aperture Motor (PWM Pins)
#define AF_ENCODER_A 2 // Encoder signal A
#define AF_ENCODER_B 3 // Encoder signal B
#define AA_ENCODER_A 7 // Encoder signal A
#define AA_ENCODER_B 8 // Encoder signal B
#define AF_MIN_RANGE 0 // Auto Focus min. range in encoder steps
#define AF_MAX_RANGE 10000 // Auto Focus Max. range in encoder steps
#define AA_MIN_RANGE 0 // Auto Focus min. range in encoder steps
#define AA_MAX_RANGE 10000 // Auto Focus Max. range in encoder steps
#define AF_LIMIT_SW 0 // Auto Focus Limit switch Pin
#define AA_LIMIT_SW 1 // Auto Focus Limit switch Pin

unsigned long int AF_pulses = 0;
unsigned long int AA_pulses = 0;
volatile long int AF_ENCODER_COUNT = 0; // to store the required pulse move information
volatile long int AF_CURRENT_POSITION = 0;
unsigned int AF_move_dir = 2; // 0: forward, 1:backward
unsigned int AA_move_dir = 2; // 0: forward, 1:backward
bool AF_active = 0;

void motor_init(void);
void limit_sw_init(void);
void AF_forward(void);
void AF_backward(void);
void AF_stop(void);
void AF_home(void);
void AF_PWM_forward(int);
void AF_PWM_backward(int);
void AF_run_motor_forward(char*);
void AF_run_motor_backward(char*);
void AF_ABS_move(char*);
void AF_ENCODER_INIT(void);
void AF_ENCODER_ISR(void);
