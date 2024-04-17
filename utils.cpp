#include "utils.h"

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