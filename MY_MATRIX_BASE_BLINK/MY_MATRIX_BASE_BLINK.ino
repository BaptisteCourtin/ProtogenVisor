//***************************** BLUETOOTH ************************************
/*
Version 1.0 --- mise à jour le 14/07/2022

Matrices de LED used : Adafruit Small 1.2" 8x8 LED Matrix w/I2C Backpack
                            16x8 1.2" LED Matrix + Backpack
Fonctionnalities : only one expressions
                   blink animation                

download libraries: Tools -> Manage libraries



Wiring cables :
    - for LED matrix :
        5V / GND / SCL / SDA
    - for little fan :
        3.3V / GND


-> Free to use code 
© ◊Frythdragon◊
*/


//***************************** INCLUDE ************************************
#include <Wire.h> // matrix LED
#include <Adafruit_GFX.h> // matrix LED
#include "Adafruit_LEDBackpack.h" // matrix LED

#include "Drawing.h"  // file for expressions


//***************************** DECLARATIONS NOMS ET NUMEROS DES MATRICES ************************************
// name of matrix
// name is NR, number is the one from A0-A1-A2 that you solder
#define NR      0     // NR = 0
#define NL      1
#define ER      2
#define EL      3
#define MR1     4
#define MR2     5
#define ML1     6
#define ML2     7

// declaration
Adafruit_8x16matrix matrix[8];  //[nb of matrix => 8 matrix in total]


//************************* VARIABLES ****************************************
// blink
// you can change these number to blink faster or slower
const unsigned long blinkInterval = 4500;
const unsigned long blinkSpeedInterval = 25;
int eachStep;


//************************* DRAWING ****************************************
// in file Drawing
// include before with #include "Drawing.h"


//************************* SETUP DE BASE ****************************************
void setup()
{
  // initialisation
  for (uint8_t i = 0; i < 8; i++) // nb matrix = 8
  {
    matrix[i].begin(0x70 + i);  // matrix[0] have the number 0x70 - because it's like that
    matrix[i].clear();  // clear
  }
  // base drawing
  matrix[NR].drawBitmap(0, 0, nose_right_A, 8, 16, LED_ON);
  matrix[NL].drawBitmap(0, 0, nose_left_A, 8, 16, LED_ON);
  matrix[ER].drawBitmap(0, 0, eye_right_A, 8, 16, LED_ON);
  matrix[EL].drawBitmap(0, 0, eye_left_A, 8, 16, LED_ON);
  matrix[MR1].drawBitmap(0, 0, mouth_right1_A, 8, 16, LED_ON);
  matrix[MR2].drawBitmap(0, 0, mouth_right2_A, 8, 16, LED_ON);
  matrix[ML1].drawBitmap(0, 0, mouth_left1_A, 8, 16, LED_ON);
  matrix[ML2].drawBitmap(0, 0, mouth_left2_A, 8, 16, LED_ON);
  for (uint8_t i = 0; i < 8; i++)
  {
    matrix[i].writeDisplay(); //matrix on 
  }

}


//************************* EN BOUCLE ****************************************
void loop() {
  
  delay(blinkInterval);
  Blink();

}


void Blink() {
  eachStep = 0;
  while (eachStep < 13) {
    delay(blinkSpeedInterval);
    if (eachStep < 7) {
      eachStep++;
      matrix[ER].clear();
      matrix[EL].clear();
      matrix[ER].drawBitmap((-eachStep+1), 0, eye_right_A, 8, 16, LED_ON);
      matrix[EL].drawBitmap((eachStep-1), 0, eye_left_A, 8, 16, LED_ON);
      matrix[ER].writeDisplay();
      matrix[EL].writeDisplay();
    }
    else if (eachStep < 13) {
      eachStep++;
      matrix[ER].clear();
      matrix[EL].clear();
      matrix[ER].drawBitmap((-13+eachStep), 0, eye_right_A, 8, 16, LED_ON);
      matrix[EL].drawBitmap((13-eachStep), 0, eye_left_A, 8, 16, LED_ON);
      matrix[ER].writeDisplay();
      matrix[EL].writeDisplay();
    }
  }
}
