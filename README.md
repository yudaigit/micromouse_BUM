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
- Chassis would be made out of circuit board. 

**Important Regulation** 
- Mouse must fit on 18cm x 18cm unit square.
- Each run that in which the mouse successfully reaches the goal is given a run time.
- Shortest time out of all runs is considered the official record. 
- 10 minutes limit including adjusting parameters.
- No limit on the number of runs

# 2. Design Goals
Design of this mouse is referred to Beginner Mouse V2 by Micromouse Hokuriku Dokokai. 

Website Link: [Click here](https://sites.google.com/a/itolab-ktc.com/mouse_hokuriku/basicmouse2) 
Website in Japanese so needs Google Translation
![初心者マウス二式](https://github.com/user-attachments/assets/799a18bd-a447-4da3-8876-ff148b1ec60e)
Picture from linked website by Micromouse Hokuriku Dokokai

**Changes to be made:**
- Microcontroller changed from RX220 to ESP32S3-devkit
- IR LED and Photo-transistor changed due to item availablity in the US
- Wheels will be manufactured using CNC mills.
- Further modification expected.

# 3. Schematic Diagram
Updated Sep 21 2024
[Schematic Diagram V1.pdf](https://github.com/user-attachments/files/17085267/Schematic.Diagram.V1.pdf)
**Explanation for V1**
- Circuits around motor-driver is set.
- Circuits around power-control is set.
- Needs modification for pin configuratino around ESP32
- Needs modification for buttons.

# 4. Parts List
| Parts Name | Part Number | Website |
| Microcontroller | ESP32-S3-DEVKITC-1-N8R8 | [Link: Digikey](https://www.digikey.com/en/products/detail/espressif-systems/ESP32-S3-DEVKITC-1-N8R8/15295894?so=88713219&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGVjI7rAclhlAR_R00akBj8bqdP8uLlM8oDSYOZye-3bv9ezUbQ4VchOdj5mMELOEFJc6lgwUlzkdWoqtAFwKCPgx3IHGqwjkK5CxoQCtvj) |
| Content Cell  | Content Cell  | ------------ | 
| Content Cell  | Content Cell  | ------------ |
