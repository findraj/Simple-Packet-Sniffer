#include "Packet.h"

Packet::Packet()
{
}

void Packet::handler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    struct tm *ltime = localtime(&pkthdr->ts.tv_sec);
    char timestr[20];
    char zone[19];
    strftime(timestr, sizeof(timestr), "%FT%T", ltime);
    strftime(zone, sizeof(zone), "%z", ltime);
    string zoneStr(zone);
    cout << timestr << "." << pkthdr->ts.tv_sec % 1000 << zoneStr.substr(0, 3) << ":" << zoneStr.substr(3,5) << endl;
}