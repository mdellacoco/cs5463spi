/*
 * ClientSocket.h
 *
 *  Created on: Mar 15, 2016
 *      Author: victoria
 */

#ifndef CLIENTSOCKET_H_
#define CLIENTSOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

using namespace std;

class ClientSocket {

private:
	//private instance data
	bool active;
	int m_sfd;
	string m_servername;  //hostname
	string m_service;  //port number

	static ClientSocket* m_clientSocketInstance; //singleton

	ClientSocket();
	ClientSocket(const ClientSocket& clientSocket) {}
	ClientSocket& operator = (const ClientSocket& clientSocket) {}


public:
	int createAndConnect();
	void writeAndRead(const string& message, string* msg_in);
	void closeSocket();
	void setServerName(const string& servername){m_servername = servername;}
	void setPortNumber(const string& portno){m_service = portno;}
	//static ClientSocket* Instance(const string& servername, const string& portno);
	static ClientSocket* Instance();
	static void StopInstance(){};

	void alive(){cout<<"I am alive .."<<endl;}

	~ClientSocket();
};

// The type of the class factories
typedef ClientSocket* createSock_t();
typedef void destroySock_t(ClientSocket*);


#endif /* CLIENTSOCKET_H_ */
