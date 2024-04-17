#include "Packet.h"

Packet::Packet()
{
    timestamp = "";
    srcMAC = "";
    dstMAC = "";
    frameLength = "";
    srcIP = "";
    dstIP = "";
    srcPort = "";
    dstPort = "";
    byteOffset = "";
}

void Packet::handler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    char tmp[30];

    struct tm *ltime = localtime(&pkthdr->ts.tv_sec);
    char timestr[20];
    char zone[10];
    strftime(timestr, sizeof(timestr), "%FT%T", ltime);
    strftime(zone, sizeof(zone), "%z", ltime);
    string zoneStr(zone);
    sprintf(tmp, "%s.%03ld%.3s:%.2s", timestr, pkthdr->ts.tv_usec / 1000, zone, zone + 3);
    timestamp = string(tmp);

    for (int i = 0; i < 6; i++)
    {
        sprintf(tmp, "%02x", packet[i]);
        srcMAC += string(tmp);
        if (i < 5)
        {
            srcMAC += ":";
        }
    }

    for (int i = 6; i < 12; i++)
    {
        sprintf(tmp, "%02x", packet[i]);
        dstMAC += string(tmp);
        if (i < 11)
        {
            dstMAC += ":";
        }
    }

    sprintf(tmp, "%d", pkthdr->len / 8);
    frameLength = string(tmp);
}

void Packet::print()
{
    cout << "timestamp: " << timestamp << endl;
    cout << "src MAC: " << srcMAC << endl;
    cout << "dst MAC: " << dstMAC << endl;
    cout << "frame length: " << frameLength << " bytes" << endl;
    cout << "src IP: " << srcIP << endl;
    cout << "dst IP: " << dstIP << endl;
    cout << "src port: " << srcPort << endl;
    cout << "dst port: " << dstPort << endl;
    cout << "byte_offset: " << byteOffset << endl;
}