#include <stdio.h>
#include <unistd.h>
#include "serial.h"
#include "tcpServer.h"


void socketOnConnect(TcpClient* client){
	printf("%s:%d connect %d.\n", client->ip, client->port, client->index);
}
void socketOnData(TcpClient* client){
	printf("%s:%d send: %s, %d, %d.\n", client->ip, client->port, client->bufRcvData, client->bufRcvLen, client->index);
	serial_send(client->bufRcvData, client->bufRcvLen);
}
void socketOnClose(TcpClient* client){
	printf("%s:%d disconnect %d.\n", client->ip, client->port, client->index);
}
void serialOnData(char *data, unsigned char len){
	printf("serial send: %s, %d.\n", data, len);
	tcpServer_send(data, len);
}


int main(int argc,char *argv[]){
	int    usrt_fd;
	int    sock_fd;
	char *serial = DEVICE;

	if( argc >= 2 ){
		serial = argv[1];
	}

	sock_fd = initTcpServer(PORT);
	tcpServer_on(e_connect, socketOnConnect);
	tcpServer_on(e_data, socketOnData);
	tcpServer_on(e_close, socketOnClose);

	usrt_fd = open_dev(serial);
	set_parity(usrt_fd,8,1,'N'); // 设置串口数据位、停止位、校验位
	set_speed(usrt_fd,9600); // 设置串口波特率
	serial_on(e_data, serialOnData);

	while(1){
		sleep(1);
	}
	close(sock_fd);
	close(usrt_fd);

	printf("main exit...\n");
	return 0;
}
