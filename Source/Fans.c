/**
 * \file Fans.c
 * \brief Code File for the configuration of the fans used in the system (resistor and extern fan).
 * \date December 2016
 * 
 */

#include "Fans.h"

/** \brief Initializes as outputs all the GPIO pins used to control the Heating Resistor, the Resistor Fan and the Cooling Fan.
    *
    * \return <b> 1 </b> Operation succeeded
    */
bool initFans()
{
	pinMode(PORT_HEAT, OUTPUT);
	digitalWrite(PORT_HEAT, LOW);
	
	pinMode(PORT_RESISTOR_FAN, OUTPUT);
	digitalWrite(PORT_RESISTOR_FAN, LOW);
	
	pinMode(PORT_COOL_FAN, OUTPUT);
	digitalWrite(PORT_COOL_FAN, LOW);
	
	return true;
}

/** \brief Sets the Heating Resistor GPIO pin according to \p on_off.
	* \param on_off Describes whether to turn on (1) or turn off (0) this GPIO pin
    */
void turnResistorHeat(bool on_off)
{
	if (on_off)
	{
		digitalWrite(PORT_HEAT, HIGH);
	}
	else
	{
		digitalWrite(PORT_HEAT, LOW);
	}
}

/** \brief Sets the Resistor Fan GPIO pin according to \p on_off.
	* \param on_off Describes whether to turn on (1) or turn off (0) this GPIO pin
    */
void turnResistorFan(bool on_off)
{
	if (on_off)
	{
		digitalWrite(PORT_RESISTOR_FAN, HIGH);
	}
	else
	{
		digitalWrite(PORT_RESISTOR_FAN, LOW);
	}
}

/** \brief Sets the Cooling Fan GPIO pin according to \p on_off.
	* \param on_off Describes whether to turn on (1) or turn off (0) this GPIO pin
    */
void turnCoolFan(bool on_off)
{
	if (on_off)
	{
		digitalWrite(PORT_COOL_FAN, HIGH);
	}
	else
	{
		digitalWrite(PORT_COOL_FAN, LOW);
	}
}
