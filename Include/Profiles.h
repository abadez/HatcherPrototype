/**
 * \file Profiles.h
 * \brief Header file for configuration of the incubation profiles.
 * \date December 2016
 * 
 */

#pragma once

#include <stdio.h>
#include <stdint.h>

#define N_PROFILES 4			/*!< Number of profiles */
typedef unsigned int uint;	/*!< Define for unsigned int */



typedef struct Profile /*! Struct to save default profiles */
{
	char name[15];			/*!< Profile name */	
	uint8_t temperature;	/*!< Profile temperature */
	uint8_t humidity;		/*!< Profile humidity */
	uint8_t days;			/*!< Profile incubation days */
} Profile;

#define Profile_Value(p, opt) (opt == 0 ? p.temperature : (opt == 1 ? p.humidity : (opt == 2 ? p.days : 0)))	/*!< Profile values */

static unsigned char Profile_Options[][16] = {
	"Temperature",
	"Humidity",
	"Hatch"
};								/*!< Strings to print */									

static unsigned char Profile_Symbols[][16] = {
	"C",
	"%",
	"mins"
};								/*!< Symbols to print */

static uint8_t Profile_Min[] = {
	0,
	0,
	1
};								/*!< Minimum values for each Profile parameter */

static const uint8_t Profile_Max[] = {
	99,
	99,
	182
};								/*!< Maximum values for each Profile parameter */

static const struct Profile Profiles[] = {
	{"Galinha", 37, 52, 2 },
	{"Pato Pequim", 37, 60, 34 },
	{"Faisao", 37, 50, 24 },
	{"DEMO", 28, 40, 8 }
};								/*!< All Profiles */
