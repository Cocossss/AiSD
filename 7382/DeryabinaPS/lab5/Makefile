all: lab5.exe

lab5.exe: lab5.o API.o ./Source/API.h
	gcc lab5.o API.o -o lab5.exe

lab5.o: ./Source/lab5.c ./Source/API.h
	gcc -c ./Source/lab5.c

API.o: ./Source/API.c ./Source/API.h
	gcc -c ./Source/API.c

clean:
	rm -rf *.o
