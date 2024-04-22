#include "filter.h"
#include "Packet.h"

void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet);

int main(int argc, char* argv[]);