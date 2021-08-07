all: code

code: main.o
	g++ main.o -o code

main.o: main.cpp
	g++ -std=c++14 -c main.cpp 

clean:
	rm -f *o code

run: code
		./code
