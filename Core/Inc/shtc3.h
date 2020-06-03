/*	
 *	SHTC3 Humidity and Temperature Sensor
 *	Power-up time max: 240us
 *	Soft reset time max: 240us
 *	Measurement duration max normal mode: 12.1ms
 *	Measurement duration max low power mode: 0.8ms
 */
 
#ifndef __SHTC3_H
#define __SHTC3_H

//# Defines
#define SHTC3_ADDR					(0x70 << 1)

//## Commands
#define SHTC3_CMD_SLEEP			0xB098
#define SHTC3_CMD_WAKEUP		0x3517

#define SHTC3_CMD_NM_CSE_T 	0x7CA2	// Normal Mode, Clock Stretching Enabled, Read T First
#define SHTC3_CMD_NM_CSE_R 	0x5C24	// Normal Mode, Clock Stretching Enabled, Read RH First
#define SHTC3_CMD_NM_CSD_T 	0x7866	// Normal Mode, Clock Stretching Disabled, Read T First
#define SHTC3_CMD_NM_CSD_R 	0x58E0	// Normal Mode, Clock Stretching Disabled, Read RH First

#define SHTC3_CMD_LP_CSE_T 	0x6458	// Low Power Mode, Clock Stretching Enabled, Read T First
#define SHTC3_CMD_LP_CSE_R 	0x44DE	// Low Power Mode, Clock Stretching Enabled, Read RH First
#define SHTC3_CMD_LP_CSD_T 	0x609C	// Low Power Mode, Clock Stretching Disabled, Read T First
#define SHTC3_CMD_LP_CSD_R	0x401A	// Low Power Mode, Clock Stretching Disabled, Read RH First

#define SHTC3_CMD_SOFTRST		0x805D	// Software reset
#define SHTC3_CMD_READID		0xEFC8	// Read ID register


#endif
