#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "tcpServer.h"

static char *address = "0.0.0.0"; //127.0.0.1是监听本机 0.0.0.0是监听整个网络
static int  port = PORT;      //监听端口
//static int  timeout = 0;   //超时时间(单位：秒)
static TcpClient* clients[CLIENT_NUM];  //客户端信息
static unsigned char clientsIndex = 0;
static void (*callback[3])(TcpClient *client); //触发事件
static void acceptClient(void *x);
static void rcvData(void *x);

void tcpServer_on(callbackType type, void (*fun)(TcpClient *client)){
	callback[type] = fun;
}
/*******
void file_get_contents(char* buf,char* url)
{
	FILE	*stream;
	char	cmd[BUFSIZ];
	sprintf(cmd,"curl %s",url);
	memset(buf, 0, BUFSIZ);//初始化buf
	stream = popen(cmd, "r" ); //将“curl”命令的输出 通过管道读取（“r”参数）到FILE* stream
	fread( buf, sizeof(char), BUFSIZ,  stream);  //将刚刚FILE* stream的数据流读取到buf中
	pclose( stream );
}
*******/

static int sock_fd; // listen on sock_fd, new connection on new_fd
static struct sockaddr_in server_addr;	// server address information
int initTcpServer(int port){
	pthread_t clientHandler;
	int yes = 1;

	server_addr.sin_family = AF_INET;		 // host byte order
	server_addr.sin_port = htons(port);	 // short, network byte order
	inet_aton(address, &server_addr.sin_addr);
	//memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

	if ((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0){perror("socket");exit(1);}
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0){perror("setsockopt");exit(1);}//多终端模式
	if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){perror("bind");exit(1);}
	if (listen(sock_fd, CLIENT_NUM) == -1){perror("listen");exit(1);}
	pthread_create(&clientHandler,NULL,(void *)acceptClient,&sock_fd);

	return sock_fd;
}

void acceptClient(void *x){
	int sock_fd = *(int *)x;
	printf("Server listening: %s:%d\n", address, port);
	while(1){
		while(clientsIndex > 250){}//等待其他断开连接
		int socket = accept(sock_fd,NULL,NULL);
		if(socket<=0){perror("sock accept");exit(1);}
		clients[clientsIndex] = malloc(sizeof(TcpClient));
		clients[clientsIndex]->index = clientsIndex;
		clients[clientsIndex]->socket = socket;
		struct sockaddr_in client_addr;
		socklen_t sockaddr_in_len = sizeof(client_addr);
		if(!getpeername(clients[clientsIndex]->socket, (struct sockaddr *)&client_addr, &sockaddr_in_len)){
			clients[clientsIndex]->ip = inet_ntoa(client_addr.sin_addr);
			clients[clientsIndex]->port = ntohs(client_addr.sin_port);
		}
		pthread_t ntid;
		pthread_create(&ntid,NULL,(void *)rcvData,clients[clientsIndex]);
		clientsIndex++;
	}
}
void rcvData(void *x){
	//pthread_detach(pthread_self());//非阻塞
	TcpClient* client=(TcpClient*)x;
	callback[e_connect](client);
	while(1){
		bzero(client->bufRcvData, BUF_SIZE);
		client->bufRcvLen = recv(client->socket, client->bufRcvData, BUF_SIZE, 0);
		if(client->bufRcvLen > 0){
			callback[e_data](client);
		}else{
			break;
		}
	}
	callback[e_close](client);

	unsigned char last_i = --clientsIndex;
	unsigned char close_i = client->index;
	free(clients[close_i]);
	clients[close_i] = NULL;
	if(last_i != close_i){
		clients[close_i] = clients[last_i];
		clients[close_i]->index = close_i;
		clients[last_i] = NULL;
		printf("mv %d to %d\n", last_i, clients[close_i]->index);
	}
}

void tcpServer_send(char *data, unsigned char len){
	unsigned char i = 0;
	for(i=0; i<clientsIndex; i++){
		if(send(clients[i]->socket, data, len, 0) < 0){
			perror("tcpServer_send");
		}
	}
}
