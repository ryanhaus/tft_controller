#ifndef TFT_CONSTANTS_H
#define TFT_CONSTANTS_H

#define TFT_RD 16
#define TFT_WR 17
#define TFT_DC 18
#define TFT_CS 19
#define TFT_RST 20

#define TFT_D_LSB 0
#define TFT_D_N 16

#define TFT_WIDTH 320
#define TFT_HEIGHT 240

#define ILI9341_NOP             0x00
#define ILI9341_SWRESET         0x01
#define ILI9341_RDDID           0xD3
#define ILI9341_RDDST           0x09
#define ILI9341_SLPIN           0x10
#define ILI9341_SLPOUT          0x11
#define ILI9341_PTLON           0x12
#define ILI9341_NORON           0x13
#define ILI9341_RDMODE          0x0A
#define ILI9341_RDMADCTL        0x0B
#define ILI9341_RDPIXFMT        0x0C
#define ILI9341_RDIMGFMT        0x0D
#define ILI9341_RDSELFDIAG      0x0F
#define ILI9341_INVOFF          0x20
#define ILI9341_INVON           0x21
#define ILI9341_GAMMASET        0x26
#define ILI9341_DISPOFF         0x28
#define ILI9341_DISPON          0x29
#define ILI9341_CASET           0x2A
#define ILI9341_PASET           0x2B
#define ILI9341_RAMWR           0x2C
#define ILI9341_RAMRD           0x2E
#define ILI9341_PTLAR           0x30
#define ILI9341_MADCTL          0x36
#define ILI9341_PIXFMT          0x3A
#define ILI9341_FRMCTR1         0xB1
#define ILI9341_FRMCTR2         0xB2
#define ILI9341_FRMCTR3         0xB3
#define ILI9341_INVCTR          0xB4
#define ILI9341_DFUNCTR         0xB6
#define ILI9341_PWCTR1          0xC0
#define ILI9341_PWCTR2          0xC1
#define ILI9341_PWCTR3          0xC2
#define ILI9341_PWCTR4          0xC3
#define ILI9341_PWCTR5          0xC4
#define ILI9341_VMCTR1          0xC5
#define ILI9341_VMCTR2          0xC7
#define ILI9341_RDID1           0xDA
#define ILI9341_RDID2           0xDB
#define ILI9341_RDID3           0xDC
#define ILI9341_RDID4           0xDD
#define ILI9341_GMCTRP1         0xE0
#define ILI9341_GMCTRN1         0xE1

// format: [# args / delay], [cmd], [args..]
// if the # args is 0x1NN (where NN would be the number of arguments, i.e. 00), then a 100ms delay should occur after its execution
const uint16_t STARTUP_SEQUENCE[] = {
    3,              0xEF,           0x03, 0x80, 0x02,
    3,              0xCF,           0x00, 0xC1, 0x30,
    4,              0xED,           0x64, 0x03, 0x12, 0x81,
    3,              0xE8,           0x85, 0x00, 0x78,
    5,              0xCB,           0x39, 0x2C, 0x00, 0x34, 0x02,
    1,              0xF7,           0x20,
    2,              0xEA,           0x00, 0x00,
    1,              0xC0,           0x23,
    1,              0xC1,           0x10,
    2,              0xC5,           0x3E, 0x28,
    1,              0xC7,           0x86,
    1,              0x36,           0x48,
    1,              0x3A,           0x55,
    2,              0xB1,           0x00, 0x18,
    3,              0xB6,           0x08, 0x82, 0x27,
    1,              0xF2,           0x00,
    1,              0x26,           0x01,
    15,             0xE0,           0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00,
    15,             0xE1,           0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F,
    0x100,          0x20,           
    0x100,          0x11,           
    0,              0x29,           
    1,              0x36,           0x28,
};

#endif