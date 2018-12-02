/**
 * \file dht11.c
 * \brief Code file for configuration of the dht11 sensor (humidity and temperature).
 * \date December 2016
 * 
 */

#include "dht11.h"

/** \brief Reads data from DHT11 sensor.
    *
    * \param temperature Where the read temperature value will be saved
    * \param humidity Where the read humidity value will be saved
    *
    * \return <b> 1 </b> Operation succeeded
    * \return <b> 0 </b> Operation failed
    */
bool dht11_read(double temperature[], double humidity[])
{
	uint8_t i;
	uint8_t counter;
	uint8_t j = 0;
	int dht11_data[5] = { 0, 0, 0, 0, 0 };
	
	// DHT11 Request
	pinMode(PORT_DHT_DATA, OUTPUT);
	// pull pin down for 18 milliseconds
	digitalWrite(PORT_DHT_DATA, LOW);
	delayMicroseconds(18000);
	// pull pin up for 40 microseconds
	digitalWrite(PORT_DHT_DATA, HIGH);
	delayMicroseconds(40);
	
	// DHT11 Reply
	pinMode(PORT_DHT_DATA, INPUT);
	counter = 0;
	while(digitalRead(PORT_DHT_DATA) == HIGH)
	{
		delayMicroseconds(1);
		counter++;
		if(counter == 255)
		{
			return false;
		}
	}
	while(digitalRead(PORT_DHT_DATA) == LOW)
	{
		delayMicroseconds(1);
	}
	counter = 0;
	while(digitalRead(PORT_DHT_DATA) == HIGH)
	{
		delayMicroseconds(1);
		counter++;
		if(counter == 255)
		{
			return false;
		}
	}

	// Communication 1-wire
	for(j = 0; j < 5; j++)
	{
		counter = 0;
		for(i = 0; i < 8; )
		{
			counter = 0;
			while(digitalRead(PORT_DHT_DATA) == LOW)
			{
				delayMicroseconds(1);
			}
			
			while(digitalRead(PORT_DHT_DATA) == HIGH)
			{
				delayMicroseconds(1);
				counter++;
				if(counter == 255)
				{
					pinMode(PORT_DHT_DATA, OUTPUT);
					return false;
				}
				
			}
			dht11_data[j] <<= 1;
			if(counter > 26)
			{
				dht11_data[j] |= 1;
			}
			i++;
		}
	}
	pinMode(PORT_DHT_DATA, INPUT);
	while(digitalRead(PORT_DHT_DATA) == LOW)
	{
		delayMicroseconds(1);
	}
	pinMode(PORT_DHT_DATA, OUTPUT);
	if (dht11_data[4] == ((dht11_data[0] + dht11_data[1] + dht11_data[2] + dht11_data[3]) & 0xFF) && dht11_data[4] > 0 )
	{
		*humidity = dht11_data[0] + (dht11_data[1] / 1000.); // decimal part, 0-255
		*temperature = dht11_data[2] + (dht11_data[3] / 1000.);
		
		return true;
	}
	return false;
}

/** \brief Initializes as output the GPIO pin used to communicate with the DHT11 sensor.
    *
    * \return <b> 1 </b> Operation succeeded
    */
bool dht11_init()
{
	pinMode(PORT_DHT_DATA, OUTPUT);
	digitalWrite(PORT_DHT_DATA, HIGH);
	return true;
}
