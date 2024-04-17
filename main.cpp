#include "Filter.h"

using namespace std;

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

    Filter filter(args);

    struct bpf_program fp;

    if (pcap_compile(handle, &fp, filter.content.c_str(), 0, mask) == PCAP_ERROR)
    {
        handleError("Error: cannot compile filter: " + string(pcap_geterr(handle)));
    }

    if (pcap_setfilter(handle, &fp) == PCAP_ERROR)
    {
        handleError("Error: cannot set filter: " + string(pcap_geterr(handle)));
    }

    return 0;
}