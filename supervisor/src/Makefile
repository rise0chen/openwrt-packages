NAME = supervisor
MYFLAGS += -Wall

$(NAME): main.o
	$(CC) $(LDFLAGS) -o $@ $^  $(MYFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -c $<      $(MYFLAGS)

clean:
	rm -rf *.o $(NAME)
