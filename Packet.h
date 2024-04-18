#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include "utils.h"
#include <chrono>
#include <iomanip>
#include <vector>

const int widthOfData = 16;

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
        vector<string> byteOffset;
        Packet();
        void handler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);
        void print();
};