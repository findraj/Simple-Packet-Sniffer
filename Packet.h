#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include "utils.h"
#include <chrono>
#include <iomanip>

class Packet
{
    public:
        string timestamp;
        string srcMAC;
        string dstMAC;
        string frameLength;
        string srcIP;
        string dstIP;
        string srcPort;
        string dstPort;
        string byteOffset;
        Packet();
        void handler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);
        void print();
};