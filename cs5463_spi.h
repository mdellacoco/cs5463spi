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
#include <bitset>
#include <iomanip>
#include <iostream>
#include "spi.h"
using namespace std;

/**
 * CS5463 Page 0 Register Addresses
 */

typedef struct {
	static const uint8_t CONF 		= 0;   	// Configuration
	static const uint8_t I_DC_OFF 	= 1;   	// Current DC Offset
	static const uint8_t I_GAIN 	= 2;   	// Current Gain
	static const uint8_t V_DC_OFF 	= 3;   	// Voltage DC Offset
	static const uint8_t V_GAIN 	= 4;   	// Voltage Gain
	static const uint8_t CYCLE_CNT 	= 5;	// Cycle Count
	static const uint8_t PULSE_RATE = 6;	// Pulse Rate E
	static const uint8_t I_INS 		= 7;	// Instantaneous Current
	static const uint8_t V_INS 		= 8;	// Instantaneous Voltage
	static const uint8_t P_INS 		= 9;	// Instantaneous Power
	static const uint8_t P_ACT 		= 10; 	// Active real power
	static const uint8_t I_RMS 		= 11;	// RMS Current
	static const uint8_t V_RMS 		= 12;	// RMS Voltage
	static const uint8_t EPSILON	= 13;	// OWR
	static const uint8_t POWER_OFF	= 14;	// Power Offset
	static const uint8_t STATUS		= 15;	// Status
	static const uint8_t I_AC_OFF 	= 16;  	// Current AC (RMS) Offset
    static const uint8_t V_AC_OFF 	= 17;  	// Voltage AC (RMS) Offset
    static const uint8_t MODE 		= 18;	// Mode
	static const uint8_t TEMP 		= 19;	// Temperature
	static const uint8_t Q_AVG		= 20;	// Average Reactive Power
    static const uint8_t Q			= 21;	// Instantaneous Reactive Power
	static const uint8_t I_PEAK 	= 22;	// Peak Current
	static const uint8_t V_PEAK 	= 23;	// Peak Voltage
	static const uint8_t Q_TRIG		= 24;	// Reactive Power calculated from Power Triangle
	static const uint8_t PF			= 25;	// Power factor
	static const uint8_t MASK		= 26;	// Interrupt Mask
	static const uint8_t S			= 27;	// Apparent Power
	static const uint8_t CTRL		= 28;	// Control
	static const uint8_t P_H		= 29;	// Harmonic Active Power
	static const uint8_t P_F		= 30;	// Fundamental Active Power
	static const uint8_t Q_F 		= 31;	// Fundamental Reactive Power

}CS5463RegPage_0;

/**
 * CS5463 Page 1 Registers Addresses
 *
 */

typedef struct {
	static const uint8_t PULSE_WIDTH 	= 0; // Energy Pulse Output Width
	static const uint8_t LOAD_MIN 		= 1; // No Load Threshold
	static const uint8_t TEMP_GAIN		= 2; // Temperature Gain
	static const uint8_t TEMP_OFF		= 3; // Temperature Sensor Offset

}CS5463RegPage_1;

/**
 * CS5463 Page 3 Registers
 *
 */

typedef struct {
	static const uint8_t V_SAG_DURATION		= 6; //Voltage Sag Sample Interval
	static const uint8_t V_SAG_LEVEL		= 7; //Voltage Sag level
	static const uint8_t I_SAG_DURATION		= 10; //Current fault sample interval
	static const uint8_t I_SAG_LEVEL		= 11; //Current fault level

}CS5463RegPage_3;


/**
 * Structure to define a range, min to max.
 */

typedef struct{
	float min;
	float max;
}ValRange;



/**
 * CS5463 Commands
 */

typedef struct {
static const uint8_t SING_CONV 	= 0xE0;  	// Single convertion
static const uint8_t CONT_CONV 	= 0xE8; 	// Continous convertion
static const uint8_t SYNC_0 	= 0xFE;    	// Sync 0 command
static const uint8_t SYNC_1 	= 0xFF;    	// Sync 1 command
static const uint8_t PW_UP_HALT = 0xA0;		// Power-up/Halt
static const uint8_t SW_RESET 	= 0x80;  	// Software reset
static const uint8_t PW_DWN_1 	= 0x88;  	// Halt and enter stand-by power saving state
static const uint8_t PW_DWN_2 	= 0x90;  	// Halt and enter sleep power saving state
static const uint8_t PW_DWN_3 	= 0x98;  	// Reserved

}cs5463Commands;

/**
 * CS5463 spi parameters.
 */
//TODO: This is temporarely to set cs5463 .. but should be removed once all working well.
typedef struct {
 static const uint8_t BIT_ORDER = 0;  		// send MSB first
 static const uint8_t MODE_0 	= 0; 		//mode 0, clock active high & data write on clock rising edge.
 static const uint8_t MODE_1 	= 1; 		// mode 1, clock active high & data read on clock falling edge.
 static const uint8_t BPW 		= 8;		// bit per words
 static const uint32_t MAX_FREQ = 2000000; 	// Max Freq 2 MHZ.

}cs5463spiParams;

/**
 * CS5463 Commands: System Calibrations
 */

typedef struct {
	static const uint8_t I_CHAN_DC_OFFSET 	= 0xC9;
	static const uint8_t V_CHAN_DC_OFFSET 	= 0xD1;
	static const uint8_t I_AND_V_DC_OFFSET 	= 0xD9;
	static const uint8_t I_CHAN_AC_OFFSET 	= 0xCD;
	static const uint8_t V_CHAN_AC_OFFSET 	= 0xD5;
	static const uint8_t I_AND_V_AC_OFFSET 	= 0xDD;
}cs5463sysCalOffsetVals;

typedef struct{
		static const uint8_t I_CHAN_DC_GAIN 	= 0xCA;
		static const uint8_t V_CHAN_DC_GAIN 	= 0xD2;
		static const uint8_t I_AND_V_DC_GAIN 	= 0xDA;
		static const uint8_t I_CHAN_AC_GAIN 	= 0xC3;
		static const uint8_t V_CHAN_AC_GAIN 	= 0xD6;
		static const uint8_t I_AND_V_AC_GAIN 	= 0xDE;
}cs5463sysCalGainVals;

/**
 * CS5463 Electricity Parameters
 */


typedef struct {
	uint8_t highByte;
	uint8_t midByte;
	uint8_t lowByte;
}RegValueHex;

typedef struct{
	static const int NOT_DEFINED 	= 0; // not defined
	static const int UBN   			= 1; // Unsigned binary notation
	static const int TwosCN 		= 2; // 2s Complement Notation
	static const int Int			= 3; // integer
}CS5463Notation;

/**
 *  A CS5463 Number is a multi dimensional entity that contains all attributes used to
 *  define a CS5463 Register: its address, the number notation type capable of holding, its default
 *  value in hex, its default value in decimal, the allowed range of values in decimal, the actual
 *  read decimal value and its human readable name. The "not-defined" number notation type is used
 *  to represent values within registers for configuration and controlling purposes only.
 */

typedef struct {
	uint8_t 	addr;			// register address
	int 		notationType;	// the number notation type: not_defined, 2s Complement, unsigned binary
	RegValueHex defaultValHex;  // default value in hexadecimal: composed of 3 bytes (uint8_t)
	float		defaultValDec;	// default value in decimal
	ValRange 	range;			// Permissible decimal range: defines a min and max numbers.
	std::string name;           // The register name description
	uint32_t 	value;			// actual read value.
	double      valueDec;       // Normalised value;
}CS5463Num;

/**
 * A cs5463RegDefPage_0 is a structure that holds all Page 0 CS5463 registers in their defined state.
 *
 */

typedef struct {

	CS5463Num CONFIG;
	CS5463Num I_DC_OFF;
	CS5463Num I_GAIN;
	CS5463Num V_DC_OFF;
	CS5463Num V_GAIN;
	CS5463Num CYCLE_CNT;
	CS5463Num PULSE_RATE;
	CS5463Num I_INS;
	CS5463Num V_INS;
	CS5463Num P_INS;
	CS5463Num P_ACT;
	CS5463Num I_RMS;
	CS5463Num V_RMS;
	CS5463Num EPSILON;
	CS5463Num POWER_OFF;
	CS5463Num STATUS;
	CS5463Num I_AC_OFF;
	CS5463Num V_AC_OFF;
	CS5463Num MODE;
	CS5463Num TEMP;
	CS5463Num Q_AVG;
	CS5463Num Q;
	CS5463Num I_PEAK;
	CS5463Num V_PEAK;
	CS5463Num Q_TRIG;
	CS5463Num PF;
	CS5463Num MASK;
	CS5463Num S;
	CS5463Num CTRL;
	CS5463Num P_H;
	CS5463Num P_F;
	CS5463Num Q_F;
}cs5463RegDefPage_0;

/**
 * A cs5463RegDefPage_1 is a structure that holds all Page 1 CS5463 registers in their defined state.
 *
 */

typedef struct{
	CS5463Num PULSE_WIDTH;
	CS5463Num LOAD_MIN;
	CS5463Num TEMP_GAIN;
	CS5463Num TEMP_OFF;
}cs5463RegDefPage_1;

/**
 * A cs5463RegDefPage_3 is a structure that holds all Page 3 CS5463 registers in their defined state.
 *
 */

typedef struct{
	CS5463Num V_SAG_DURATION;
	CS5463Num V_SAG_LEVEL;
	CS5463Num I_SAG_DURATION;
	CS5463Num I_SAG_LEVEL;
}cs5463RegDefPage_3;

/**
 * Class that defines the functionalities of CS5463.
 * It derives from the spi class
 */

class cs5463spi : public spi {

public:
	cs5463spi();

	virtual ~cs5463spi(){}
	void Run();
	void Calibrate(int calType = 0);

	void SetConfigVal(uint8_t highByte, uint8_t midByte, uint8_t lowByte);
	void SetModeVal(uint8_t highByte, uint8_t midByte, uint8_t lowByte);
	void SetMaskVal(uint8_t highByte, uint8_t midByte, uint8_t lowByte);
	void SetCtrlVal(uint8_t highByte, uint8_t midByte, uint8_t lowByte);
	RegValueHex GetConfigVal(){return m_configVal;}
	RegValueHex GetModeVal(){return m_modeVal;}
	RegValueHex GetMaskVal(){return m_maskVal;}
	RegValueHex GetCtrlVal(){return m_ctrlVal;}

protected:
	void SerialPortInit();
	void SerialPortReInit();
	void spiInit();

private:
	int WriteRegister(uint8_t addr, uint8_t highByte,
			           uint8_t midByte, uint8_t lowByte);
	int ReadRegister(uint8_t addr, uint8_t* pRxed);
	int sendCmd(uint8_t cmd);
	void setPage(uint8_t pg);
	void SwReset();
	void PowerDown(uint8_t pwCmd);
	void Sync(uint8_t syncType);
	int StartConvertion(uint8_t startCmd);

	bool InterruptHandlerInit(bool DRDY);
	bool DisableInterrupts();
	void InterruptHandler();

	void CheckStatus();
	bool CheckStatusReady(int bit);
    // Calibration methods
	//Offset calibration
	bool IchannDCoffsetCal();
	bool VchannDCoffsetCal();
	bool IVChannelDCOffsetCal();
	bool IchannACoffsetCal();
	bool VchannACoffsetCal();
	bool CalStatusReadyCheck(long long maxElapsedTime);
	//Gain Calibration
	bool VChannACGainCal();
	bool IChannACGainCal();
	bool VChannDCGainCal();
	bool IChannDCGainCal();
	//Run methods
	void MakeReadings();

	//Test bits Settings
	bool IsSet(uint8_t byte, int pos);


	void setModeSpi(uint8_t wrMode, uint8_t rdMode);

	uint32_t make32(uint8_t *var);
    //float NumNotationConv(uint32_t num, int numNotation);
    void NumNotationConv(int reg);

	void InitPageZero();
	void InitPageOne();
	void InitPageThree();


private:
	cs5463spiParams	   		 m_spiParams;
	cs5463Commands     		 m_cmds;
	CS5463RegPage_0          m_regAddrPage_0;
	CS5463RegPage_1			 m_regAddrPage_1;
	CS5463RegPage_3			 m_regAddrPage_3;
	cs5463sysCalOffsetVals   m_sysCalOffset;
	cs5463sysCalGainVals     m_sysCalGain;
	RegValueHex              m_configVal;
	RegValueHex				 m_modeVal;
	RegValueHex				 m_maskVal;
	RegValueHex				 m_ctrlVal;
	CS5463Notation			 m_numberNotation;
	cs5463RegDefPage_0       m_regDefPage_0;
	cs5463RegDefPage_1		 m_regDefPage_1;
	cs5463RegDefPage_3       m_regDefPage_3;


	std::vector<std::string> 	m_statusWarn;
	std::vector<CS5463Num> 		m_cs5463NumList;

    //Status Register bit convention
	enum {ic_not, fup, lsd, iod, vod,tod=6, tup,
		vsag=10, ifault, eor, vror, iror, vor=16,
		ior, crdy=20, drdy=23};
    //cs5463 calibration types
	enum {v_dc_offset_cal = 1, i_dc_offset_cal, iv_dc_offset_cal, v_ac_offset_cal, i_ac_offset_cal,
	      v_dc_gain_cal, i_dc_gain_cal, v_ac_gain_cal, i_ac_gain_cal };
    //cs5463 registers
	enum{conf=0, i_dc_offset, i_gain, v_dc_offset, v_gain, cycle_count, pulse_rate, i_int, v_int,
	     p_int, p_act, i_rms, v_rms, epsilon, p_offset, status, i_ac_offset, v_ac_offset, mode,
	     temp, q_avg, q, i_peak, v_peak, q_trig, pf, mask, s, ctrl, p_h, p_f, q_f, pulse_width,
	     load_min, temp_gain, temp_off,v_sag_duration, v_sag_level, i_sag_duration, i_sag_level};

};


extern "C" spi* create(){
	return new cs5463spi;
}

extern "C" void destroy(spi* p) {
	delete p;
}

#endif /* CS5463_SPI_H_ */
