/**
 * \file Humidity.c
 * \brief Code File for the configuration of the humidity LED.
 * \date December 2016
 * 
 */

#include "Humidity.h"

/** \brief Initializes as output the GPIO pin used by the Humidity LED.
    *
    * \return <b> 1 </b> Operation succeeded
    */
bool initHumidity()
{
	pinMode(PORT_HUMIDITY, OUTPUT);
	digitalWrite(PORT_HUMIDITY, LOW);
	
	return true;
}

/** \brief Sets the Humidity LED GPIO pin according to \p on_off.
	* \param on_off Describes whether to turn on (1) or turn off (0) this GPIO pin
    */
void turnHumidity(bool on_off)
{
	if (on_off)
	{
		digitalWrite(PORT_HUMIDITY, HIGH);
	}
	else
	{
		digitalWrite(PORT_HUMIDITY, LOW);
	}
}
