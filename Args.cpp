#include "Args.h"
/**
 * @brief Constructor of object of class Args
*/
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
    numberOfPackets = 1;
    interface = "";
    port = -1;
    portSource = -1;
    portDestination = -1;
}

/**
 * @brief Parse the arguments from the command line\
 * 
 * @param argc number of arguments
 * @param argv array of arguments
*/
void Args::parse(int argc, char* argv[])
    {
        for (int i = 1; i < argc; i++) // start from 1 to skip the program name
        {
            string arg = argv[i];
            if (arg == "--port-destination")
            {
                if (port != -1) // if port is set, then it is not possible to set port destination
                {
                    handleError("Error: port destination is already set");
                }
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
                if (port != -1) // if port is set, then it is not possible to set port source
                {
                    handleError("Error: port source is already set");
                }
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
                if (portSource != -1 || portDestination != -1) // if port source or port destination is set, then it is not possible to set port
                {
                    handleError("Error: ports are already set");
                }
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