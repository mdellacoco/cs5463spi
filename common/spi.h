/*
 * spi.h
 *
 *  Created on: Apr 3, 2014
 *      Author: victoria
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>
#include <ctime>
#include <time.h>

#include "Logger.h"

using namespace std;

typedef struct {
	static const char *device;
	uint8_t bitOrder;
	uint8_t spiWrMode;
	uint8_t spiRdMode;
	uint8_t spiBPW;
	uint32_t spiSpeed;
	uint32_t spiMaxSpeed;
	uint16_t spiDelay;
	int fd;
}spiParams;

typedef struct {

	std::time_t time;
	std::string date;

}timeDate;


/**
 * SPI is a abstract base class that defines the functionality of SPI.
 * the clas is an SPI and has a Sys log member to write messages ang error to the
 * linux sys log utility.
 */

class spi {
protected:                    // only derived class can use constructor
	spi();


public:
	virtual ~spi();
	virtual void SerialPortInit(){}
	virtual void ReadValues(){}
	virtual void Run(){}
	virtual void Calibrate(int calType){}

	//Set variables
	int openDevice(const char *pDevice);

	void setSpiSpeed(uint32_t spiSpeed){m_spiParams.spiSpeed = spiSpeed;}
	void setSpiDelay(uint16_t spiDelay){m_spiParams.spiDelay = spiDelay;}
	void setBitOrder(uint8_t bitOrder){m_spiParams.bitOrder = bitOrder;}
	//void setLog(SystemLog *pspiSysLog){m_mySPISysLog = pspiSysLog;}
	void setLogger(Logger* myLogger){ m_pMyLogger = myLogger;}

	//Logger* getLogger(){return m_pMyLogger;}

	virtual void spiInit();
	virtual void Exit(int exitType, const string& msg);


protected:
    virtual void WriteRegister(){}
    virtual int ReadRegister(){return 0;}
    int spiSendReceive(uint8_t *pTxBuf, int iTxLen, uint8_t *pRxBuf, int iRxLen);
    void spiInitBitOrderLSB();
    void setSpiWrMode(uint8_t spiWrMode){m_spiParams.spiWrMode = spiWrMode;}
    void setSpiRdMode(uint8_t spiRdMode){m_spiParams.spiRdMode = spiRdMode;}
    void setSpiMode(uint8_t spiMode){m_spiParams.spiRdMode = spiMode;}
    void setSpiBPW(uint8_t spiBPW){m_spiParams.spiBPW = spiBPW;}
    void setSpiMaxSpeed(uint32_t maxSpeed){m_spiParams.spiMaxSpeed = maxSpeed;}

    void currentTimeDate();

    long ElapsedTime(struct timespec startTime);

    struct timespec CurrentTime();



 private:
    void spiAbort(const char *msg);
    spi(const spi&) = delete; //private non-implemented copy constructor
    const spi& operator= (const spi&) = delete;

 protected:

    Logger*		  m_pMyLogger;
    std::string	  m_dateTime;

    struct timespec time;


 private:
    spiParams    m_spiParams;


	};

// The type of the class factories
typedef spi* create_t();
typedef void destroy_t(spi*);

#endif /* SPI_H_ */
