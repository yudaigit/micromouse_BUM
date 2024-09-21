# Micromouse "BUM"
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
Regulation found here [2024 IEEE MIT Micromouse Guideline.pdf](https://github.com/user-attachments/files/17085412/2024.IEEE.MIT.Micromouse.Guideline.pdf)

![Micromouse_maze](https://github.com/user-attachments/assets/13d8e27c-e055-4e7b-ac1e-0cdf1fed27a1)
Picture from Wikipedia [Link](https://en.wikipedia.org/wiki/Micromouse)

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
- Circuit around motor-driver is set.
- Circuit around power-control is set.
- Needs modification for pin configuratino around ESP32
- Needs modification for buttons.

# 4. Parts List
| Parts Name | Part Number | Website | Explanation |
| ---------- | ----------- | ------- | ----------- |
| Microcontroller | ESP32-S3-DEVKITC-1-N8R8 | [Link: Digikey](https://www.digikey.com/en/products/detail/espressif-systems/ESP32-S3-DEVKITC-1-N8R8/15295894?so=88713219&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGVjI7rAclhlAR_R00akBj8bqdP8uLlM8oDSYOZye-3bv9ezUbQ4VchOdj5mMELOEFJc6lgwUlzkdWoqtAFwKCPgx3IHGqwjkK5CxoQCtvj) | Devkit includes USB-UART bridge, Reset/Boot-mode bottons, LDO regulator, micro-USB connector. |
| Motor Driver  | A3982SLBTR-T | [Link: Digikey](https://www.digikey.com/en/products/detail/allegro-microsystems/A3982SLBTR-T/1006337?so=88713219&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGVjI7rAXo1NKZFh-lfgPb5J_lPGqp54pRkpawmU758xRtKlHEaEAZEIfTsmPXZYi-8XfwW9QOW9wnnimUpZHAQ6QVG9tBGOJKe-bg7pqzY) | Output drive capacity of up to 35 V and ±2 A |
| Transistor Array  | TBD62083AFNG,EL  | [Link: Digikey](https://www.digikey.com/en/products/detail/toshiba-semiconductor-and-storage/TBD62083AFNG-EL/5514101?so=88713219&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGVjI7rASWC-GBVGhXV-_J2TC-AzhnJu9-OEVNVk5YSU11mHZzysy7OMH7-JYZRrl2jqi5ujeSUjEmdH1xTrglv5ZYsNYvOeUH_rRTn88Kt) |
| IR LED | SFH 4545 | [Link: Digikey](https://www.digikey.com/en/products/detail/ams-osram-usa-inc/SFH-4545/2205955?so=88714059&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGVjRuHY0UsPo8PqHZpcf0OJ5lFMERFDRTdYCMr3sMDzpaXmtWfPRvpUV_ZyHRayo5sOlhpeXiFwpQmKslB2cN6vLcBioWK0pLHrexKfSO7) | Peak Wavelength of 950nm. |
| Phototransistor | TEFT4300 | [Link: Digikey](https://www.digikey.com/en/products/detail/vishay-semiconductor-opto-division/TEFT4300/1681175?so=88714059&content=productdetail_US&mkt_tok=MDI4LVNYSy01MDcAAAGVjRuHY_XwD63POgCk77Uz4CcDU6UOm_5Ec3PsV4QUbsIlVZEZImGF-MNmtf094ZbBvAZZl5DjMfcmu5q6gha0bCU4jfj_RwPxrJv7J39u) | Full performance at wavelength of 940nm |
| Motor | PKP213D05A | [Link: MISUMI](https://us.misumi-ec.com/vona2/detail/221004949472/?HissuCode=PKP213D05A) | Rated Voltage of 4.25V and rated current of 0.5A |
| Regulator | NJM2845DL1-05 | [Link: MOUSER](https://www.mouser.com/ProductDetail/Nisshinbo/NJM2845DL1-05-TE1?qs=Vf9KeiGtj%252BGbfCGSGlajaA%3D%3D&countryCode=US&currencyCode=USD) | Converts 12V to 5V |
| Regulator | NJM2845DL1-33 | [Link: MOUSER](https://www.mouser.com/ProductDetail/Nisshinbo/NJM2845DL1-33-TE1?qs=Vf9KeiGtj%252BHsxdmME1E7bA%3D%3D&countryCode=US&currencyCode=USD) | Converts 5V to 3.3V |
| Variable Resistor | 3362P-1-103LF | [Link: MOUSER](https://www.mouser.com/ProductDetail/Bourns/3362P-1-103LF?qs=tS7CBNq%252BQ07BavGNEQud%252BA%3D%3D&countryCode=US&currencyCode=USD) |

# 5. Codes
Codes were taken and based on Pi:Co V2 Micromouse developed by RT.corp.
Github repo for Pi:Co V2 is found here. [Link](https://github.com/rt-net/pico_v2_arduino_examples)

Explanation of code V1:
- Codes are mostly similar to the one made for Pi:Co V2.
- Some codes were added for better performance, including slalom, hardware correction and wall-cut correction.
- Instead of pushing the button to start, it starts when you wipe a hand in front of the wall-sensor.
- All values were taken for half-size micromouse. For this competition, they must be changed.
