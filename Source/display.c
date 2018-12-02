/**
 * \file display.c
 * \brief Code file for condiguration of the LCD 16x2 display.
 * \date December 2016
 * 
 */

#include "display.h"

#define LCD_ROW         2   /*!< 2 Line display*/
#define LCD_COL         16  /*!< 16 Char display */
#define LCD_BUS         4   /*!< Interface 4 Bit mode */

uint8_t lcdHandle = 0;	/*!< LCD handle */

/** \brief Updates the messages printed on the LCD
    *
    * \param line1 Message to be printed on the 1st LCD line
    * \param line2 Message to be printed on the 2nd LCD line
    */
void updateDisplay(unsigned char line1[], unsigned char line2[]) // UTF-16
{
	uint8_t n;
	//lcdClear(lcdHandle);
	lcdHome(lcdHandle);
	// Line 1
	lcdPosition(lcdHandle, 0, 0); // Make sure it will start writing at the start of line 1
	for(n = 0; line1[n] != (unsigned char)'\0' && n < LCD_COL; n++)
	{
		lcdPutchar(lcdHandle, line1[n]);
	}
	for(; n < LCD_COL; n++)
	{
		lcdPutchar(lcdHandle, (unsigned char)' '); // Blank spaces until end of line to reset
	}
	// Line 2
	lcdPosition(lcdHandle, 0, 1); // Make sure it will start writing at the start of line 2
	for(n = 0; line2[n] != (unsigned char)'\0' && n < LCD_COL; n++)
	{
		lcdPutchar(lcdHandle, line2[n]);
	}
	for(; n < LCD_COL; n++)
	{
		lcdPutchar(lcdHandle, (unsigned char)' '); // Blank spaces until end of line to reset
	}
}

/** \brief Initializes the LCD, printing a default message.
    *
    * \return <b> 1 </b> Operation succeeded
    * \return <b> 0 </b> Operation failed
    */
bool initDisplay()
{
	lcdHandle = lcdInit (LCD_ROW, LCD_COL, LCD_BUS,
							PORT_LCD_RS, PORT_LCD_E,
							PORT_LCD_D4, PORT_LCD_D5, PORT_LCD_D6, PORT_LCD_D7,
							0, 0, 0, 0);
	if(lcdHandle < 0)
	{
		return false;
	}
	
	unsigned char line1[16] = {"1234567890abcdef"};
	unsigned char line2[16] = {"1234567890abcdef"};
	
	updateDisplay(line1, line2);
	return true;
}
