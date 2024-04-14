#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <getopt.h>
#include <cstring>

using namespace std;

void handleError(std::string message)
{
    std::cerr << message << std::endl;
    exit(1);
}

void printHelp()
{
    std::cout << "Usage: ./ipk-sniffer [-i interface | --interface interface] {-p|--port-source|--port-destination port [--tcp|-t] [--udp|-u]} [--arp] [--icmp4] [--icmp6] [--igmp] [--mld] {-n num}" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -i interface, --interface interface" << std::endl;
    std::cout << "  -p port, --port port" << std::endl;
    std::cout << "  --port-source port" << std::endl;
    std::cout << "  --port-destination port" << std::endl;
    std::cout << "  -t, --tcp" << std::endl;
    std::cout << "  -u, --udp" << std::endl;
    std::cout << "  --icmp4" << std::endl;
    std::cout << "  --icmp6" << std::endl;
    std::cout << "  --arp" << std::endl;
    std::cout << "  --ndp" << std::endl;
    std::cout << "  --igmp" << std::endl;
    std::cout << "  --mld" << std::endl;
    std::cout << "  -n num, --number-of-packets num" << std::endl;
    std::cout << "  -h, --help" << std::endl;
    exit(0);
}

class Args
{
    public:
        bool tcp;
        bool udp;
        bool icmp4;
        bool icmp6;
        bool arp;
        bool ndp;
        bool igmp;
        bool mld;
        int numberOfPackets;
        string interface;
        int port;
        int portSource;
        int portDestination;

    Args()
    {
        tcp = false;
        udp = false;
        icmp4 = false;
        icmp6 = false;
        arp = false;
        ndp = false;
        igmp = false;
        mld = false;
        numberOfPackets = 0;
        interface = "";
        port = 0;
        portSource = 0;
        portDestination = 0;
    }

    void parse(int argc, char* argv[])
    {
        if (argc < 2)
        {
            printHelp();
        }

        for (int i = 1; i < argc; i++)
        {
            string arg = argv[i];
            if (arg == "--port-destination")
            {
                if (i + 1 < argc)
                {
                    portDestination = atoi(argv[i + 1]);
                    i++;
                }
                else
                {
                    handleError("Error: port destination is missing");
                }
            }
            else if (arg == "--port-source")
            {
                if (i + 1 < argc)
                {
                    portSource = atoi(argv[i + 1]);
                    i++;
                }
                else
                {
                    handleError("Error: port source is missing");
                }
            }
            else if (arg == "--port" || arg == "-p")
            {
                if (i + 1 < argc)
                {
                    port = atoi(argv[i + 1]);
                    i++;
                }
                else
                {
                    handleError("Error: port is missing");
                }
            }
            else if (arg == "--interface" || arg == "-i")
            {
                if (i + 1 < argc)
                {
                    interface = argv[i + 1];
                    i++;
                }
                else
                {
                    handleError("Error: interface is missing");
                }
            }
            else if (arg == "--number-of-packets" || arg == "-n")
            {
                if (i + 1 < argc)
                {
                    numberOfPackets = atoi(argv[i + 1]);
                    i++;
                }
                else
                {
                    handleError("Error: number of packets is missing");
                }
            }
            else if (arg == "--tcp" || arg == "-t")
            {
                tcp = true;
            }
            else if (arg == "--udp" || arg == "-u")
            {
                udp = true;
            }
            else if (arg == "--icmp4")
            {
                icmp4 = true;
            }
            else if (arg == "--icmp6")
            {
                icmp6 = true;
            }
            else if (arg == "--arp")
            {
                arp = true;
            }
            else if (arg == "--ndp")
            {
                ndp = true;
            }
            else if (arg == "--igmp")
            {
                igmp = true;
            }
            else if (arg == "--mld")
            {
                mld = true;
            }
            else if (arg == "--help" || arg == "-h")
            {
                printHelp();
            }
            else
            {
                handleError("Error: invalid argument");
            
            }
        }
    }
        
};

int main(int argc, char* argv[]) {
    Args args;
    args.parse(argc, argv);
    return 0;
}