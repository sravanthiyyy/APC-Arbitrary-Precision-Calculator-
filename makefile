calculator.exe: main.o add.o sub.o mul.o div.o validation.o
	gcc -o calculator.exe main.o add.o sub.o mul.o div.o validation.o

main.o: main.c
	gcc -c main.c

addition.o: add.c
	gcc -c add.c

subraction.o: sub.c
	gcc -c sub.c

mul.o: mul.c
	gcc -c mul.c

div.o: div.c
	gcc -c div.c

validation.o: validation.c
	gcc -c validation.c

clean:
	rm -f *.exe *.o
