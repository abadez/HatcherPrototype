/**
 * \file ir.h
 * \brief Header File for the configuration of the infrared sensor.
 * \date December 2016
 * 
 */

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <lirc_client.h>
#include "buttons.h"

/** \brief Initializes new thread to run the infrared sensor separadetly from main thread.
	*
    */
void* threadIR(void*);

/** \brief Ends the created thread.
	*
    */
bool freeIR();

/** \brief Initiates the created thread.
	*
    */
bool initIR();
