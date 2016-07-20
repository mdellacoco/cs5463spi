/*
 * Logger.cpp
 *
 *  Created on: Mar 15, 2016
 *      Author: victoria
 */

#include "Logger.h"

Logger* Logger::instance = NULL;


// --------------------------------------
// function implementations
// --------------------------------------

Logger::Logger() : active(false), pSocketHandler(NULL), pLoggerInfo(NULL){}

//Logger* Logger::Instance(const string& logFile,
		 //                ClientSocket* pSocketHandler,
		       //          loggerInfo* pMyLoggerInfo)
Logger* Logger::Instance()
{
   if(!instance) {

      instance = new Logger;
      instance->active = true;
 //   instance.minPriority = minPriority;
      instance->minPriority = DEBUG;
    //  instance->pSocketHandler = pSocketHandler;
     // instance->pLoggerInfo = pMyLoggerInfo;
	}
   // if (logFile != "")
    //{
   //     instance->fileStream.open(logFile.c_str());
   // }
	return instance;
}

Logger::~Logger() {

   active = false;
   if(instance)
      delete instance;
}


void Logger::StopInstance()
{
    instance->active = false;
    if (instance->fileStream.is_open())
    {
        instance->fileStream.close();
    }
}
/*
void Logger::Write(Priority priority, const string& message)
{
    if (instance.active && priority >= instance.minPriority)
    {
        // identify current output stream
        ostream& stream
            = instance.fileStream.is_open() ? instance.fileStream : std::cout;

      //  stream  << PRIORITY_NAMES[priority]
        //        << ": "
         //       << message
         //       << endl;
    }
}
*/

void Logger::WriteLocal(int facility, int priority, const string& message){

	openlog(instance->pLoggerInfo->appName.c_str(), LOG_PID, facility);
	syslog(priority, "%s", message.c_str());
	closelog();
}

//void Logger::WriteReadRemote(Priority priority, const string& message) {
void Logger::WriteReadRemote(const string& message) {


   std::string localStr = instance->pLoggerInfo->clientName +
		                  " " +
		                  instance->pLoggerInfo->appName +
		                  " " +
		                  instance->pLoggerInfo->pidNo;

   localStr += " " + message;

	if(instance->pSocketHandler->createAndConnect() != -1) {

	    instance->pSocketHandler->writeAndRead(localStr, NULL);
	    instance->pSocketHandler->closeSocket();
	}
}

void Logger::Success(){

	cout<<"Success.." <<endl;

	instance->pSocketHandler->alive();

}

extern "C" Logger* createLog(){
	return Logger::Instance();
}

extern "C" void destroyLog(Logger* p) {
	Logger::StopInstance();
	//delete p;
}


