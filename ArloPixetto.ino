/*
 * AR.L.O. Pixetto
 * Based on AR.L.O. project developed by (c)2020 Giovanni Bernardo (https://www.settorezero.com)
 * 
 * This is a version of software that implement a movement of Robot based on information sendend by VIA Pixetto
 * 
 */

// Libraries for OLED display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "src/Motors.hpp"
#include <SmartSensor.h>

// Arduino used pins
#define MotorRPin   9           // signal for right servomotor
#define MotorLPin   10          // signal for left servomotor
#define P1          6           // pushbutton P1
#define P2          7           // pushbutton P2

// Inizialize Motors object
Motors ArloMotors(MotorRPin, MotorLPin);

// stuff used by oled display
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   32
#define OLED_RESET      -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Global variables
volatile long distance=0; // distance measured by sonar, cm

SmartSensor pixetto(0,1);

void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    // pushbuttons setup
    pinMode(P1,INPUT_PULLUP);
    pinMode(P2,INPUT_PULLUP);
    // Builtin led Off
    digitalWrite(LED_BUILTIN, LOW);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
    { // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
        while(1); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE,SSD1306_BLACK);
    display.setCursor(0,0);
    display.println("WAIT");
    display.display(); 

    delay(2000);
    pixetto.begin();

    // Motors setup
    ArloMotors.EnableMotors();
    ArloMotors.Alt();
}

void loop()
{
    static int x=0, y=0, w=0, h=0, centerObjectDetectedX=0, centerObjectDetectedY=0;

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("ARLO RUN");

    if(pixetto.isDetected())
    {
        digitalWrite(LED_BUILTIN, HIGH);
        
        x = pixetto.getPosX();
        y = pixetto.getPosY();
        w = pixetto.getWidth();
        h = pixetto.getHeight();

        centerObjectDetectedX = x + (w / 2);
        centerObjectDetectedY = y + (h / 2);

        display.print("X:");
        display.print(x);
        display.print(" W:");
        display.print(w);
        display.print(" CX:");
        display.println(centerObjectDetectedX);

        display.print("Y:");
        display.print(y);
        display.print(" H:");
        display.print(h);
        display.print(" CY:");
        display.println(centerObjectDetectedY);

        if(centerObjectDetectedX < 40)
        {
            // Turn left
            ArloMotors.LeftSlow();
            display.println("<<<<<<<<<<");
        }
        else if(centerObjectDetectedX > 60)
        {
            // Turn right
            ArloMotors.RightSlow();
            display.println(">>>>>>>>>>");
        }
        else
        {
            // Alt
            ArloMotors.Alt();
            display.println("----------");
        }
    }
    else
    {
        ArloMotors.Alt();
        digitalWrite(LED_BUILTIN, LOW);
        display.println("----------");
    }
    
    display.display();
}
