CXX = g++
CFLAGS = -std=c++20 -Wall -Wextra -pedantic -g
OBJ = main.o

all : clean program

clean:
	rm -f ipk-sniffer
	rm -f xfindr01.zip

program: main.o Args.o utils.o filter.o Packet.o
	$(CXX) $(CFLAGS) -o ipk-sniffer main.o Args.o utils.o filter.o Packet.o -lpcap
	rm -f main.o
	rm -f Args.o
	rm -f utils.o
	rm -f filter.o
	rm -f Packet.o

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

Args.o: Args.cpp
	$(CXX) $(CFLAGS) -c Args.cpp

utils.o: utils.cpp
	$(CXX) $(CFLAGS) -c utils.cpp

filter.o: filter.cpp
	$(CXX) $(CFLAGS) -c filter.cpp

Packet.o: Packet.cpp
	$(CXX) $(CFLAGS) -c Packet.cpp

pack: clean
	zip -r xfindr01.zip .

test: program
	sudo ./ipk-sniffer -i eth0