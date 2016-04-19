/*
 * ClientSocket.cpp
 *
 *  Created on: Mar 15, 2016
 *      Author: victoria
 */

#include "ClientSocket.h"


ClientSocket* ClientSocket::m_clientSocketInstance = NULL;

ClientSocket::ClientSocket() : active(false){}

ClientSocket* ClientSocket::Instance(const string& servername, const string& portno) {
    if(!m_clientSocketInstance){
    	m_clientSocketInstance = new ClientSocket;
	    m_clientSocketInstance->active = true;
	    m_clientSocketInstance->m_servername = servername;
	    m_clientSocketInstance->m_service = portno;
	    m_clientSocketInstance->m_sfd = -1;
    }
    return m_clientSocketInstance;
	//if(!m_clientSocketInstance.active) {
		//m_clientSocket = new ClientSocket();
		///m_clientSocketInstance.active = true;
		//return m_clientSocket;
	//}
	//else
	//	return m_clientSocket;

}

ClientSocket::~ClientSocket() {
	active = false;
	if(m_clientSocketInstance)
	   delete m_clientSocketInstance;
}

int ClientSocket::createAndConnect() {
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	int s;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Stream socket */
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          /* Any protocol */

	if(getaddrinfo(m_clientSocketInstance->m_servername.c_str(),
			       m_clientSocketInstance->m_service.c_str(),
			       &hints, &result)) {
	   perror("getaddrinfo");
	}
	//NB handle error

	for (rp = result; rp != NULL; rp = rp->ai_next) {

        m_clientSocketInstance->m_sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

	    if (m_clientSocketInstance->m_sfd == -1)
	    	continue;

	    if (connect(m_clientSocketInstance->m_sfd, rp->ai_addr, rp->ai_addrlen) != -1) {
	    	break;                  /* Success */
	    }
	       close(m_clientSocketInstance->m_sfd);
	    }

	//NB handle error no address succeded.
	freeaddrinfo(result);

	return m_clientSocketInstance->m_sfd;

}

void ClientSocket::writeAndRead(const string& message, string* msg_in) {
    int n, nread;
	n = write(m_clientSocketInstance->m_sfd,message.c_str(),strlen(message.c_str()));
	//nread = read(m_sfd, buf, BUF_SIZE);
}


void ClientSocket::closeSocket(){
     close(m_clientSocketInstance->m_sfd);
}



