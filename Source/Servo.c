/**
 * \file Servo.c
 * \brief Code file for configuration of the servomotor.
 * \date December 2016
 * 
 */

#include "Servo.h"

uint16_t SERVO_DUTY = SERVO_LEFT;	/*!< Servomotor initial position */
pthread_mutex_t SERVO_MUTEX;	/*!< Thread for control the servomotor */

/** \brief Initializes the pwm functions.
    *
    * \return <b> 1 </b> Operation succeeded
    * \return <b> 0 </b> Operation failed
    */
bool initServo()
{	
	bool init = pwm0_freq(SERVO_FREQ);
	if(init == false)
	{
		return false;
	}
	init = pwm0_duty(SERVO_DUTY);
	if(init == false)
	{
		return false;
	}
	init = pwm0_enable();
	if(init == false)
	{
		return false;
	}
	if(pthread_mutex_init(&SERVO_MUTEX, NULL) != 0)
	{
		return false;
	}
		
	return true;
}

/** \brief A thread that keeps tracking of the servo current position and changes the duty-cycle to move to a new position.
    *
    * \param arg A structure of type \p servo_struct containning the new duty-cycle target position to move.
    */
void* threadServo(void* arg)
{
	ss* args = arg;
	uint16_t current = *args->current;
	
	uint16_t new = args->new;
	if(new > current)
	{
		while(current < (new - 1))
		{
			if(current > SERVO_RIGHT)
			{
				return 0;
			}
			current++;
			(bool) pwm0_duty(current);
			delay(100);
		}
		current++;
		(bool) pwm0_duty(current);
	}
	else if(new < current)
	{
		while(current > (new + 1))
		{
			if(current < SERVO_LEFT)
			{
				return 0;
			}
			current--;
			(bool) pwm0_duty(current);
			delay(100);
		}
		current--;
		(bool) pwm0_duty(current);
	}
	*args->current = current;
	return 0;
}

/** \brief Moves the servo to the position associated to \p position duty-cycle value, by calling the threadServo with a new argument.
    *
    * \param position The duty-cycle value of the new position
    */
void repositionServo(uint16_t position)
{
	if(position != SERVO_DUTY)
	{
		pthread_t rotateThread;
		servo_struct aux = (servo_struct)malloc(sizeof(servo_struct));
		aux->current = &SERVO_DUTY;
		aux->new = position;
		if(pthread_create(&rotateThread, NULL, threadServo, (void*) aux))
		{
			return;
		}
	}
}

/** \brief Resets the servo position to a default value.
    *
    */
void resetServoPosition()
{
	if(SERVO_DUTY <= SERVO_MIDDLE)
	{
		repositionServo(SERVO_LEFT);
	}
	else
	{
		repositionServo(SERVO_RIGHT);
	}
}

/** \brief Toggles the servo position between Right and Left.
    *
    */
void rotateServo()
{
	if(SERVO_DUTY == SERVO_LEFT)
	{
		repositionServo(SERVO_RIGHT);
	}
	else
	{
		repositionServo(SERVO_LEFT);
	}
}
