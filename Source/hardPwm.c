/**
* \file hardPwm.c
* \brief Code file for the configuration of hardware pwm's used in LED's and servomotor.
* \date December 2016
*/

#include "hardPwm.h"

/** \brief Check if pwm system file exists
* \param filename Name of the file
*
* \return <b> 1 </b> File exists
* \return <b> 0 </b> File does not exist
*/
bool fileExists(char* filename)
{
	struct stat buffer;
	int8_t trash;
	trash = stat(filename, &buffer);
	if(trash == 0)
	{
		return true;
	}
	return false;
}

/** \brief Changes PWM frequency for PWM0
* \param freq Desired frequency forr PWM0
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm0_freq(uint16_t freq)
{
	bool trash;
	char* filename = "/sys/devices/platform/pwm-ctrl/freq0";
	trash = fileExists(filename);
	if(trash == true)
	{
		FILE * f = fopen(filename, "w");
		if(f != NULL)
		{
			char buffer[4];
			(int)sprintf(buffer, "%hu", freq);
			fputs(buffer, f);
			fclose(f);
			return true;
		}
	}
	return false;
}

/** \brief Changes PWM duty cycle for PWM0
* \param duty Desired duty-cycle for PWM0
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm0_duty(uint16_t duty)
{
	bool trash;
	char* filename = "/sys/devices/platform/pwm-ctrl/duty0";
	trash = fileExists(filename);
	if(trash == true)
	{
		FILE * f = fopen(filename, "w");
		if(f != NULL)
		{
			char buffer[4];
			(int)sprintf(buffer, "%hu", duty);
			fputs(buffer, f);
			fclose(f);
			return true;
		}
	}
	return false;
}

/** \brief Enables PWM0 signal
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm0_enable()
{
	bool trash;
	char* filename = "/sys/devices/platform/pwm-ctrl/enable0";
	trash = fileExists(filename);
	if(trash == true)
	{
		FILE * f = fopen(filename, "w");
		if(f != NULL)
		{
			fputs("1", f);
			fclose(f);
			return true;
		}
	}
	return false;
}

/** \brief Disables PWM0 signal
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm0_disable()
{
	bool trash;
	char* filename = "/sys/devices/platform/pwm-ctrl/enable0";
	trash = fileExists(filename);
	if(trash == true)
	{
		FILE * f = fopen(filename, "w");
		if(f != NULL)
		{
			fputs("0", f);
			fclose(f);
			return true;
		}
	}
	return false;
}

/** \brief Changes PWM frequency for PWM1
* \param freq Desired frequency forr PWM1
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm1_freq(uint16_t freq)
{
	bool trash;
	char* filename = "/sys/devices/platform/pwm-ctrl/freq1";
	trash = fileExists(filename);
	if(trash == true)
	{
		FILE * f = fopen(filename, "w");
		if(f != NULL)
		{
			char buffer[4];
			(int)sprintf(buffer, "%hu", freq);
			fputs(buffer, f);
			fclose(f);
			return true;
		}
	}
	return false;
}

/** \brief Changes PWM duty cycle for PWM1
* \param duty Desired duty-cycle for PWM1
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm1_duty(uint16_t duty)
{
	bool trash;
	char* filename = "/sys/devices/platform/pwm-ctrl/duty1";
	trash = fileExists(filename);
	if(trash == true)
	{
		FILE * f = fopen(filename, "w");
		if(f != NULL)
		{
			char buffer[4];
			(int)sprintf(buffer, "%hu", duty);
			fputs(buffer, f);
			fclose(f);
			return true;
		}
	}
	return false;
}

/** \brief Enables PWM1 signal
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm1_enable()
{
	bool trash;
	char* filename = "/sys/devices/platform/pwm-ctrl/enable1";
	trash = fileExists(filename);
	if(trash == true)
	{
		FILE * f = fopen(filename, "w");
		if(f != NULL)
		{
			fputs("1", f);
			fclose(f);
			return true;
		}
	}
	return false;
}

/** \brief Disables PWM1 signal
*
* \return <b> 1 </b> Operation Succeeded
* \return <b> 0 </b> Operation failed
*/
bool pwm1_disable()
{
	bool trash;
	char* filename = "/sys/devices/platform/pwm-ctrl/enable1";
	trash = fileExists(filename);
	if(trash == true)
	{
		FILE * f = fopen(filename, "w");
		if(f != NULL)
		{
			fputs("0", f);
			fclose(f);
			return true;
		}
	}
	return false;
}
