/*
 * arducam.h
 *
 *  Created on: 2015.01.16
 *      Author: Lee
 */

#ifndef SRC_ARDUCAM_H_
#define SRC_ARDUCAM_H_

/*
  ArduCAM.h - Arduino library support for CMOS Image Sensor
  Copyright (C)2011-2015 ArduCAM.com. All right reserved

  Basic functionality of this library are based on the demo-code provided by
  ArduCAM.com. You can find the latest version of the library at
  http://www.ArduCAM.com

  Now supported controllers:
		-	OV2640
		-	OV5642

	We will add support for many other sensors in next release.

  Supported MCU platform
 		-	Theoretically support all Arduino families
  		-	Arduino UNO R3			(Tested)
  		-	Arduino MEGA2560 R3		(Tested)
  		-	Arduino Leonardo R3		(Tested)
  		-	Arduino Nano			(Tested)
  		-	Arduino DUE				(Tested)
  		-	Arduino Yun				(Tested)
  		-	Raspberry Pi			(Tested)


  If you make any modifications or improvements to the code, I would appreciate
  that you share the code with me so that I might include it in the next release.
  I can be contacted through http://www.ArduCAM.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*------------------------------------
	Revision History:
	2015/01/16 	V1.0	by Lee	first release for Raspberry Pi
	
	2016/06/13 	V1.1	by Lee	add support for burst mode

--------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>

#include <wiringPiI2C.h>

#define regtype volatile uint8_t
#define regsize uint8_t

#define fontuint8_t(x) cfont.font[x]

#define PROGMEM

#define pgm_read_byte(x)        (*((char *)x))
//  #define pgm_read_word(x)        (*((short *)(x & 0xfffffffe)))
#define pgm_read_word(x)        ( ((*((unsigned char *)x + 1)) << 8) + (*((unsigned char *)x)))
#define pgm_read_byte_near(x)   (*((char *)x))
#define pgm_read_byte_far(x)    (*((char *)x))
//  #define pgm_read_word_near(x)   (*((short *)(x & 0xfffffffe))
//  #define pgm_read_word_far(x)    (*((short *)(x & 0xfffffffe)))
#define pgm_read_word_near(x)   ( ((*((unsigned char *)x + 1)) << 8) + (*((unsigned char *)x)))
#define pgm_read_word_far(x)    ( ((*((unsigned char *)x + 1)) << 8) + (*((unsigned char *)x))))

#define PSTR(x)  x
#if defined F
  #undef F
#endif
#define F(X) (X)

//****************************************************/
//* Camera Choose Pin Definition	

//****************************************************/
//   CAM_CS  |    BCM   |   wPi
/****************************************************/								
//   CAM1_CS |    17    |    0
//---------------------------------------------------/   
//   CAM2_CS |    23    |    4
//---------------------------------------------------/ 
//   CAM3_CS |    22    |    3
//---------------------------------------------------/  
//   CAM4_CS |    24    |    5
/****************************************************/

#define CAM1_CS 0
#define CAM2_CS 4
#define CAM3_CS 3
#define CAM4_CS 5



/****************************************************/
/* Sensor related definition 												*/
/****************************************************/
typedef enum {
  fmtBMP,
  fmtJPEG
} image_format_t;

typedef enum {
  smOV7670,
  smMT9D111,
  smOV7675,
  smOV5642,
  smOV3640,
  smOV2640,
  smOV9655,
  smMT9M112,
  smOV7725,
  smOV7660
} sensor_model_t;

typedef enum {
  sz160x120,
  sz176x144,
  sz320x240,
  sz352x288,
  sz640x480,
  sz800x600,
  sz1024x768,
  sz1280x960,
  sz1600x1200,
  OV5642_320x240,
  OV5642_640x480,
  //OV5642_1280x720,
  OV5642_1920x1080,
  OV5642_2048x1536,
  OV5642_2592x1944
} jpeg_size_t;

struct sensor_reg {
  uint16_t reg;
  uint16_t val;
};

struct CAM {
  image_format_t m_fmt;
  sensor_model_t sensor_model;
  uint8_t sensor_addr;
};

/****************************************************/
/* I2C Control Definition 													*/
/****************************************************/
#define I2C_ADDR_8BIT 0
#define I2C_ADDR_16BIT 1
#define I2C_REG_8BIT 0
#define I2C_REG_16BIT 1
#define I2C_DAT_8BIT 0
#define I2C_DAT_16BIT 1

/* Register initialization tables for SENSORs */
/* Terminating list entry for reg */
#define SENSOR_REG_TERM_8BIT                0xFF
#define SENSOR_REG_TERM_16BIT               0xFFFF
/* Terminating list entry for val */
#define SENSOR_VAL_TERM_8BIT                0xFF
#define SENSOR_VAL_TERM_16BIT               0xFFFF

/****************************************************/
/* ArduChip related definition 											*/
/****************************************************/
#define ARDUCHIP_TEST1       	0x00  //TEST register
#define ARDUCHIP_TEST2      	0x01  //TEST register

#define ARDUCHIP_MODE      		0x02  //Mode register
#define MCU2LCD_MODE       		0x00
#define CAM2LCD_MODE       		0x01
#define LCD2MCU_MODE       		0x02


#define ARDUCHIP_GPIO			  0x06  //GPIO Write Register
#define GPIO_RESET_MASK			0x01  //0 = default state,		1 =  Sensor reset IO value
#define GPIO_PWDN_MASK			0x02  //0 = Sensor power down IO value, 1 = Sensor power enable IO value

#define BURST_FIFO_READ			0x3C  //Burst FIFO read operation


#define ARDUCHIP_TIM       		0x03  //Timming control
#define HREF_LEVEL_MASK    		0x01  //0 = High active , 		1 = Low active
#define VSYNC_LEVEL_MASK   		0x02  //0 = High active , 		1 = Low active
#define LCD_BKEN_MASK      		0x04  //0 = Enable, 			1 = Disable
#define DELAY_MASK         		0x08  //0 = no delay, 			1 = delay one clock
#define MODE_MASK          		0x10  //0 = LCD mode, 			1 = FIFO mode
#define FIFO_PWRDN_MASK	   		0x20  //0 = Normal operation, 	1 = FIFO power down

#define ARDUCHIP_FIFO      		0x04  //FIFO and I2C control
#define FIFO_CLEAR_MASK    		0x01
#define FIFO_START_MASK    		0x02
#define FIFO_RDPTR_RST_MASK     0x10
#define FIFO_WRPTR_RST_MASK     0x20


#define ARDUCHIP_REV       		0x40  //ArduCHIP revision
#define VER_LOW_MASK       		0x3F
#define VER_HIGH_MASK      		0xC0

#define ARDUCHIP_TRIG      		0x41  //Trigger source
#define VSYNC_MASK         		0x01
#define SHUTTER_MASK       		0x02
#define CAP_DONE_MASK      		0x08


#define FIFO_SIZE1				0x42  //Camera write FIFO size[7:0] for burst to read
#define FIFO_SIZE2				0x43  //Camera write FIFO size[15:8]
#define FIFO_SIZE3				0x44  //Camera write FIFO size[18:16]

/****************************************************/


/****************************************************************/
/* define a structure for sensor register initialization values */
/****************************************************************/

int arducam(sensor_model_t model,int SPI_CS1, int SPI_CS2, int SPI_CS3, int SPI_CS4);
void arducam_init();

void arducam_flush_fifo(int SPI_CS);
void arducam_start_capture(int SPI_CS);
void arducam_clear_fifo_flag(int SPI_CS);
uint8_t arducam_read_fifo(int SPI_CS);
uint8_t arducam_burst_read_fifo();
void set_fifo_burst(uint8_t data);
void arducam_transfers(uint8_t *buf, uint32_t size);

uint8_t arducam_read_reg(uint8_t addr, int SPI_CS);

void arducam_write_reg(uint8_t addr, uint8_t data, int SPI_CS);
void arducam_transfer(uint8_t data);
uint32_t read_fifo_length(int SPI_CS);
void arducam_set_jpeg_size(jpeg_size_t size);
void arducam_set_format(image_format_t fmt);
void arducam_OV5642_set_jpeg_size(jpeg_size_t size);

void set_bit(uint8_t addr, uint8_t bit, int SPI_CS);
void clear_bit(uint8_t addr, uint8_t bit, int SPI_CS);



#include "arducam_arch.h"

#endif