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

//コンストラクタ
MapManager::MapManager()
{
  for (int i = 0; i < MAZESIZE_X; i++) {
    for (int j = 0; j < MAZESIZE_Y; j++) {
      wall[i][j].north = wall[i][j].east = wall[i][j].south = wall[i][j].west =
        _UNKNOWN;  //迷路の全体がわからない事を設定する
    }
  }

  for (int i = 0; i < MAZESIZE_X; i++) {
    wall[i][0].south = WALL;               //四方の壁を追加する(南)
    wall[i][MAZESIZE_Y - 1].north = WALL;  //四方の壁を追加する(北)
  }

  for (int i = 0; i < MAZESIZE_Y; i++) {
    wall[0][i].west = WALL;               //四方の壁を追加する(西)
    wall[MAZESIZE_X - 1][i].east = WALL;  //四方の壁を追加する(東)
  }
  //   x,y
  wall[0][0].east = wall[1][0].west = WALL;  //スタート地点の右の壁を追加する
  wall[0][0].north = wall[0][1].south = NOWALL;
}

// Initialize my position to (0,0)
void MapManager::positionInit(void)
{
  mypos.x = mypos.y = 0;
  mypos.dir = north;
}

// Update the robot's direction
void MapManager::setMyPosDir(t_direction_glob dir) { mypos.dir = dir; }

// Obtain the robot's x coordinate
short MapManager::getMyPosX(void) { return mypos.x; }

// Obtain the robot's y coordinate
short MapManager::getMyPosY(void) { return mypos.y; }

// Determine if there is a wall in the direction the robot is facing. 
char MapManager::getWallData(unsigned char x, unsigned char y, t_direction_glob dir)
{
  switch (dir) {
    case north:
      return wall[x][y].north;
      break;
    case west:
      return wall[x][y].west;
      break;
    case south:
      return wall[x][y].south;
      break;
    case east:
      return wall[x][y].east;
      break;
  }
  return 99;
}

// Set data about wall by taking the robot's direction and wall data.
void MapManager::setWallData(unsigned char x, unsigned char y, t_direction_glob dir, char data)
{
  switch (dir) {
    case north:
      wall[x][y].north = data;
      break;
    case west:
      wall[x][y].west = data;
      break;
    case south:
      wall[x][y].south = data;
      break;
    case east:
      wall[x][y].east = data;
      break;
  }
}

// Obtain x coordinate of goal
char MapManager::getGoalX(void) { return goal_mx; }

// Obtain y coordinate of goal
char MapManager::getGoalY(void) { return goal_my; }

// Set x coordinate of goal from data
void MapManager::setGoalX(short data) { goal_mx = data; }

// Set y coordinate of goal from data
void MapManager::setGoalY(short data) { goal_my = data; }

// Update the robot's position based on its current direction. 
void MapManager::axisUpdate(void)
{
  switch (mypos.dir) {
    case north:
      mypos.y++;
      break;
    case east:
      mypos.x++;
      break;
    case south:
      mypos.y--;
      break;
    case west:
      mypos.x--;
      break;
  }
}

// Update the robot's direction based on the given dir which can be right or left. 
void MapManager::nextDir(t_direction dir)
{
  if (dir == right) {
    switch (mypos.dir) {
      case north:
        mypos.dir = east;
        break;
      case east:
        mypos.dir = south;
        break;
      case south:
        mypos.dir = west;
        break;
      case west:
        mypos.dir = north;
        break;
    }
  } else if (dir == left) {
    switch (mypos.dir) {
      case north:
        mypos.dir = west;
        break;
      case east:
        mypos.dir = north;
        break;
      case south:
        mypos.dir = east;
        break;
      case west:
        mypos.dir = south;
        break;
    }
  }
}

// Records the wall information detected by the sensors and updates the wall data based on
// the robot's current direction. 
void MapManager::setWall(bool IS_SEN_FR, bool IS_SEN_R, bool IS_SEN_L)  //壁情報を記録
{
  switch (mypos.dir) {
    case north:
      wall[mypos.x][mypos.y].north = IS_SEN_FR ? WALL : NOWALL;
      wall[mypos.x][mypos.y].east = IS_SEN_R ? WALL : NOWALL;
      wall[mypos.x][mypos.y].west = IS_SEN_L ? WALL : NOWALL;
      if (mypos.y < 15) wall[mypos.x][mypos.y + 1].south = IS_SEN_FR ? WALL : NOWALL;
      if (mypos.x < 15) wall[mypos.x + 1][mypos.y].west = IS_SEN_R ? WALL : NOWALL;
      if (mypos.x > 0) wall[mypos.x - 1][mypos.y].east = IS_SEN_L ? WALL : NOWALL;
      break;
    case east:
      wall[mypos.x][mypos.y].east = IS_SEN_FR ? WALL : NOWALL;
      wall[mypos.x][mypos.y].south = IS_SEN_R ? WALL : NOWALL;
      wall[mypos.x][mypos.y].north = IS_SEN_L ? WALL : NOWALL;
      if (mypos.x < 15) wall[mypos.x + 1][mypos.y].west = IS_SEN_FR ? WALL : NOWALL;
      if (mypos.y > 0) wall[mypos.x][mypos.y - 1].north = IS_SEN_R ? WALL : NOWALL;
      if (mypos.y < 15) wall[mypos.x][mypos.y + 1].south = IS_SEN_L ? WALL : NOWALL;
      break;
    case south:
      wall[mypos.x][mypos.y].south = IS_SEN_FR ? WALL : NOWALL;
      wall[mypos.x][mypos.y].west = IS_SEN_R ? WALL : NOWALL;
      wall[mypos.x][mypos.y].east = IS_SEN_L ? WALL : NOWALL;
      if ((mypos.y - 1) > -1) wall[mypos.x][mypos.y - 1].north = IS_SEN_FR ? WALL : NOWALL;
      if ((mypos.x - 1) > -1) wall[mypos.x - 1][mypos.y].east = IS_SEN_R ? WALL : NOWALL;
      if ((mypos.x + 1) < 16) wall[mypos.x + 1][mypos.y].west = IS_SEN_L ? WALL : NOWALL;
      break;
    case west:
      wall[mypos.x][mypos.y].west = IS_SEN_FR ? WALL : NOWALL;
      wall[mypos.x][mypos.y].north = IS_SEN_R ? WALL : NOWALL;
      wall[mypos.x][mypos.y].south = IS_SEN_L ? WALL : NOWALL;
      if ((mypos.x - 1) > -1) wall[mypos.x - 1][mypos.y].east = IS_SEN_FR ? WALL : NOWALL;
      if ((mypos.y + 1) < 16) wall[mypos.x][mypos.y + 1].south = IS_SEN_R ? WALL : NOWALL;
      if ((mypos.y - 1) > -1) wall[mypos.x][mypos.y - 1].north = IS_SEN_L ? WALL : NOWALL;
      break;
  }
}

// Determins the next direction for the robot to move based on the current position, 
// wall data, and the priority of directions. 
t_direction MapManager::getNextDir(char x, char y, t_direction_glob * dir)
{
  int little, priority, tmp_priority;

  makeSearchMap(x, y);
  little = 65535;
  priority = 0;

  if ((wall[mypos.x][mypos.y].north != WALL) && (mypos.y < (MAZESIZE_Y - 1))) {
    tmp_priority = getPriority(mypos.x, mypos.y + 1, north);
    if (steps_map[mypos.x][mypos.y + 1] < little) {
      little = steps_map[mypos.x][mypos.y + 1];
      *dir = north;
      priority = tmp_priority;
    } else if (steps_map[mypos.x][mypos.y + 1] == little) {
      if (priority < tmp_priority) {
        *dir = north;
        priority = tmp_priority;
      }
    }
  }

  if ((wall[mypos.x][mypos.y].east != WALL) && (mypos.x < (MAZESIZE_X - 1))) {
    tmp_priority = getPriority(mypos.x + 1, mypos.y, east);
    if (steps_map[mypos.x + 1][mypos.y] < little) {
      little = steps_map[mypos.x + 1][mypos.y];
      *dir = east;
      priority = tmp_priority;
    } else if (steps_map[mypos.x + 1][mypos.y] == little) {
      if (priority < tmp_priority) {
        *dir = east;
        priority = tmp_priority;
      }
    }
  }

  if ((wall[mypos.x][mypos.y].south != WALL) && (mypos.y > 0)) {
    tmp_priority = getPriority(mypos.x, mypos.y - 1, south);
    if (steps_map[mypos.x][mypos.y - 1] < little) {
      little = steps_map[mypos.x][mypos.y - 1];
      *dir = south;
      priority = tmp_priority;
    } else if (steps_map[mypos.x][mypos.y - 1] == little) {
      if (priority < tmp_priority) {
        *dir = south;
        priority = tmp_priority;
      }
    }
  }

  if ((wall[mypos.x][mypos.y].west != WALL) && (mypos.x > 0)) {
    tmp_priority = getPriority(mypos.x - 1, mypos.y, west);
    if (steps_map[mypos.x - 1][mypos.y] < little) {
      little = steps_map[mypos.x - 1][mypos.y];
      *dir = west;
      priority = tmp_priority;
    } else if (steps_map[mypos.x - 1][mypos.y] == little) {
      if (priority < tmp_priority) {
        *dir = west;
        priority = tmp_priority;
      }
    }
  }

  if (steps_map[mypos.x][mypos.y] == 65535) {
    while (1) {
      setLED(0x0a);
      delay(500);
      setLED(0x05);
      delay(500);
    }
  } else {
    switch (*dir) {
      case north:
        switch (mypos.dir) {
          case north:
            return front;
            break;
          case east:
            return left;
            break;
          case south:
            return rear;
            break;
          case west:
            return right;
            break;
        }
        break;
      case east:
        switch (mypos.dir) {
          case east:
            return front;
            break;
          case south:
            return left;
            break;
          case west:
            return rear;
            break;
          case north:
            return right;
            break;
        }
        break;
      case south:
        switch (mypos.dir) {
          case south:
            return front;
            break;
          case west:
            return left;
            break;
          case north:
            return rear;
            break;
          case east:
            return right;
            break;
        }
        break;
      case west:
        switch (mypos.dir) {
          case west:
            return front;
            break;
          case north:
            return left;
            break;
          case east:
            return rear;
            break;
          case south:
            return right;
            break;
        }
        break;
    }
  }

  return front;
}

// Create a map for pathfinding. Determinesthe next direction to move by evaluationg
// the wall data and proprities for each possible direction. 
t_direction MapManager::getNextDir2(short x, short y, t_direction_glob * dir)
{
  int little, priority, tmp_priority;

  makeMap2(x, y);
  little = 65535;

  priority = 0;

  if ((wall[mypos.x][mypos.y].north == NOWALL) && ((mypos.y + 1) < MAZESIZE_Y)) {
    tmp_priority = getPriority(mypos.x, mypos.y + 1, north);
    if (steps_map[mypos.x][mypos.y + 1] < little) {
      little = steps_map[mypos.x][mypos.y + 1];
      *dir = north;
      priority = tmp_priority;
    } else if (steps_map[mypos.x][mypos.y + 1] == little) {
      if (priority < tmp_priority) {
        *dir = north;
        priority = tmp_priority;
      }
    }
  }

  if ((wall[mypos.x][mypos.y].east == NOWALL) && ((mypos.x + 1) < MAZESIZE_X)) {
    tmp_priority = getPriority(mypos.x + 1, mypos.y, east);
    if (steps_map[mypos.x + 1][mypos.y] < little) {
      little = steps_map[mypos.x + 1][mypos.y];
      *dir = east;
      priority = tmp_priority;
    } else if (steps_map[mypos.x + 1][mypos.y] == little) {
      if (priority < tmp_priority) {
        *dir = east;
        priority = tmp_priority;
      }
    }
  }

  if ((wall[mypos.x][mypos.y].south == NOWALL) && (mypos.y > 0)) {
    tmp_priority = getPriority(mypos.x, mypos.y - 1, south);
    if (steps_map[mypos.x][mypos.y - 1] < little) {
      little = steps_map[mypos.x][mypos.y - 1];
      *dir = south;
      priority = tmp_priority;
    } else if (steps_map[mypos.x][mypos.y - 1] == little) {
      if (priority < tmp_priority) {
        *dir = south;
        priority = tmp_priority;
      }
    }
  }

  if ((wall[mypos.x][mypos.y].west == NOWALL) && (mypos.x > 0)) {
    tmp_priority = getPriority(mypos.x - 1, mypos.y, west);
    if (steps_map[mypos.x - 1][mypos.y] < little) {
      little = steps_map[mypos.x - 1][mypos.y];
      *dir = west;
      priority = tmp_priority;
    } else if (steps_map[mypos.x - 1][mypos.y] == little) {
      if (priority < tmp_priority) {
        *dir = west;
        priority = tmp_priority;
      }
    }
  }

  if (steps_map[mypos.x][mypos.y] == 65535) {  //Goalにいけない
    while (1) {
      setLED(0x0a);
      delay(500);
      setLED(0x05);
      delay(500);
    }
  } else {
    switch (*dir) {
      case north:
        switch (mypos.dir) {
          case north:
            return front;
            break;
          case east:
            return left;
            break;
          case south:
            return rear;
            break;
          case west:
            return right;
            break;
        }
        break;
      case east:
        switch (mypos.dir) {
          case east:
            return front;
            break;
          case south:
            return left;
            break;
          case west:
            return rear;
            break;
          case north:
            return right;
            break;
        }
        break;
      case south:
        switch (mypos.dir) {
          case south:
            return front;
            break;
          case west:
            return left;
            break;
          case north:
            return rear;
            break;
          case east:
            return right;
            break;
        }
        break;
      case west:
        switch (mypos.dir) {
          case west:
            return front;
            break;
          case north:
            return left;
            break;
          case east:
            return rear;
            break;
          case south:
            return right;
            break;
        }
        break;
    }
  }

  return front;
}

// Creates a search map by initializing the steps_map and updating it based on
// the wall data to determine the shortest path from teh given coordinates. 
void MapManager::makeSearchMap(int x, int y)
{
  bool change_flag;

  for (int i = 0; i < MAZESIZE_X; i++) {
    for (int j = 0; j < MAZESIZE_Y; j++) {
      steps_map[i][j] = 65535;
    }
  }
  steps_map[x][y] = 0;

  do {
    change_flag = false;
    for (int i = 0; i < MAZESIZE_X; i++) {
      for (int j = 0; j < MAZESIZE_Y; j++) {
        if (steps_map[i][j] == 65535) continue;
        if (j < (MAZESIZE_Y - 1)) {
          if (wall[i][j].north != WALL) {
            if (steps_map[i][j + 1] == 65535) {
              steps_map[i][j + 1] = steps_map[i][j] + 1;
              change_flag = true;
            }
          }
        }

        if (i < (MAZESIZE_X - 1)) {
          if (wall[i][j].east != WALL) {
            if (steps_map[i + 1][j] == 65535) {
              steps_map[i + 1][j] = steps_map[i][j] + 1;
              change_flag = true;
            }
          }
        }

        if (j > 0) {
          if (wall[i][j].south != WALL) {
            if (steps_map[i][j - 1] == 65535) {
              steps_map[i][j - 1] = steps_map[i][j] + 1;
              change_flag = true;
            }
          }
        }

        if (i > 0) {
          if (wall[i][j].west != WALL) {
            if (steps_map[i - 1][j] == 65535) {
              steps_map[i - 1][j] = steps_map[i][j] + 1;
              change_flag = true;
            }
          }
        }
      }
    }
  } while (change_flag == true);
}

// Updates the step_map using a different wall condition. Initialize the steps_map
// and updates it based on the wall data to determine the shortest path. 
// Used for fast run, since it determines path based on NOWALL. 
void MapManager::makeMap2(int x, int y)
{
  bool change_flag;

  for (int i = 0; i < MAZESIZE_X; i++) {
    for (int j = 0; j < MAZESIZE_Y; j++) {
      steps_map[i][j] = 65535;
    }
  }
  steps_map[x][y] = 0;

  do {
    change_flag = false;
    for (int i = 0; i < MAZESIZE_X; i++) {
      for (int j = 0; j < MAZESIZE_Y; j++) {
        if (steps_map[i][j] == 65535) continue;
        if (j < (MAZESIZE_Y - 1)) {
          if (wall[i][j].north == NOWALL) {
            if (steps_map[i][j + 1] == 65535) {
              steps_map[i][j + 1] = steps_map[i][j] + 1;
              change_flag = true;
            }
          }
        }

        if (i < (MAZESIZE_X - 1)) {
          if (wall[i][j].east == NOWALL) {
            if (steps_map[i + 1][j] == 65535) {
              steps_map[i + 1][j] = steps_map[i][j] + 1;
              change_flag = true;
            }
          }
        }

        if (j > 0) {
          if (wall[i][j].south == NOWALL) {
            if (steps_map[i][j - 1] == 65535) {
              steps_map[i][j - 1] = steps_map[i][j] + 1;
              change_flag = true;
            }
          }
        }

        if (i > 0) {
          if (wall[i][j].west == NOWALL) {
            if (steps_map[i - 1][j] == 65535) {
              steps_map[i - 1][j] = steps_map[i][j] + 1;
              change_flag = true;
            }
          }
        }
      }
    }
  } while (change_flag == true);
}

// Make a priority for different cases of robot's direction. 
int MapManager::getPriority(unsigned char x, unsigned char y, t_direction_glob dir)
{
  int priority;

  priority = 0;

  if (mypos.dir == dir) {
    priority = 2;
  } else if (
    ((mypos.dir == north) && (dir == south)) || ((mypos.dir == east) && (dir == west)) ||
    ((mypos.dir == south) && (dir == north)) || ((mypos.dir == west) && (dir == east))) {
    priority = 0;
  } else {
    priority = 1;
  }

  if (
    (wall[x][y].north == _UNKNOWN) || (wall[x][y].east == _UNKNOWN) ||
    (wall[x][y].south == _UNKNOWN) || (wall[x][y].west == _UNKNOWN)) {
    priority += 4;
  }

  return priority;
}
