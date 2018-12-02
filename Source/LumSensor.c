/**
 * \file LumSensor.c
 * \brief Code file for the control of the luminosity sensor.
 * \date December 2016
 * 
 */

#include "LumSensor.h"

#define PWM_MAX 1020	/*!< Max pwm value */
#define PWM_MIN 0		/*!< Min pwm value */

#define LUM_REFRESH 200	/*!< Refresh time of the luminosity sensor */

pthread_t lum_thread;	/*!< Thread for control of luminosity */

/** \brief Initializes the lum_struct structure.
	*
    */
bool initLumSensor(uint16_t * lumens, uint16_t * luminosity, bool * LED_STATUS)
{
	uint16_t freq = 50;
	uint16_t duty = 0;
	
	bool init = pwm1_freq(freq);
	if(init == false)
	{
		return false;
	}
	init = pwm1_duty(duty);
	if(init == false)
	{
		return false;
	}
	init = pwm1_enable();
	if(init == false)
	{
		return false;
	}
	
	lum_struct args;
	args = (lum_struct)malloc(sizeof(lum_struct));
	args->lumens = lumens;
	args->luminosity = luminosity;
	args->LED_STATUS = LED_STATUS;
	
	//printf("%ld - %ld\n", args.lumens, args.luminosity);
	
	if(pthread_create(&lum_thread, NULL, &threadLum, (void*) args))
	{
		return false;
	}
	
	return true;
}

/** \brief Reads the luminosity sensor.
	*
    */
uint16_t readLumSensor()
{
	uint16_t soma = 0;
	for (int c=0 ; c < 32 ; c++)
	{
		soma += analogRead(PORT_ADC0);
	}
	soma >>= 5;
	return soma;
}

/** \brief Initializes a separate thread for the reading of the sensor.
	*
    */
void* threadLum(void* arg)
{
	ls* args = arg;
	uint16_t * lumens = args->lumens;
	uint16_t lumens_ref = 110;
	uint16_t * luminosity = args->luminosity;
	bool * LED_STATUS = args->LED_STATUS;
	uint16_t LUM_READ; 
	uint16_t LUM_DUTY;
	
	//uint16_t reading;
	/*FILE * f = fopen("ola", "w");
	char buf[40];
	sprintf(buf, "%d - %d", lumens, luminosity);
	fputs(buf, f);
	fclose(f);*/
	LUM_READ = readLumSensor();
	*lumens = (uint16_t)(LUM_READ * 100 / 1023);
	LUM_DUTY = 0;
	pwm1_duty(LUM_DUTY);
	
	struct timeval timerCur;
	struct timeval timerPWM;
	struct timeval timerAnalog;
	struct timeval timerCalc;
	//gettimeofday(&timerCur, NULL);
	gettimeofday(&timerPWM, NULL);
	gettimeofday(&timerAnalog, NULL);
	gettimeofday(&timerCalc, NULL);
	while(1)
	{
		//if(*LED_STATUS == true || *LED_STATUS == false)
		//{
		gettimeofday(&timerCur, NULL);
		if(tmillis(timerCur, timerCalc) > 300)
		{
			gettimeofday(&timerCalc, NULL);
			while(LUM_READ < (lumens_ref - LUM_DELTA) || LUM_READ > (lumens_ref + LUM_DELTA))
			{
				if(LUM_READ < (lumens_ref - LUM_DELTA))
				{
					if(LUM_DUTY < PWM_MAX)
					{
						LUM_DUTY += 20;
					}
					else
					{
						break;
					}
				}
				else if(LUM_READ > (lumens_ref + LUM_DELTA))
				{
					if(LUM_DUTY > PWM_MIN)
					{
						LUM_DUTY -= 20;
					}
					else
					{
						break;
					}
				}
				if(*LED_STATUS == false && LUM_DUTY > 0)
				{
					LUM_DUTY = 0;
					pwm1_duty(LUM_DUTY);
					LUM_READ = (LUM_READ + readLumSensor()) >> 1;
					gettimeofday(&timerCur, NULL);
					if(tmillis(timerCur, timerAnalog) > LUM_REFRESH)
					{
						*lumens = (uint16_t)(LUM_READ * 100 / 1023);
						gettimeofday(&timerAnalog, NULL);
					}
					gettimeofday(&timerCur, NULL);
					if(tmillis(timerCur, timerPWM) > LUM_REFRESH)
					{
						*luminosity = (uint16_t)(LUM_DUTY * 100 / PWM_MAX);
						gettimeofday(&timerPWM, NULL);
					}
				}
				else
				{
					LUM_READ = (LUM_READ + readLumSensor()) >> 1;
					pwm1_duty(LUM_DUTY);
					gettimeofday(&timerCur, NULL);
					if(tmillis(timerCur, timerAnalog) > LUM_REFRESH)
					{
						*lumens = (uint16_t)(LUM_READ * 100 / 1023);
						gettimeofday(&timerAnalog, NULL);
					}
					gettimeofday(&timerCur, NULL);
					if(tmillis(timerCur, timerPWM) > LUM_REFRESH)
					{
						*luminosity = (uint16_t)(LUM_DUTY * 100 / PWM_MAX);
						gettimeofday(&timerPWM, NULL);
					}
				}
			}
			if(*LED_STATUS == false && LUM_DUTY > 0)
			{
				LUM_DUTY = 0;
				pwm1_duty(LUM_DUTY);
				LUM_READ = (LUM_READ + readLumSensor()) >> 1;
				gettimeofday(&timerCur, NULL);
				if(tmillis(timerCur, timerAnalog) > LUM_REFRESH)
				{
					*lumens = LUM_READ;
					gettimeofday(&timerAnalog, NULL);
				}
				gettimeofday(&timerCur, NULL);
				if(tmillis(timerCur, timerPWM) > LUM_REFRESH)
				{
					*luminosity = (uint16_t)(LUM_DUTY * 100 / PWM_MAX);
					gettimeofday(&timerPWM, NULL);
				}
			}
			else
			{
				pwm1_duty(LUM_DUTY);
				LUM_READ = readLumSensor();
				gettimeofday(&timerCur, NULL);
				if(tmillis(timerCur, timerAnalog) > LUM_REFRESH)
				{
					*lumens = (uint16_t)(LUM_READ * 100 / 1023);
					gettimeofday(&timerAnalog, NULL);
				}
				gettimeofday(&timerCur, NULL);
				if(tmillis(timerCur, timerPWM) > LUM_REFRESH)
				{
					*luminosity = (uint16_t)(LUM_DUTY * 100 / PWM_MAX);
					gettimeofday(&timerPWM, NULL);
				}
			}
			//args->lumens = reading;
			//((lum_struct*)(arg))->lumens = reading;
			//*lumens += 1;
			//*(args->luminosity) = (uint16_t)(LUM_DUTY * 100 / PWM_MAX);
		}
		/*if(*LED_STATUS == false && LUM_DUTY > 0)
		{
			LUM_DUTY = 0;
			pwm1_duty(LUM_DUTY);
			LUM_READ = (LUM_READ + readLumSensor()) >> 1;
			gettimeofday(&timerCur, NULL);
			if(tmillis(timerCur, timerAnalog) > LUM_REFRESH)
			{
				*lumens = LUM_READ;
				gettimeofday(&timerAnalog, NULL);
			}
			gettimeofday(&timerCur, NULL);
			if(tmillis(timerCur, timerPWM) > LUM_REFRESH)
			{
				*luminosity = (uint16_t)(LUM_DUTY * 100 / PWM_MAX);
				gettimeofday(&timerPWM, NULL);
			}
		}*/
	}
	return 0;
}
