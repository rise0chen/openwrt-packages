/********************************************************************************
 *      Copyright:  (C) 2016 Lu Zengmeng<1540999272@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  serial.h
 *    Description:  This head file
 *
 *        Version:  1.0.0(08/01/2016)
 *         Author:  Lu Zengmeng <1540999272@qq.com>
 *      ChangeLog:  1, Release initial version on "08/01/2016 06:44:25 PM"
 *
 ********************************************************************************/
#ifndef __SERIAL_H__
#define __SERIAL_H__
#include "config.h"

extern int  set_speed(int fd, int speed);
extern int  set_parity(int fd,int databits,int stopbits,int parity);
extern void serial_on(callbackType type, void (*fun)(char *data, unsigned char len));
extern int  open_dev(char *dev);
extern void serial_send(char *data, unsigned char len);
#endif
