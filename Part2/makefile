.PHONY: build rebuild clean_all clean_obj clean_lab1
	
build: lab1
	./lab1 Ident

rebuild: clean_all lab1
	./lab1 Ident

clean_all: clean_obj clean_lab1
	
clean_obj:
	rm -rvf *.o

clean_lab1:
	rm -rvf lab1

lab1: main.o
	gcc -o lab1 main.o

main.o: main.c
	gcc -c -o main.o main.c
