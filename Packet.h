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
        ether_header etherHeader;
        ip Ip;
        tcphdr tcpHeader;
        udphdr udpHeader;
        Packet();
        static void handler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);
};