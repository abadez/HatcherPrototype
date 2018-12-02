/**
 * \file dht11.h
 * \brief Header file for configuration of the dht11 sensor (humidity and temperature).
 * \date December 2016
 * 
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <wiringPi.h>
#include "Pins.h"

/** \brief Reads data from DHT11 sensor.
    *
    * \param temperature Where the read temperature value will be saved
    * \param humidity Where the read humidity value will be saved
    *
    * \return <b> 1 </b> Operation succeeded
    * \return <b> 0 </b> Operation failed
    */
bool dht11_read(double temperature[], double humidity[]);

/** \brief Initializes as output the GPIO pin used to communicate with the DHT11 sensor.
    *
    * \return <b> 1 </b> Operation succeeded
    */
bool dht11_init();
