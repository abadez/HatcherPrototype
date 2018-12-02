/**
 * \file Pins.h
 * \brief Header file to save the used GPIO pins.
 * \date December 2016
 * 
 */

#pragma once

// ADC
#define PORT_ADC0			0		/*!< ADC.AIN0(AIN0) */
#define PORT_ADC1			1		/*!< ADC.AIN1(AIN1) */

// PWM
#define PORT_LUM_PIN		12		/*!< pwm1 pin for Lum:	GPIOX.BIT10(#107) */
#define PORT_SERVO_PIN		23		/*!< pwm0 pin for Servo:GPIOX.BIT11(#108) */

// LCD
#define PORT_LCD_RS			7		/*!< Register Select:	GPIOY.BIT3(#83) */
#define PORT_LCD_E			0		/*!< Enable Signal:		GPIOY.BIT8(#88) */
#define PORT_LCD_D4			2		/*!< Data Bus:			GPIOX.BIT19(#116) */
#define PORT_LCD_D5			3		/*!< Data Bus:			GPIOX.BIT18(#115) */
#define PORT_LCD_D6			1		/*!< Data Bus:			GPIOY.BIT7(#87) */
#define PORT_LCD_D7			4		/*!< Data Bus:			GPIOX.BIT7(#104) */

// Buttons
#define PORT_BUTTON_UP		13		/*!< UP:				GPIOX.BIT9(#106) */
#define PORT_BUTTON_LEFT	21		/*!< LEFT:				GPIOX.BIT4(#101) */
#define PORT_BUTTON_RIGHT	14		/*!< RIGHT:				GPIOX.BIT8(#105) */
#define PORT_BUTTON_DOWN	24		/*!< DOWN:				GPIOX.BIT0(#97) */
#define PORT_BUTTON_LED		26		/*!< LED:				GPIOX.BIT2(#99) */

// Fans and Heat
#define PORT_HEAT			6		/*!< HEAT Pin:			GPIOX.BIT6(#103) */
#define PORT_RESISTOR_FAN	10		/*!< Resistor Fan Pin:	GPIOX.BIT20(#117) */
#define PORT_COOL_FAN		11		/*!< Cool Fan Pin:		GPIOX.BIT21(#118) */

// DHT11
#define PORT_DHT_DATA		27		/*!< Data Pin:			GPIOX.BIT5(#102) */

// Humidity led
#define PORT_HUMIDITY		5		/*!< Humidity:			GPIOX.BIT5(#102) */

/**
 * Pins to use:
 * 
 * 22		// Malfunction:				GPIOX.BIT3(#100)
 */
