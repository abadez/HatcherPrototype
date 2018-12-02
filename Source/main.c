/**
 * \file main.c
 * \brief Code file for the control of the system main program.
 * \date December 2016
 * 
 */

#include "main.h"

/** \brief System shutdown, free threads and turn off components.
 *
 */
void sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		(void) freeIR();
		turnResistorFan(false);
		turnCoolFan(false);
		turnResistorHeat(false);
		turnHumidity(false);
		updateDisplay((unsigned char*)"Thanks for using", (unsigned char*)"Chocadeira 16/17");
		exit(EXIT_SUCCESS);
	}
}

/** \brief Show hatch erros.
 *
 */
void hatch_error()
{
	// TODO
}

/** \brief Main loop function to hatch.
 *
 */
bool hatch()
{
	bool dht11 = false;
	double temperature = 0.0;
	double humidity = 0.0;
	uint8_t mindex;
	static const uint8_t maxindex = 4; // temperature, humidity, lumens, led intensity
	
	// Flags
	bool HeatFlag = false;
	bool ResistorFanFlag = false;
	bool CoolFanFlag = false;
	bool QuitMessage = false;
	
	// Timers
	struct timeval timerDHT11;
	struct timeval timerResistorFan;
	struct timeval timerServo;
	struct timeval timerDisplay;
	struct timeval timerDisplayRotate;
	struct timeval timerCur;
	struct timeval timerHatch;
	
	// Display
	unsigned char line1[16];
	unsigned char line2[16];
	gettimeofday(&timerHatch, NULL);
	gettimeofday(&timerCur, NULL);
	if((timerHatch.tv_sec + (customPerfil.days * 60) - timerCur.tv_sec) > 90)
	{
		if((timerHatch.tv_sec + (customPerfil.days * 60) - timerCur.tv_sec) % 60 == 0)
		{
			(int)sprintf((char*)line1, "Time Left: %dm", (int)((timerHatch.tv_sec + (customPerfil.days * 60) - timerCur.tv_sec) / 60));
		}
		else
		{
			(int)sprintf((char*)line1, "Time Left: %dm", (int)((timerHatch.tv_sec + (customPerfil.days * 60) - timerCur.tv_sec) / 60) + 1);
		}
	}
	else
	{
		(int)sprintf((char*)line1, "Time Left: %ds", (int)((timerHatch.tv_sec + (customPerfil.days * 60) - timerCur.tv_sec)));
	}
	(int)sprintf((char*)line2, "Temperature: %dC", (int)temperature);
	updateDisplay(line1, line2);
	gettimeofday(&timerDisplay, NULL);
	gettimeofday(&timerDisplayRotate, NULL);
	
	// Button Reset (Reset before checking for buffer command)
	SELECT = 0;
	
	// Checking all
	uint8_t aux_counter = 0;
	do
	{
		dht11 = dht11_read(&temperature, &humidity);
		delay(2000);
		aux_counter++;
	} while(dht11 == false && aux_counter < 5);
	if(dht11 == false)
	{
		hatch_error();
		return false;
	}
	// First check for humidity
	if(humidity > ((customPerfil.humidity) + HUM_DELTA))
	{
		turnHumidity(false);
		turnCoolFan(true);
		turnResistorFan(true);
	}
	else if (humidity < ((customPerfil.humidity) - HUM_DELTA))
	{
		turnHumidity(true);
	}
	// Init Servo position
	resetServoPosition();
	gettimeofday(&timerServo, NULL);
	
	while(1)
	{
		switch(SELECT)
		{
			case RIGHT:
				if(QuitMessage == true)
				{
					turnCoolFan(false);
					turnResistorHeat(false);
					turnResistorFan(false);
					turnHumidity(false);
					return false;
				}
				break;
			case LEFT:
				if(QuitMessage == true)
				{
					QuitMessage = false;
				}
				else
				{
					QuitMessage = true;
				}
				break;
			case UP:
				mindex = (mindex + maxindex) % (maxindex + 1);
				gettimeofday(&timerDisplayRotate, NULL);
				break;
			case DOWN:
				mindex = (mindex + 1) % (maxindex + 1);
				gettimeofday(&timerDisplayRotate, NULL);
				break;
		}
		SELECT = 0;
		gettimeofday(&timerCur, NULL);
		if(tmillis(timerCur, timerDHT11) > 10000)
		{
			dht11 = dht11_read(&temperature, &humidity);
			gettimeofday(&timerDHT11, NULL);
			
			if(humidity > ((customPerfil.humidity) + HUM_DELTA))
			{
				turnHumidity(false);
				turnCoolFan(true);
				turnResistorFan(true);
			}
			else if (humidity < ((customPerfil.humidity) - HUM_DELTA))
			{
				turnHumidity(true);
			}
			
			if(HeatFlag == true)
			{
				if(temperature > (customPerfil.temperature))
				{
					HeatFlag = false;
					ResistorFanFlag = false;
					turnResistorHeat(HeatFlag);
					turnResistorFan(ResistorFanFlag);
				}
				else
				{
					if(ResistorFanFlag == true)
					{
						gettimeofday(&timerCur, NULL);
						if(tmillis(timerCur, timerResistorFan) > 60000) // 1 minute
						{
							ResistorFanFlag = false;
							turnResistorFan(ResistorFanFlag);
							gettimeofday(&timerResistorFan, NULL);
						}
					}
					else
					{
						gettimeofday(&timerCur, NULL);
						if(tmillis(timerCur, timerResistorFan) > 360000) // 6 minutes
						{
							ResistorFanFlag = true;
							turnResistorFan(ResistorFanFlag);
							gettimeofday(&timerResistorFan, NULL);
						}
					}
				}
			}
			else if(CoolFanFlag == true)
			{
				if(temperature <= (customPerfil.temperature))
				{
					CoolFanFlag = false;
					turnCoolFan(CoolFanFlag);
				}
			}
			else
			{
				if(temperature > customPerfil.temperature)
				{
					// Redundancy check
					if(HeatFlag == true)
					{
						HeatFlag = false;
						ResistorFanFlag = false;
						turnResistorHeat(HeatFlag);
						turnResistorFan(ResistorFanFlag);						
					}
					CoolFanFlag = true;
					turnCoolFan(CoolFanFlag);
				}
				else if(temperature < customPerfil.temperature)
				{
					// Redundancy check
					if(CoolFanFlag == true)
					{
						CoolFanFlag = false;
						turnCoolFan(CoolFanFlag);
					}
					HeatFlag = true;
					ResistorFanFlag = false;
					turnResistorHeat(HeatFlag);
					gettimeofday(&timerResistorFan, NULL);
				}
				else
				{
					// Redundancy check
					if(CoolFanFlag == true)
					{
						CoolFanFlag = false;
						turnCoolFan(CoolFanFlag);
					}
					// Redundancy check
					if(HeatFlag == true)
					{
						HeatFlag = false;
						ResistorFanFlag = false;
						turnResistorHeat(HeatFlag);
						turnResistorFan(ResistorFanFlag);						
					}
				}
			}
		}
		gettimeofday(&timerCur, NULL);
		if(tmillis(timerCur, timerServo) > 60000) // 60 seconds
		{
			rotateServo();
			gettimeofday(&timerServo, NULL);
		}
		gettimeofday(&timerCur, NULL);
		if(tmillis(timerCur, timerDisplay) > 20)
		{
			if(QuitMessage == true)
			{
				(int)sprintf((char*)line1, "Stop Hatch ?!?");
				(int)sprintf((char*)line2, "-> To confirm");
				updateDisplay(line1, line2);
			}
			else
			{
				if((timerHatch.tv_sec + (customPerfil.days * 60) - timerCur.tv_sec) > 90)
				{
					if((timerHatch.tv_sec + (customPerfil.days * 60) - timerCur.tv_sec) % 60 == 0)
					{
						(int)sprintf((char*)line1, "Time Left: %dm", (int)((timerHatch.tv_sec + (customPerfil.days * 60) - timerCur.tv_sec) / 60));
					}
					else
					{
						(int)sprintf((char*)line1, "Time Left: %dm", (int)((timerHatch.tv_sec + (customPerfil.days * 60) - timerCur.tv_sec) / 60) + 1);
					}
				}
				else
				{
					(int)sprintf((char*)line1, "Time Left: %ds", (int)((timerHatch.tv_sec + (customPerfil.days * 60) - timerCur.tv_sec)));
				}
				switch(mindex)
				{
					case 0:
						(int)sprintf((char*)line2, "Temp: %dC", (int)temperature);
						break;
					case 1:
						(int)sprintf((char*)line2, "Humidity: %d%%", (int)humidity);
						break;
					case 2:
						(int)sprintf((char*)line2, "Light: %d%%", (int)lumens);
						break;
					case 3:
						(int)sprintf((char*)line2, "LED: %d%%", (int)luminosity);
						break;
				}
				updateDisplay(line1, line2);
			}
			gettimeofday(&timerDisplay, NULL);
		}
		gettimeofday(&timerCur, NULL);
		if(tmillis(timerCur, timerDisplayRotate) > 5000)
		{
			mindex = (mindex + 1) % (maxindex + 1);
			gettimeofday(&timerDisplayRotate, NULL);
		}
		gettimeofday(&timerCur, NULL);
		if((timerHatch.tv_sec + (customPerfil.days * 60)) < timerCur.tv_sec)
		{
			turnCoolFan(false);
			turnResistorHeat(false);
			turnResistorFan(false);
			turnHumidity(false);
			return true;
		}
	}
}

/** \brief Confirm hatch menu.
 *
 */
bool hatch_confirm()
{
	uint8_t mindex = 0;
	static const uint8_t maxindex = 2; // temperature, humidity, days
	struct timeval timerDisplay;
	struct timeval timerCur;
	gettimeofday(&timerDisplay, NULL);
	static unsigned char line1[16] = "# Confirm Hatch";
	//(int)sprintf((char*)line1, "# Confirm Hatch");
	unsigned char line2[16];
	(int)sprintf((char*)line2, "%s: %hu%s",  Profile_Options[mindex], Profile_Value(customPerfil, mindex), (char*)Profile_Symbols[mindex]);
	updateDisplay(line1, line2);
	SELECT = 0;
	while(true)
	{
		switch(SELECT)
		{
			case RIGHT:
				return true;
				break;
			case LEFT:
				return false;
				break;
			case UP:
				mindex = (mindex + maxindex) % (maxindex + 1);
				gettimeofday(&timerDisplay, NULL);
				(int)sprintf((char*)line2, "%s: %hu%s",  Profile_Options[mindex], Profile_Value(customPerfil, mindex), (char*)Profile_Symbols[mindex]);
				updateDisplay(line1, line2);
				break;
			case DOWN:
				mindex = (mindex + 1) % (maxindex + 1);
				gettimeofday(&timerDisplay, NULL);
				(int)sprintf((char*)line2, "%s: %hu%s",  Profile_Options[mindex], Profile_Value(customPerfil, mindex), (char*)Profile_Symbols[mindex]);
				updateDisplay(line1, line2);
				break;
		}
		SELECT = 0;
		
		gettimeofday(&timerCur, NULL);
		if(tmillis(timerCur, timerDisplay) > 5000)
		{
			mindex = (mindex + 1) % (maxindex + 1);
			(int)sprintf((char*)line2, "%s: %hu%s",  Profile_Options[mindex], Profile_Value(customPerfil, mindex), (char*)Profile_Symbols[mindex]);
			updateDisplay(line1, line2);
			gettimeofday(&timerDisplay, NULL);
		}
	}
	return true;
}

/** \brief Main loop to run the incubator.
 *
 */
void run()
{
	bool confirm;
	confirm = hatch_confirm();
	if(confirm == true)
	{
		confirm = hatch();
		repositionServo(SERVO_MIDDLE);
	}
}

/** \brief Select Profile menu.
 *
 */
void setPerfilMenu()
{
	uint8_t mindex = 0;
	static const uint8_t maxindex = N_PROFILES - 1;
	struct timeval timerDisplay;
	struct timeval timerCur;
	gettimeofday(&timerDisplay, NULL);
	unsigned char line1[16];
	(int)sprintf((char*)line1, "# Perfil %hu/%d", mindex+1, N_PROFILES);
	unsigned char line2[16];
	(int)sprintf((char*)line2, "-> %s", Profiles[mindex].name);
	updateDisplay(line1, line2);
	SELECT = 0;
	while(true)
	{
		switch(SELECT)
		{
			case RIGHT:
				customPerfil = Profiles[mindex];
				(int)sprintf((char*)line1, "PROFILE SELECTED");
				(int)sprintf((char*)line2, "-> %s", Profiles[mindex].name);
				for(uint8_t i = 0; i <= 8; i++)
				{
					if(i % 2 == 0)
					{
						updateDisplay(line1, line2);
						delay(300);
					}
					else
					{
						updateDisplay((unsigned char*)"", line2);
						delay(100);
					}
				}
				return;
				break;
			case LEFT:
				return;
				break;
			case UP:
				mindex = (mindex + maxindex) % (maxindex+1);
				break;
			case DOWN:
				mindex = (mindex + 1) % (maxindex+1);
				break;
		}
		SELECT = 0;
		
		gettimeofday(&timerCur, NULL);
		if(tmillis(timerCur, timerDisplay) > 20)
		{
			(int)sprintf((char*)line1, "# Perfil %hu/%d", mindex+1, N_PROFILES);
			(int)sprintf((char*)line2, "-> %s", Profiles[mindex].name);
			updateDisplay(line1, line2);
			gettimeofday(&timerDisplay, NULL);
		}
	}
}

/** \brief Select Option Values menu.
 *
 */
void setOptionMenu(uint8_t opt)
{
	uint8_t * aux;
	switch(opt)
	{
		case 0:
			aux = &customPerfil.temperature;
			break;
		case 1:
			aux = &customPerfil.humidity;
			break;
		case 2:
			aux = &customPerfil.days;
			break;
		default:
			return;
			break;
	}
	uint8_t val = *aux;
	
	struct timeval timerDisplay;
	struct timeval timerCur;
	gettimeofday(&timerDisplay, NULL);
	unsigned char line1[16];
	(int)sprintf((char*)line1, "# %s", Profile_Options[opt]);
	unsigned char line2[16];
	(int)sprintf((char*)line2, "-> %hu/%hu", val, Profile_Max[opt]);
	updateDisplay(line1, line2);
	SELECT = 0;
	while(true)
	{
		switch(SELECT)
		{
			case RIGHT:
				*aux = val;
				sprintf(customPerfil.name, "Custom");
				return;
				break;
			case LEFT:
				return;
				break;
			case UP:
				val = (val + 1) % (Profile_Max[opt] + 1);
				if(val == 0)
				{
					val = Profile_Min[opt];
				}
				break;
			case DOWN:
				if(val == Profile_Min[opt])
				{
					val = Profile_Max[opt];
				}
				else
				{
					val = (val + Profile_Max[opt]) % (Profile_Max[opt] + 1);
				}
				break;
		}
		SELECT = 0;
		
		gettimeofday(&timerCur, NULL);
		if(tmillis(timerCur, timerDisplay) > 20)
		{
			(int)sprintf((char*)line2, "-> %hu/%hu", val, Profile_Max[opt]);
			updateDisplay(line1, line2);
			gettimeofday(&timerDisplay, NULL);
		}
	}
}

/** \brief Select Option menu.
 *
 */
void OptionMenu()
{
	uint8_t mindex = 0;
	static const uint8_t maxindex = 2; // temperature, humidity, days
	struct timeval timerDisplay;
	struct timeval timerCur;
	gettimeofday(&timerDisplay, NULL);
	unsigned char line1[16];
	(int)sprintf((char*)line1, "# Option %hu/%d", mindex+1, maxindex+1);
	unsigned char line2[16];
	(int)sprintf((char*)line2, "-> %s",  Profile_Options[mindex]);
	updateDisplay(line1, line2);
	SELECT = 0;
	while(true)
	{
		switch(SELECT)
		{
			case RIGHT:
				setOptionMenu(mindex);
				break;
			case LEFT:
				return;
				break;
			case UP:
				mindex = (mindex + maxindex) % (maxindex+1);
				break;
			case DOWN:
				mindex = (mindex + 1) % (maxindex+1);
				break;
		}
		SELECT = 0;
		
		gettimeofday(&timerCur, NULL);
		if(tmillis(timerCur, timerDisplay) > 20)
		{
			(int)sprintf((char*)line1, "# Option %hu/%d", mindex+1, maxindex+1);
			(int)sprintf((char*)line2, "-> %s", Profile_Options[mindex]);
			updateDisplay(line1, line2);
			gettimeofday(&timerDisplay, NULL);
		}
	}
}

/** \brief Show Main menu.
 *
 */
void mainMenu()
{
	static unsigned char line1[16] = {" - CHOCADEIRA - "};
	static unsigned char line2[][16] = {"-> Start",  "-> Change Perfil", "-> Customize"};
	uint8_t mindex = 0;
	static const uint8_t maxindex = 2;
	updateDisplay(line1, line2[mindex]);
	struct timeval timerDisplay;
	struct timeval timerCur;
	gettimeofday(&timerDisplay, NULL);
	while(1)
	{
		switch(SELECT)
		{
			case RIGHT:
				switch(mindex)
				{
					case 0:
						run();
						break;
					case 1:
						setPerfilMenu();
						break;
					case 2:
						OptionMenu();
						break;
				}
				break;
			case LEFT:
				break;
			case UP:
				mindex = (mindex + maxindex) % (maxindex + 1);
				break;
			case DOWN:
				mindex = (mindex + 1) % (maxindex + 1);
				break;
		}
		SELECT = 0;
		gettimeofday(&timerCur, NULL);
		if(tmillis(timerCur, timerDisplay) > 20)
		{
			updateDisplay(line1, line2[mindex]);
			gettimeofday(&timerDisplay, NULL);
		}
	}
}

/** \brief Start system, initiate components and show Main menu.
 *
 */
int main()
{
	
	if(signal(SIGINT, sig_handler) == SIG_ERR)
	{
		fprintf(stderr, "%s: Signal Setup error.\n", __func__);
		exit(EXIT_FAILURE);
	}
	int8_t setup;
	setup = wiringPiSetup();
	if(setup < 0)
	{
		fprintf(stderr, "%s: wiringPi Setup error.\n", __func__);
		exit(EXIT_FAILURE);
	}
	
	bool init;
	init = initIR();
	if(init == false)
	{
		fprintf(stderr, "%s: Infrared Setup error.\n", __func__);
		exit(EXIT_FAILURE);
	}
	init = initDisplay();
	if(init == false)
	{
		fprintf(stderr, "%s: Display Setup error.\n", __func__);
		exit(EXIT_FAILURE);
	}
	init = dht11_init();
	if(init == false)
	{
		fprintf(stderr, "%s: DHT11 Sensor Setup error.\n", __func__);
		exit(EXIT_FAILURE);
	}
	init = initServo();
	if(init == false)
	{
		fprintf(stderr, "%s: Servo Setup error.\n", __func__);
		exit(EXIT_FAILURE);
	}
	init = initFans();
	if(init == false)
	{
		fprintf(stderr, "%s: Fans Setup error.\n", __func__);
		exit(EXIT_FAILURE);
	}
	init = initHumidity();
	if(init == false)
	{
		fprintf(stderr, "%s: Humidity Setup error.\n", __func__);
		exit(EXIT_FAILURE);
	}
	lumens = 0;
	luminosity = 0;
	LED_STATUS = true;
	init = initLumSensor(&lumens, &luminosity, &LED_STATUS);
	if(init == false)
	{
		fprintf(stderr, "%s: Luminosity Sensor Setup error.\n", __func__);
		exit(EXIT_FAILURE);
	}
	init = initButtons();
	if(init == false)
	{
		fprintf(stderr, "%s: Buttons Setup error.\n", __func__);
		exit(EXIT_FAILURE);
	}
	customPerfil = Profiles[0];
	
	SELECT = 0;
	
	mainMenu();
	exit(EXIT_SUCCESS);
	return 0;
}
