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

#include "FS.h"
#include "SPIFFS.h"
#include "device.h"
#include "map_manager.h"
#include "mytypedef.h"
#include "parameter.h"

signed char g_mode;
short g_battery_value;
t_sensor g_sen_r, g_sen_l, g_sen_fr, g_sen_fl;
t_control g_con_wall;

float r_adjust_len = 0.0, l_adjust_len = 0.0;

volatile double g_accel_r;
volatile double g_accel_l;
double g_max_speed_r, g_max_speed_l, g_min_speed_r, g_min_speed_l;
volatile double g_speed_r;
volatile double g_speed_l;
volatile bool g_motor_move;
MapManager g_map_control;

void setup()
{
  // put your setup code here, to run once:

  initAll();
  disableBuzzer();
  g_mode = 1;
}

void loop()
{
  int run_modes[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; // 1から3の走行モードを指定

  setLED(g_mode);
  switch (getSW()) {
    case SW_RM: // 右のボタンが押された時
      g_mode = incButton(g_mode, 15, 1);
      break;
    case SW_LM: // 左のボタンが押された時
      okButton(); // ブザーを鳴らす
      for (int run_mode : run_modes){
        if (g_mode == run_mode) {
          enableMotor();
          detect_hand();
          okButton();
        }
      }
      execByMode(g_mode);
      break;
  }
  delay(1);
}

void execByMode(int mode)
{
  delay(1000);

  switch (mode) {
    case 1:
      searchLefthand();
      break;
    case 2:  //足立法
      g_map_control.positionInit();
      searchAdachi(g_map_control.getGoalX(), g_map_control.getGoalY());
      rotate(right, 2);
      g_map_control.nextDir(right);
      g_map_control.nextDir(right);
      goalAppeal();
      searchAdachi(0, 0);
      rotate(right, 2);
      g_map_control.nextDir(right);
      g_map_control.nextDir(right);
      mapWrite();
      break;
    case 3:  //最短走行
      copyMap();
      g_map_control.positionInit();
      fastRun1(g_map_control.getGoalX(), g_map_control.getGoalY());
      rotate(right, 2);
      g_map_control.nextDir(right);
      g_map_control.nextDir(right);
      goalAppeal();
      fastRun1(0, 0);
      rotate(right, 2);
      g_map_control.nextDir(right);
      g_map_control.nextDir(right);
      break;
    case 4:
      copyMap();
      g_map_control.positionInit();
      fastRun2(g_map_control.getGoalX(), g_map_control.getGoalY());
      rotate(right, 2);
      g_map_control.nextDir(right);
      g_map_control.nextDir(right);
      goalAppeal();
      fastRun2(0, 0);
      rotate(right, 2);
      g_map_control.nextDir(right);
      g_map_control.nextDir(right);
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      break;
    case 9:
      break;
    case 10:
      break;
    case 11:
      break;
    case 12:
      break;
    case 13:
      break;
    case 14:
      break;
    case 15:
      disableMotor();
      adjustMenu();  //調整メニューに行く
      break;
    default:
      break;
  }
  disableMotor();
}

void detect_hand(void) {
  int count = 0;
  const int TH_DETECT_FR = 700;
  const int TH_DETECT_FL = 900;

  while(count <= 5){
    if (g_sen_fr.value > TH_DETECT_FR || g_sen_fl.value > TH_DETECT_FL){
      count++;
      delay(100);
    //}
    delay(10);
  }
}
}

