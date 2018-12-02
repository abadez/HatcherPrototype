/*! \mainpage 
* \brief This is the project code documentation for the Embedded Systems Programming class 
* final project which is used for the incubation process of the incubator that was designed and built
* during the semester
*
* \author Pedro Abade nº 59385
* \author André Temprilho nº 64177
* \author Cláudio Patrício nº 73284
* \author Ricardo Gonçalves nº 76001
*
* \date January 2017
*
*/

/**
 * \file main.h
 * \brief Header file for configuration of the servomotor.
 * \date December 2016
 * 
 */

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <signal.h>
#include <inttypes.h>
#include <wiringPi.h>
#include "hardPwm.h"
#include "buttons.h"
#include "display.h"
#include "ir.h"
#include "dht11.h"
#include "Servo.h"
#include "LumSensor.h"
#include "Fans.h"
#include "Humidity.h"
#include "Profiles.h"
#include "timers.h"

#define TIMER_DISPLAY_CONFIRM 5000			/*!< Time (in milliseconds) for the user to confirm an operation after being asked */
#define TIMER_DISPLAY_REFRESH 50			/*!< Display refresh period (in milliseconds) */

struct Profile customPerfil;				/*!< Struct define to temporarily save a custom profile */
uint16_t lumens;							/*!< Variable to save current light sensor value */
uint16_t luminosity;						/*!< Variable to save current LED light intensity */

typedef unsigned int uint;

/** \brief Show hatch erros.
 *
 */
void hatch_error();

/** \brief Main loop function to hatch.
 *
 */
bool hatch();

/** \brief Confirm hatch menu.
 *
 */
bool hatch_confirm();

/** \brief Main loop to run the incubator.
 *
 */
void run();

//void startMenu();

/** \brief Select Option Values menu to be customized.
 *
 * \param opt The option (temperature, humidity or days) to customize
 */
void setOptionMenu(uint8_t opt);

/** \brief Select Option menu.
 *
 */
void OptionMenu();

/** \brief Select Profile menu.
 *
 */
void setPerfilMenu();

/** \brief Start system, initiate components and show Main menu.
 *
 */
void mainMenu();

/** \brief System shutdown, free threads and turn off components.
 *
 */
void sig_handler(int signo);
int main();
