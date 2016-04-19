/*
 * cs5463_spi.h
 *
 *  Created on: Jun 23, 2014
 *      Author: victoria
 */

#ifndef CS5463_SPI_H_
#define CS5463_SPI_H_


#include <sstream>
#include <stdint.h>
#include <math.h>
#include <vector>
#include <string>
#include "spi.h"
using namespace std;

/**
 * CS5463 registers names and addresses
 */

typedef struct {
	static const uint8_t CONF = 0x00;   // configuration address
	static const uint8_t I_DC_OFF = 0x02;
	static const uint8_t I_GAIN = 0x04;
	static const uint8_t V_DC_OFF = 0x06;
	static const uint8_t v_GN = 0x08;
	static const uint8_t CYC_CNT = 0x10;
	static const uint8_t PUL_RA = 0x12;
	static const uint8_t I_INS = 0x14;
	static const uint8_t V_INS = 0x16;
	static const uint8_t P_INS = 0x18;
	static const uint8_t TEMP = 0x26;
	static const uint8_t STATUS = 0x1E;

}RegReadCmd;

typedef struct {
	static const uint8_t CONF = 0x40;
	static const uint8_t STATUS = 0x5E;
	static const uint8_t MASK = 0x74;

}RegWrCmd;

typedef struct {
	static const uint8_t T_GAIN = 0x68;
	static const uint8_t T_OFF = 0x70;

}cs5463RegAddPg1;

/**
 * CS5463 commands
 */

typedef struct {
static const uint8_t SING_CONV = 0xE0;  // Single convertion
static const uint8_t CONT_CONV = 0xE8; // continous convertion
static const uint8_t SYNC_0 = 0xFE;    // sync 0 command
static const uint8_t SYNC_1 = 0xFF;    // sync 1 command
static const uint8_t PW_UP_HALT = 0xA0;
static const uint8_t SW_RESET = 0x80;  // Software reset
static const uint8_t PW_DWN_1 = 0x88;  // Halt and enter stand-by power saving state
static const uint8_t PW_DWN_2 = 0x90;  // Halt and enter sleep power saving state
static const uint8_t PW_DWN_3 = 0x98;  // Reserved

}cs5463Commands;

/**
 * CS5463 local spi parameters.
 */

typedef struct {
 static const uint8_t BIT_ORDER = 0;  	// send MSB first
 static const uint8_t MODE_0 = 0; 		//mode 0, clock active high & data write on clock rising edge.
 static const uint8_t MODE_1 = 1; 		// mode 1, clock active high & data read on clock falling edge.
 static const uint8_t BPW = 8;			// bit per words
 static const uint32_t MAX_FREQ = 2000000; // Max Freq 2 MHZ.

}cs5463spiParams;

/**
 * CS5463 electricity attributes.
 */
typedef struct {

	uint8_t AvgPower;
	uint8_t Irms;
	uint8_t Vrms;
	uint8_t AppPw;
	uint8_t Ipeak;
	uint8_t Vpeak;
	uint8_t TrigReactPw;
	uint8_t PwFact;
	uint8_t HarmPw;
	uint8_t FundActPw;
	uint8_t FundReactPw;
	uint8_t AvgReactPw;
}cs5463ElectricityAttr;


/**
 * Class that defines the functionalities of CS5463. It derives from the spi class
 */

class cs5463spi : public spi {

public:
	cs5463spi();

	virtual ~cs5463spi(){}
	void Run();

protected:
	void SerialPortInit();
	void SerialPortReInit();
	void spiInit();

private:
	int WriteRegister(uint8_t cmd, uint8_t highByte,
			           uint8_t midByte, uint8_t lowByte);
	int ReadRegister(uint8_t cmd, uint8_t* pRxed);
	void sendCmd(uint8_t cmd);
	//void StartConvertion(uint8_t startCmd);
	void setPage(uint8_t pg);
	void SwReset();
	void PowerDown(uint8_t pwCmd);
	void Sync(uint8_t syncType);


	bool InterruptHandlerInit(bool DRDY);
	bool DisableInterrupts();
	void InterruptHandler();

	void CheckStatus(uint8_t* status);
	bool CheckStatusReady(uint8_t byte, int bit);

	cs5463ElectricityAttr getReadValues(){return m_electricityAttr;}
	void setModeSpi(uint8_t wrMode, uint8_t rdMode);

	uint32_t make32(uint8_t var1, uint8_t var2, uint8_t var3, uint8_t var4);



private:
	RegReadCmd    			m_regReadCmd;
	RegWrCmd				m_regWrCmd;
	cs5463Commands     		m_cmds;
	cs5463ElectricityAttr   m_electricityAttr;
	cs5463spiParams	   		m_spiParams;

	std::vector<std::string> m_statusWarn;

	enum {ic_not, fup, lsd, iod, vod,tod=6, tup,
		vsag=10, ifault, eor, vror, iror, vor=16,
		ior, crdy=20, drdy=23};


	uint8_t  m_rxBuf[2];

};

extern "C" spi* create(){
	return new cs5463spi;
}

extern "C" void destroy(spi* p) {
	delete p;
}

#endif /* CS5463_SPI_H_ */
