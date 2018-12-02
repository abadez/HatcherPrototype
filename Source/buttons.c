/**
 * \file buttons.c
 * \brief Code file for configuration of buttons used in interactions with the user.
 * \date December 2016
 * 
 */

#include "buttons.h"

/** \brief ISR for the Up button.
 *
 */
void buttonUp_fall()
{
	struct timeval timerCur;
	gettimeofday(&timerCur, NULL);
	if(tmillis(timerCur, timerButtonUp) > BUTTON_REFRESH)
	{
		SELECT = UP;
		gettimeofday(&timerButtonUp, NULL);
	}
}

/*void buttonUp_fall()
{
	SELECT = UP;
}*/

/** \brief ISR for the Left button.
    *
    */
void buttonLeft_fall()
{
	struct timeval timerCur;
	gettimeofday(&timerCur, NULL);
	if(tmillis(timerCur, timerButtonLeft) > BUTTON_REFRESH)
	{
		SELECT = LEFT;
		gettimeofday(&timerButtonLeft, NULL);
	}
}

/*void buttonLeft()
{
	SELECT = LEFT;
}*/

/** \brief ISR for the Right button.
    *
    */
void buttonRight_fall()
{
	struct timeval timerCur;
	gettimeofday(&timerCur, NULL);
	if(tmillis(timerCur, timerButtonRight) > BUTTON_REFRESH)
	{
		SELECT = RIGHT;
		gettimeofday(&timerButtonRight, NULL);
	}
}

/*void buttonRight_fall()
{
	SELECT = RIGHT;
}*/

/** \brief ISR for the Down button.
    *
    */
void buttonDown_fall()
{
	struct timeval timerCur;
	gettimeofday(&timerCur, NULL);
	if(tmillis(timerCur, timerButtonDown) > BUTTON_REFRESH)
	{
		SELECT = DOWN;
		gettimeofday(&timerButtonDown, NULL);
	}
}

/** \brief ISR for the Led button.
    *
    */
void buttonLed_fall()
{
	struct timeval timerCur;
	gettimeofday(&timerCur, NULL);
	//printf("LED\n");
	if(tmillis(timerCur, timerButtonLed) > BUTTON_REFRESH)
	{
		LED_STATUS = !LED_STATUS;
		gettimeofday(&timerButtonLed, NULL);
		/*if(LED_STATUS == true)
		{
			printf("LED 1\n");
		}
		else
		{
			printf("LED 0\n");
		}*/
	}
}

/** \brief ISR for the LedUp button.
    *
    */
void buttonLedUp_fall()
{
	/*if(lumens_reference < 1023)
	{
		lumens_reference++;
	}*/
}

/** \brief ISR for the LedDown button.
    *
    */
void buttonLedDown_fall()
{
	/*if(lumens_reference > 0)
	{
		lumens_reference--;
	}*/
}

/** \brief Initializes all the buttons functionality.
    *
    * Sets all the GPIO pins used by the buttons as Inputs; 
    * Configures interruptions, so all ISR button functions will be triggered by a high-to-low transition on the corresponding inputs.
    *
    * \return <b> 1 </b> Operation succeeded
    */
bool initButtons()
{
	// Button UP Fall
	pinMode(PORT_BUTTON_UP, INPUT);
	pullUpDnControl(PORT_BUTTON_UP, PUD_DOWN);
	gettimeofday(&timerButtonUp, NULL);
	if(wiringPiISR(PORT_BUTTON_UP, INT_EDGE_FALLING, &buttonUp_fall) < 0)
	{
		fprintf(stderr, "%s : Init Button UP Fall failed!\n", __func__);
		exit(EXIT_FAILURE);
	}
	
	// Button LEFT Fall
	pinMode(PORT_BUTTON_LEFT, INPUT);
	pullUpDnControl(PORT_BUTTON_LEFT, PUD_DOWN);
	gettimeofday(&timerButtonLeft, NULL);
	if(wiringPiISR(PORT_BUTTON_LEFT, INT_EDGE_FALLING, &buttonLeft_fall) < 0)
	{
		fprintf(stderr, "%s : Init Button LEFT Fall failed!\n", __func__);
		exit(EXIT_FAILURE);
	}
	
	// Button RIGHT Fall
	pinMode(PORT_BUTTON_RIGHT, INPUT);
	pullUpDnControl(PORT_BUTTON_RIGHT, PUD_DOWN);
	gettimeofday(&timerButtonRight, NULL);
	if(wiringPiISR(PORT_BUTTON_RIGHT, INT_EDGE_FALLING, &buttonRight_fall) < 0)
	{
		fprintf(stderr, "%s : Init Button RIGHT Fall failed!\n", __func__);
		exit(EXIT_FAILURE);
	}
	
	// Button DOWN Fall
	pinMode(PORT_BUTTON_DOWN, INPUT);
	pullUpDnControl(PORT_BUTTON_DOWN, PUD_DOWN);
	gettimeofday(&timerButtonDown, NULL);
	if(wiringPiISR(PORT_BUTTON_DOWN, INT_EDGE_FALLING, &buttonDown_fall) < 0)
	{
		fprintf(stderr, "%s : Init Button DOWN Fall failed!\n", __func__);
		exit(EXIT_FAILURE);
	}
	
	
	// Button LED Fall
	/*pullUpDnControl(PORT_BUTTON_LED, PUD_DOWN);
	pinMode(PORT_BUTTON_LED, INPUT);
	gettimeofday(&timerButtonLed, NULL);
	if(wiringPiISR(PORT_BUTTON_LED, INT_EDGE_FALLING, &buttonLed_fall) < 0)
	{
		fprintf(stderr, "%s : Init Button LED Fall failed!\n", __func__);
		exit(EXIT_FAILURE);
	}*/
	
	return true;
}
