/**
    \file       VT100.cpp
    \copybrief  VT100.h
    \details    For more details please refer to VT100.h
*/




#include "VT100.h"



VT100_Control VT100;


//************************************************************************
// Constructor and helper functions
VT100_Control::VT100_Control(void)
{
	_serial = NULL;
}

void VT100_Control::_sendCMD(uint8_t val)
{
	_serial->write("\e[");
	_serial->print(val);
}

void VT100_Control::_formatText(uint8_t val)
{
	_sendCMD(val);
	_serial->write('m');
}

void VT100_Control::begin(Stream &_ser)
{
	//Set serial port
	_serial = &_ser;
	
	reset();
}

void VT100_Control::reset(void)
{
	_serial->write(VT_TERMINAL_RESET);
	_serial->flush();
	delay(10);
}


//************************************************************************
// Cursor related functions
void VT100_Control::cursorUp(uint8_t n)
{
	_sendCMD(n);
	_serial->write('A');
}

void VT100_Control::cursorDown(uint8_t n)
{
	_sendCMD(n);
	_serial->write('B');
}

void VT100_Control::cursorRight(uint8_t n)
{
	_sendCMD(n);
	_serial->write('C');
}

void VT100_Control::cursorLeft(uint8_t n)
{
	_sendCMD(n);
	_serial->write('D');
}

void VT100_Control::setCursor(uint8_t x, uint8_t y)
{
	_sendCMD(x);
	_serial->write(';');
	_serial->print(y);
	_serial->write('H');
}

void VT100_Control::cursorOn(void)
{
	_serial->write(VT_CURSOR_ON);
}

void VT100_Control::cursorOff(void)
{
	_serial->write(VT_CURSOR_OFF);
}

void VT100_Control::cursorHome(void)
{
	_serial->write(VT_CURSOR_HOME);
}

void VT100_Control::cursorSave(void)
{
	_serial->write(VT_CURSOR_SAVE);
}

void VT100_Control::cursorRestore(void)
{
	_serial->write(VT_CURSOR_RESTORE);
}


//************************************************************************
// Text clearing related functions
void VT100_Control::clearLineAfter(void)
{
	_serial->write(VT_CLR_LINE_AFTER_CURSOR);
}

void VT100_Control::clearLineBefore(void)
{
	_serial->write(VT_CLR_LINE_TO_CURSOR);
}

void VT100_Control::clearLine(void)
{
	_serial->write(VT_CLR_LINE);
}

void VT100_Control::clearScreen(void)
{
	_serial->write(VT_CLR_SCREEN);
}

void VT100_Control::clearAll(void)
{
	_serial->write(VT_CLR_ALL);
}


//************************************************************************
// Text and output formatting functions
void VT100_Control::setBackgroundColor(VT100_Colors color)
{
	_formatText((uint8_t)color + 10);
}

void VT100_Control::setTextColor(VT100_Colors color)
{
	_formatText((uint8_t)color);
}

void VT100_Control::formatText(VT100_TextFormat format)
{
	_formatText((uint8_t)format);
}
