#ifndef PARAMETER_H_
#define PARAMETER_H_

#define TIRE_DIAMETER (24.7)
#define TREAD_WIDTH (30.4)
#define TREAD_CIRCUIT (TREAD_WIDTH * PI / 4)
#define PULSE (TIRE_DIAMETER * PI / (35.0 / 10.0 * 20.0 * 8.0))
#define MIN_HZ 40

#define WAITLOOP_SLED 10

#define REF_SEN_R 370
#define REF_SEN_L 460

#define TH_SEN_R 128
#define TH_SEN_L 143
#define TH_SEN_FR 152
#define TH_SEN_FL 176

#define CONTROL_TH_SEN_R TH_SEN_R
#define CONTROL_TH_SEN_L TH_SEN_L

#define CON_WALL_KP 0.12 // 0.12
#define SEARCH_ACCEL 1.5
#define TURN_ACCEL 0.3
#define HOSEI_ACCEL 0.3
#define HOSEI_SPEED 50

#define SEARCH_SPEED 200
#define MAX_SPEED 600
#define MIN_SPEED (MIN_HZ * PULSE)

#define GOAL_X 4
#define GOAL_Y 4

#define INC_FREQ 3000
#define DEC_FREQ 2000

#define BATT_MAX 4000
#define BATT_MIN 3800

#define HALF_SECTION 45
#define SECTION 90

#define r_hosei 54.25
#define l_hosei 56.65

#define slalom_speed_longer 301//267
#define slalom_speed_shorter 98
#define slalom_accel_longer 1
#define slalom_accel_shorter -1
const double turnRadius = 36.0;

#endif  // PARAMETER_H_