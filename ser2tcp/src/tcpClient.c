#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "tcpClient.h"


static int                    fd;
static struct sockaddr_in     serv_addr;
static void (*callback[3])(char *data, unsigned char len); //触发事件
static void rcvData(void *x);

void tcpClient_on(callbackType type, void (*fun)(char *data, unsigned char len)){
	callback[type] = fun;
}

int initTcpClient(char *ip, int port){
	pthread_t clientHandler;
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port   = htons(port);
	if ((inet_pton(AF_INET,ip,&serv_addr.sin_addr)) < 0){
			perror("inet_pton");
			exit(1);
	}
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0){
			perror("socket");
			exit(1);
	}
	if (-1 == connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))){
			perror("connect");
			exit(1);
	}
	pthread_create(&clientHandler,NULL,(void *)rcvData,&fd);

	return fd;
}

void rcvData(void *x){
	int  sock_fd = *(int*)x;
	char buf[BUF_SIZE];
	int  len = 0;

	printf("connect sucesseful\n");
	while(1){
			memset(buf,0,BUF_SIZE);
			len = read(sock_fd,buf,BUF_SIZE);
			if(len>0)	{
				callback[e_data](buf, len);
			}else{
				break;
			}
	}
	printf("tcpClient disconnect...\n");
	//pthread_exit(0);
}

void tcpClient_send(char *data, unsigned char len){
	if(write(fd,data,len)<0){
		perror("tcpClient_send");
	}
}
