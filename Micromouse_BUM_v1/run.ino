// Copyright 2023 RT Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

void straight(int len, int init_speed, int max_speed, int finish_speed)
{
  int obj_step;
  char r_wall_check = 0, l_wall_check = 0, hosei_f = 0; //

  controlInterruptStop();
  g_max_speed_r = g_max_speed_l = max_speed;
  g_accel_r = g_accel_l = SEARCH_ACCEL;

  if (init_speed < MIN_SPEED) {
    g_speed_r = g_speed_l = MIN_SPEED;
    clearStepR();
    clearStepL();
  } else {
    g_speed_r = g_speed_l = init_speed;
  }
  if (finish_speed < MIN_SPEED) {
    finish_speed = MIN_SPEED;
  }
  if (init_speed < finish_speed) {
    g_min_speed_r = g_min_speed_l = MIN_SPEED;
  } else {
    g_min_speed_r = g_min_speed_l = finish_speed;
  }
  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));

  g_con_wall.enable = true;
  obj_step = (int)((float)len * 2.0 / PULSE);
  moveDir(MOT_FORWARD, MOT_FORWARD);  //left,right
  controlInterruptStart();

  r_wall_check = g_sen_r.is_wall; //
  l_wall_check = g_sen_l.is_wall; //

  g_motor_move = 1;
  while ((len - (getStepR() + getStepL()) / 2.0 * PULSE) >
         (((g_speed_r * g_speed_r) - (finish_speed * finish_speed)) / (2.0 * 1000.0 * SEARCH_ACCEL))) {
          delayMicroseconds(100);

        if (len - (getStepR() + getStepL()) / 2.0 * PULSE < 45) { //        
        }

        if (len - (getStepR() + getStepL()) / 2.0 * PULSE < 90) { //
          if ((g_sen_r.is_wall == false) && (r_wall_check == true) && (hosei_f == 0)) {
            len = (getStepR() + getStepL()) / 2.0 * PULSE + 90 - r_hosei;
            hosei_f = 1;
            //Serial.println("Hosei function called");
          }
          if ((g_sen_l.is_wall == false) && (l_wall_check == true) && (hosei_f == 0)) {
            len = (getStepR() + getStepL()) / 2.0 * PULSE + 90 - l_hosei;
            hosei_f = 1;
            //Serial.println("Hosei function called");
          }
        }
    continue;
  }
  g_accel_r = g_accel_l = -1.0 * SEARCH_ACCEL;

  while ((getStepR() + getStepL()) < obj_step) {
    continue;
  }

  if (finish_speed == SEARCH_SPEED) {
    controlInterruptStop();
    g_max_speed_r = g_min_speed_r = g_speed_r = finish_speed;
    g_max_speed_l = g_min_speed_l = g_speed_l = finish_speed;
    g_accel_r = g_accel_l = 0.0;
    clearStepR();
    clearStepL();
    controlInterruptStart();
  } else {
    g_motor_move = 0;
  }
}

void straight_faster(int len, int init_speed, int max_speed, int finish_speed)
{
  int obj_step;
  char r_wall_check = 0, l_wall_check = 0, hosei_f = 0; //

  controlInterruptStop();
  g_max_speed_r = g_max_speed_l = max_speed;
  g_accel_r = g_accel_l = 1.8;

  if (init_speed < MIN_SPEED) {
    g_speed_r = g_speed_l = MIN_SPEED;
    clearStepR();
    clearStepL();
  } else {
    g_speed_r = g_speed_l = init_speed;
  }
  if (finish_speed < MIN_SPEED) {
    finish_speed = MIN_SPEED;
  }
  if (init_speed < finish_speed) {
    g_min_speed_r = g_min_speed_l = MIN_SPEED;
  } else {
    g_min_speed_r = g_min_speed_l = finish_speed;
  }
  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));

  g_con_wall.enable = true;
  obj_step = (int)((float)len * 2.0 / PULSE);
  moveDir(MOT_FORWARD, MOT_FORWARD);  //left,right
  controlInterruptStart();

  r_wall_check = g_sen_r.is_wall; //
  l_wall_check = g_sen_l.is_wall; //

  g_motor_move = 1;
  while ((len - (getStepR() + getStepL()) / 2.0 * PULSE) >
         (((g_speed_r * g_speed_r) - (finish_speed * finish_speed)) / (2.0 * 1000.0 * SEARCH_ACCEL))) {
          delayMicroseconds(100);

        if (len - (getStepR() + getStepL()) / 2.0 * PULSE < 45) { //        
        }

        if (len - (getStepR() + getStepL()) / 2.0 * PULSE < 90) { //
          if ((g_sen_r.is_wall == false) && (r_wall_check == true) && (hosei_f == 0)) {
            len = (getStepR() + getStepL()) / 2.0 * PULSE + 90 - r_hosei;
            hosei_f = 1;
            //Serial.println("Hosei function called");
          }
          if ((g_sen_l.is_wall == false) && (l_wall_check == true) && (hosei_f == 0)) {
            len = (getStepR() + getStepL()) / 2.0 * PULSE + 90 - l_hosei;
            hosei_f = 1;
            //Serial.println("Hosei function called");
          }
        }
    continue;
  }
  g_accel_r = g_accel_l = -1.0 * SEARCH_ACCEL;

  while ((getStepR() + getStepL()) < obj_step) {
    continue;
  }

  if (finish_speed == SEARCH_SPEED) {
    controlInterruptStop();
    g_max_speed_r = g_min_speed_r = g_speed_r = finish_speed;
    g_max_speed_l = g_min_speed_l = g_speed_l = finish_speed;
    g_accel_r = g_accel_l = 0.0;
    clearStepR();
    clearStepL();
    controlInterruptStart();
  } else {
    g_motor_move = 0;
  }
}

void accelerate(int len, int finish_speed)
{
  int obj_step;

  controlInterruptStop();
  g_max_speed_r = g_max_speed_l = finish_speed;
  g_accel_r = g_accel_l = SEARCH_ACCEL;
  g_speed_r = g_min_speed_r = MIN_SPEED;
  g_speed_l = g_min_speed_l = MIN_SPEED;
  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));
  clearStepR();
  clearStepL();
  g_con_wall.enable = true;
  obj_step = (int)((float)len * 2.0 / PULSE);
  moveDir(MOT_FORWARD, MOT_FORWARD);
  controlInterruptStart();

  g_motor_move = 1;

  while ((getStepR() + getStepL()) < obj_step) {
    continue;
  }

  controlInterruptStop();
  g_max_speed_r = g_min_speed_r = g_speed_r = finish_speed;
  g_max_speed_l = g_min_speed_l = g_speed_l = finish_speed;
  g_accel_r = g_accel_l = 0.0;
  clearStepR();
  clearStepL();
  controlInterruptStart();
}

void oneStep(int len, int tar_speed)
{
  int obj_step;
  char r_wall_check = 0, l_wall_check = 0, hosei_f = 0; //
  controlInterruptStop();
  g_speed_r = g_min_speed_r = g_max_speed_r = tar_speed;
  g_speed_l = g_min_speed_l = g_max_speed_l = tar_speed;
  g_accel_r = g_accel_l = 0.0;
  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));
  g_con_wall.enable = true;
  obj_step = (int)((float)len * 2.0 / PULSE);
  moveDir(MOT_FORWARD, MOT_FORWARD);

  r_wall_check = g_sen_r.is_wall; //
  l_wall_check = g_sen_l.is_wall; //

  controlInterruptStart();

  while ((getStepR() + getStepL()) < obj_step) {
    delayMicroseconds(100);

    if (len - (getStepR() + getStepL()) / 2.0 * PULSE < 90) { //
      if ((g_sen_r.is_wall == false) && (r_wall_check == true) && (hosei_f == 0)) {
        len = (getStepR() + getStepL()) / 2.0 * PULSE + 90 - r_hosei;
        hosei_f = 1;
        okButton();
        //Serial.println("Hosei function called");
      }
      if ((g_sen_l.is_wall == false) && (l_wall_check == true) && (hosei_f == 0)) {
        len = (getStepR() + getStepL()) / 2.0 * PULSE + 90 - l_hosei;
        hosei_f = 1;
        okButton();
        //Serial.println("Hosei function called");
      }
    }
    continue;
  }
  controlInterruptStop();
  g_max_speed_r = g_min_speed_r = g_speed_r = tar_speed;
  g_max_speed_l = g_min_speed_l = g_speed_l = tar_speed;
  g_accel_r = g_accel_l = 0.0;
  clearStepR();
  clearStepL();
  controlInterruptStart();
}

void oneStep2(int len, int tar_speed)
{
  int obj_step;
  char r_wall_check = 0, l_wall_check = 0, hosei_f = 0; //
  controlInterruptStop();
  g_speed_r = g_min_speed_r = g_max_speed_r = tar_speed;
  g_speed_l = g_min_speed_l = g_max_speed_l = tar_speed;
  g_accel_r = g_accel_l = 0.0;
  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));
  g_con_wall.enable = false;
  obj_step = (int)((float)len * 2.0 / PULSE);
  moveDir(MOT_FORWARD, MOT_FORWARD);

  r_wall_check = g_sen_r.is_wall; //
  l_wall_check = g_sen_l.is_wall; //

  controlInterruptStart();

  while ((getStepR() + getStepL()) < obj_step) {
    delayMicroseconds(100);

    if (len - (getStepR() + getStepL()) / 2.0 * PULSE < 90) { //
      if ((g_sen_r.is_wall == false) && (r_wall_check == true) && (hosei_f == 0)) {
        len = (getStepR() + getStepL()) / 2.0 * PULSE + 90 - r_hosei;
        hosei_f = 1;
        okButton();
        //Serial.println("Hosei function called");
      }
      if ((g_sen_l.is_wall == false) && (l_wall_check == true) && (hosei_f == 0)) {
        len = (getStepR() + getStepL()) / 2.0 * PULSE + 90 - l_hosei;
        hosei_f = 1;
        okButton();
        //Serial.println("Hosei function called");
      }
    }
    continue;
  }
  controlInterruptStop();
  g_max_speed_r = g_min_speed_r = g_speed_r = tar_speed;
  g_max_speed_l = g_min_speed_l = g_speed_l = tar_speed;
  g_accel_r = g_accel_l = 0.0;
  clearStepR();
  clearStepL();
  controlInterruptStart();
}

void decelerate(int len, int tar_speed)
{
  int obj_step;
  controlInterruptStop();
  g_max_speed_r = g_max_speed_l = tar_speed;
  g_accel_r = g_accel_l = 0.0;
  g_speed_r = g_min_speed_r = tar_speed;
  g_speed_l = g_min_speed_l = tar_speed;

  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));
  g_con_wall.enable = true;
  obj_step = (int)((float)len * 2.0 / PULSE);
  moveDir(MOT_FORWARD, MOT_FORWARD);
  controlInterruptStart();

  while ((len - (getStepR() + getStepL()) / 2.0 * PULSE) >
         (((g_speed_r * g_speed_r) - (MIN_SPEED * MIN_SPEED)) / (2.0 * 1000.0 * SEARCH_ACCEL))) {
    continue;
  }
  g_accel_r = g_accel_l = -1.0 * SEARCH_ACCEL;
  g_min_speed_r = MIN_SPEED;
  g_min_speed_l = MIN_SPEED;

  while ((getStepR() + getStepL()) < obj_step) {
    continue;
  }

  g_motor_move = 0;

  delay(300);
}

void rotate(t_direction dir, int times)
{
  int obj_step;
  controlInterruptStop();
  g_max_speed_r = g_max_speed_l = SEARCH_SPEED;
  g_accel_r = g_accel_l = TURN_ACCEL;
  g_speed_r = g_min_speed_r = MIN_SPEED;
  g_speed_l = g_min_speed_l = MIN_SPEED;
  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));
  clearStepR();
  clearStepL();
  g_con_wall.enable = false;
  obj_step = (int)(TREAD_WIDTH * PI / 4.0 * (float)times * 2.0 / PULSE);

  switch (dir) {
    case right:
      moveDir(MOT_FORWARD, MOT_BACK);
      g_motor_move = 1;
      break;
    case left:
      moveDir(MOT_BACK, MOT_FORWARD);
      g_motor_move = 1;
      break;
    default:
      g_motor_move = 0;
      break;
  }
  controlInterruptStart();

  while (((obj_step - (getStepR() + getStepL())) / 2.0 * PULSE) >
         (((g_speed_r * g_speed_r) - (MIN_SPEED * MIN_SPEED)) / (2.0 * 1000.0 * TURN_ACCEL))) {
    continue;
  }
  g_accel_r = g_accel_l = -1.0 * TURN_ACCEL;

  while ((getStepR() + getStepL()) < obj_step) {
    continue;
  }

  g_motor_move = 0;
  delay(300);
}


void slalom(t_direction dir)
{
  int obj_step_r;
  int obj_step_l;
  controlInterruptStop();
  
  switch (dir){
    case right:
      g_accel_r = slalom_accel_shorter; // 移動距離が短い右側のタイヤの加速度を設定
      g_accel_l = slalom_accel_longer; // 移動距離が長い左側のタイヤの加速度を設定
      g_max_speed_l = slalom_speed_longer; // 左タイヤの最高速度を設定
      g_min_speed_r = slalom_speed_shorter; // 右タイヤの最低速度を設定
      g_speed_r = SEARCH_SPEED; // 現在の右タイヤの速度を最高速度として設定する。
      g_speed_l = g_min_speed_l = SEARCH_SPEED; // 左タイヤの現在の速度を最低速度として設定する。
      obj_step_r = (int)((turnRadius - TREAD_WIDTH / 2) * 2 * PI / 4 / PULSE ); // 右タイヤの移動距離を計算
      obj_step_l = (int)((turnRadius + TREAD_WIDTH / 2) * 2 * PI / 4 / PULSE ); // 左タイヤの移動距離を計算
      break;
    case left:
      g_accel_l = slalom_accel_shorter;
      g_accel_r = slalom_accel_longer;
      g_max_speed_r = slalom_speed_longer;
      g_min_speed_l = slalom_speed_shorter;
      g_speed_l = SEARCH_SPEED;
      g_speed_r = g_min_speed_r = SEARCH_SPEED;
      obj_step_r = (int)((turnRadius + TREAD_WIDTH / 2) * 2 * PI / 4 / PULSE );
      obj_step_l = (int)((turnRadius - TREAD_WIDTH / 2) * 2 * PI / 4 / PULSE );
      break;
    default:
      return;
  }

  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));
  clearStepR();
  clearStepL();
  g_con_wall.enable = false;
  moveDir(MOT_FORWARD, MOT_FORWARD);  //left,right

  controlInterruptStart();

while (((obj_step_r - getStepR()) > (((g_speed_r * g_speed_r) - (MIN_SPEED * MIN_SPEED)) / (2.0 * 1000.0 * slalom_speed_longer))) &&
      ((obj_step_l - getStepL()) > (((g_speed_l * g_speed_l) - (MIN_SPEED * MIN_SPEED)) / (2.0 * 1000.0 * slalom_speed_longer)))) {
    continue;
}

g_accel_r = g_accel_r * (-1.0);
g_accel_l = g_accel_l * (-1.0);

  switch (dir){
    case right:
      g_max_speed_r = g_min_speed_l = SEARCH_SPEED; // 右タイヤの最高速度を設定
      break;
    case left:
      g_max_speed_l = g_min_speed_r = SEARCH_SPEED; // 右タイヤの最高速度を設定
      break;
    default:
      return;
  }


  while ((getStepR() < obj_step_r) && (getStepL() < obj_step_l)) {
      continue;
  }

  controlInterruptStop();
  g_max_speed_r = g_min_speed_r = g_speed_r = SEARCH_SPEED;
  g_max_speed_l = g_min_speed_l = g_speed_l = SEARCH_SPEED;
  g_accel_r = g_accel_l = 0.0;
  clearStepR();
  clearStepL();
  controlInterruptStart();

}

void check_straight(int tar_speed) // Needs change
{
  int obj_step;
  float current_distance;
  controlInterruptStop();
  g_speed_r = g_min_speed_r = g_max_speed_r = tar_speed;
  g_speed_l = g_min_speed_l = g_max_speed_l = tar_speed;
  g_accel_r = g_accel_l = 0.0;
  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));
  g_con_wall.enable = true;
  r_adjust_len = l_adjust_len = 0;
  obj_step = (int)((float)90 * 2.0 / PULSE);
  moveDir(MOT_FORWARD, MOT_FORWARD);
  controlInterruptStart();

  while ((getStepR() + getStepL()) < obj_step) {
    if ((g_sen_r.is_wall == false) && (r_adjust_len == 0)) {
      current_distance = ((float)(getStepR() + getStepL()) / 2.0) * PULSE;
      r_adjust_len = current_distance;
      delay(10);
    }
    if ((g_sen_l.is_wall == false) && (l_adjust_len == 0)) {
      current_distance = ((float)(getStepR() + getStepL()) / 2.0) * PULSE;
      l_adjust_len = current_distance;
      Serial.println(r_adjust_len);
      delay(10);
    }
  }

  controlInterruptStop();
  g_max_speed_r = g_min_speed_r = g_speed_r = tar_speed;
  g_max_speed_l = g_min_speed_l = g_speed_l = tar_speed;
  g_accel_r = g_accel_l = 0.0;
  clearStepR();
  clearStepL();
  controlInterruptStart();
}

void hardwareHosei (int len){
  int obj_step;
  controlInterruptStop();
  g_max_speed_r = g_max_speed_l = HOSEI_SPEED;
  g_accel_r = g_accel_l = HOSEI_ACCEL;
  g_speed_r = g_min_speed_r = MIN_SPEED;
  g_speed_l = g_min_speed_l = MIN_SPEED;
  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));
  clearStepR();
  clearStepL();
  g_con_wall.enable = false;
  obj_step = (int)((float)len * 2.0 / PULSE);

  moveDir(MOT_BACK, MOT_BACK);
  g_motor_move = 1;
  controlInterruptStart();

  while (((obj_step - (getStepR() + getStepL())) / 2.0 * PULSE) >
         (((g_speed_r * g_speed_r) - (MIN_SPEED * MIN_SPEED)) / (2.0 * 1000.0 * HOSEI_ACCEL))) {
    continue;
  }
  g_accel_r = g_accel_l = -1.0 * TURN_ACCEL;
  

  while ((getStepR() + getStepL()) < obj_step) {
    continue;
  }

  g_motor_move = 0;
  delay(300);
}

const double WALL_SEN_FR = 246.0;
const double WALL_SEN_FL = 314.0;

void frontWallhosei(int len, int tar_speed)
{
  int obj_step;
  controlInterruptStop();
  g_speed_r = g_min_speed_r = g_max_speed_r = tar_speed;
  g_speed_l = g_min_speed_l = g_max_speed_l = tar_speed;
  g_accel_r = g_accel_l = 0.0;
  setRStepHz((unsigned short)(g_speed_r / PULSE));
  setLStepHz((unsigned short)(g_speed_l / PULSE));
  obj_step = (int)((float)len * 2.0 / PULSE);
  g_con_wall.enable = false;
  moveDir(MOT_FORWARD, MOT_FORWARD);

  controlInterruptStart();

    if (!g_sen_fr.is_wall) {
        while ((getStepR() + getStepL()) < obj_step) {
            continue;
        }
    } else {
        while ((g_sen_fr.value < WALL_SEN_FR) || (g_sen_fl.value < WALL_SEN_FL)) {
            delayMicroseconds(100);
            continue;
        }
    }

  controlInterruptStop();
  g_max_speed_r = g_min_speed_r = g_speed_r = tar_speed;
  g_max_speed_l = g_min_speed_l = g_speed_l = tar_speed;
  g_accel_r = g_accel_l = 0.0;
  clearStepR();
  clearStepL();
  controlInterruptStart();
}