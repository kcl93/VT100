/**
    \file       VT100.h
    \brief      Library to control a VT100 terminal via an Arduino
    \details    Using this library it is possible to make better use of VT100 capable terminal programs such as Tera Term.
				This library does not work when being used with the Serial Monitor of the Arduino IDE.
				The Serial Monitor does not support VT100 commands und will not react to them properly.
    \author     Kai Clemens Liebich
    \date       2019-11-29
    \version    1.0
*/


#ifndef VT100_H_
#define VT100_H_

#include <Arduino.h>


//Reset
#define VT_TERMINAL_RESET			"\ec" //Wait >10ms after this command before sending any other commands

//Erasing
#define VT_CLR_LINE_AFTER_CURSOR	"\e[K"
#define VT_CLR_LINE_TO_CURSOR		"\e[1K"
#define VT_CLR_LINE					"\e[2K"
#define	VT_CLR_SCREEN				"\e[2J"
#define VT_CLR_ALL					"\e[1;1H\e[2J"

//Cursor
#define VT_CURSOR_OFF				"\e[?25l"
#define VT_CURSOR_ON				"\e[?25h"
#define VT_CURSOR_HOME				"\e[H"
#define VT_CURSOR_SAVE				"\e7"
#define VT_CURSOR_RESTORE			"\e8"
#define VT_CURSOR_UP				"\e[A"
#define VT_CURSOR_DOWN				"\e[B"
#define VT_CURSOR_RIGHT				"\e[C"
#define VT_CURSOR_LEFT				"\e[D"

//Text
#define VT_TEXT_DEFAULT				"\e[0m"
#define VT_TEXT_BRIGHT				"\e[1m"
#define VT_TEXT_DIM					"\e[2m"
#define VT_TEXT_UNDERSCORE			"\e[4m"
#define VT_TEXT_BLINK				"\e[5m"
#define VT_TEXT_REVERSE				"\e[7m"
#define VT_TEXT_HIDDEN				"\e[8m"

//Text colors
#define VT_FOREGROUND_BLACK			"\e[30m"
#define VT_FOREGROUND_RED			"\e[31m"
#define VT_FOREGROUND_GREEN			"\e[32m"
#define VT_FOREGROUND_YELLOW		"\e[33m"
#define VT_FOREGROUND_BLUE			"\e[34m"
#define VT_FOREGROUND_MAGNETA		"\e[35m"
#define VT_FOREGROUND_CYAN			"\e[36m"
#define VT_FOREGROUND_WHITE			"\e[37m"
#define VT_FOREGROUND_DEFAULT		"\e[39m"

//Background colors
#define VT_BACKGROUND_BLACK			"\e[40m"
#define VT_BACKGROUND_RED			"\e[41m"
#define VT_BACKGROUND_GREEN			"\e[42m"
#define VT_BACKGROUND_YELLOW		"\e[43m"
#define VT_BACKGROUND_BLUE			"\e[44m"
#define VT_BACKGROUND_MAGNETA		"\e[45m"
#define VT_BACKGROUND_CYAN			"\e[46m"
#define VT_BACKGROUND_WHITE			"\e[47m"
#define VT_BACKGROUND_DEFAULT		"\e[49m"

/**
	\brief	Enum defining all available text and background colors for the VT100 terminal
*/
typedef enum
{
	VT_BLACK	= 30,	//!< Black
	VT_RED		= 31,	//!< Red
	VT_GREEN	= 32,	//!< Green
	VT_YELLOW	= 33,	//!< Yellow
	VT_BLUE		= 34,	//!< Blue
	VT_MAGENTA	= 35,	//!< Magenta
	VT_CYAN		= 36,	//!< Cyan
	VT_WHITE	= 37,	//!< White
	VT_DEFAULT	= 39	//!< Default color of terminal
} VT100_Colors;

/**
	\brief	Enumg defining all available text formatting options (beside colors)
*/
typedef enum
{
	VT_RESET		= 0,	//!< Reset all formats to standard
	VT_BRIGHT		= 1,	//!< Bold text?
	VT_DIM			= 2,	//!< Cursive text?
	VT_UNDERSCORE	= 4,	//!< Underscore text
	VT_BLINK		= 5,	//!< Blink text at cursor
	VT_REVERSE		= 7,	//!< Reverse writing direction
	VT_HIDDEN		= 8		//!< Hide text?
} VT100_TextFormat;


class VT100_Control
{
	private:
		Stream *_serial;
		void _sendCMD(uint8_t val);
		void _formatText(uint8_t val);
		
	public:
		/**
			\brief	Constructor for a VT100_Control object
		*/
		VT100_Control(void);
		
		/**
			\brief	Begin using the VT100_Control object
			\param[in]	_ser	Stream object that will be used for communication (can be any serial interface, e.G. Serial, SoftwareSerial, SerialUSB, etc.)
		*/
		void begin(Stream &_ser);
		
		/**
			\brief Reset the VT100 terminal to standard settings
		*/
		void reset(void);
		
		/**
			\brief Move the cursor up one or more lines
			\param[in]	n	Number of lines to move (default = 1)
		*/
		void cursorUp(uint8_t n = 1);
		
		/**
			\brief Move the cursor down one or more lines
			\param[in]	n	Number of lines to move (default = 1)
		*/
		void cursorDown(uint8_t n = 1);
		
		/**
			\brief Move the cursor one or more characters to the left
			\param[in]	n	Number of characters to move (default = 1)
		*/
		void cursorLeft(uint8_t n = 1);
		
		/**
			\brief Move the cursor one or more characters to the right
			\param[in]	n	Number of characters to move (default = 1)
		*/
		void cursorRight(uint8_t n = 1);
		
		/**
			\brief Set the cursor to a specific position
			\param[in]	x	Horizontal position
			\param[in]	y	Vertical position
		*/
		void setCursor(uint8_t x, uint8_t y);
		
		/**
			\brief Make the cursor visible
		*/
		void cursorOn(void);
		
		/**
			\brief Make the cursor invisible
		*/
		void cursorOff(void);
		
		/**
			\brief Set cursor to home position
		*/
		void cursorHome(void);
		
		/**
			\brief Save current cursor position
		*/
		void cursorSave(void);
		
		/**
			\brief Restore previously saved cursor position
		*/
		void cursorRestore(void);
		
		/**
			\brief Clear line after cursor
		*/
		void clearLineAfter(void);
		
		/**
			\brief Clear line before cursor
		*/
		void clearLineBefore(void);
		
		/**
			\brief Clear complete line
		*/
		void clearLine(void);
		
		/**
			\brief Clear the complete screen
		*/
		void clearScreen(void);
		
		/**
			\brief Clear all text
		*/
		void clearAll(void);
		
		/**
			\brief Set the background color of the terminal
			\param[in] color	Any member of ::VT100_Colors
		*/
		void setBackgroundColor(VT100_Colors color = VT_DEFAULT);
		
		/**
			\brief Set text color
			\param[in] color	Any member of ::VT100_Colors
		*/
		void setTextColor(VT100_Colors color = VT_DEFAULT);
		
		/**
			\brief Format the text
			\param[in] format	Any member of ::VT100_TextFormat
		*/
		void formatText(VT100_TextFormat format = VT_RESET);
};


/**
	\brief VT100_Control that can directly be used to use all VT100 functions
*/
extern VT100_Control VT100;

#endif /* VT100_H_ */