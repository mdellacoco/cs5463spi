/*
 * SystemLog.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: victoria
 */

#include "SystemLog.h"

SystemLog::SystemLog(const char* pDaemon):m_pDeamon(pDaemon) {
	// TODO Auto-generated constructor stub
	setlogmask(LOG_UPTO(LOG_INFO));
	openlog(m_pDeamon, LOG_CONS | LOG_PERROR, LOG_LOCAL6);

}

SystemLog::~SystemLog() {
	// TODO Auto-generated destructor stub
	closelog();
}

void SystemLog::writeMsgLog(const char *msg) {

  openlog(m_pDeamon,LOG_PID, LOG_LOCAL6);
  syslog(LOG_INFO, "%s", msg);
  closelog();

}
int SystemLog::writeErrLog(const char *msg) {
	char *pstrMsg;
	char* pErrmsg =0;
	int success = 0;

	pErrmsg = strerror(errno);
	int size = asprintf(&pstrMsg, "%s %s", msg, pErrmsg);

	if(pstrMsg && size){   //if there is a valid message
	  openlog(m_pDeamon,LOG_PID, LOG_LOCAL7);
	  syslog(LOG_ERR, "%s", pstrMsg);
	  closelog();
	  free (pstrMsg);
	}
	else
	  success = -1;

	return success;

	}

