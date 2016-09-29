#makefile
serial:serial.c
	gcc -c serial.c pipe.c config.c protocol.c 
	gcc -shared -o libserial.so serial.o pipe.o config.o protocol.o
install:
	@sudo mv libserial.so /usr/lib
clean:
	@echo "clean project"
	-rm *.o
	@echo "clean complete"
.PHONY:clean
