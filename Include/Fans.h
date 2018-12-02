/**
 * \file Fans.h
 * \brief Header File for the configuration of the fans used in the system (resistor and extern fan).
 * \date December 2016
 * 
 */

#pragma once

#include <stdbool.h>
#include "wiringPi.h"
#include "Pins.h"

/** \brief Initializes as outputs all the GPIO pins used to control the Heating Resistor, the Resistor Fan and the Cooling Fan.
    *
    * \return <b> 1 </b> Operation succeeded
    */
bool initFans();

/** \brief Sets the Heating Resistor GPIO pin according to \p on_off.
	* \param on_off Describes whether to turn on (1) or turn off (0) this GPIO pin
    */
void turnResistorHeat(bool on_off);

/** \brief Sets the Resistor Fan GPIO pin according to \p on_off.
	* \param on_off Describes whether to turn on (1) or turn off (0) this GPIO pin
    */
void turnResistorFan(bool on_off);

/** \brief Sets the Cooling Fan GPIO pin according to \p on_off.
	* \param on_off Describes whether to turn on (1) or turn off (0) this GPIO pin
    */
void turnCoolFan(bool on_off);
