#ifndef Motors_H
#define Motors_H

#include <Arduino.h>
// Library for using servo on Timer 2 (https://github.com/nabontra/ServoTimer2)
#include <ServoTimer2.h>
// Library for Arduino internal eeprom memory
#include <EEPROM.h>

class Motors
{
private:
    static const uint16_t _SpeedMax = 200;	// Normal speed for forward moving (center point+speed microseconds)
    static const uint16_t _SppedSlow = 50;	// Speed used for maneuvers

    ServoTimer2 _MotorL;            // Left servomotor object
    ServoTimer2 _MotorR;            // Right servomotor object

    uint8_t _MotorRightPin;				// Pin for Right servomotor
    uint8_t _MotorLeftPin;				// Pin for Left servomotor
    uint16_t _servoL_center = 1500; // Default value for left servomotor center point
    uint16_t _servoR_center = 1500; // Default value for right servomotor center point
    uint8_t _servoL_eeprom = 0;     // Eeprom memory location for storing point zero of left servomotor
    uint8_t _servoR_eeprom = 2;     // Eeprom memory location for storing point zero of right servomotor

public:
    /**
     * Define the pin used to drive motors and read the "zero spped" from the Arduino EEPROM
     * 
     * @param pinMotorRight The pin connected to the Right Motor
     * @param pinMotorLeft The pin connected to the Left Motor
     */
    Motors(uint8_t pinMotorRight, uint8_t pinMotorLeft);

    ~Motors();

    /**
     * Attach the Servo Motors to the correspondend Arduino PIN
     */
    void EnableMotors();

    /**
     * Move the Robot forward at speed indicated
     * 
     * @param speed The speed of motors in percentage (0-100)
     */
    void Forward(uint8_t speed);

    /**
     * Move the Robot backwards for a ms milliseconds
     * 
     * @param milliSeconds The number of milliseconds
     */
    void Backwards(long milliSeconds);

    /**
     * Turns the Robot right at slow speed for ms milliseconds
     * 
     * @param ms The number of milliseconds
     */
    void Right(long ms);

    /**
     * Turns the Robot right at slow speed until the next motor command
     */
    void RightSlow();

    /**
     * Turns the Robot left at slow speed for ms milliseconds
     * 
     * @param ms The number of milliseconds
     */
    void Left(long ms);

    /**
     * Turns the Robot left at slow speed until the next motor command
     */
    void LeftSlow();

    /**
     * Stop the Robot for ms milliseconds
     * 
     * @param milliSeconds The number of milliseconds to wait
     */
    void Stop(long milliSeconds);

    /**
     * Stop the Robot indefinitively
     */
    void Alt();
};

#endif