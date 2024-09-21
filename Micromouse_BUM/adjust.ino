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

void mapView(void)
{
  Serial.printf("\x1b[2j");
  Serial.printf("\x1b[0;0H");
  Serial.printf("\n\r+");
  for (int i = 0; i < MAZESIZE_X; i++) {
    switch (g_map_control.getWallData(i, MAZESIZE_Y - 1, north)) {  //黒色は"[30m"
      case NOWALL:
        Serial.printf("\x1b[37m  +");  //NOWALL
        break;
      case WALL:
        Serial.printf("\x1b[37m--+");  //WALL
        break;
      case _UNKNOWN:
        Serial.printf("\x1b[31m--+");  //UNNOWN
        break;
      default:
        Serial.printf("\x1b[33m--+");  //VWALL
        break;
    }
  }
  Serial.printf("\n\r");
  for (int j = (MAZESIZE_Y - 1); j > -1; j--) {
    switch (g_map_control.getWallData(0, j, west)) {
      case NOWALL:
        // Serial.printf("\x1b[37m ");  //NOWALL
        Serial.printf(" ");  //NOWALL
        break;
      case WALL:
        // Serial.printf("\x1b[37m|");  //WALL
        Serial.printf("|");  //WALL
        break;
      case _UNKNOWN:
        // Serial.printf("\x1b[31m|");  //UNNOWN
        Serial.printf("|");  //UNNOWN
        break;
      default:
        // Serial.printf("\x1b[33m|");  //VWALL
        Serial.printf("|");  //VWALL
        break;
    }
    for (int i = 0; i < MAZESIZE_X; i++) {
      switch (g_map_control.getWallData(i, j, east)) {
        case NOWALL:
          //Serial.printf("\x1b[37m   ");  //NOWALL
          Serial.printf("   ");  //NOWALL
          break;
        case WALL:
          // Serial.printf("\x1b[37m  |");  //WALL
          Serial.printf("  |");  //WALL
          break;
        case _UNKNOWN:
          // Serial.printf("\x1b[31m  |");  //UNNOWN
          Serial.printf("  |");  //UNNOWN
          break;
        default:
          // Serial.printf("\x1b[33m  |");  //VWALL
          Serial.printf("  |");  //VWAL
          break;
      }
    }
    Serial.printf("\n\r+");
    for (int i = 0; i < MAZESIZE_X; i++) {
      switch (g_map_control.getWallData(i, j, south)) {
        case NOWALL:
          // Serial.printf("\x1b[37m  +");  //NOWALL
          Serial.printf("  +");  //NOWALL
          break;
        case WALL:
          // Serial.printf("\x1b[37m--+");  //WALL
          Serial.printf("--+");  //WALL
          break;
        case _UNKNOWN:
          // Serial.printf("\x1b[31m--+");  //UNNOWN
          Serial.printf("--+");  //UNNOWN
          break;
        default:
          // Serial.printf("\x1b[33m--+");  //VWALL
          Serial.printf("--+");  //VWALL
          break;
      }
    }
    Serial.printf("\n\r");
  }
}

void viewAdc(void)
{
  disableMotor();

  while (1) {
    Serial.printf("r_sen        is\t%d   \r\n", g_sen_r.value);
    Serial.printf("fr_sen       is\t%d   \r\n", g_sen_fr.value);
    Serial.printf("fl_sen       is\t%d  \r\n", g_sen_fl.value);
    Serial.printf("l_sen        is\t%d   \r\n", g_sen_l.value);
    Serial.printf("VDD          is\t%d mV\r\n", g_battery_value);
    Serial.printf("\n\r");  //改行
    delay(100);
    Serial.printf("\x1b[2j");
    Serial.printf("\x1b[0;0H");
  }
}

void straightCheck(int section_check)
{
  enableMotor();
  delay(1000);
  accelerate(HALF_SECTION, SEARCH_SPEED);
  if (section_check > 1) {
    straight(SECTION * (section_check - 1), SEARCH_SPEED, MAX_SPEED, SEARCH_SPEED);
  }
  decelerate(HALF_SECTION, SEARCH_SPEED);

  disableMotor();
}

void straightCheck2(void)
{
  enableMotor();
  delay(1000);
  accelerate(HALF_SECTION, SEARCH_SPEED);
  oneStep(25.5,SEARCH_SPEED);
  slalom(right);
  oneStep(25.5,SEARCH_SPEED);
  oneStep(25.5,SEARCH_SPEED);
  slalom(right);
  oneStep(25.5,SEARCH_SPEED);
  oneStep(25.5,SEARCH_SPEED);
  slalom(right);
  oneStep(25.5,SEARCH_SPEED);
  oneStep(25.5,SEARCH_SPEED);
  slalom(right);
  oneStep(25.5,SEARCH_SPEED);
  oneStep(25.5,SEARCH_SPEED);
  slalom(right);
  oneStep(25.5,SEARCH_SPEED);
  oneStep(25.5,SEARCH_SPEED);
  slalom(right);
  oneStep(25.5,SEARCH_SPEED);
  oneStep(25.5,SEARCH_SPEED);
  slalom(right);
  oneStep(25.5,SEARCH_SPEED);
  oneStep(25.5,SEARCH_SPEED);
  slalom(right);
  oneStep(25.5,SEARCH_SPEED);
  decelerate(HALF_SECTION, SEARCH_SPEED);

  disableMotor();
}


void get_adjust_len(float * r_len, float * l_len){ // 簡単に取得できるように専用関数を作る
    *r_len = r_adjust_len;
    *l_len = l_adjust_len;
}

void rotationCheck(void)
{
  enableMotor();
  delay(1000);
  for (int i = 0; i < 8; i++) {
    rotate(right, 1);
  }
  disableMotor();
}

void testSlalom(void)
{
  enableMotor();
  delay(1000);
  accelerate(HALF_SECTION, SEARCH_SPEED);
  oneStep(9.8, SEARCH_SPEED);
  slalom(right);
  oneStep(9.8, SEARCH_SPEED);
  oneStep(9.8, SEARCH_SPEED);
  slalom(right);
  oneStep(9.8, SEARCH_SPEED);
  oneStep(9.8, SEARCH_SPEED);
  slalom(right);
  oneStep(9.8, SEARCH_SPEED);
  oneStep(9.8, SEARCH_SPEED);
  slalom(right);
  oneStep(9.8, SEARCH_SPEED);
  oneStep(9.8, SEARCH_SPEED);
  slalom(right);
  oneStep(9.8, SEARCH_SPEED);
  oneStep(9.8, SEARCH_SPEED);
  slalom(right);
  oneStep(9.8, SEARCH_SPEED);
  oneStep(9.8, SEARCH_SPEED);
  slalom(right);
  oneStep(9.8, SEARCH_SPEED);
  oneStep(9.8, SEARCH_SPEED);
  slalom(right);
  oneStep(9.8, SEARCH_SPEED);
  decelerate(HALF_SECTION,SEARCH_SPEED);
  disableMotor();
}

void testSlalom2(void)
{
  enableMotor();
  delay(1000);
  accelerate(HALF_SECTION, SEARCH_SPEED);
  //oneStep(10, SEARCH_SPEED);
  slalom(right);
  decelerate(HALF_SECTION,SEARCH_SPEED);
  disableMotor();
}

void adjustMenu(void)
{
  unsigned char mode = 1;
  char LED3_data;
  char sw;

  while (1) {
    setLED(mode);
    while (1) {
      sw = getSW();
      if (sw != 0) break; // スイッチが押されたらこのループを抜ける
      delay(33);
      LED3_data ^= 1;
      setLED((mode & 0x7) + ((LED3_data << 3) & 0x08));
    }
    LED3_data = 0;
    switch (sw) {
      case SW_RM: // 右のボタンが押された場合
        mode = incButton(mode, 7, 1);
        break;
      case SW_LM: // 左のボタンが押された場合
        okButton();
        if (execByModeAdjust(mode) == 1) {
          return;
        }
        break;
      default:
        break;
    }
  }
}

void wall_hosei_check(void){ // Not working
  enableMotor();
  delay(1000);
  accelerate(HALF_SECTION, SEARCH_SPEED);
  check_straight(SEARCH_SPEED);
  decelerate(HALF_SECTION, SEARCH_SPEED);
  disableMotor();
  delay(3000);
  printAdjustLen();
}

void printAdjustLen() { // Not working
  Serial.print("Left adjust length: ");
  Serial.println(l_adjust_len);
  Serial.print("Right adjust length: ");
  Serial.println(r_adjust_len);
}


unsigned char execByModeAdjust(unsigned char mode)
{
  disableMotor();
  switch (mode) {
    case 1:
      viewAdc();
      break;
    case 2:
      //straightCheck(15);
      straightCheck(15);
      break;

    case 3:
      //rotationCheck();
      testSlalom();
      break;
    case 4:
      copyMap();
      mapView();
      break;

    case 5:
      wall_hosei_check();
      break;

    case 6:
      printAdjustLen();
      break;

    default:
      return 1;
      break;
  }

  return 0;
}
