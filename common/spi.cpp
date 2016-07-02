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

}

/**
 * Virtual destructor
 */

spi::~spi() {
	close(m_spiParams.fd);
}

int spi::openDevice(const char *pDevice){

	m_spiParams.fd = open(pDevice, O_RDWR);

	if(m_spiParams.fd == -1) {
		printf("\n open() failed with error [%s]\n",strerror(errno));
		return -1;
	}
	else
		return m_spiParams.fd;


}

/** spiSendReceive has two functionalities sends|/writes to the SPI and send/receive
 * from the SPI. The method make use of the linux function ioctl that performs the
 * generic I/O operations.
 */

int spi::spiSendReceive(uint8_t *pTxBuf, int iTxLen, uint8_t *pRxBuf, int iRxLen){
    int status;
	struct spi_ioc_transfer xfer;
	memset(&xfer, 0, sizeof(xfer));

	xfer.tx_buf = (unsigned long)pTxBuf;
	xfer.rx_buf = (unsigned long)pRxBuf;
	xfer.len = iTxLen;
	xfer.speed_hz = m_spiParams.spiSpeed;
	xfer.delay_usecs = m_spiParams.spiDelay;
	xfer.bits_per_word = m_spiParams.spiBPW;

	currentTimeDate();
	status = ioctl(m_spiParams.fd, SPI_IOC_MESSAGE(1), &xfer);

	if(status < 0) {

		std::string msg;
		int errorNum;

		errorNum = errno;

		std::string errDescription(strerror(errorNum));

		msg = "Can't send SPI message: " + errDescription;
		//m_mySPISysLog->writeErrLog("Can't send SPI message:");
		//m_pMyLogger->WriteLocal();
	    Exit(EXIT_FAILURE, msg.c_str());
		//return status;
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

	struct tm* timeInfo;
	char buffer [80];

	std::time_t rawTime = std::time(NULL);
	timeInfo = std::localtime(&rawTime);
	strftime (buffer, 80, "%F %T", timeInfo);
	m_dateTime = buffer;
}

/**
 *
 * ElapsedTime - works out the time passed/elapsed from a starting time.
 */

long spi::ElapsedTime(struct timespec startTime){
 struct timespec nowTime;
 clock_gettime(CLOCK_REALTIME, &nowTime);
 long elapsedTime = (nowTime.tv_sec - startTime.tv_sec)*1E9 +
		             (nowTime.tv_nsec - startTime.tv_nsec);

 return elapsedTime;

}

/**
 *
 * TimeStart - gets the current time.
 */
struct timespec spi::CurrentTime(){
	struct timespec timeStart;
	clock_gettime(CLOCK_REALTIME, &timeStart);
	return timeStart;
}

/**
 * Exit() .. terminates the application gracefully due to either abnormal termination or
 * intended termination.
 */
void spi::Exit(int exitType, const char *msg){
//TODO: do a time read to know when the program terminated. or even write the date too ..
	if(EXIT_FAILURE)
	   m_mySPISysLog->writeErrLog(msg);

	if(EXIT_SUCCESS)
		m_mySPISysLog->writeMsgLog(msg);


	 exit(exitType);
}
