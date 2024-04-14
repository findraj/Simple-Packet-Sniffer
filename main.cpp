#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <getopt.h>
#include <cstring>
#include <pcap.h>

using namespace std;

void handleError(std::string message)
{
    cerr << message << std::endl;
    exit(1);
}

void printHelp()
{
    cout << "Usage: ./ipk-sniffer [-i interface | --interface interface] {-p|--port-source|--port-destination port [--tcp|-t] [--udp|-u]} [--arp] [--icmp4] [--icmp6] [--igmp] [--mld] {-n num}" << std::endl;
    cout << "Options:" << std::endl;
    cout << "  -i interface, --interface interface" << std::endl;
    cout << "  -p port, --port port" << std::endl;
    cout << "  --port-source port" << std::endl;
    cout << "  --port-destination port" << std::endl;
    cout << "  -t, --tcp" << std::endl;
    cout << "  -u, --udp" << std::endl;
    cout << "  --icmp4" << std::endl;
    cout << "  --icmp6" << std::endl;
    cout << "  --arp" << std::endl;
    cout << "  --ndp" << std::endl;
    cout << "  --igmp" << std::endl;
    cout << "  --mld" << std::endl;
    cout << "  -n num, --number-of-packets num" << std::endl;
    cout << "  -h, --help" << std::endl;
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
    char errbuf[PCAP_ERRBUF_SIZE];
    Args args;
    args.parse(argc, argv);

    if (args.interface == "")
    {
        pcap_if_t *alldevsp;
        if (pcap_findalldevs(&alldevsp, NULL) == -1)
        {
            handleError("Error: cannot find any device");
        }
        pcap_if_t *device = alldevsp;
        cout << "Available devices:" << endl;
        while (device != NULL)
        {
            cout << device->name << endl;
            device = device->next;
        }
        pcap_freealldevs(alldevsp);
        return 1;
    }

    bpf_u_int32 mask;
    bpf_u_int32 net;

    if (pcap_lookupnet(args.interface.c_str(), &net, &mask, errbuf) == -1)
    {
        handleError("Error: cannot find any device: " + string(errbuf));
    }

    pcap_t *handle = pcap_open_live(args.interface.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL)
    {
        handleError("Error: cannot open device: " + string(errbuf));
    }

    if (pcap_datalink(handle) != DLT_EN10MB)
    {
        handleError("Error: device is not Ethernet: " + string(errbuf));
    }

    return 0;
}