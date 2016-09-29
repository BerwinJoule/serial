all:
	make -C library
	make -C library install
	make -C library clean
	#gcc main.c -lserial -o serial;
	g++ main.cpp -lserial -o serial;
	mv serial out/
	echo !!!!!!success!!!!!!!!
	echo !!!!!!success!!!!!!!!
	echo !!!!!!success!!!!!!!!
	echo !!!!!!success!!!!!!!!
clean:
	@echo "clean project"
	-rm *.o
	@echo "clean complete"
.PHONY:clean
