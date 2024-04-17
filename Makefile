CXX = g++
CFLAGS = -std=c++20 -Wall -Wextra -pedantic -g
OBJ = main.o

all : clean program

clean:
	rm -f ipk-sniffer
	rm -f xfindr01.zip

program: main.o Args.o utils.o
	$(CXX) $(CFLAGS) -o ipk-sniffer main.o Args.o utils.o -lpcap
	rm -f main.o
	rm -f Args.o
	rm -f utils.o

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

Args.o: Args.cpp
	$(CXX) $(CFLAGS) -c Args.cpp

utils.o: utils.cpp
	$(CXX) $(CFLAGS) -c utils.cpp

pack: clean
	zip -r xfindr01.zip .

test: program
	sudo ./ipk-sniffer -i eth0