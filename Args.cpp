#include "Args.h"

Args::Args()
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

void Args::parse(int argc, char* argv[])
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