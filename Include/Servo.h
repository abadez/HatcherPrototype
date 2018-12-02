/**
 * \file Servo.h
 * \brief Header file for configuration of the servomotor.
 * \date December 2016
 * 
 */

#pragma once

#include <stdbool.h>
#include <pthread.h>
#include <wiringPi.h>
#include "hardPwm.h"
#include "Pins.h"

#define SERVO_FREQ		50		/*!< Frequency (Hz) of the servo PWM signal */
#define SERVO_LEFT		50		/*!< Duty-cycle to move servo to fully left */
#define SERVO_RIGHT		72		/*!< Duty-cycle to move servo to fully right */
#define SERVO_MIDDLE	61		/*!< Duty-cycle to move servo to the middle position */

typedef unsigned int uint;	/*!< Define for unsigned int */

typedef struct servo_struct * servo_struct;	/*!< Struct to save the servomotor status */

typedef struct servo_struct /*! Struct define to save the servomotor status */
{
	uint16_t * current;	/*!< Current angle/position */
	uint16_t new;		/*!< New angle/position */
} ss;

/** \brief Initializes the pwm functions.
    *
    * \return <b> 1 </b> Operation succeeded
    * \return <b> 0 </b> Operation failed
    */
bool initServo();

/** \brief A thread that keeps tracking of the servo current position and changes the duty-cycle to move to a new position.
    *
    * \param arg A structure of type \p servo_struct containning the new duty-cycle target position to move.
    */
void* threadServo(void* arg);

/** \brief Moves the servo to the position associated to \p position duty-cycle value, by calling the threadServo with a new argument.
    *
    * \param position The duty-cycle value of the new position
    */
void repositionServo(uint16_t position);

/** \brief Resets the servo position to a default value.
    *
    */
void resetServoPosition();

/** \brief Toggles the servo position between Right and Left.
    *
    */
void rotateServo();
