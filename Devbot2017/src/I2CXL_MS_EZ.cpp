/*
 * I2CXL_MS_EZ.cpp
 *
 *  Created on: Feb 8, 2017
 *      Author: mdbal
 */

#include <I2CXL_MS_EZ.h>

using MaxSonar;

I2CXL_EZ::I2CXL_EZ(uint8_t address, enum frc::I2C::Port port) : _wire(port, address)
{
	_address = address;
	_port = port;
	_byte1 = 0;
	_byte2 = 0;
}

I2CXL_EZ::~I2CXL_EZ()
{

}

void I2CXL_EZ::TakeMeasurement()
{
	uint8_t cmd[2];
	cmd[0] = _address;
	cmd[1] = I2CXLMSEZ_RANGE_CMD;
	Send(&cmd, 2);
};

uint16_t I2CXL_EZ::GetLastRange()
{
	uint8_t cmd = _address | 0x01;
	Send(&cmd,1);
	return GetWord();
};


bool I2CXL_EZ::ChangeAddress(uint8_t toAddress)
{
	// Reject invalid addresses.
	if ((toAddress == 0) || (toAddress == 80) || (toAddress == 164) || (toAddress == 170)) return false;
	if ((toAddress % 2) != 0) return false;

	uint8_t cmd[4];
	cmd[0] = _address;
	cmd[1] = I2CXLMSEZ_ADDRESS_UNLOCK1;
	cmd[2] = I2CXLMSEZ_ADDRESS_UNLOCK2;
	cmd[3] = toAddress;
	Send(&cmd,4);
	return true;
};

uint16_t I2CXL_EZ::GetWord()
{
	_wire.ReadOnly(1,&_byte1);
	_wire.ReadOnly(1,&_byte2);

    uint16_t w = (_byte2 << 8) + _byte1;
    return w;
}

uint8_t I2CXL_EZ::GetByte()
{
	_wire.ReadOnly(1,&_byte1);
	return _byte1;
}

int8_t I2CXL_EZ::Send(uint8_t *data, uint8_t len)
{
    _wire.WriteBulk(data, len);
    return len;
}

