/* File: font.h for LCD-ST7565 Lib
 * Purpose: main source file for for eclipse project template
 *          for use with GCC 'GNU Tools ARM Embedded' and Eclipse
 * Version: V1.1
 * Date: 20 Oct 2014
 *
 * createt for the bachelor thesis "Entwurf und Aufbau einer Entwicklungsumgebung für ARM"
 * by Martin Landsdorf
*/
/* Based on the Adafruit-Arduino-Library
--> Original License Header
$Id:$
ST7565 LCD library!
Copyright (C) 2010 Limor Fried, Adafruit Industries
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
// some of this code was written by <cstone@pobox.com> originally; it is in the public domain.
*/


#include <stdint.h>

#ifndef __FONT_H_
#define __FONT_H_

#define ZEILE_1 0
#define ZEILE_2 8
#define ZEILE_3 16
#define ZEILE_4 24
#define ZEILE_5 32
#define ZEILE_6 40
#define ZEILE_7 48
#define ZEILE_8 56

struct FONT_DEF {
	uint8_t u8Width; /* Character width for storage         */
	uint8_t u8Height; /* Character height for storage        */
	uint8_t u8FirstChar; /* The first character available       */
	uint8_t u8LastChar; /* The last character available        */
	const uint8_t *au8FontTable; /* Font table start address in memory  */
};

extern const struct FONT_DEF Font_5x7;
extern const uint8_t lcdfont5x7[];

#endif
