exec:	./objs/main.o 
	clang++ -ggdb3 -std=c++11 ./objs/main.o -std=c++11 -o exec

./objs/main.o: main.cpp
	clang++ -std=c++11 -c main.cpp -o ./objs/main.o

run:
	./exec
