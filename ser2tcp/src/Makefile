NAME = ser2tcp
MYFLAGS += -Wall
MYFLAGS += -lpthread

$(NAME): main.o serial.o tcpClient.o tcpServer.o
	$(CC) $(LDFLAGS) -o $@ $^  $(MYFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -c $<      $(MYFLAGS)

clean:
	rm -rf *.o $(NAME)
