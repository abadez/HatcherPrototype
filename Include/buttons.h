/**
 * \file buttons.h
 * \brief Header file for configuration of buttons used in interactions with the user.
 * \date December 2016
 * 
 */

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <wiringPi.h>
#include "Pins.h"
#include "timers.h"

#define RIGHT	1			/*!< Right button system code */
#define LEFT	2			/*!< Left button system code */
#define DOWN	4			/*!< Down button system code */
#define UP		8			/*!< Up button system code */
#define BUTTON_REFRESH 200	/*!< Minimum amount of time (ms) needed to distinguish successive button interactions */

int8_t SELECT; /*!< Button Selected RIGHT: 0b0001 | LEFT: 0b0010 | DOWN: 0b0100 | UP: 0b1000 */
bool LED_STATUS; /*!< LED status on/off */
struct timeval timerButtonLed; /*!< Timer for LED button */
struct timeval timerButtonUp; /*!< Timer for up button */
struct timeval timerButtonLeft; /*!< Timer for left button */
struct timeval timerButtonRight; /*!< Timer for right button */
struct timeval timerButtonDown; /*!< Timer for down button */

/** \brief ISR for the Up button.
    *
    */
void buttonUp_fall();

/** \brief ISR for the Left button.
    *
    */
void buttonLeft_fall();

/** \brief ISR for the Right button.
    *
    */
void buttonRight_fall();

/** \brief ISR for the Down button.
    *
    */
void buttonDown_fall();

/** \brief ISR for the Led button.
    *
    */
void buttonLed_fall();

/** \brief ISR for the LedUp button.
    *
    */
void buttonLedUp_fall();

/** \brief ISR for the LedDown button.
    *
    */
void buttonLedDown_fall();

/** \brief Initializes all the buttons functionality.
    *
    * Sets all the GPIO pins used by the buttons as Inputs; 
    * Configures interruptions, so all ISR button functions will be triggered by a high-to-low transition on the corresponding inputs.
    *
    * \return <b> 1 </b> Operation succeeded
    */
bool initButtons();
