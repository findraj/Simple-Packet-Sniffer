#include "main.h"

using namespace std;

/**
 * @brief Handle loaded packets
 * 
 * @param userData user data
 * @param pkthdr packet header
 * @param packet packet
 */
void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    Packet p; // create a packet object
    p.handler(userData, pkthdr, packet); // handle the packet
    p.print(); // print the packet
}

/**
 * @brief main function
 * 
 * @param argc number of arguments from the command line
 * @param argv array of arguments from the command line
 */
int main(int argc, char* argv[]) {
    char errbuf[PCAP_ERRBUF_SIZE]; // error buffer
    Args args; // create an object of class Args
    args.parse(argc, argv); // parse the arguments

    if (args.interface == "")
    {
        pcap_if_t *alldevsp; // all devices
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

    if (pcap_lookupnet(args.interface.c_str(), &net, &mask, errbuf) == -1) // get the network and mask
    {
        handleError("Error: cannot find any device: " + string(errbuf));
    }

    pcap_t *handle = pcap_open_live(args.interface.c_str(), BUFSIZ, 1, 1000, errbuf); // open the device
    if (handle == NULL)
    {
        handleError("Error: cannot open device: " + string(errbuf));
    }

    if (pcap_datalink(handle) != DLT_EN10MB)
    {
        handleError("Error: device is not Ethernet: " + string(errbuf));
    }

    string filter = createFilter(args); // create a filter based on the arguments

    struct bpf_program fp;

    if (pcap_compile(handle, &fp, filter.c_str(), 0, mask) == PCAP_ERROR) // compile the filter
    {
        handleError("Error: cannot compile filter: " + string(pcap_geterr(handle)));
    }

    if (pcap_setfilter(handle, &fp) == PCAP_ERROR) // set the filter
    {
        handleError("Error: cannot set filter: " + string(pcap_geterr(handle)));
    }

    if (pcap_loop(handle, args.numberOfPackets, packetHandler, NULL) == PCAP_ERROR) // capture packets
    {
        handleError("Error: cannot capture packets: " + string(pcap_geterr(handle)));
    }

    return 0;
}