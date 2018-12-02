/**
 * \file display.h
 * \brief Header file for condiguration of the LCD 16x2 display.
 * \date December 2016
 * 
 */

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>
#include "Pins.h"

/** \brief Updates the messages printed on the LCD
    *
    * \param line1 Message to be printed on the 1st LCD line
    * \param line2 Message to be printed on the 2nd LCD line
    */
void updateDisplay(unsigned char line1[], unsigned char line2[]);

/** \brief Initializes the LCD, printing a default message.
    *
    * \return <b> 1 </b> Operation succeeded
    * \return <b> 0 </b> Operation failed
    */
bool initDisplay();
