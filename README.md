# ProtogenVisorCode
Free Protogen Visor Code with bluetooth (or not) for adafruit 8x8 and 8x16 matrix LED


## Table of contents
1. Introduction
2. How to use
3. What in each folder
4. Wiring
5. Issues
6. License


## Introduction
I use Arduino UNO card and a bluetooth module HC-05 (not needed if you don't want to change expressions with your phone).
I use two 8x8 matrix for the nose, two 8x16  the eyes and four 8x16 for the mouth.

There id good tutorials on Adafruit if you want to know how to soldering.
https://learn.adafruit.com/adafruit-led-backpack/1-2-8x8-matrix-assembly

Don't forgot to give them a number by soldering the A0-A1-A2

I know the code is not perfect but it work and I tried to make it easy.


## How to use :
In each folder you will find documents. One is the main code, the other is to make the expressions.
Put them in Arduino.
Download libraries. You can find them in Tools -> manage libraries
Then upload it in your Arduino card.

If your matrix doesn't have the same number (A0-A1-A2) you can change it at the begging of the code.
If your matrix aren't in same sens as mine, you can change the expressions in the document. 1 mean LED on 0 mean LED off.

If you use bluetooth, the card is in sleep mode so you need to wake it up before give it an instruction. For that, just put the same number two time. Instead of send 1 send 11.


## What in each folder

#### in MY_MATRIX 
You will find a code to change the expressions by using bluetooth module (HC-05) and your phone.
The application that I use is Bluetooth Terminal HC-05. You can find it in Playstore and Appstore.
The card is in sleep mode, the pin to wake it up is the same as the TX (2 in the code), so if you don't use this pin change the number in the sleep function at the end of the code.

#### in MY_MATRIX_BASE 
you will find a code to only have one expression and no change.

#### in MY_MATRIX_BASE_BLINK
you will find a code with only one expression with a blinking animation. You can choose your delay for the animation.


## Issues
If there is issue you can push the reset button on the Arduino card

Normally there is no issue with MY_MATRIX_BASE and MY_MATRIX_BASE_BLINK.

With MY_MATRIX there is instruction that will appear on your phone. Like that you will be able to know wich expression is actually visible.
For expression that make a loop (B and C in the code) wait until the end of the turn to give an other instruction. Otherwise the next instruction will be offset. (push the reset button on the Arduino card to restart)


## Wiring
For the LED matrix solder cables to have only of each at the end
VCC -> 5V
GND -> GND
SCL -> SCL
SDA -> SDA

For the bluetooth HC-05
VCC -> IOREF (it make 5V like the 5V pin)
GND -> GND
TX -> pin 2 (you can change it in the code)
RX -> pin 6 (you can change it in the code)

If you use a little fan you can put it on 3.3V and there is a last GND


## License
It's free,
I hope it help you,
If you think my code is nice thanks to credit.
Have fun :)


◊Frythdragon◊

https://drive.google.com/drive/folders/1atYqXofQmKWQx3DvoGH-8TVNVVNZd75p?usp=sharing
