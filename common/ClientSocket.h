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
	static ClientSocket* Instance(const string& servername, const string& portno);

	~ClientSocket();
};

#endif /* CLIENTSOCKET_H_ */
