CXX = g++
CFLAGS = -std=c++20 -Wall -Wextra -pedantic -g
OBJ = main.o

all : clean program

clean:
	rm -f ipk-sniffer
	rm -f xfindr01.zip

program: main.o
	$(CXX) $(CFLAGS) -o ipk-sniffer main.o -lpcap
	rm -f main.o

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

pack: clean
	zip -r xfindr01.zip .