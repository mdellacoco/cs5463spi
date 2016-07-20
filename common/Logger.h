/*
 * Logger.h
 *
 *  Created on: Mar 15, 2016
 *      Author: victoria
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <fstream>
#include <iostream>
#include <syslog.h>
#include "ClientSocket.h"

using namespace std;

typedef struct {
	std::string clientName;
	std::string appName;
	std::string pidNo;

}loggerInfo;

class Logger {
public:
    // log priorities
    enum Priority
    {
        DEBUG,
        CONFIG,
        INFO,
        WARNING,
        ERROR
    };

    // start/stop logging
    // - messages with priority >= minPriority will be written in log
    // - set logFile = "" to write to standard output
    //static void Start(Priority minPriority, const string& logFile);
    //static Logger* Instance(const string& logFile,
    		             //   ClientSocket* pSocketHandler,
    		              //  loggerInfo* pMyLoggerInfo);

    static Logger* Instance();
    static void StopInstance();

    ~Logger();
     void Success();

     void SetSocketHandler(ClientSocket* pSocketHand){pSocketHandler = pSocketHand;}
     void SetLoggerInfo(loggerInfo* pMyLoggerInfo){pLoggerInfo = pMyLoggerInfo;}

    // write message
    void WriteReadRemote(const string& message);
    void WriteLocal(int facility, int priority, const string& message);

private:
    // Logger adheres to the singleton design pattern, hence the private
    // constructor, copy constructor and assignment operator.
    Logger();
    Logger(const Logger& logger) {}
    Logger& operator = (const Logger& logger) {}



    // private instance data
    bool          active;
    ofstream      fileStream;
    Priority      minPriority;
    ClientSocket* pSocketHandler;  //for non-local logger
    loggerInfo*	  pLoggerInfo;


    // names describing the items in enum Priority
    static const string PRIORITY_NAMES[];
    // the sole Logger instance (singleton)
    static Logger* instance;
};

// The type of the class factories
typedef Logger* createLog_t();
typedef void destroyLog_t(Logger*);


#endif /* LOGGER_H_ */
