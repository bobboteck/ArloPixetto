#include "Motors.hpp"

Motors::Motors(uint8_t pinMotorRight, uint8_t pinMotorLeft)
{
    _MotorRightPin = pinMotorRight;
    _MotorLeftPin = pinMotorLeft;

    // center values used for servomotors, loaded from eeprom
    // if in the eeprom are saved values out of the range 500-2500, 1500 will be used
    // (this happens when eeprom memory was never used since contains 0xFFFF value)
    uint16_t LV = EEPROM.read(_servoL_eeprom) << 8;
    LV |= EEPROM.read(_servoL_eeprom + 1);
    uint16_t RV = EEPROM.read(_servoR_eeprom) << 8;
    RV |= EEPROM.read(_servoR_eeprom + 1);
    if (LV < 2501 && LV > 499) _servoL_center = LV;
    if (RV < 2501 && RV > 499) _servoR_center = RV;

/*    pinMode(_MotorRightPin, OUTPUT);
    digitalWrite(_MotorRightPin, LOW);
    pinMode(_MotorLeftPin, OUTPUT);
    digitalWrite(_MotorLeftPin, LOW);*/
}

Motors::~Motors()
{}

void Motors::EnableMotors()
{
    _MotorL.attach(_MotorLeftPin);
    _MotorR.attach(_MotorRightPin);
}

void Motors::Forward(uint8_t speed)
{
    uint8_t _speed=0;

    if(speed > 100)
    {
     _speed = _SpeedMax;
    }
    else
    {
        // Mapping speed with speed max 
        //_speed = speed * (_SpeedMax / 100);   //TODO: Verificare ad esempio 75 che valore ritorna
        _speed = map(speed, 0, 100, 0, 200);
    }

    _MotorL.write(_servoL_center + _speed);
    _MotorR.write(_servoR_center - _speed);
}

void Motors::Backwards(long milliSeconds)
{
    long timenow = millis();

    while((millis() - timenow) < milliSeconds)
    {
        _MotorL.write(_servoL_center - _SppedSlow);
        _MotorR.write(_servoR_center + _SppedSlow);
    }
}

void Motors::Right(long milliSeconds)
{
    long timenow = millis();

    while((millis() - timenow) < milliSeconds)
    {
        _MotorL.write(_servoL_center + _SppedSlow);
        _MotorR.write(_servoR_center + _SppedSlow);
    }
}

void Motors::RightSlow()
{
    _MotorL.write(_servoL_center + _SppedSlow);
    _MotorR.write(_servoR_center + _SppedSlow);
}

void Motors::Left(long milliSeconds)
{
    long timenow = millis();

    while((millis() - timenow) < milliSeconds)
    {
        _MotorL.write(_servoL_center - _SppedSlow);
        _MotorR.write(_servoR_center - _SppedSlow);
    }
}

void Motors::LeftSlow()
{
    _MotorL.write(_servoL_center - _SppedSlow);
    _MotorR.write(_servoR_center - _SppedSlow);
}

void Motors::Stop(long milliSeconds)
{
    long timenow=millis();

    while((millis() - timenow) < milliSeconds)
    {
        _MotorL.write(_servoL_center);
        _MotorR.write(_servoR_center);
    }
}

void Motors::Alt()
{
    //_MotorL.write(0);
    //_MotorR.write(0);
    _MotorL.write(_servoL_center);
    _MotorR.write(_servoR_center);
}