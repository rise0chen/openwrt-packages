#ifndef __TCPSERVER_H_
#define __TCPSERVER_H_
#include "config.h"

typedef struct{
	unsigned char index;
	int  socket;
	char *ip;
	int  port;
	char bufRcvData[BUF_SIZE];
	unsigned char bufRcvLen;
} TcpClient;

extern void tcpServer_on(callbackType type, void (*fun)(TcpClient *client));
extern int  initTcpServer(int port);
extern void tcpServer_send(char *data, unsigned char len);

#endif
