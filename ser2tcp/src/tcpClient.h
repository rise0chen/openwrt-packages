#ifndef __TCPCLIENT_H_
#define __TCPCLIENT_H_
#include "config.h"

extern void tcpClient_on(callbackType type, void (*fun)(char *data, unsigned char len));
extern int initTcpClient(char *ip, int port);
extern void tcpClient_send(char *data, unsigned char len);
#endif
