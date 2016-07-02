/*
 * cs5463_spi.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: Margarita E. Della Sera
 */

#include "cs5463_spi.h"


/**
 * Constructor
 */

cs5463spi::cs5463spi(){

	m_statusWarn.push_back("Invalid command.");
	m_statusWarn.push_back("Epsilon updated.");
	m_statusWarn.push_back("Low supply detected.");
	m_statusWarn.push_back("Modulator oscillation detected on voltage.");
	m_statusWarn.push_back("Modulation oscillation detected on current channel.");
	m_statusWarn.push_back("n/a");
	m_statusWarn.push_back("Modulator oscillation detected on temperature channel.");
	m_statusWarn.push_back("Temperature updated.");
	m_statusWarn.push_back("n/a");
	m_statusWarn.push_back("n/a");
	m_statusWarn.push_back("Voltage sag occurred (VSAG).");
	m_statusWarn.push_back("Current fault occurred (IFAULT).");
	m_statusWarn.push_back("Energy out of range (EOR).");
	m_statusWarn.push_back("Vrms out of range (VROR)");
	m_statusWarn.push_back("Irms out of range (IROR)");
	m_statusWarn.push_back("n/a");
	m_statusWarn.push_back("Voltage out of range (VOR).");
	m_statusWarn.push_back("Current out of range (IOR).");
	m_statusWarn.push_back("n/a");
	m_statusWarn.push_back("n/a");
	m_statusWarn.push_back("Convertion ready (CRDY).");
	m_statusWarn.push_back("n/a");
	m_statusWarn.push_back("n/a");
	m_statusWarn.push_back("Data ready (DRDY).");

	//Sets values for

	m_configVal.highByte = 0x00;
	m_configVal.midByte = 0x00;
	m_configVal.lowByte = 0x01;


	m_modeVal.highByte = 0x00;
	m_modeVal.midByte = 0x00;
	m_modeVal.lowByte = 0x00; // Enables HPF on Current and Voltage Channels.

	m_maskVal.highByte = 0x00;
	m_maskVal.midByte = 0x00;
	m_maskVal.lowByte = 0x00;

	m_ctrlVal.highByte = 0x00;
	m_ctrlVal.midByte = 0x00;
	m_ctrlVal.lowByte = 0x00;

	InitPageZero();
	InitPageOne();
    InitPageThree();


	}
/**
 * InitPageZero() : Initializes Page 0 attributes as per data sheet.
 *
 */

void cs5463spi::InitPageZero(){


   //Configuration CS5463 Number
	m_regDefPage_0.CONFIG.addr = m_regAddrPage_0.CONF;
	m_regDefPage_0.CONFIG.notationType = m_numberNotation.NOT_DEFINED;
	m_regDefPage_0.CONFIG.defaultValHex.highByte = 0x00;
	m_regDefPage_0.CONFIG.defaultValHex.midByte = 0x00;
	m_regDefPage_0.CONFIG.defaultValHex.lowByte = 0x00;
	m_regDefPage_0.CONFIG.name = "Configuration";

	m_cs5463NumList.push_back(m_regDefPage_0.CONFIG);

    //Current DC Offset Number
	m_regDefPage_0.I_DC_OFF.addr = m_regAddrPage_0.I_DC_OFF;
	m_regDefPage_0.I_DC_OFF.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.I_DC_OFF.defaultValHex.highByte = 0x00;
	m_regDefPage_0.I_DC_OFF.defaultValHex.midByte = 0x00;
	m_regDefPage_0.I_DC_OFF.defaultValHex.lowByte = 0x00;
	m_regDefPage_0.I_DC_OFF.range.min = -1.0;
	m_regDefPage_0.I_DC_OFF.range.max = 0.999;
	m_regDefPage_0.I_DC_OFF.name = "Current DC Offset";

	m_cs5463NumList.push_back(m_regDefPage_0.I_DC_OFF);

    //Current Gain CS5463 Number
	m_regDefPage_0.I_GAIN.addr = m_regAddrPage_0.I_GAIN;
	m_regDefPage_0.I_GAIN.notationType = m_numberNotation.NOT_DEFINED;
	m_regDefPage_0.I_GAIN.defaultValHex.highByte = 0x40;
	m_regDefPage_0.I_GAIN.defaultValHex.midByte = 0x00;
	m_regDefPage_0.I_GAIN.defaultValHex.lowByte = 0x00;
	m_regDefPage_0.I_GAIN.range.min = 0.0;
	m_regDefPage_0.I_GAIN.range.max = 3.98;
	m_regDefPage_0.I_GAIN.name = "Current Gain";

	m_cs5463NumList.push_back(m_regDefPage_0.I_GAIN);

	//Voltage DC Offset
	m_regDefPage_0.V_DC_OFF.addr = m_regAddrPage_0.V_DC_OFF;
	m_regDefPage_0.V_DC_OFF.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.V_DC_OFF.defaultValHex.highByte = 0x00;
	m_regDefPage_0.V_DC_OFF.defaultValHex.midByte = 0x00;
	m_regDefPage_0.V_DC_OFF.defaultValHex.lowByte = 0x00;
	m_regDefPage_0.V_DC_OFF.range.min = -1.0;
	m_regDefPage_0.V_DC_OFF.range.max = 0.999;
	m_regDefPage_0.V_DC_OFF.name = "Voltage DC Offset";

	m_cs5463NumList.push_back(m_regDefPage_0.V_DC_OFF);

	//Voltage Gain
	m_regDefPage_0.V_GAIN.addr = m_regAddrPage_0.V_GAIN;
	m_regDefPage_0.V_GAIN.notationType = m_numberNotation.NOT_DEFINED;
	m_regDefPage_0.V_GAIN.defaultValHex.highByte = 0x40;
	m_regDefPage_0.V_GAIN.defaultValHex.midByte = 0x00;
	m_regDefPage_0.V_GAIN.defaultValHex.lowByte = 0x01;
	m_regDefPage_0.V_GAIN.range.min = 0.0;
	m_regDefPage_0.V_GAIN.range.max = 3.98;
	m_regDefPage_0.V_GAIN.name = "Voltage Gain";

	m_cs5463NumList.push_back(m_regDefPage_0.V_GAIN);

	//Cycle Count
	m_regDefPage_0.CYCLE_CNT.addr = m_regAddrPage_0.CYCLE_CNT;
	m_regDefPage_0.CYCLE_CNT.notationType = m_numberNotation.NOT_DEFINED;
	m_regDefPage_0.CYCLE_CNT.defaultValHex.highByte = 0x00;
	m_regDefPage_0.CYCLE_CNT.defaultValHex.midByte = 0x0F;
	m_regDefPage_0.CYCLE_CNT.defaultValHex.lowByte = 0xA0;
	m_regDefPage_0.CYCLE_CNT.defaultValDec = 4000;
	m_regDefPage_0.CYCLE_CNT.name = "Cycle Count";

	m_cs5463NumList.push_back(m_regDefPage_0.CYCLE_CNT);

	//Pulse Rate E
	m_regDefPage_0.PULSE_RATE.addr = m_regAddrPage_0.PULSE_RATE;
	m_regDefPage_0.PULSE_RATE.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.PULSE_RATE.defaultValHex.highByte = 	0x80;
	m_regDefPage_0.PULSE_RATE.defaultValHex.midByte = 	0x00;
	m_regDefPage_0.PULSE_RATE.defaultValHex.lowByte = 	0x00;
	m_regDefPage_0.PULSE_RATE.defaultValDec = 1.0;
	m_regDefPage_0.PULSE_RATE.range.min = -1.0;
	m_regDefPage_0.PULSE_RATE.range.max = 0.99;
	m_regDefPage_0.PULSE_RATE.name = "Pulse rate E";

	m_cs5463NumList.push_back(m_regDefPage_0.PULSE_RATE);

	//Instantaneous Current
	m_regDefPage_0.I_INS.addr = m_regAddrPage_0.I_INS;
	m_regDefPage_0.I_INS.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.I_INS.range.min = -1.0;
	m_regDefPage_0.I_INS.range.max = 0.99;
	m_regDefPage_0.I_INS.name = "Instantaneous Current";

	m_cs5463NumList.push_back(m_regDefPage_0.I_INS);

	//Instantaneous Voltage
	m_regDefPage_0.V_INS.addr = m_regAddrPage_0.V_INS;
	m_regDefPage_0.V_INS.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.V_INS.range.min = -1.0;
	m_regDefPage_0.V_INS.range.max = 0.99;
	m_regDefPage_0.V_INS.name = "Instantaneous Voltage";

	m_cs5463NumList.push_back(m_regDefPage_0.V_INS);

	//Instantaneous Power
	m_regDefPage_0.P_INS.addr = m_regAddrPage_0.P_INS;
	m_regDefPage_0.P_INS.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.P_INS.range.min = -1.0;
	m_regDefPage_0.P_INS.range.max = 0.99;
	m_regDefPage_0.P_INS.name = "Instantaneous Power";

	m_cs5463NumList.push_back(m_regDefPage_0.P_INS);

	//Active Real Power
	m_regDefPage_0.P_ACT.addr = m_regAddrPage_0.P_ACT;
	m_regDefPage_0.P_ACT.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.P_ACT.range.min = -1.0;
	m_regDefPage_0.P_ACT.range.max = 0.99;
	m_regDefPage_0.P_ACT.name = "Active Real Power";

	m_cs5463NumList.push_back(m_regDefPage_0.P_ACT);

	//RMS Current
	m_regDefPage_0.I_RMS.addr = m_regAddrPage_0.I_RMS;
	m_regDefPage_0.I_RMS.notationType = m_numberNotation.UBN;
	m_regDefPage_0.I_RMS.range.min = 0.0;
	m_regDefPage_0.I_RMS.range.max = 0.99;
	m_regDefPage_0.I_RMS.name = "RMS Current";

	m_cs5463NumList.push_back(m_regDefPage_0.I_RMS);

	//RMS Voltage
	m_regDefPage_0.V_RMS.addr = m_regAddrPage_0.V_RMS;
	m_regDefPage_0.V_RMS.notationType = m_numberNotation.UBN;
	m_regDefPage_0.V_RMS.range.min = 0.0;
	m_regDefPage_0.V_RMS.range.max = 0.99;
	m_regDefPage_0.V_RMS.name = "RMS Voltage";

	m_cs5463NumList.push_back(m_regDefPage_0.V_RMS);

	//Epsilon
	m_regDefPage_0.EPSILON.addr = m_regAddrPage_0.EPSILON;
	m_regDefPage_0.EPSILON.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.EPSILON.defaultValHex.highByte = 	0x01;
	m_regDefPage_0.EPSILON.defaultValHex.midByte = 	0x99;
	m_regDefPage_0.EPSILON.defaultValHex.lowByte = 	0x9A;
	m_regDefPage_0.EPSILON.defaultValDec = 0.0125;
	m_regDefPage_0.EPSILON.range.min = -1.0;
	m_regDefPage_0.EPSILON.range.max = 0.99;
	m_regDefPage_0.EPSILON.name = "Epsilon";

	m_cs5463NumList.push_back(m_regDefPage_0.EPSILON);

	//Power Offset
	m_regDefPage_0.POWER_OFF.addr = m_regAddrPage_0.POWER_OFF;
	m_regDefPage_0.POWER_OFF.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.POWER_OFF.defaultValHex.highByte = 	0x00;
	m_regDefPage_0.POWER_OFF.defaultValHex.midByte = 	0x00;
	m_regDefPage_0.POWER_OFF.defaultValHex.lowByte = 	0x00;
	m_regDefPage_0.POWER_OFF.range.min = -1.0;
	m_regDefPage_0.POWER_OFF.range.max = 0.99;
	m_regDefPage_0.POWER_OFF.name = "Power Offset";

	m_cs5463NumList.push_back(m_regDefPage_0.POWER_OFF);

    // Status Register
	m_regDefPage_0.STATUS.addr = m_regAddrPage_0.STATUS;
	m_regDefPage_0.STATUS.notationType = m_numberNotation.NOT_DEFINED;
	m_regDefPage_0.STATUS.defaultValHex.highByte = 0x80;
	m_regDefPage_0.STATUS.defaultValHex.midByte = 0x00;
	m_regDefPage_0.STATUS.defaultValHex.lowByte = 0x01;
	m_regDefPage_0.STATUS.name = "Status";

	m_cs5463NumList.push_back(m_regDefPage_0.STATUS);

	//Current AC (RMS) Offset
	m_regDefPage_0.I_AC_OFF.addr = m_regAddrPage_0.I_AC_OFF;
	m_regDefPage_0.I_AC_OFF.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.I_AC_OFF.range.min = -1.0;
	m_regDefPage_0.I_AC_OFF.range.max = 0.99;
	m_regDefPage_0.I_AC_OFF.name = "Current AC (RMS) Offset";

	m_cs5463NumList.push_back(m_regDefPage_0.I_AC_OFF);

	//Voltage AC (RMS) Offset
	m_regDefPage_0.V_AC_OFF.addr = m_regAddrPage_0.V_AC_OFF;
	m_regDefPage_0.V_AC_OFF.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.V_AC_OFF.range.min = -1.0;
	m_regDefPage_0.V_AC_OFF.range.max = 0.99;
	m_regDefPage_0.V_AC_OFF.name = "Voltage AC (RMS) Offset";

	m_cs5463NumList.push_back(m_regDefPage_0.V_AC_OFF);

	// Mode Register
	m_regDefPage_0.MODE.addr = m_regAddrPage_0.MODE;
	m_regDefPage_0.MODE.notationType = m_numberNotation.NOT_DEFINED;
	m_regDefPage_0.MODE.defaultValHex.highByte = 0x00;
	m_regDefPage_0.MODE.defaultValHex.midByte = 0x00;
	m_regDefPage_0.MODE.defaultValHex.lowByte = 0x00;
	m_regDefPage_0.MODE.name = "Mode";

	m_cs5463NumList.push_back(m_regDefPage_0.MODE);

	//Temperature Register
	m_regDefPage_0.TEMP.addr = m_regAddrPage_0.TEMP;
	m_regDefPage_0.TEMP.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.TEMP.range.min = -128.0;
	m_regDefPage_0.TEMP.range.max = 127.99;
	m_regDefPage_0.TEMP.name = "Temperature";

	m_cs5463NumList.push_back(m_regDefPage_0.TEMP);

	//Average Reactive Power
	m_regDefPage_0.Q_AVG.addr = m_regAddrPage_0.Q_AVG;
	m_regDefPage_0.Q_AVG.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.Q_AVG.range.min = -1.0;
	m_regDefPage_0.Q_AVG.range.max = 0.999;
	m_regDefPage_0.Q_AVG.name = "Average Reactive Power";

	m_cs5463NumList.push_back(m_regDefPage_0.Q_AVG);

	//Instantaneous Reactive Power
	m_regDefPage_0.Q.addr = m_regAddrPage_0.Q;
	m_regDefPage_0.Q.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.Q.range.min = -1.0;
	m_regDefPage_0.Q.range.max = 0.999;
	m_regDefPage_0.Q.name = "Instantaneous Reactive Power";

	m_cs5463NumList.push_back(m_regDefPage_0.Q);

	//Peak Current
	m_regDefPage_0.I_PEAK.addr = m_regAddrPage_0.I_PEAK;
	m_regDefPage_0.I_PEAK.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.I_PEAK.range.min = -1.0;
	m_regDefPage_0.I_PEAK.range.max = 0.999;
	m_regDefPage_0.I_PEAK.name = "Peak Current";

	m_cs5463NumList.push_back(m_regDefPage_0.I_PEAK);

	//Peak Current
	m_regDefPage_0.V_PEAK.addr = m_regAddrPage_0.V_PEAK;
	m_regDefPage_0.V_PEAK.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.V_PEAK.range.min = -1.0;
	m_regDefPage_0.V_PEAK.range.max = 0.999;
	m_regDefPage_0.V_PEAK.name = "Peak Voltage";

	m_cs5463NumList.push_back(m_regDefPage_0.V_PEAK);


	//Reactive Power calculated form power triangle
	m_regDefPage_0.Q_TRIG.addr = m_regAddrPage_0.Q_TRIG;
	m_regDefPage_0.Q_TRIG.notationType = m_numberNotation.UBN;
	m_regDefPage_0.Q_TRIG.range.min = 0;
	m_regDefPage_0.Q_TRIG.range.max = 0.999;
	m_regDefPage_0.Q_TRIG.name = "Reactive Power Trig";

	m_cs5463NumList.push_back(m_regDefPage_0.Q_TRIG);

	//Power Factor
	m_regDefPage_0.PF.addr = m_regAddrPage_0.PF;
	m_regDefPage_0.PF.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.PF.range.min = -1.0;
	m_regDefPage_0.PF.range.max = 0.999;
	m_regDefPage_0.PF.name = "Power Factor";

	m_cs5463NumList.push_back(m_regDefPage_0.PF);

	// Mask
	m_regDefPage_0.MASK.addr = m_regAddrPage_0.MASK;
	m_regDefPage_0.MASK.notationType = m_numberNotation.NOT_DEFINED;
	m_regDefPage_0.MASK.defaultValHex.highByte = 0x00;
	m_regDefPage_0.MASK.defaultValHex.midByte = 0x00;
	m_regDefPage_0.MASK.defaultValHex.lowByte = 0x00;
	m_regDefPage_0.MASK.name = "Mask";

	m_cs5463NumList.push_back(m_regDefPage_0.MASK);

	//Apparent Power
	m_regDefPage_0.S.addr = m_regAddrPage_0.S;
	m_regDefPage_0.S.notationType = m_numberNotation.UBN;
	m_regDefPage_0.S.range.min = 0;
	m_regDefPage_0.S.range.max = 0.999;
	m_regDefPage_0.S.name = "Apparent Power";

	m_cs5463NumList.push_back(m_regDefPage_0.S);

	// Control Register
	m_regDefPage_0.CTRL.addr = m_regAddrPage_0.CTRL;
	m_regDefPage_0.CTRL.notationType = m_numberNotation.NOT_DEFINED;
	m_regDefPage_0.CTRL.defaultValHex.highByte = 0x00;
	m_regDefPage_0.CTRL.defaultValHex.midByte = 0x00;
	m_regDefPage_0.CTRL.defaultValHex.lowByte = 0x00;
	m_regDefPage_0.CTRL.name = "Control";

	m_cs5463NumList.push_back(m_regDefPage_0.CTRL);


	//Harmonic Active Power
	m_regDefPage_0.P_H.addr = m_regAddrPage_0.P_H;
	m_regDefPage_0.P_H.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.P_H.range.min = -1.0;
	m_regDefPage_0.P_H.range.max = 0.999;
	m_regDefPage_0.P_H.name = "Harmonic Active Power";

	m_cs5463NumList.push_back(m_regDefPage_0.P_H);

	//Fundamental Active Power
	m_regDefPage_0.P_F.addr = m_regAddrPage_0.P_F;
	m_regDefPage_0.P_F.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.P_F.range.min = -1.0;
	m_regDefPage_0.P_F.range.max = 0.999;
	m_regDefPage_0.P_F.name = "Fundamental Active Power";

	m_cs5463NumList.push_back(m_regDefPage_0.P_F);

	//Fundamental Reactive Power
	m_regDefPage_0.Q_F.addr = m_regAddrPage_0.Q_F;
	m_regDefPage_0.Q_F.notationType = m_numberNotation.TwosCN;
	m_regDefPage_0.Q_F.range.min = -1.0;
	m_regDefPage_0.Q_F.range.max = 0.999;
	m_regDefPage_0.Q_F.name = "Fundamental Reactive Power";

	m_cs5463NumList.push_back(m_regDefPage_0.Q_F);


}
/**
 * InitPageOne() : Initializes Page 1 attributes as per data sheet.
 *
 */
void cs5463spi::InitPageOne(){
	//Pulse Width
	m_regDefPage_1.PULSE_WIDTH.addr = m_regAddrPage_1.PULSE_WIDTH;
	m_regDefPage_1.PULSE_WIDTH.notationType = m_numberNotation.Int;
	m_regDefPage_1.PULSE_WIDTH.range.min = 1;
	m_regDefPage_1.PULSE_WIDTH.range.max = 8388607; //TODO NB. integer in a float
	m_regDefPage_1.PULSE_WIDTH.name = "Pulse Width";

	m_cs5463NumList.push_back(m_regDefPage_1.PULSE_WIDTH);

	//Load Min
	m_regDefPage_1.LOAD_MIN.addr = m_regAddrPage_1.LOAD_MIN;
	m_regDefPage_1.LOAD_MIN.notationType = m_numberNotation.TwosCN;
	m_regDefPage_1.LOAD_MIN.defaultValHex.highByte = 	0x00;
	m_regDefPage_1.LOAD_MIN.defaultValHex.midByte = 	0x00;
	m_regDefPage_1.LOAD_MIN.defaultValHex.lowByte = 	0x00;
	m_regDefPage_1.LOAD_MIN.defaultValDec = 0;
	m_regDefPage_1.LOAD_MIN.range.min = -1.0;
	m_regDefPage_1.LOAD_MIN.range.max = 0.99;
	m_regDefPage_1.LOAD_MIN.name = "No Load Threshold";

	m_cs5463NumList.push_back(m_regDefPage_1.LOAD_MIN);

	//Temperature Gain Register
	m_regDefPage_1.TEMP_GAIN.addr = m_regAddrPage_1.TEMP_GAIN;
	m_regDefPage_1.TEMP_GAIN.notationType = m_numberNotation.UBN;
	m_regDefPage_1.TEMP_GAIN.defaultValHex.highByte = 0x2F;
	m_regDefPage_1.TEMP_GAIN.defaultValHex.midByte = 0x03;
	m_regDefPage_1.TEMP_GAIN.defaultValHex.lowByte = 0xC3;
	m_regDefPage_1.TEMP_GAIN.defaultValDec = 23.5073471;
	m_regDefPage_1.TEMP_GAIN.range.min = 0;
	m_regDefPage_1.TEMP_GAIN.range.max = 128; //TODO Note the upper limit number.
	m_regDefPage_1.TEMP_GAIN.name = "Temperature Gain Register";

	m_cs5463NumList.push_back(m_regDefPage_1.TEMP_GAIN);


	//Temperature Offset Register
	m_regDefPage_1.TEMP_OFF.addr = m_regAddrPage_1.TEMP_OFF;
	m_regDefPage_1.TEMP_OFF.notationType = m_numberNotation.UBN;
	m_regDefPage_1.TEMP_OFF.defaultValHex.highByte = 0xF3;
	m_regDefPage_1.TEMP_OFF.defaultValHex.midByte = 0xD3;
	m_regDefPage_1.TEMP_OFF.defaultValHex.lowByte = 0x5A;
	m_regDefPage_1.TEMP_OFF.defaultValDec = -0.0951126;
	m_regDefPage_1.TEMP_OFF.range.min = -1.0;
	m_regDefPage_1.TEMP_OFF.range.max = 1.0; //TODO Note the upper limit number.
	m_regDefPage_1.TEMP_OFF.name = "Temperature Offset Register";

	m_cs5463NumList.push_back(m_regDefPage_1.TEMP_OFF);

}

/**
 * InitPageThree() : Initializes Page 3 attributes as per data sheet.
 *
 */
void cs5463spi::InitPageThree(){
    //Voltage Sag Duration
	m_regDefPage_3.V_SAG_DURATION.addr = m_regAddrPage_3.V_SAG_DURATION;
	m_regDefPage_3.V_SAG_DURATION.notationType = m_numberNotation.Int;
	m_regDefPage_3.V_SAG_DURATION.defaultValHex.highByte = 0x00;
	m_regDefPage_3.V_SAG_DURATION.defaultValHex.midByte = 0x00;
	m_regDefPage_3.V_SAG_DURATION.defaultValHex.lowByte = 0x00;
	m_regDefPage_3.V_SAG_DURATION.defaultValDec = 0;
	m_regDefPage_3.V_SAG_DURATION.name = "Voltage Sag Duration";

	m_cs5463NumList.push_back(m_regDefPage_3.V_SAG_DURATION);


	//Voltage Sag Level
	m_regDefPage_3.V_SAG_LEVEL.addr = m_regAddrPage_3.V_SAG_LEVEL;
	m_regDefPage_3.V_SAG_LEVEL.notationType = m_numberNotation.UBN;
	m_regDefPage_3.V_SAG_LEVEL.defaultValHex.highByte = 0x00;
	m_regDefPage_3.V_SAG_LEVEL.defaultValHex.midByte = 0x00;
	m_regDefPage_3.V_SAG_LEVEL.defaultValHex.lowByte = 0x00;
	m_regDefPage_3.V_SAG_LEVEL.defaultValDec = 0;
	m_regDefPage_3.V_SAG_LEVEL.range.min = 0;
	m_regDefPage_3.V_SAG_LEVEL.range.max = 1.0;
	m_regDefPage_3.V_SAG_LEVEL.name = "Voltage Sag Level";

	m_cs5463NumList.push_back(m_regDefPage_3.V_SAG_LEVEL);


	//Current Fault Duration
	m_regDefPage_3.I_SAG_DURATION.addr = m_regAddrPage_3.I_SAG_DURATION;
	m_regDefPage_3.I_SAG_DURATION.notationType = m_numberNotation.Int;
	m_regDefPage_3.I_SAG_DURATION.defaultValHex.highByte = 0x00;
	m_regDefPage_3.I_SAG_DURATION.defaultValHex.midByte = 0x00;
	m_regDefPage_3.I_SAG_DURATION.defaultValHex.lowByte = 0x00;
	m_regDefPage_3.I_SAG_DURATION.defaultValDec = 0;
	m_regDefPage_3.I_SAG_DURATION.name = "Current Fault Duration";

	m_cs5463NumList.push_back(m_regDefPage_3.I_SAG_DURATION);


	//Current Fault Level
	m_regDefPage_3.I_SAG_LEVEL.addr = m_regAddrPage_3.I_SAG_LEVEL;
	m_regDefPage_3.I_SAG_LEVEL.notationType = m_numberNotation.UBN;
	m_regDefPage_3.I_SAG_LEVEL.defaultValHex.highByte = 0x00;
	m_regDefPage_3.I_SAG_LEVEL.defaultValHex.midByte = 0x00;
	m_regDefPage_3.I_SAG_LEVEL.defaultValHex.lowByte = 0x00;
	m_regDefPage_3.I_SAG_LEVEL.defaultValDec = 0;
	m_regDefPage_3.I_SAG_LEVEL.range.min = 0;
	m_regDefPage_3.I_SAG_LEVEL.range.max = 1.0;
	m_regDefPage_3.I_SAG_LEVEL.name = "Current Fault Level";

	m_cs5463NumList.push_back(m_regDefPage_3.I_SAG_LEVEL);

	}



/**
 * SetConfigVal - sets values for the config reg.
 *
 */

void cs5463spi::SetConfigVal(uint8_t highByte, uint8_t midByte, uint8_t lowByte){
	m_configVal.highByte = highByte;
	m_configVal.midByte = midByte;
	m_configVal.lowByte = lowByte;
}

/**
 * SetModeVal - sets values for the mode reg.
 *
 */

void cs5463spi::SetModeVal(uint8_t highByte, uint8_t midByte, uint8_t lowByte){
	m_modeVal.highByte = highByte;
	m_modeVal.midByte = midByte;
	m_modeVal.lowByte = lowByte;
}

/**
 * setMaskVal - sets values for the Mask reg.
 *
 */

void cs5463spi::SetMaskVal(uint8_t highByte, uint8_t midByte, uint8_t lowByte){
	m_maskVal.highByte = highByte;
	m_maskVal.midByte = midByte;
	m_maskVal.lowByte = lowByte;
}

/**
 * setCtrlVal - sets values for the control reg.
 *
 */

void cs5463spi::SetCtrlVal(uint8_t highByte, uint8_t midByte, uint8_t lowByte){
	m_ctrlVal.highByte = highByte;
	m_ctrlVal.midByte = midByte;
	m_ctrlVal.lowByte = lowByte;
}


 /**
 * Initilalizes spi Device.
 */

void cs5463spi::spiInit() {
  //Set generic spi parameters
    spi::setSpiMaxSpeed(m_spiParams.MAX_FREQ);
    spi::setSpiWrMode(m_spiParams.MODE_0);
    spi::setSpiRdMode(m_spiParams.MODE_0);
	spi::setBitOrder(m_spiParams.BIT_ORDER);  //sets the bit order for CS5463
	spi::setSpiBPW(m_spiParams.BPW);
	spi::spiInitBitOrder();
	spi::spiInit();

	//Set CS5463 running parameters (Init Serial Port)

	SerialPortInit();

}
 /**
 * Initializes the CS5463's SPI.
 * This is an overridden function.
 */

void cs5463spi::SerialPortInit() {

	//Software reset  //TODO: maybe convert this to boolean to signal successful serial port Init
	SwReset();

	sendCmd(m_cmds.SYNC_1);
	sendCmd(m_cmds.SYNC_1);
	sendCmd(m_cmds.SYNC_1);
	sendCmd(m_cmds.SYNC_1);

	if(CheckStatusReady(drdy)) {
	   //Set CONF Reg
       if(WriteRegister(m_cs5463NumList[conf].addr,
			         m_configVal.highByte, m_configVal.midByte, m_configVal.lowByte) >=0)
           cout << "Configuration Register set successfully .. " << endl;

	  //Set MODE Reg
	   if(WriteRegister(m_cs5463NumList[mode].addr,
			             m_modeVal.highByte, m_modeVal.midByte, m_modeVal.lowByte) >= 0)
		   cout << "Operational Mode  Register set successfully .. " << endl;

	  //Set MASK Reg
	   if(WriteRegister(m_cs5463NumList[mask].addr,
			            m_maskVal.highByte, m_maskVal.midByte, m_maskVal.lowByte) >= 0)
		   cout << "Mask Register set successfully .. " << endl;


	  //Set CTRL Reg
	   if(WriteRegister(m_cs5463NumList[ctrl].addr,
				        m_ctrlVal.highByte, m_ctrlVal.midByte, m_ctrlVal.lowByte) >= 0)
		   cout << "Control Register set successfully .. " << endl;
	}
	else
		cout << m_statusWarn[drdy].c_str() << " NOT" << endl;

}


/**
 * Sets the SPI mode. This is needed as the CS5463 has different spi modes
 * for data reads and data writes.
 */

void cs5463spi::setModeSpi(uint8_t wrMode, uint8_t rdMode){
	spi::setSpiWrMode(wrMode);
	spi::setSpiRdMode(rdMode);
	spi::spiInit();
}

/**
 * This function reinitializes the CS5463 serial port
 */

void cs5463spi::SerialPortReInit() {

	sendCmd(m_cmds.SYNC_1);
	sendCmd(m_cmds.SYNC_1);
	sendCmd(m_cmds.SYNC_1);
	sendCmd(m_cmds.SYNC_1);
	sendCmd(m_cmds.SYNC_0);
}

/**
 * Performs a software reset of CS5463 SPI
 */

void cs5463spi::SwReset()
{
  sendCmd(m_cmds.SW_RESET);  // Tx --> 8 bits

}

/**
 * Starts CS5463 convertion.
 */

int cs5463spi::StartConvertion(uint8_t startCmd)
{
	int status = sendCmd(startCmd);

	return status;
}


/**
 * Writes command/value to register
 */


int cs5463spi::WriteRegister(uint8_t addr, uint8_t highByte,
		                       uint8_t midByte, uint8_t lowByte)
{
	int result;
	uint8_t TxBuf[4];
	uint8_t rxBuf[4];
	memset(TxBuf, 0x00, sizeof(TxBuf));
	memset(rxBuf, 0x00, sizeof(rxBuf));
	int txLength = sizeof(TxBuf);

	TxBuf[0] = 0x40 + (addr << 1);
	TxBuf[1] = highByte;
	TxBuf[2] = midByte;
	TxBuf[3] = lowByte;

	result = spiSendReceive(TxBuf, txLength, rxBuf, txLength);

	return result;

}

/**
 * Reads register value. This is a overridden function.
 * Spi mode 1 is used to read data. (data is read on the clock falling edge.
 */

int cs5463spi::ReadRegister(uint8_t addr, uint8_t* pRxed)
{
	uint8_t txBuf[4];

	int txLength = sizeof(txBuf);
	int res;

	memset(txBuf, 0xFF, txLength);
	memset(pRxed, 0x00, txLength);



	txBuf[0] = addr << 1;  //register address

	printf("Txed to Read: 0x%x 0x%x 0x%x 0x%x\n", txBuf[0], txBuf[1], txBuf[2], txBuf[3]);

	res = spi::spiSendReceive(txBuf, txLength, pRxed, txLength);

	return res;
}

/**
 * Sets command to register
 * Commands are 8 bit in length (one byte)
 */

int cs5463spi::sendCmd(uint8_t cmd)
{
	int status = -1;
	uint8_t rxCmd;
	int txCmdLength = 1;

	status  = spi::spiSendReceive(&cmd, txCmdLength, &rxCmd, txCmdLength);

	return status;
}

/**
 *
 * Power Down
 */

void cs5463spi::PowerDown(uint8_t pwCmd)
{
	sendCmd(pwCmd);
}


//--------------------------------- set sync type

void cs5463spi::Sync(uint8_t syncType)
{
	sendCmd(syncType);
}

// set page

void cs5463spi::setPage(uint8_t pg){
	sendCmd(0x7E);
	sendCmd(0x00);
	sendCmd(0x00);
	sendCmd(pg);

}

/**
 * DisableInterrupts()
 **/

bool cs5463spi::DisableInterrupts(){

   bool action = false;

   if(WriteRegister(m_cs5463NumList[status].addr, 0x00, 0x00, 0x00)) {  //disables interrupts
	  action = true;
   }
   else
      m_mySPISysLog->writeErrLog("Disable Interrupts failed.");

  return action;
}

/**
 * Enables Interrupts
 **/

bool cs5463spi::InterruptHandlerInit(bool DRDY){
	uint8_t mask_ = DRDY ? 0x80 : 0x10; //TODO: ????

	int localstatus = -1;

	// Status Reg clear/reset
	localstatus = WriteRegister(m_cs5463NumList[status].addr, m_cmds.SYNC_1, m_cmds.SYNC_1, m_cmds.SYNC_1);
	if(localstatus < 0) {
		m_mySPISysLog->writeErrLog("Enable Interrupts: clear/reset Status Register failed.");
		return false;
	}
	//enable interrupts
	if(localstatus){
		localstatus = WriteRegister(m_cs5463NumList[mask].addr, 0x03, 0x7C, 0xDC);

	  if(localstatus < 0)
		  m_mySPISysLog->writeErrLog("Enable Interrupts failed.");
	}
	return status;
}




void cs5463spi::InterruptHandler(){ //TODO : look through it .. maybe wrong


	uint8_t rx1[4];
	memset(rx1, 0, 4);

	if(ReadRegister(m_cs5463NumList[status].addr, rx1)){  //read status //TODO not clear enough

		if(DisableInterrupts()) {  //disable interrupts.
			CheckStatus(); //handles the interrupts
			WriteRegister(m_cs5463NumList[status].addr, rx1[1], rx1[3], rx1[4]); //clear status
		}
	}
}

/**
 * CheckStatus
 **/

void cs5463spi::CheckStatus() {

   int count = 0;
   uint8_t result = 0;
   uint8_t rx1[4];
   memset(rx1, 0x00, sizeof(rx1));

   ReadRegister(m_cs5463NumList[status].addr, rx1);

   for(int y = 3; y >= 1; y--){

	  uint8_t a = 0x01;
      uint8_t value = *(rx1 + y);

      for(int i = 0; i < 8; i++) {

	     if(count == lsd || count == iod || count == vod
		    || count == tod || count == vsag || count == ifault
		    || count == eor || count == vror || count == iror
		    || count == vor || count == ior) {

             result = value & (a << i);

		     if(result) {
		    	 std::string msg;
		    	 msg = "Status: " + m_statusWarn[i];
		    	 m_mySPISysLog->writeMsgLog(msg.c_str());
			     printf("%s\n", msg.c_str());
		    }
	      }
	      count++;
       }
      count++;
  }
}

/**
 * bool CheckStatusReady(uint8_t* byte, int bit);
 * check data ready and convertion ready
 * returns tru or false on Data Ready or Convertion Ready
 **/

bool cs5463spi::CheckStatusReady(int bit){

  uint8_t rx1[4];
  memset(rx1, 0x00, sizeof(rx1));

  bool bReady = false;

  //Reads Status Register

  ReadRegister(m_cs5463NumList[status].addr, rx1); //TODO change to correct index.


   //TODO: assert functionality if unsuccessful register reading

   uint8_t a = 0x01;
   int pos = 0;

   if(bit == drdy || bit == crdy){
      pos = bit - 16;

      if((rx1[1] & (a << pos))) {
         bReady = true;
       }
   }
   else if(bit == tup) {
	   pos = tup;
   }
      if((rx1[3] & (a << pos))) {
	     bReady = true;

   }

   return bReady;
}


/**
 * Starts register reading. This is an overridden function.
 */

void cs5463spi::MakeReadings() {

	uint8_t rx1[4];
	memset(rx1, 0x00, sizeof(rx1));

	uint8_t rx2[4];

	memset(rx2, 0xFF, sizeof(rx2));


	while(1){

	 char *strAcc=0;

	 int bDone = false;
	 int i = 1;

	 //Status Clear
	 WriteRegister(m_cs5463NumList[status].addr,m_cmds.SYNC_1, m_cmds.SYNC_1, m_cmds.SYNC_1);

     do {
           ReadRegister(m_cs5463NumList[i_rms].addr, rx1);
           ReadRegister(m_cs5463NumList[v_rms].addr, rx2);
           bDone = CheckStatusReady(drdy);
           i++;
     }while(bDone == false);

     cout << i << "  "<< m_cs5463NumList[i_rms].name <<endl;

     printf("Rxed Irms..: 0x%x  0x%x  0x%x 0x%x\n", *(rx1+0), *(rx1+1), *(rx1+2), *(rx1+3));
     printf("Rxed Vrms..: 0x%x  0x%x  0x%x 0x%x\n\n", *(rx2+0), *(rx2+1), *(rx2+2), *(rx2+3));

     ToDecimal(make32(rx1));
     ToDecimal(make32(rx2));

	 asprintf(&strAcc, "%sT 0.5 0.60 0.60 0.36 %d %d %d %d 1.0 0.000082 0.36 0.0000086 0.00051",
			 m_dateTime.c_str(), rx1[0], rx1[1], rx1[2], rx1[3]);


	// m_mySPISysLog->writeMsgLog(strAcc);

	// m_pMyLogger->WriteReadRemote(strAcc);

	  free(strAcc);
	  sleep(1);
	 }
}

/**
 *
 * Reads all required Electrical parameters
 */

void cs5463spi::Run() {

   StartConvertion(m_cmds.CONT_CONV);
   MakeReadings();
}


/**
 * Calibrate Method, public domain
 */

void cs5463spi::Calibrate(int calType){
   bool bSuccess = false;
   uint8_t rx1[4];
   memset(rx1, 0x00, sizeof(rx1));

   //checks data Ready: i.e. device in active state and ready to receive commands.
   if(CheckStatusReady(drdy)) {

      switch(calType) {
	     case v_dc_offset_cal:
	    	ReadRegister(m_cs5463NumList[mode].addr, rx1);
	    	if(!IsSet(*(rx1+3), 5))
		       bSuccess = this->VchannDCoffsetCal();
	    	   if(bSuccess)
	    		   cout << "Voltage DC Offset Calibration successfully performed." << endl;
	    	else{
	    		  cout << "HPF set, no need for Voltage Offset calibration" << endl;
	    		  WriteRegister(m_cs5463NumList[v_dc_offset].addr, 0x00, 0x00, 0x00); //TODO: maybe set somewhere else
	    		}
	    	memset(rx1, 0x00, sizeof(rx1));
	     break;
	     case i_dc_offset_cal:
	    	 ReadRegister(m_cs5463NumList[mode].addr, rx1);
	    	 if(!IsSet(*(rx1+3), 6)) {
	            bSuccess = this->IchannDCoffsetCal();
	    		if(bSuccess)
	    	       cout << "Current DC Offset Calibration successfully performed." << endl;
	    	 }
	    	 else {
	    	 	  cout << "HPF set, no need for Current Offset calibration" << endl;
	    	 	  WriteRegister(m_cs5463NumList[i_dc_offset].addr, 0x00, 0x00, 0x00); //TODO: maybe set somewhere else
	    	 	   }
	    	 memset(rx1, 0x00, sizeof(rx1));
		 break;
	    case iv_dc_offset_cal:
		//bSuccess = this->
		break;
	    case v_ac_offset_cal:
	    	bSuccess = this->VchannACoffsetCal();
	    	if(bSuccess)
	    	   cout << "Voltage AC Offset Calibration successfully performed." << endl;
	    break;
	    case i_ac_offset_cal:
	    	bSuccess = this->IchannACoffsetCal();
	    	if(bSuccess)
	           cout << "Current AC Offset Calibration successfully performed." << endl;
	    	break;
	    case v_dc_gain_cal:
             //check V gain register.if it is 1, do not perform calibration
	    	cout << "hmm" << endl;
	    	ReadRegister(m_cs5463NumList[v_gain].addr, rx1);
	    	if(!(make32(rx1) == 1))
	    	  this->VChannDCGainCal();
	    	else
	    		cout << "No Need for Voltage Channel AC Gain Calibration" << endl;
	    	break;
	    case i_dc_gain_cal:

	    break;
	    case v_ac_gain_cal:

	    break;
	    case i_ac_gain_cal:

	    break;
	    default:
	    break;
	 }
   }
   else
	   cout << "Status: " << m_statusWarn[drdy].c_str() << " NOT" << endl;

}

/**
 *  Makes 3 bytes into a 32 bit number;
 *
 */

uint32_t cs5463spi::make32(uint8_t *var){

	uint32_t num = (*(var+1)<<16) + (*(var+2)<<8) + *(var+3);

	printf("0x%x, 0x%x, 0x%x\n", *(var+1), *(var+2), *(var+3));

	cout << "NUmber is: " << num << endl;
	return num;

}

/**
 * CalStatusReadyCheck
 * Check whether staus is ready or not.
 */
bool cs5463spi::CalStatusReadyCheck(long long maxElapsedTime){

   struct timespec startTime;
   long long elapsedTime = 0;
   bool bCalStatusRdy = false;

   startTime = this->CurrentTime();

      do{
         elapsedTime = ElapsedTime(startTime);
         bCalStatusRdy = CheckStatusReady(drdy);
   	     }while(!bCalStatusRdy && elapsedTime < maxElapsedTime);

   cout << "Elapsed Time: " << (elapsedTime/1E9) << endl;
   if(bCalStatusRdy)
      cout << "Status: " << m_statusWarn[drdy].c_str() << endl;
   else
 	  cout << "Status: " << m_statusWarn[drdy].c_str() << " NOT" << endl;

   return bCalStatusRdy;
}

/**
 *  Performs I Channel DC Offset Calibration
 *
 */

bool cs5463spi::IchannDCoffsetCal(){

   bool bCalRdy = false;
   int result, registerWrite;

   registerWrite = WriteRegister(m_cs5463NumList[i_gain].addr, 0x40, 0x00, 0x00);  //sets Gain to 1;
   result = sendCmd(m_sysCalOffset.I_CHAN_DC_OFFSET);  // Inits I channel DC Offset Calibration

   if(result >= 0 && registerWrite >= 0)
	   bCalRdy = CalStatusReadyCheck(2E9);

   return bCalRdy;
}

/**
 *
 *  Performs V Channel DC Offset calibration
 */

bool cs5463spi::VchannDCoffsetCal(){

   bool bCalRdy = false;
   int result, registerWrite;

   registerWrite = WriteRegister(m_cs5463NumList[v_gain].addr, 0x40, 0x00, 0x00);  //sets Gain to 1;
   result = sendCmd(m_sysCalOffset.V_CHAN_DC_OFFSET);  // Inits V channel DC Offset Calibration

   if(result >= 0 && registerWrite >= 0)
   	   bCalRdy = CalStatusReadyCheck(2E9);

   return bCalRdy;
}

/**
 * Performs I Channel AC Offset Calibration
 *
 */

bool cs5463spi::IchannACoffsetCal() {
   bool bCalRdy = false;
   int result, registerWrite;

   registerWrite = WriteRegister(m_cs5463NumList[i_ac_offset].addr,0x00, 0x00, 0x00);// Clears I_AC_Offset Register
   result = sendCmd(m_sysCalOffset.I_CHAN_AC_OFFSET);  // Inits I channel AC Offset Calibration

   if(result >= 0 && registerWrite >= 0)
   	   bCalRdy = CalStatusReadyCheck(6E9);

   return bCalRdy;
}

/**
 * Performs V Channel AC Offset Calibration
 *
 */

bool cs5463spi::VchannACoffsetCal() {

   bool bCalRdy = false;
   int result, registerWrite;

   registerWrite = WriteRegister(m_cs5463NumList[v_ac_offset].addr,0x00, 0x00, 0x00); // Clears V_AC_Offset Register
   result = sendCmd(m_sysCalOffset.V_CHAN_AC_OFFSET);  // Inits I channel AC Offset Calibration

   if(result >= 0 && registerWrite >= 0)
   	   bCalRdy = CalStatusReadyCheck(6E9);

   return bCalRdy;
}

/**
 *
 *
 */
bool cs5463spi::VChannACGainCal() {
    bool bSuccess = false;
	int registerWrite, result;
	registerWrite = WriteRegister(m_cs5463NumList[v_gain].addr, 0x40, 0x00, 0x00);  //sets Gain to 1;
	result = sendCmd(m_sysCalGain.V_CHAN_AC_GAIN);  // Inits V channel AC Gain Calibration

	if(registerWrite >= 0 && result >= 0)
		bSuccess = true;

	return bSuccess;
}


/**
 *
 * IChannACGainCal() .. returns true on a successful gain setting to 1 and successful
 * calibration send.
 */
bool cs5463spi::IChannACGainCal() {
	bool bSuccess = false;
	int registerWrite, result;
	registerWrite = WriteRegister(m_cs5463NumList[i_gain].addr, 0x40, 0x00, 0x00);  //sets Gain to 1;
	result = sendCmd(m_sysCalGain.V_CHAN_AC_GAIN);  // Inits I channel AC Gain Calibration

	if(registerWrite >= 0 && result >= 0)
	  bSuccess = true;

	return bSuccess;
}

/**
 *
 *
 */
bool cs5463spi::VChannDCGainCal(){
	cout << "ufff" << endl;
	bool bSuccess = false;
	int result;
	result = sendCmd(m_sysCalGain.V_CHAN_AC_GAIN);  // Inits V channel DC Gain Calibration
//TODO - check for gain registered being 1; use it in the if statement.
	if(result >= 0)
		bSuccess = true;

	return bSuccess;
}

/**
 *
 *
 */

bool cs5463spi::IChannDCGainCal(){
	bool bSuccess = false;
	int result;
	result = sendCmd(m_sysCalGain.I_CHAN_DC_GAIN);  // Inits I channel DC Gain Calibration
	//TODO - check for gain registered being 1; use it in the if statement.
	if(result >= 0)
		bSuccess = true;

	return bSuccess;
}

/**
 * IsSet : tests whether a bit is set or not.
 */

bool cs5463spi::IsSet(uint8_t byte, int pos) {
   std::bitset<8> bit(byte);
   bool bSet = false;

   if(bit.test(pos))
	   bSet = true;

   return bSet;
}

/**
 *
 *  Converts 2s complements to decimal.
 *
 */
uint32_t cs5463spi::ToDecimal(uint32_t num){
	std::bitset<24> bits(num);

	int32_t result = num;

	if(bits[23] == 1)  // then number is negative
	{   cout << "negative number " << endl;

	    bits.flip();  // flip
		result = bits.to_ulong() + 1; // add one
		result *= -1; // multiply by -1;

		cout << result << endl;
	}
	else
		cout << result << endl;



	return 32;
}









