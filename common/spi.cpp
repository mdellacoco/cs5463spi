/*
 * spi.cpp
 *
 *  Created on: Apr 3, 2014
 *      Author: victoria
 */

#include "spi.h"


spi::spi()//
   : m_mySPISysLog(0), m_pMyLogger(0)
{
	m_spiParams.fd = 0;
	m_spiParams.bitOrder = 0x00;
	m_spiParams.spiBPW = 0;
	m_spiParams.spiDelay = 0;
	m_spiParams.spiWrMode = 0;
	m_spiParams.spiRdMode = 0;
	m_spiParams.spiSpeed = 0;

	//m_pMyTimeDate->date = "";
	//m_pMyTimeDate->time = 0;
}

/**
 * Virtual destructor
 */

spi::~spi() {
	close(m_spiParams.fd);
}

void spi::openDevice(const char *pDevice){
	printf("I am about to open file ..\n");
	m_spiParams.fd = open(pDevice, O_RDWR);
	printf("fd: %i\n", m_spiParams.fd);
}

/** spiSendReceive has two functionalities sends|/writes to the SPI and send/receive
 * from the SPI. The method make use of the linux function ioctl that performs the
 * generic I/O operations.
 */

int spi::spiSendReceive(uint8_t *pTxBuf, int iTxLen, uint8_t *pRxBuf, int iRxLen){
    int status = -1;
	struct spi_ioc_transfer xfer;
	memset(&xfer, 0, sizeof(xfer));

	xfer.tx_buf = (unsigned long)pTxBuf;
	xfer.rx_buf = (unsigned long)pRxBuf;
	xfer.len = iTxLen;
	xfer.delay_usecs = m_spiParams.spiDelay;
	xfer.speed_hz = m_spiParams.spiSpeed;
	xfer.bits_per_word = m_spiParams.spiBPW;

	currentTimeDate();
	status = ioctl(m_spiParams.fd, SPI_IOC_MESSAGE(1), &xfer);


	if(status < 0) {
		m_mySPISysLog->writeErrLog("Can't send SPI message:");
		//m_pMyLogger->WriteLocal();
		return status;
	}

	return status;
}
/**
 * Abort the application, but before it writes to the system log as an error.
 */


void spi::spiAbort(const char *msg) {

  //m_mySPISysLog->writeErrLog(msg);
	printf("Error: %s\n", msg);
  abort();
}


/**
 * Initializes the spi driver
 * */

void spi::spiInit(){


	int status = 1;

	//mode

	status = ioctl(m_spiParams.fd, SPI_IOC_WR_MODE, &m_spiParams.spiWrMode);

	if(status <0 )
	   spiAbort("Can't set spi mode");

	status = ioctl(m_spiParams.fd, SPI_IOC_RD_MODE, &m_spiParams.spiRdMode);

	if(status < 0)
      this->spiAbort("Can't set spi mode");

	// bits per word

	status = ioctl(m_spiParams.fd, SPI_IOC_WR_BITS_PER_WORD, &m_spiParams.spiBPW);
	if(status < 0)
	  spiAbort("Can't set spi BPW");

	status = ioctl(m_spiParams.fd, SPI_IOC_RD_BITS_PER_WORD, &m_spiParams.spiBPW);
	if(status < 0)
	  spiAbort("Can't set spi BPW");

	//max speed

	status = ioctl(m_spiParams.fd, SPI_IOC_WR_MAX_SPEED_HZ, &m_spiParams.spiMaxSpeed);
	if(status < 0)
       spiAbort("Can't set spi speed");


	status = ioctl(m_spiParams.fd, SPI_IOC_RD_MAX_SPEED_HZ, &m_spiParams.spiMaxSpeed);
	if(status < 0)
      spiAbort("Can't set spi speed");

}

/**
 * Sets bit order
 * */

void spi::spiInitBitOrder() {
	int status = 1;

	status = ioctl(m_spiParams.fd, SPI_IOC_WR_LSB_FIRST, &m_spiParams.bitOrder);

	if(status <0 )
		spiAbort("Can't set spi bit order");

	status = ioctl(m_spiParams.fd, SPI_IOC_RD_LSB_FIRST, &m_spiParams.bitOrder);

	if(status <0 )
		spiAbort("Can't set spi bit order");
}

/**
 * void CurrentTimeDate()
 * Works out the current date and time when sensor data was read.
 * */

void spi::currentTimeDate() {

	//m_MyTimeDate.time = std::time(NULL);
	//m_MyTimeDate.date = std::asctime(std::localtime(&m_MyTimeDate.time));
	//m_MyTimeDate.date.erase(m_MyTimeDate.date.size() - 1);
	//time_t rawTime;
	struct tm* timeInfo;
	char buffer [80];

	std::time_t rawTime = std::time(NULL);
	timeInfo = std::localtime(&rawTime);
	strftime (buffer, 80, "%F %T", timeInfo);
	m_dateTime = buffer;



}

