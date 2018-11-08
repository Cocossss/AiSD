all: lab4.exe

lab4.exe: lab4.o API.o ./Source/API.h
	gcc lab4.o API.o -o lab4.exe

lab4.o: ./Source/lab4.c ./Source/API.h
	gcc -c ./Source/lab4.c

API.o: ./Source/API.c ./Source/API.h
	gcc -c ./Source/API.c

clean:
	rm -rf *.o
