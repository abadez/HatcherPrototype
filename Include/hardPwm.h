/**
* \file hardPwm.h
* \brief Header file for the configuration of hardware pwm's used in LED's and servomotor.
* \date December 2016
*/

#pragma once

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


/** \brief Check if pwm system file exists
* \param filename Name of the file
*
* \return <b> 1 </b> File exists
* \return <b> 0 </b> File does not exist
*/
bool fileExists(char* filename);

/** \brief Changes PWM frequency for PWM0
* \param freq Desired frequency forr PWM0
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm0_freq(uint16_t freq);

/** \brief Changes PWM duty cycle for PWM0
* \param duty Desired duty-cycle for PWM0
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm0_duty(uint16_t duty);

/** \brief Enables PWM0 signal
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm0_enable();

/** \brief Disables PWM0 signal
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm0_disable();

/** \brief Changes PWM frequency for PWM1
* \param freq Desired frequency forr PWM1
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm1_freq(uint16_t freq);

/** \brief Changes PWM duty cycle for PWM1
* \param duty Desired duty-cycle for PWM1
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm1_duty(uint16_t duty);

/** \brief Enables PWM1 signal
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm1_enable();

/** \brief Disables PWM1 signal
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm1_disable();
