/**
 * \file LumSensor.h
 * \brief Header file for the control of the luminosity sensor.
 * \date December 2016
 * 
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include "hardPwm.h"
#include "Pins.h"
#include "timers.h"

#define LUM_DELTA 10			/*!< Maximum delta allowed to luminosity target value */
#define LUM_BASE_REFERENCE 110	/*!< Luminosity target value, read by the ADC */

typedef unsigned int uint;	/*!< Define for unsigned int */

typedef struct lum_struct * lum_struct;	/*!< Struct to save luminosity status */
typedef struct lum_struct /*! Struct define to save luminosity status */
{
	uint16_t * lumens; /*!< Sensor read */
	uint16_t * luminosity; /*!< Power of the LEDS */
	bool * LED_STATUS; /*!< LED's on/off */
} ls;

/** \brief Initializes the lum_struct structure.
	*
    */
bool initLumSensor(uint16_t * lumens, uint16_t * luminosity, bool * LED_STATUS);

/** \brief Reads the luminosity sensor.
	*
    */
uint16_t readLumSensor();

/** \brief Initializes a separate thread for the reading of the sensor.
	*
    */
void* threadLum(void * arg);
