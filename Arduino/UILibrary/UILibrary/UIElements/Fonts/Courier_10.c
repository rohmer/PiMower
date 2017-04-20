/*******************************************************************************

* name: Courier_10
* family: Courier Prime
* size: 10
* style: Normal
* --------------------------------------
* included characters:  !"#$%&'()*+,-./0123456789:;<=>?\x0040ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
* --------------------------------------
* antialiasing: no
* type: proportional
* encoding: latin1
* unicode bom: no
*
* data block size: 8 bit(s), uint8_t
* RLE compression enabled: no
* conversion type: Monochrome, Edge 128
* bits per pixel: 1
*
* preprocess:
*  main scan direction: top_to_bottom
*  line scan direction: forward
*  inverse: yes
* ------------------------------------------------------------------------------
* Created by a custom template of LCD-Image-Converter for .s.u.m.o.t.o.y. RA8875
* Font template version: 2.0
* Note: Font height should be fixed and all glyps must have the same height!
* ------------------------------------------------------------------------------
*******************************************************************************/

#include "font.h"
#include <stdint.h>

static const uint8_t image_data_Courier_10_0x20[11] = {
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};////character: ' '

static const tImage Courier_10_0x20 = { image_data_Courier_10_0x20,
	6, 11 };//character: ' ' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x21[11] = {
	0x00,
	0x00,
	0x30,
	0x20,
	0x20,
	0x20,
	0x30,
	0x30,
	0x00,
	0x00,
	0x00
};////character: '!'

static const tImage Courier_10_0x21 = { image_data_Courier_10_0x21,
	6, 11 };//character: '!' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x22[11] = {
	0x00,
	0x00,
	0x78,
	0x30,
	0x50,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '"'

static const tImage Courier_10_0x22 = { image_data_Courier_10_0x22,
	6, 11 };//character: '"' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x23[11] = {
	0x00,
	0x28,
	0x28,
	0x7c,
	0x50,
	0xf8,
	0x50,
	0x60,
	0x00,
	0x00,
	0x00
};////character: '#'

static const tImage Courier_10_0x23 = { image_data_Courier_10_0x23,
	6, 11 };//character: '#' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x24[11] = {
	0x00,
	0x00,
	0x20,
	0x78,
	0x68,
	0x30,
	0x68,
	0x78,
	0x20,
	0x00,
	0x00
};////character: '$'

static const tImage Courier_10_0x24 = { image_data_Courier_10_0x24,
	6, 11 };//character: '$' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x25[11] = {
	0x00,
	0x00,
	0xc0,
	0xa8,
	0xd0,
	0x2c,
	0x54,
	0x0c,
	0x00,
	0x00,
	0x00
};////character: '%'

static const tImage Courier_10_0x25 = { image_data_Courier_10_0x25,
	6, 11 };//character: '%' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x26[11] = {
	0x00,
	0x00,
	0x78,
	0x48,
	0x40,
	0x6c,
	0x58,
	0x7c,
	0x00,
	0x00,
	0x00
};////character: '&'

static const tImage Courier_10_0x26 = { image_data_Courier_10_0x26,
	6, 11 };//character: '&' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x27[11] = {
	0x00,
	0x00,
	0x30,
	0x20,
	0x20,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '''

static const tImage Courier_10_0x27 = { image_data_Courier_10_0x27,
	6, 11 };//character: ''' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x28[11] = {
	0x00,
	0x00,
	0x30,
	0x40,
	0x40,
	0x40,
	0x40,
	0x40,
	0x20,
	0x10,
	0x00
};////character: '('

static const tImage Courier_10_0x28 = { image_data_Courier_10_0x28,
	6, 11 };//character: '(' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x29[11] = {
	0x00,
	0x00,
	0x30,
	0x10,
	0x08,
	0x08,
	0x08,
	0x08,
	0x10,
	0x20,
	0x00
};////character: ')'

static const tImage Courier_10_0x29 = { image_data_Courier_10_0x29,
	6, 11 };//character: ')' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x2a[11] = {
	0x00,
	0x00,
	0x20,
	0x68,
	0x30,
	0x50,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '*'

static const tImage Courier_10_0x2a = { image_data_Courier_10_0x2a,
	6, 11 };//character: '*' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x2b[11] = {
	0x00,
	0x00,
	0x10,
	0x10,
	0x7c,
	0x10,
	0x10,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '+'

static const tImage Courier_10_0x2b = { image_data_Courier_10_0x2b,
	6, 11 };//character: '+' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x2c[11] = {
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x30,
	0x20,
	0x00,
	0x00
};////character: ','

static const tImage Courier_10_0x2c = { image_data_Courier_10_0x2c,
	6, 11 };//character: ',' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x2d[11] = {
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x78,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '-'

static const tImage Courier_10_0x2d = { image_data_Courier_10_0x2d,
	6, 11 };//character: '-' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x2e[11] = {
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x30,
	0x30,
	0x00,
	0x00,
	0x00
};////character: '.'

static const tImage Courier_10_0x2e = { image_data_Courier_10_0x2e,
	6, 11 };//character: '.' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x2f[11] = {
	0x00,
	0x00,
	0x08,
	0x10,
	0x10,
	0x20,
	0x20,
	0x40,
	0x40,
	0x00,
	0x00
};////character: '/'

static const tImage Courier_10_0x2f = { image_data_Courier_10_0x2f,
	6, 11 };//character: '/' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x30[11] = {
	0x00,
	0x00,
	0x30,
	0x48,
	0x48,
	0x48,
	0x48,
	0x30,
	0x00,
	0x00,
	0x00
};////character: '0'

static const tImage Courier_10_0x30 = { image_data_Courier_10_0x30,
	6, 11 };//character: '0' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x31[11] = {
	0x00,
	0x00,
	0x30,
	0x50,
	0x10,
	0x10,
	0x10,
	0x7c,
	0x00,
	0x00,
	0x00
};////character: '1'

static const tImage Courier_10_0x31 = { image_data_Courier_10_0x31,
	6, 11 };//character: '1' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x32[11] = {
	0x00,
	0x00,
	0x78,
	0x48,
	0x08,
	0x30,
	0x48,
	0x78,
	0x00,
	0x00,
	0x00
};////character: '2'

static const tImage Courier_10_0x32 = { image_data_Courier_10_0x32,
	6, 11 };//character: '2' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x33[11] = {
	0x00,
	0x00,
	0x78,
	0x48,
	0x30,
	0x08,
	0x08,
	0x70,
	0x00,
	0x00,
	0x00
};////character: '3'

static const tImage Courier_10_0x33 = { image_data_Courier_10_0x33,
	6, 11 };//character: '3' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x34[11] = {
	0x00,
	0x00,
	0x10,
	0x70,
	0x50,
	0xf8,
	0x10,
	0x38,
	0x00,
	0x00,
	0x00
};////character: '4'

static const tImage Courier_10_0x34 = { image_data_Courier_10_0x34,
	6, 11 };//character: '4' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x35[11] = {
	0x00,
	0x00,
	0x78,
	0x40,
	0x70,
	0x08,
	0x08,
	0x70,
	0x00,
	0x00,
	0x00
};////character: '5'

static const tImage Courier_10_0x35 = { image_data_Courier_10_0x35,
	6, 11 };//character: '5' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x36[11] = {
	0x00,
	0x00,
	0x18,
	0x20,
	0x70,
	0x48,
	0x48,
	0x30,
	0x00,
	0x00,
	0x00
};////character: '6'

static const tImage Courier_10_0x36 = { image_data_Courier_10_0x36,
	6, 11 };//character: '6' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x37[11] = {
	0x00,
	0x00,
	0x78,
	0x48,
	0x10,
	0x10,
	0x10,
	0x20,
	0x00,
	0x00,
	0x00
};////character: '7'

static const tImage Courier_10_0x37 = { image_data_Courier_10_0x37,
	6, 11 };//character: '7' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x38[11] = {
	0x00,
	0x00,
	0x78,
	0x48,
	0x30,
	0x48,
	0x48,
	0x30,
	0x00,
	0x00,
	0x00
};////character: '8'

static const tImage Courier_10_0x38 = { image_data_Courier_10_0x38,
	6, 11 };//character: '8' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x39[11] = {
	0x00,
	0x00,
	0x30,
	0x48,
	0x48,
	0x38,
	0x10,
	0x60,
	0x00,
	0x00,
	0x00
};////character: '9'

static const tImage Courier_10_0x39 = { image_data_Courier_10_0x39,
	6, 11 };//character: '9' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x3a[11] = {
	0x00,
	0x00,
	0x00,
	0x30,
	0x30,
	0x00,
	0x30,
	0x30,
	0x00,
	0x00,
	0x00
};////character: ':'

static const tImage Courier_10_0x3a = { image_data_Courier_10_0x3a,
	6, 11 };//character: ':' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x3b[11] = {
	0x00,
	0x00,
	0x00,
	0x30,
	0x30,
	0x00,
	0x00,
	0x30,
	0x20,
	0x00,
	0x00
};////character: ';'

static const tImage Courier_10_0x3b = { image_data_Courier_10_0x3b,
	6, 11 };//character: ';' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x3c[11] = {
	0x00,
	0x00,
	0x00,
	0x08,
	0x70,
	0x40,
	0x38,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '<'

static const tImage Courier_10_0x3c = { image_data_Courier_10_0x3c,
	6, 11 };//character: '<' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x3d[11] = {
	0x00,
	0x00,
	0x00,
	0x00,
	0x78,
	0x00,
	0x78,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '='

static const tImage Courier_10_0x3d = { image_data_Courier_10_0x3d,
	6, 11 };//character: '=' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x3e[11] = {
	0x00,
	0x00,
	0x00,
	0x40,
	0x38,
	0x08,
	0x70,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '>'

static const tImage Courier_10_0x3e = { image_data_Courier_10_0x3e,
	6, 11 };//character: '>' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x3f[11] = {
	0x00,
	0x00,
	0x70,
	0x48,
	0x18,
	0x20,
	0x30,
	0x30,
	0x00,
	0x00,
	0x00
};////character: '?'

static const tImage Courier_10_0x3f = { image_data_Courier_10_0x3f,
	6, 11 };//character: '?' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x40[11] = {
	0x00,
	0x00,
	0x00,
	0x78,
	0x74,
	0xb4,
	0xbc,
	0x80,
	0x70,
	0x00,
	0x00
};////character: '\x0040'

static const tImage Courier_10_0x40 = { image_data_Courier_10_0x40,
	6, 11 };//character: '\x0040' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x41[11] = {
	0x00,
	0x00,
	0x70,
	0x30,
	0x50,
	0x38,
	0x48,
	0xfc,
	0x00,
	0x00,
	0x00
};////character: 'A'

static const tImage Courier_10_0x41 = { image_data_Courier_10_0x41,
	6, 11 };//character: 'A' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x42[11] = {
	0x00,
	0x00,
	0xf8,
	0x48,
	0x78,
	0x48,
	0x48,
	0xf0,
	0x00,
	0x00,
	0x00
};////character: 'B'

static const tImage Courier_10_0x42 = { image_data_Courier_10_0x42,
	6, 11 };//character: 'B' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x43[11] = {
	0x00,
	0x00,
	0x38,
	0x48,
	0x40,
	0x40,
	0x48,
	0x38,
	0x00,
	0x00,
	0x00
};////character: 'C'

static const tImage Courier_10_0x43 = { image_data_Courier_10_0x43,
	6, 11 };//character: 'C' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x44[11] = {
	0x00,
	0x00,
	0xf0,
	0x48,
	0x48,
	0x48,
	0x48,
	0xf0,
	0x00,
	0x00,
	0x00
};////character: 'D'

static const tImage Courier_10_0x44 = { image_data_Courier_10_0x44,
	6, 11 };//character: 'D' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x45[11] = {
	0x00,
	0x00,
	0xf8,
	0x58,
	0x70,
	0x50,
	0x48,
	0xf8,
	0x00,
	0x00,
	0x00
};////character: 'E'

static const tImage Courier_10_0x45 = { image_data_Courier_10_0x45,
	6, 11 };//character: 'E' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x46[11] = {
	0x00,
	0x00,
	0xf8,
	0x58,
	0x70,
	0x50,
	0x40,
	0xe0,
	0x00,
	0x00,
	0x00
};////character: 'F'

static const tImage Courier_10_0x46 = { image_data_Courier_10_0x46,
	6, 11 };//character: 'F' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x47[11] = {
	0x00,
	0x00,
	0x38,
	0x48,
	0x40,
	0x7c,
	0x48,
	0x38,
	0x00,
	0x00,
	0x00
};////character: 'G'

static const tImage Courier_10_0x47 = { image_data_Courier_10_0x47,
	6, 11 };//character: 'G' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x48[11] = {
	0x00,
	0x00,
	0xfc,
	0x48,
	0x78,
	0x48,
	0x48,
	0xfc,
	0x00,
	0x00,
	0x00
};////character: 'H'

static const tImage Courier_10_0x48 = { image_data_Courier_10_0x48,
	6, 11 };//character: 'H' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x49[11] = {
	0x00,
	0x00,
	0x7c,
	0x10,
	0x10,
	0x10,
	0x10,
	0x78,
	0x00,
	0x00,
	0x00
};////character: 'I'

static const tImage Courier_10_0x49 = { image_data_Courier_10_0x49,
	6, 11 };//character: 'I' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x4a[11] = {
	0x00,
	0x00,
	0x7c,
	0x10,
	0x10,
	0x50,
	0x50,
	0x70,
	0x00,
	0x00,
	0x00
};////character: 'J'

static const tImage Courier_10_0x4a = { image_data_Courier_10_0x4a,
	6, 11 };//character: 'J' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x4b[11] = {
	0x00,
	0x00,
	0xec,
	0x48,
	0x70,
	0x50,
	0x48,
	0xec,
	0x00,
	0x00,
	0x00
};////character: 'K'

static const tImage Courier_10_0x4b = { image_data_Courier_10_0x4b,
	6, 11 };//character: 'K' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x4c[11] = {
	0x00,
	0x00,
	0xf0,
	0x40,
	0x40,
	0x48,
	0x48,
	0xf8,
	0x00,
	0x00,
	0x00
};////character: 'L'

static const tImage Courier_10_0x4c = { image_data_Courier_10_0x4c,
	6, 11 };//character: 'L' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x4d[11] = {
	0x00,
	0x00,
	0x48,
	0x48,
	0x78,
	0x68,
	0x48,
	0xfc,
	0x00,
	0x00,
	0x00
};////character: 'M'

static const tImage Courier_10_0x4d = { image_data_Courier_10_0x4d,
	6, 11 };//character: 'M' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x4e[11] = {
	0x00,
	0x00,
	0xdc,
	0x68,
	0x68,
	0x68,
	0x58,
	0xe8,
	0x00,
	0x00,
	0x00
};////character: 'N'

static const tImage Courier_10_0x4e = { image_data_Courier_10_0x4e,
	6, 11 };//character: 'N' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x4f[11] = {
	0x00,
	0x00,
	0x70,
	0x88,
	0x88,
	0x88,
	0x88,
	0x70,
	0x00,
	0x00,
	0x00
};////character: 'O'

static const tImage Courier_10_0x4f = { image_data_Courier_10_0x4f,
	6, 11 };//character: 'O' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x50[11] = {
	0x00,
	0x00,
	0xf0,
	0x48,
	0x48,
	0x70,
	0x40,
	0xe0,
	0x00,
	0x00,
	0x00
};////character: 'P'

static const tImage Courier_10_0x50 = { image_data_Courier_10_0x50,
	6, 11 };//character: 'P' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x51[11] = {
	0x00,
	0x00,
	0x70,
	0x88,
	0x88,
	0x88,
	0x88,
	0x70,
	0x78,
	0x00,
	0x00
};////character: 'Q'

static const tImage Courier_10_0x51 = { image_data_Courier_10_0x51,
	6, 11 };//character: 'Q' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x52[11] = {
	0x00,
	0x00,
	0xf0,
	0x48,
	0x48,
	0x70,
	0x58,
	0xec,
	0x00,
	0x00,
	0x00
};////character: 'R'

static const tImage Courier_10_0x52 = { image_data_Courier_10_0x52,
	6, 11 };//character: 'R' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x53[11] = {
	0x00,
	0x00,
	0x78,
	0x48,
	0x60,
	0x18,
	0x48,
	0x78,
	0x00,
	0x00,
	0x00
};////character: 'S'

static const tImage Courier_10_0x53 = { image_data_Courier_10_0x53,
	6, 11 };//character: 'S' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x54[11] = {
	0x00,
	0x00,
	0x78,
	0x58,
	0x58,
	0x10,
	0x10,
	0x38,
	0x00,
	0x00,
	0x00
};////character: 'T'

static const tImage Courier_10_0x54 = { image_data_Courier_10_0x54,
	6, 11 };//character: 'T' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x55[11] = {
	0x00,
	0x00,
	0xfc,
	0x48,
	0x48,
	0x48,
	0x48,
	0x38,
	0x00,
	0x00,
	0x00
};////character: 'U'

static const tImage Courier_10_0x55 = { image_data_Courier_10_0x55,
	6, 11 };//character: 'U' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x56[11] = {
	0x00,
	0x00,
	0xcc,
	0x48,
	0x48,
	0x50,
	0x30,
	0x30,
	0x00,
	0x00,
	0x00
};////character: 'V'

static const tImage Courier_10_0x56 = { image_data_Courier_10_0x56,
	6, 11 };//character: 'V' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x57[11] = {
	0x00,
	0x00,
	0xcc,
	0x88,
	0xb8,
	0x78,
	0x48,
	0x48,
	0x00,
	0x00,
	0x00
};////character: 'W'

static const tImage Courier_10_0x57 = { image_data_Courier_10_0x57,
	6, 11 };//character: 'W' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x58[11] = {
	0x00,
	0x00,
	0x78,
	0x30,
	0x30,
	0x30,
	0x48,
	0xfc,
	0x00,
	0x00,
	0x00
};////character: 'X'

static const tImage Courier_10_0x58 = { image_data_Courier_10_0x58,
	6, 11 };//character: 'X' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x59[11] = {
	0x00,
	0x00,
	0xcc,
	0x48,
	0x28,
	0x10,
	0x10,
	0x38,
	0x00,
	0x00,
	0x00
};////character: 'Y'

static const tImage Courier_10_0x59 = { image_data_Courier_10_0x59,
	6, 11 };//character: 'Y' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x5a[11] = {
	0x00,
	0x00,
	0x78,
	0x50,
	0x20,
	0x20,
	0x48,
	0x78,
	0x00,
	0x00,
	0x00
};////character: 'Z'

static const tImage Courier_10_0x5a = { image_data_Courier_10_0x5a,
	6, 11 };//character: 'Z' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x5b[11] = {
	0x00,
	0x00,
	0x70,
	0x40,
	0x40,
	0x40,
	0x40,
	0x40,
	0x40,
	0x70,
	0x00
};////character: '['

static const tImage Courier_10_0x5b = { image_data_Courier_10_0x5b,
	6, 11 };//character: '[' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x5c[11] = {
	0x00,
	0x00,
	0x40,
	0x40,
	0x20,
	0x20,
	0x10,
	0x10,
	0x08,
	0x00,
	0x00
};////character: '\'

static const tImage Courier_10_0x5c = { image_data_Courier_10_0x5c,
	6, 11 };//character: '\' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x5d[11] = {
	0x00,
	0x00,
	0x38,
	0x08,
	0x08,
	0x08,
	0x08,
	0x08,
	0x08,
	0x38,
	0x00
};////character: ']'

static const tImage Courier_10_0x5d = { image_data_Courier_10_0x5d,
	6, 11 };//character: ']' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x5e[11] = {
	0x00,
	0x00,
	0x20,
	0x30,
	0x48,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '^'

static const tImage Courier_10_0x5e = { image_data_Courier_10_0x5e,
	6, 11 };//character: '^' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x5f[11] = {
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0xfc,
	0x00
};////character: '_'

static const tImage Courier_10_0x5f = { image_data_Courier_10_0x5f,
	6, 11 };//character: '_' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x60[11] = {
	0x00,
	0x40,
	0x30,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '`'

static const tImage Courier_10_0x60 = { image_data_Courier_10_0x60,
	6, 11 };//character: '`' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x61[11] = {
	0x00,
	0x00,
	0x00,
	0x78,
	0x08,
	0x78,
	0x48,
	0x7c,
	0x00,
	0x00,
	0x00
};////character: 'a'

static const tImage Courier_10_0x61 = { image_data_Courier_10_0x61,
	6, 11 };//character: 'a' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x62[11] = {
	0x00,
	0x00,
	0xc0,
	0x70,
	0x48,
	0x48,
	0x48,
	0xf0,
	0x00,
	0x00,
	0x00
};////character: 'b'

static const tImage Courier_10_0x62 = { image_data_Courier_10_0x62,
	6, 11 };//character: 'b' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x63[11] = {
	0x00,
	0x00,
	0x00,
	0x38,
	0x48,
	0x40,
	0x48,
	0x38,
	0x00,
	0x00,
	0x00
};////character: 'c'

static const tImage Courier_10_0x63 = { image_data_Courier_10_0x63,
	6, 11 };//character: 'c' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x64[11] = {
	0x00,
	0x00,
	0x18,
	0x08,
	0x38,
	0x48,
	0x48,
	0x3c,
	0x00,
	0x00,
	0x00
};////character: 'd'

static const tImage Courier_10_0x64 = { image_data_Courier_10_0x64,
	6, 11 };//character: 'd' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x65[11] = {
	0x00,
	0x00,
	0x00,
	0x30,
	0x48,
	0x78,
	0x40,
	0x3c,
	0x00,
	0x00,
	0x00
};////character: 'e'

static const tImage Courier_10_0x65 = { image_data_Courier_10_0x65,
	6, 11 };//character: 'e' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x66[11] = {
	0x00,
	0x00,
	0x38,
	0x24,
	0x78,
	0x20,
	0x20,
	0x78,
	0x00,
	0x00,
	0x00
};////character: 'f'

static const tImage Courier_10_0x66 = { image_data_Courier_10_0x66,
	6, 11 };//character: 'f' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x67[11] = {
	0x00,
	0x00,
	0x00,
	0x3c,
	0x48,
	0x48,
	0x48,
	0x38,
	0x08,
	0x70,
	0x00
};////character: 'g'

static const tImage Courier_10_0x67 = { image_data_Courier_10_0x67,
	6, 11 };//character: 'g' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x68[11] = {
	0x00,
	0x00,
	0xc0,
	0x58,
	0x68,
	0x48,
	0x48,
	0xfc,
	0x00,
	0x00,
	0x00
};////character: 'h'

static const tImage Courier_10_0x68 = { image_data_Courier_10_0x68,
	6, 11 };//character: 'h' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x69[11] = {
	0x00,
	0x20,
	0x20,
	0x60,
	0x20,
	0x20,
	0x20,
	0xf8,
	0x00,
	0x00,
	0x00
};////character: 'i'

static const tImage Courier_10_0x69 = { image_data_Courier_10_0x69,
	6, 11 };//character: 'i' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x6a[11] = {
	0x00,
	0x10,
	0x10,
	0x70,
	0x10,
	0x10,
	0x10,
	0x10,
	0x10,
	0xf0,
	0x00
};////character: 'j'

static const tImage Courier_10_0x6a = { image_data_Courier_10_0x6a,
	6, 11 };//character: 'j' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x6b[11] = {
	0x00,
	0x00,
	0xc0,
	0x58,
	0x50,
	0x60,
	0x50,
	0xec,
	0x00,
	0x00,
	0x00
};////character: 'k'

static const tImage Courier_10_0x6b = { image_data_Courier_10_0x6b,
	6, 11 };//character: 'k' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x6c[11] = {
	0x00,
	0x00,
	0x60,
	0x20,
	0x20,
	0x20,
	0x20,
	0xf8,
	0x00,
	0x00,
	0x00
};////character: 'l'

static const tImage Courier_10_0x6c = { image_data_Courier_10_0x6c,
	6, 11 };//character: 'l' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x6d[11] = {
	0x00,
	0x00,
	0x00,
	0xfc,
	0x54,
	0x54,
	0x54,
	0xfe,
	0x00,
	0x00,
	0x00
};////character: 'm'

static const tImage Courier_10_0x6d = { image_data_Courier_10_0x6d,
	7, 11 };//character: 'm' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x6e[11] = {
	0x00,
	0x00,
	0x00,
	0xf8,
	0x48,
	0x48,
	0x48,
	0xfc,
	0x00,
	0x00,
	0x00
};////character: 'n'

static const tImage Courier_10_0x6e = { image_data_Courier_10_0x6e,
	6, 11 };//character: 'n' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x6f[11] = {
	0x00,
	0x00,
	0x00,
	0x30,
	0x48,
	0x48,
	0x48,
	0x30,
	0x00,
	0x00,
	0x00
};////character: 'o'

static const tImage Courier_10_0x6f = { image_data_Courier_10_0x6f,
	6, 11 };//character: 'o' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x70[11] = {
	0x00,
	0x00,
	0x00,
	0xf0,
	0x48,
	0x48,
	0x48,
	0x70,
	0x40,
	0xe0,
	0x00
};////character: 'p'

static const tImage Courier_10_0x70 = { image_data_Courier_10_0x70,
	6, 11 };//character: 'p' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x71[11] = {
	0x00,
	0x00,
	0x00,
	0x3c,
	0x48,
	0x48,
	0x48,
	0x38,
	0x08,
	0x1c,
	0x00
};////character: 'q'

static const tImage Courier_10_0x71 = { image_data_Courier_10_0x71,
	6, 11 };//character: 'q' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x72[11] = {
	0x00,
	0x00,
	0x00,
	0x6c,
	0x30,
	0x20,
	0x20,
	0x78,
	0x00,
	0x00,
	0x00
};////character: 'r'

static const tImage Courier_10_0x72 = { image_data_Courier_10_0x72,
	6, 11 };//character: 'r' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x73[11] = {
	0x00,
	0x00,
	0x00,
	0x78,
	0x48,
	0x38,
	0x48,
	0x78,
	0x00,
	0x00,
	0x00
};////character: 's'

static const tImage Courier_10_0x73 = { image_data_Courier_10_0x73,
	6, 11 };//character: 's' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x74[11] = {
	0x00,
	0x00,
	0x20,
	0x20,
	0x78,
	0x20,
	0x24,
	0x38,
	0x00,
	0x00,
	0x00
};////character: 't'

static const tImage Courier_10_0x74 = { image_data_Courier_10_0x74,
	6, 11 };//character: 't' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x75[11] = {
	0x00,
	0x00,
	0x00,
	0xd8,
	0x48,
	0x48,
	0x48,
	0x7c,
	0x00,
	0x00,
	0x00
};////character: 'u'

static const tImage Courier_10_0x75 = { image_data_Courier_10_0x75,
	6, 11 };//character: 'u' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x76[11] = {
	0x00,
	0x00,
	0x00,
	0xcc,
	0x48,
	0x50,
	0x30,
	0x30,
	0x00,
	0x00,
	0x00
};////character: 'v'

static const tImage Courier_10_0x76 = { image_data_Courier_10_0x76,
	6, 11 };//character: 'v' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x77[11] = {
	0x00,
	0x00,
	0x00,
	0xcc,
	0xa8,
	0x78,
	0x78,
	0x48,
	0x00,
	0x00,
	0x00
};////character: 'w'

static const tImage Courier_10_0x77 = { image_data_Courier_10_0x77,
	6, 11 };//character: 'w' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x78[11] = {
	0x00,
	0x00,
	0x00,
	0xfc,
	0x30,
	0x10,
	0x68,
	0xfc,
	0x00,
	0x00,
	0x00
};////character: 'x'

static const tImage Courier_10_0x78 = { image_data_Courier_10_0x78,
	6, 11 };//character: 'x' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x79[11] = {
	0x00,
	0x00,
	0x00,
	0xcc,
	0x48,
	0x50,
	0x30,
	0x20,
	0x20,
	0xc0,
	0x00
};////character: 'y'

static const tImage Courier_10_0x79 = { image_data_Courier_10_0x79,
	6, 11 };//character: 'y' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x7a[11] = {
	0x00,
	0x00,
	0x00,
	0x78,
	0x50,
	0x20,
	0x48,
	0x78,
	0x00,
	0x00,
	0x00
};////character: 'z'

static const tImage Courier_10_0x7a = { image_data_Courier_10_0x7a,
	6, 11 };//character: 'z' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x7b[11] = {
	0x00,
	0x00,
	0x30,
	0x20,
	0x20,
	0x40,
	0x20,
	0x20,
	0x20,
	0x30,
	0x00
};////character: '{'

static const tImage Courier_10_0x7b = { image_data_Courier_10_0x7b,
	6, 11 };//character: '{' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x7c[11] = {
	0x00,
	0x00,
	0x20,
	0x20,
	0x20,
	0x20,
	0x20,
	0x20,
	0x20,
	0x20,
	0x00
};////character: '|'

static const tImage Courier_10_0x7c = { image_data_Courier_10_0x7c,
	6, 11 };//character: '|' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x7d[11] = {
	0x00,
	0x00,
	0x30,
	0x10,
	0x10,
	0x08,
	0x10,
	0x10,
	0x10,
	0x20,
	0x00
};////character: '}'

static const tImage Courier_10_0x7d = { image_data_Courier_10_0x7d,
	6, 11 };//character: '}' , height: 11, (charW,total bytes)

static const uint8_t image_data_Courier_10_0x7e[11] = {
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x78,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
};////character: '~'

static const tImage Courier_10_0x7e = { image_data_Courier_10_0x7e,
	6, 11 };//character: '~' , height: 11, (charW,total bytes)

static const tChar Courier_10_array[] = {
	// character: ' '
	{0x20, &Courier_10_0x20},
	// character: '!'
	{0x21, &Courier_10_0x21},
	// character: '"'
	{0x22, &Courier_10_0x22},
	// character: '#'
	{0x23, &Courier_10_0x23},
	// character: '$'
	{0x24, &Courier_10_0x24},
	// character: '%'
	{0x25, &Courier_10_0x25},
	// character: '&'
	{0x26, &Courier_10_0x26},
	// character: '''
	{0x27, &Courier_10_0x27},
	// character: '('
	{0x28, &Courier_10_0x28},
	// character: ')'
	{0x29, &Courier_10_0x29},
	// character: '*'
	{0x2a, &Courier_10_0x2a},
	// character: '+'
	{0x2b, &Courier_10_0x2b},
	// character: ','
	{0x2c, &Courier_10_0x2c},
	// character: '-'
	{0x2d, &Courier_10_0x2d},
	// character: '.'
	{0x2e, &Courier_10_0x2e},
	// character: '/'
	{0x2f, &Courier_10_0x2f},
	// character: '0'
	{0x30, &Courier_10_0x30},
	// character: '1'
	{0x31, &Courier_10_0x31},
	// character: '2'
	{0x32, &Courier_10_0x32},
	// character: '3'
	{0x33, &Courier_10_0x33},
	// character: '4'
	{0x34, &Courier_10_0x34},
	// character: '5'
	{0x35, &Courier_10_0x35},
	// character: '6'
	{0x36, &Courier_10_0x36},
	// character: '7'
	{0x37, &Courier_10_0x37},
	// character: '8'
	{0x38, &Courier_10_0x38},
	// character: '9'
	{0x39, &Courier_10_0x39},
	// character: ':'
	{0x3a, &Courier_10_0x3a},
	// character: ';'
	{0x3b, &Courier_10_0x3b},
	// character: '<'
	{0x3c, &Courier_10_0x3c},
	// character: '='
	{0x3d, &Courier_10_0x3d},
	// character: '>'
	{0x3e, &Courier_10_0x3e},
	// character: '?'
	{0x3f, &Courier_10_0x3f},
	// character: '\x0040'
	{0x40, &Courier_10_0x40},
	// character: 'A'
	{0x41, &Courier_10_0x41},
	// character: 'B'
	{0x42, &Courier_10_0x42},
	// character: 'C'
	{0x43, &Courier_10_0x43},
	// character: 'D'
	{0x44, &Courier_10_0x44},
	// character: 'E'
	{0x45, &Courier_10_0x45},
	// character: 'F'
	{0x46, &Courier_10_0x46},
	// character: 'G'
	{0x47, &Courier_10_0x47},
	// character: 'H'
	{0x48, &Courier_10_0x48},
	// character: 'I'
	{0x49, &Courier_10_0x49},
	// character: 'J'
	{0x4a, &Courier_10_0x4a},
	// character: 'K'
	{0x4b, &Courier_10_0x4b},
	// character: 'L'
	{0x4c, &Courier_10_0x4c},
	// character: 'M'
	{0x4d, &Courier_10_0x4d},
	// character: 'N'
	{0x4e, &Courier_10_0x4e},
	// character: 'O'
	{0x4f, &Courier_10_0x4f},
	// character: 'P'
	{0x50, &Courier_10_0x50},
	// character: 'Q'
	{0x51, &Courier_10_0x51},
	// character: 'R'
	{0x52, &Courier_10_0x52},
	// character: 'S'
	{0x53, &Courier_10_0x53},
	// character: 'T'
	{0x54, &Courier_10_0x54},
	// character: 'U'
	{0x55, &Courier_10_0x55},
	// character: 'V'
	{0x56, &Courier_10_0x56},
	// character: 'W'
	{0x57, &Courier_10_0x57},
	// character: 'X'
	{0x58, &Courier_10_0x58},
	// character: 'Y'
	{0x59, &Courier_10_0x59},
	// character: 'Z'
	{0x5a, &Courier_10_0x5a},
	// character: '['
	{0x5b, &Courier_10_0x5b},
	// character: '\'
	{0x5c, &Courier_10_0x5c},
	// character: ']'
	{0x5d, &Courier_10_0x5d},
	// character: '^'
	{0x5e, &Courier_10_0x5e},
	// character: '_'
	{0x5f, &Courier_10_0x5f},
	// character: '`'
	{0x60, &Courier_10_0x60},
	// character: 'a'
	{0x61, &Courier_10_0x61},
	// character: 'b'
	{0x62, &Courier_10_0x62},
	// character: 'c'
	{0x63, &Courier_10_0x63},
	// character: 'd'
	{0x64, &Courier_10_0x64},
	// character: 'e'
	{0x65, &Courier_10_0x65},
	// character: 'f'
	{0x66, &Courier_10_0x66},
	// character: 'g'
	{0x67, &Courier_10_0x67},
	// character: 'h'
	{0x68, &Courier_10_0x68},
	// character: 'i'
	{0x69, &Courier_10_0x69},
	// character: 'j'
	{0x6a, &Courier_10_0x6a},
	// character: 'k'
	{0x6b, &Courier_10_0x6b},
	// character: 'l'
	{0x6c, &Courier_10_0x6c},
	// character: 'm'
	{0x6d, &Courier_10_0x6d},
	// character: 'n'
	{0x6e, &Courier_10_0x6e},
	// character: 'o'
	{0x6f, &Courier_10_0x6f},
	// character: 'p'
	{0x70, &Courier_10_0x70},
	// character: 'q'
	{0x71, &Courier_10_0x71},
	// character: 'r'
	{0x72, &Courier_10_0x72},
	// character: 's'
	{0x73, &Courier_10_0x73},
	// character: 't'
	{0x74, &Courier_10_0x74},
	// character: 'u'
	{0x75, &Courier_10_0x75},
	// character: 'v'
	{0x76, &Courier_10_0x76},
	// character: 'w'
	{0x77, &Courier_10_0x77},
	// character: 'x'
	{0x78, &Courier_10_0x78},
	// character: 'y'
	{0x79, &Courier_10_0x79},
	// character: 'z'
	{0x7a, &Courier_10_0x7a},
	// character: '{'
	{0x7b, &Courier_10_0x7b},
	// character: '|'
	{0x7c, &Courier_10_0x7c},
	// character: '}'
	{0x7d, &Courier_10_0x7d},
	// character: '~'
	{0x7e, &Courier_10_0x7e}
};

//num chars, array, width, height, compression

const tFont Courier_10 = { 95, Courier_10_array,0,11,0 };