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

}

 /**
 * Initilalizes spi Device.
 */

void cs5463spi::spiInit() {

    spi::setSpiMaxSpeed(m_spiParams.MAX_FREQ);
    spi::setSpiWrMode(m_spiParams.MODE_0);
    spi::setSpiRdMode(m_spiParams.MODE_0);
	spi::setBitOrder(m_spiParams.BIT_ORDER);  //sets the bit order for CS5463
	spi::setSpiBPW(m_spiParams.BPW);
	spi::spiInitBitOrder();
	spi::spiInit();

}
 /**
 * Initilalizes the CS5463's SPI. This is an overridden function.
 */

void cs5463spi::SerialPortInit() {

	//Software reset
	SwReset();

	sendCmd(m_cmds.SYNC_1);
	sendCmd(m_cmds.SYNC_1);
	sendCmd(m_cmds.SYNC_1);
	sendCmd(m_cmds.SYNC_1);

	//start convertion
	sendCmd(m_cmds.CONT_CONV);
	//StartConvertion(m_cmds.CONT_CONV);

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

	//sendCmd(m_cmds.SYNC_1);
	//sendCmd(m_cmds.SYNC_1);
	//sendCmd(m_cmds.SYNC_1);
	//sendCmd(m_cmds.SYNC_1);
	//sendCmd(m_cmds.SYNC_0);
}

/**
 * Performs a software reset of CS5463 SPI
 */

void cs5463spi::SwReset()
{
  sendCmd(m_cmds.SW_RESET);  // Tx --> 8 bits

}
/**
 * Starts cs5463 convertion.
 */


//------------------------------- Start conversion

//void cs5463spi::StartConvertion(uint8_t startCmd)
//{
//	sendCmd(startCmd);
//}


/**
 * Writes command/value to register
 */



int cs5463spi::WriteRegister(uint8_t cmd, uint8_t highByte,
		                       uint8_t midByte, uint8_t lowByte)
{
	int result;
	uint8_t TxBuf[4];
	uint8_t rxBuf[4];
	memset(TxBuf, 0x00, sizeof(TxBuf));
	memset(rxBuf, 0x00, sizeof(rxBuf));
	int txLength = sizeof(TxBuf);

	TxBuf[0] = cmd;
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

int cs5463spi::ReadRegister(uint8_t cmd, uint8_t* pRxed)
{
	uint8_t txBuf[4];

	int txLength = sizeof(txBuf);
	int res = -1;

	memset(txBuf, 0xFF, txLength);
	memset(pRxed, 0x00, txLength);

	txBuf[0] = cmd;  //register address
	printf("Bytes to Tx: 0x%x  0x%x  0x%x  0x%x\n\n", *(txBuf+0), *(txBuf+1), *(txBuf+2), *(txBuf+3));

	res = spi::spiSendReceive(txBuf, txLength, pRxed, txLength);

	return res;
}

/**
 * Sets command to register
 * Commands are 8 bit in length (one byte)
 */

void cs5463spi::sendCmd(uint8_t cmd)
{
	uint8_t txCmd;
	uint8_t* rxCmd = 0;
	int txCmdLength = 1;
	int status = -1;

	txCmd = cmd;

	status  = spi::spiSendReceive(&txCmd, txCmdLength, rxCmd, txCmdLength);

}



//------------------------------- Set power down states

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

   if(WriteRegister(m_regWrCmd.MASK, 0x00, 0x00, 0x00)) {  //disables interrupts
	  action = true;
   }
   else
      m_mySPISysLog->writeErrLog("Disable Interrupts failed.");

  return action;
}

/**
 * Enable Interrupts
 **/

bool cs5463spi::InterruptHandlerInit(bool DRDY){
	uint8_t mask = DRDY ? 0x80 : 0x10;

	int status = -1;

	// Status Reg clear/reset
	status = WriteRegister(m_regWrCmd.STATUS, m_cmds.SYNC_1, m_cmds.SYNC_1, m_cmds.SYNC_1);
	if(status < 0) {
		m_mySPISysLog->writeErrLog("Enable Interrupts: clear/reset Status Register failed.");
		return false;
	}
	//enable interrupts
	if(status){
	  status = WriteRegister(m_regWrCmd.MASK, 0x03, 0x7C, 0xDC);
	  if(status < 0)
		  m_mySPISysLog->writeErrLog("Enable Interrupts failed.");
	}
	return status;
}




void cs5463spi::InterruptHandler(){

	int status = -1;
	uint8_t rx1[4];
	memset(rx1, 0, 4);

	if(ReadRegister(m_regReadCmd.STATUS, rx1)){  //read status

		if(DisableInterrupts()) {  //disable interrupts.
			CheckStatus(rx1); //handles the interrupts
			WriteRegister(m_regWrCmd.STATUS, rx1[1], rx1[3], rx1[4]); //clear status
		}
	}
}
/**
 * CheckStatus
 **/

void cs5463spi::CheckStatus(uint8_t* status) {

   int count = 0;
   uint8_t result = 0;

   for(int y = 3; y >= 1; y--){

	  uint8_t a = 0x01;
      uint8_t value = *(status + y);

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
 * void CheckStatusReady(uint8_t* byte, int bit);
 * check data ready and convertion ready
 **/

bool cs5463spi::CheckStatusReady(uint8_t byte, int bit){

   uint8_t a = 0x01;
   int pos = 0;
   bool ready = false;

   if(bit == drdy || bit == crdy){
      pos = bit - 16;
	}
   else
      pos = bit;

   if((byte & (a << pos)))
      ready = true;

   return ready;
}


/**
 * Starts register reading. This is an overridden function.
 */

void cs5463spi::Run() {
	int status = 0;
	uint8_t rx1[4];
	memset(rx1, 0x00, sizeof(rx1));

	//Status Clear
	WriteRegister(m_regWrCmd.STATUS,m_cmds.SYNC_1, m_cmds.SYNC_1, m_cmds.SYNC_1);

	//Init serial port
	SerialPortInit();

	// init interrupt handler
	bool intInitSuccess = InterruptHandlerInit(false);

	//interrupt handler
	InterruptHandler();

	while(1){

	 char *strAcc=0;


	 status = ReadRegister(m_regReadCmd.TEMP, rx1);

	 CheckStatus(rx1);

	 //check data ready
	 if(CheckStatusReady(rx1[1], drdy))
		printf("status: %s\n\n",  m_statusWarn[drdy].c_str());

	 // check convertion ready
	 if(CheckStatusReady(rx1[1], crdy))
	 	printf("status: %s\n\n",  m_statusWarn[crdy].c_str());

	 //check temperature updated
	 if(CheckStatusReady(rx1[3], tup))
		 printf("status: %s\n\n",  m_statusWarn[tup].c_str());

	 if(!CheckStatusReady(rx1[3], ic_not))
	 	 printf("status: %s\n\n",  m_statusWarn[ic_not].c_str());

	 asprintf(&strAcc, "%sT 0.5 0.60 0.60 0.36 %d %d %d %d 1.0 0.000082 0.36 0.0000086 0.00051",
			 m_dateTime.c_str(), rx1[0], rx1[1], rx1[2], rx1[3]);

	 printf("Rxed is..: 0x%x  0x%x  0x%x 0x%x\n\n", *(rx1+0), *(rx1+1), *(rx1+2), *(rx1+3));
	 m_mySPISysLog->writeMsgLog(strAcc);

	 m_pMyLogger->WriteReadRemote(strAcc);

	  free(strAcc);
	  sleep(5);
	 }

}

uint32_t cs5463spi::make32(uint8_t var1, uint8_t var2, uint8_t var3, uint8_t var4){

	return (((((uint32_t)var1 << 8 | var2) << 8) | var3) << 8) | var4;

}








