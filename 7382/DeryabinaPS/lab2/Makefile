all: lab2.exe

lab2.exe: lab2.o API.o ./Sources/API.h
	gcc lab2.o API.o -o lab2.exe

lab2.o: ./Sources/lab2.c ./Sources/API.h
	gcc -c ./Sources/lab2.c

API.o: ./Sources/API.c ./Sources/API.h
	gcc -c ./Sources/API.c

clean:
	rm -rf *.o
