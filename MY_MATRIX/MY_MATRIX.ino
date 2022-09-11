//***************************** BLUETOOTH ************************************
/*
BUT : send a number / letter with phone by bluetooth and it will change expressions



Version 2.0 --- mise à jour le 14/07/2022

Matrices de LED used : Adafruit Small 1.2" 8x8 LED Matrix w/I2C Backpack
                            16x8 1.2" LED Matrix + Backpack
Fonctionnalities : multi expressions
                   sleep() mode
                   bluetooth communications
                   confirms the expression by sending a number/letter to the phone
                   

download libraries: Tools -> Manage libraries



Wiring cables :
    - for LED matrix :
        5V / GND / SCL / SDA
    - for little fan :
        3.3V / GND
    - for bluetooth HC-05 (code 1234 ou 0000 for the first connection with the phone)
        IOREF(it's like 5V) / GND / 2pin (here 2 and 6)    

Connected bluetooth with the phone
Send two time the same number / letter (first to wake up the card the second to give instruction)
-> example: 11 instead of 1

-> don't send instruction while other aren't finish (for B et C)
-> informations are send to your phone to know what append

-> if there is bug: use the reset button of the Arduino card



-> Free to use code 
© ◊Frythdragon◊
*/


//***************************** INCLUDE ************************************
#include <Wire.h> // matrix LED
#include <Adafruit_GFX.h> // matrix LED
#include "Adafruit_LEDBackpack.h" // matrix LED

#include <SoftwareSerial.h> // bluetooth
#include "Drawing.h"  // file for expressions
#include <avr/sleep.h>  // sleep() mode


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
SoftwareSerial bluetooth(2, 6); // (TX, RX)

int count = 0;
char telToOrdi = 'x'; //leave

// for sleep
int nbTurn = 0;


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

  // Bluetooth communication
  bluetooth.begin(9600);
  bluetooth.println("START");

  sleepPwrDown();
}//



//************************* EN BOUCLE ****************************************
void loop()
/*
  (start line   ,    start row   ,      thing to do       ,   nb of line  ,   nb of row  ,   LED_ON)
  (     0       ,      0         ,    name in Drawing.h   ,     8         ,    16        ,   LED_ON)
*/
{
  // communication in double => 11
  
  // communication
  if (bluetooth.available()) {  // if communication from phone to card
    telToOrdi = bluetooth.read();
  }

  // communications are in char so let '' in == test
  if (telToOrdi == '1') {
    bluetooth.println("1"); // confirmation send to the phone
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_1, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_1, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_1, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_1, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_1, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_1, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_1, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_1, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
  }
  else if (telToOrdi == '2') {
    bluetooth.println("2");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_2, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_2, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_2, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_2, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_2, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_2, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_2, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_2, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
  }
  else if (telToOrdi == '3') {
    bluetooth.println("3");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_3, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_3, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_3, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_3, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_3, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_3, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_3, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_3, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
  }
  else if (telToOrdi == '4') {
    bluetooth.println("4");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_4, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_4, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_4, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_4, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_4, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_4, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_4, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_4, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
  }
  else if (telToOrdi == '5') {
    bluetooth.println("5");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_5, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_5, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_5, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_5, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_5, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_5, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_5, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_5, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
  }
  else if (telToOrdi == '6') {
    bluetooth.println("6");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_6, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_6, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_6, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_6, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_6, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_6, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_6, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_6, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
  }
  else if (telToOrdi == '7') {
    bluetooth.println("7");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_7, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_7, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_7, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_7, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_7, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_7, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_7, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_7, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
  }
  else if (telToOrdi == '8') {
    bluetooth.println("8");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_8, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_8, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_8, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_8, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_8, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_8, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_8, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_8, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
  }
  else if (telToOrdi == '9') {
    bluetooth.println("9");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_9, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_9, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_9, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_9, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_9, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_9, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_9, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_9, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
  }
  else if (telToOrdi == 'A') {
    bluetooth.println("A - BASE");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_A, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_A, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_A, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_A, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_A, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_A, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_A, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_A, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
  }
  else if (telToOrdi == 'B') {
    bluetooth.println("B - FADE EYE");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_B, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_B, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_B_1, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_B_1, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_B, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_B, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_B, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_B, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
    delay(750);
    matrix[ER].clear();
    matrix[EL].clear();
    matrix[ER].drawBitmap(0, 0, eye_B_2, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_B_2, 8, 16, LED_ON);
    matrix[ER].writeDisplay();
    matrix[EL].writeDisplay();
    delay(750);
    matrix[ER].clear();
    matrix[EL].clear();
    matrix[ER].drawBitmap(0, 0, eye_B_3, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_B_3, 8, 16, LED_ON);
    matrix[ER].writeDisplay();
    matrix[EL].writeDisplay();
    delay(750);
    matrix[ER].clear();
    matrix[EL].clear();
    matrix[ER].drawBitmap(0, 0, eye_B_4, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_B_4, 8, 16, LED_ON);
    matrix[ER].writeDisplay();
    matrix[EL].writeDisplay();
    delay(750);
    matrix[ER].clear();
    matrix[EL].clear();
    matrix[ER].drawBitmap(0, 0, eye_B_5, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_B_5, 8, 16, LED_ON);
    matrix[ER].writeDisplay();
    matrix[EL].writeDisplay();
    delay(750);
    matrix[ER].clear();
    matrix[EL].clear();
    matrix[ER].drawBitmap(0, 0, eye_B_6, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_B_6, 8, 16, LED_ON);
    matrix[ER].writeDisplay();
    matrix[EL].writeDisplay();
    delay(750);
    matrix[ER].clear();
    matrix[EL].clear();
    matrix[ER].drawBitmap(0, 0, eye_right_B_7, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_B_7, 8, 16, LED_ON);
    matrix[ER].writeDisplay();
    matrix[EL].writeDisplay();
    delay(1500);
    matrix[ER].clear();
    matrix[EL].clear();
    matrix[ER].drawBitmap(0, 0, eye_B_1, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_B_1, 8, 16, LED_ON);
    matrix[ER].writeDisplay();
    matrix[EL].writeDisplay();
  }
  else if (telToOrdi == 'C') {
    bluetooth.println("C - CRUNCH");
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].clear();
    }
    matrix[NR].drawBitmap(0, 0, nose_right_C, 8, 16, LED_ON);
    matrix[NL].drawBitmap(0, 0, nose_left_C, 8, 16, LED_ON);
    matrix[ER].drawBitmap(0, 0, eye_right_C, 8, 16, LED_ON);
    matrix[EL].drawBitmap(0, 0, eye_left_C, 8, 16, LED_ON);
    matrix[MR1].drawBitmap(0, 0, mouth_right1_C_1, 8, 16, LED_ON);
    matrix[MR2].drawBitmap(0, 0, mouth_right2_C_1, 8, 16, LED_ON);
    matrix[ML1].drawBitmap(0, 0, mouth_left1_C_1, 8, 16, LED_ON);
    matrix[ML2].drawBitmap(0, 0, mouth_left2_C_1, 8, 16, LED_ON);
    for (uint8_t i = 0; i < 8; i++) {
      matrix[i].writeDisplay();
    }
    for (count = 0 ; count < 3 ; count++) {
      delay(500);
      for (uint8_t i = 4; i < 8; i++) {
        matrix[i].clear();
      }
      matrix[MR1].drawBitmap(0, 0, mouth_right1_C_2, 8, 16, LED_ON);
      matrix[MR2].drawBitmap(0, 0, mouth_right2_C_2, 8, 16, LED_ON);
      matrix[ML1].drawBitmap(0, 0, mouth_left1_C_2, 8, 16, LED_ON);
      matrix[ML2].drawBitmap(0, 0, mouth_left2_C_2, 8, 16, LED_ON);
      for (uint8_t i = 4; i < 8; i++) {
        matrix[i].writeDisplay();
      }
      delay(500);
      for (uint8_t i = 4; i < 8; i++) {
        matrix[i].clear();
      }
      matrix[MR1].drawBitmap(0, 0, mouth_right1_C_3, 8, 16, LED_ON);
      matrix[MR2].drawBitmap(0, 0, mouth_right2_C_3, 8, 16, LED_ON);
      matrix[ML1].drawBitmap(0, 0, mouth_left1_C_3, 8, 16, LED_ON);
      matrix[ML2].drawBitmap(0, 0, mouth_left2_C_3, 8, 16, LED_ON);
      for (uint8_t i = 4; i < 8; i++) {
        matrix[i].writeDisplay();
      }
      delay(500);
      for (uint8_t i = 4; i < 8; i++) {
        matrix[i].clear();
      }
      matrix[MR1].drawBitmap(0, 0, mouth_right1_C_1, 8, 16, LED_ON);
      matrix[MR2].drawBitmap(0, 0, mouth_right2_C_1, 8, 16, LED_ON);
      matrix[ML1].drawBitmap(0, 0, mouth_left1_C_1, 8, 16, LED_ON);
      matrix[ML2].drawBitmap(0, 0, mouth_left2_C_1, 8, 16, LED_ON);
      for (uint8_t i = 4; i < 8; i++) {
        matrix[i].writeDisplay();
      }
    }
  }

  
  bluetooth.println("turn");
  // it make 2 turn I don't know why (let it like that)

  // so sleep if 2 turn
  // if there is a fail communication it come back to sleep()
  nbTurn++;
  if (nbTurn > 1){
      sleepPwrDown();
      nbTurn = 0;
  }


}



// first communication to wake it up => 11 instead of 1
void wakeCallback() {}
void sleepPwrDown() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(2, wakeCallback, CHANGE); //2 = pin to wake up (pin TX)
  sleep_mode();
  sleep_disable();
}
