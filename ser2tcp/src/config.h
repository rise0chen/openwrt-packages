#ifndef __CONFIG_H_
#define __CONFIG_H_

#define CLIENT_NUM  256 //客户端最大数量
#define BUF_SIZE    256 //消息长度

#define  IPADDR      "0.0.0.0" //IP地址
#define  PORT        16464 //端口号
#define  DEVICE      "/dev/ttyS1" //串口地址


typedef enum{
	e_connect=0,
	e_data,
	e_close
} callbackType;

#endif
