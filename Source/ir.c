/**
 * \file ir.c
 * \brief Code File for the configuration of the infrared sensor.
 * \date December 2016
 * 
 */

#include "ir.h"

#define isButton(x, y) (strstr(x, y) != NULL)	/*!< Verify if it's a valid button */
#define BTN_UP		"KEY_UP"			/*!< Label for up button */
#define BTN_LEFT	"KEY_LEFT"			/*!< Label for left button */
#define BTN_RIGHT	"KEY_RIGHT"			/*!< Label for right button */
#define BTN_DOWN	"KEY_DOWN"			/*!< Label for down button */
#define BTN_ENTER	"KEY_ENTER"			/*!< Label for enter button */
#define BTN_LED		"KEY_MUTE"			/*!< Label for mute button */
#define BTN_LEDUP 	"KEY_VOLUMEUP"		/*!< Label for volume up button */
#define BTN_LEDDOWN	"KEY_VOLUMEDOWN"	/*!< Label for volume down button */

struct lirc_config *ir_config;	/*!< Struct for infrared configuration */
pthread_t ir_thread;	/*!< Thread for infrared sensor */

/** \brief Initializes new thread to run the infrared sensor separadetly from main thread.
	*
    */
void* threadIR(void *dummy)
{
	char* code;
	struct timeval tstart, tstop;
	uint64_t elapsed; // Elapsed time in ms
	if(lirc_readconfig("/etc/lirc/lirc.conf", &ir_config, NULL) == 0)
	{
		gettimeofday(&tstart, NULL);
		do
		{
			lirc_nextcode(&code);
			gettimeofday(&tstop, NULL);
			elapsed = (uint64_t)(tstop.tv_sec - tstart.tv_sec) * 1000 + (tstop.tv_usec - tstart.tv_usec) / 1000;
			if(elapsed < 200) // 200ms (button delay)
			{
				continue;
			}
			gettimeofday(&tstart, NULL); // Restart timer delay
			if(isButton(code, BTN_UP))
			{
				buttonUp_fall();
			}
			else if(isButton(code, BTN_DOWN))
			{
				buttonDown_fall();
			}
			else if(isButton(code, BTN_LEFT))
			{
				buttonLeft_fall();
			}
			else if(isButton(code, BTN_RIGHT) || isButton(code, BTN_ENTER))
			{
				buttonRight_fall();
			}
			else if(isButton(code, BTN_LED))
			{
				buttonLed_fall();
			}
			/*else if(isButton(code, BTN_LEDUP))
			{
				buttonLedUp_fall();
			}
			else if(isButton(code, BTN_LEDDOWN))
			{
				buttonLedDown_fall();
			}*/
		} while(true); // while(!isButton(code, BTN_UP));
	}
	return 0;
}

/** \brief Ends the created thread.
	*
    */
bool freeIR()
{
	//(void) pthread_exit(&ir_thread);
	(void) pthread_cancel(ir_thread);
	if(ir_config != NULL)
	{
		lirc_freeconfig(ir_config);
	}
	lirc_deinit();
	return true;
}

/** \brief Initiates the created thread.
	*
    */
bool initIR()
{
	ir_config = NULL;
	if(lirc_init("chocadeira", 1) == -1)
	{
		return false;
	}
	if(pthread_create(&ir_thread, NULL, threadIR, NULL))
	{
		return false;
	}
	return true;
}
