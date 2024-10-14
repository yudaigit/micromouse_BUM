#ifndef MYTYPEDEF_H_
#define MYTYPEDEF_H_

typedef struct
{
  short value;      // Sensor value
  short p_value;    // Previous sensor value
  short error;      // Error value
  short ref;        // Reference value
  short th_wall;    // Wall threshold
  short th_control; // Control threshold
  bool is_wall;     // Boolean indicating if there is a wall
  bool is_control;  // Boolean indicating if control is unabled. 
} t_sensor;

typedef struct
{
  double control;
  double error;
  double p_error;
  double diff;
  double sum;
  double sum_max;
  double kp;
  double kd;
  double ki;
  bool enable;
} t_control;

typedef enum { MOT_FORWARD, MOT_BACK } t_CW_CCW;

#endif  // MYTYPEDEF_H_