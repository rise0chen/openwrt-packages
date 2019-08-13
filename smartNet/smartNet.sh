#!/bin/sh /etc/rc.common
USE_PROCD=1
PROCD_DEBUG=1
SERVICE=smartNet

start_service() {
	procd_open_instance
	procd_set_param command /usr/bin/smartNet
	procd_set_param respawn 3600 120 30
	procd_set_param stdout 1
	procd_set_param stderr 1
	procd_close_instance
}
