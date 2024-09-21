# micromouse_bomb
Contains micromouse specification, code, and list of items.

# Table of Contents
1. Introduction
2. Design Goals
3. Schematic diagram
4. Parts List
5. Codes

# 1. Introduction
**Micromouse** : A maze-solving robot with wall sensors and electric motor.

**Expected specification of this mouse**
- Motor: Stepping Motor (for ease of coding)
- Microcontroller: ESP32
- Wall detection: IR LED + suitable phototransistor
- Wheels: 2 wheels + sheet with smooth surface in front
- Battery: Lipo battery (12V)
- Maze-solving algorism Adachi method

**Important Regulation** 
- Mouse must fit on 18cm x 18cm unit square.
- Each run that in which the mouse successfully reaches the goal is given a run time.
- Shortest time out of all runs is considered the official record. 
- 10 minutes limit including adjusting parameters.
- No limit on the number of runs

# 2. Design Goals
Design of this mouse is referred to Beginner Mouse V2 by Micromouse Hokuriku Association. 
Website Link: [Click here](https://sites.google.com/a/itolab-ktc.com/mouse_hokuriku/basicmouse2) 
* Website in Japanese so needs Google Translation
