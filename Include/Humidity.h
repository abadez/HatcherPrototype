/**
 * \file Humidity.h
 * \brief Header File for the configuration of the humidity LED.
 * \date December 2016
 * 
 */

#pragma once

#include <stdbool.h>
#include "wiringPi.h"
#include "Pins.h"

#define HUM_DELTA 5 /*!< Maximum delta allowed to humidity target value */

/** \brief Initializes as output the GPIO pin used by the Humidity LED.
    *
    * \return <b> 1 </b> Operation succeeded
    */
bool initHumidity();

/** \brief Sets the Humidity LED GPIO pin according to \p on_off.
	* \param on_off Describes whether to turn on (1) or turn off (0) this GPIO pin
    */
void turnHumidity(bool on_off);
