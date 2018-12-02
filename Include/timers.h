/**
 * \file timers.h
 * \brief Header file for the control of the internal timers (miliseconds and microseconds).
 * \date December 2016
 * 
 */

#pragma once

#include <time.h>
#include <sys/time.h>

#define tmillis(a, b) \
	((a).tv_usec < (b).tv_usec ? \
		((a).tv_sec - (b).tv_sec - 1) * 1000 + (1000000 - ((b).tv_usec - (a).tv_usec)) / 1000 : \
		(((a).tv_sec - (b).tv_sec) * 1000) + (((a).tv_usec - (b).tv_usec) / 1000))		/*!< Function to wait for x miliseconds */

#define tmicros(a, b) \
	((a).tv_usec < (b).tv_usec ? \
		((a).tv_sec - (b).tv_sec - 1) * 1000000 + (1000000 - ((b).tv_usec - (a).tv_usec)) : \
		(((a).tv_sec - (b).tv_sec) * 1000000) + (((a).tv_usec - (b).tv_usec)))			/*!< Function to wait for x microseconds */
