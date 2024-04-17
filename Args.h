#include "utils.h"

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
        Args();
        void parse(int argc, char* argv[]);
};