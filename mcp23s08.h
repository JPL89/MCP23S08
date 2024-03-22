// @File		MCP23S08.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		21/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef MCP23S08_H
#define MCP23S08_H

#define MCP23S08_SCK PORTCbits.RC0
#define MCP23S08_SDI PORTCbits.RC1
#define MCP23S08_SDO PORTCbits.RC2
#define MCP23S08_CS PORTCbits.RC3

#define MCP23S08_SCK_TRIS TRISCbits.RC0
#define MCP23S08_SDI_TRIS TRISCbits.RC1
#define MCP23S08_SDO_TRIS TRISCbits.RC2
#define MCP23S08_CS_TRIS TRISCbits.RC3

#define MCP23S08_IODIR 0x00
#define MCP23S08_IPOL 0x01
#define MCP23S08_GPINTEN 0x02
#define MCP23S08_DEFVAL 0x03
#define MCP23S08_INTCON 0x04
#define MCP23S08_IOCON 0x05
#define MCP23S08_GPPU 0x06
#define MCP23S08_INTF 0x07
#define MCP23S08_INTCAP 0x08
#define MCP23S08_GPIO 0x09
#define MCP23S08_OLAT 0x0A

void SPI_write(unsigned char data)
{
    for(unsigned char mask = 0x80; mask; mask >>=1)
    {
        if(data & mask) MCP23S08_SDI = 1; else MCP23S08_SDI = 0;
        
        MCP23S08_SCK = 1;
        __asm__ __volatile__("nop");
        MCP23S08_SCK = 0;        
        __asm__ __volatile__("nop");
    }
}

void MCP23S08_write(unsigned char reg, unsigned char data)
{
    MCP23S08_CS = 0;
    SPI_write(0x40);
    SPI_write(reg);
    SPI_write(data);
    MCP23S08_CS = 1;
}

void MCP23S08_init(void)
{
    MCP23S08_SCK_TRIS = 0;
    MCP23S08_SDI_TRIS = 0;
    MCP23S08_SDO_TRIS = 1;
    MCP23S08_CS_TRIS = 0;
    
    MCP23S08_CS = 1;
}

#endif
