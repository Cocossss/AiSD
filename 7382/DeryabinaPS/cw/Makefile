all: cw.exe

cw.exe: cw.o API.o ./Source/API.h
	gcc cw.o API.o -o cw.exe

cw.o: ./Source/cw.c ./Source/API.h
	gcc -c ./Source/cw.c

API.o: ./Source/API.c ./Source/API.h
	gcc -c ./Source/API.c

clean:
	rm -rf *.o
