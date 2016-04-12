/*
 * SystemLog.h
 *
 *  Created on: Feb 3, 2015
 *      Author: victoria
 */

#ifndef SYSTEMLOG_H_
#define SYSTEMLOG_H_

#include <errno.h>

#include <syslog.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class SystemLog {
public:
	SystemLog(const char* pDaemon);
	virtual ~SystemLog();

	void writeMsgLog(const char *msg);
	int writeErrLog(const char *msg);

private:
    const char*  m_pDeamon;
};

#endif /* SYSTEMLOG_H_ */
