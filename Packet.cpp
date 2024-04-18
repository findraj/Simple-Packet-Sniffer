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
    byteOffset = vector<string>();
}

void Packet::handler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    char tmp[35];

    struct tm *ltime = localtime(&pkthdr->ts.tv_sec);
    char timestr[20];
    char zone[10];
    strftime(timestr, sizeof(timestr), "%FT%T", ltime);
    strftime(zone, sizeof(zone), "%z", ltime);
    sprintf(tmp, "%s.%.3d%.3s:%.2s", timestr, (int)pkthdr->ts.tv_usec / 1000, zone, zone + 3);
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

    const struct ether_header *eth_header = (const struct ether_header *)packet;
    const struct ip *ip_header = (const struct ip *)(packet + sizeof(struct ether_header));
    struct tcphdr *tcp_header = (struct tcphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip));
    struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip));

    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP)
    {
        char srcIP4[INET_ADDRSTRLEN];
        char dstIP4[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_src), srcIP4, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(ip_header->ip_dst), dstIP4, INET_ADDRSTRLEN);
        srcIP = string(srcIP4);
        dstIP = string(dstIP4);

        if (ip_header->ip_p == IPPROTO_TCP)
        {
            sprintf(tmp, "%d", ntohs(tcp_header->th_sport));
            srcPort = string(tmp);
            sprintf(tmp, "%d", ntohs(tcp_header->th_dport));
            dstPort = string(tmp);
        }
        else if (ip_header->ip_p == IPPROTO_UDP)
        {
            sprintf(tmp, "%d", ntohs(udp_header->uh_sport));
            srcPort = string(tmp);
            sprintf(tmp, "%d", ntohs(udp_header->uh_dport));
            dstPort = string(tmp);
        }
    }
    else if (ntohs(eth_header->ether_type) == ETHERTYPE_IPV6)
    {
        char srcIP6[INET6_ADDRSTRLEN];
        char dstIP6[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(ip_header->ip_src), srcIP6, INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &(ip_header->ip_dst), dstIP6, INET6_ADDRSTRLEN);
        srcIP = string(srcIP6);
        dstIP = string(dstIP6);

        if (ip_header->ip_p == IPPROTO_TCP)
        {
            sprintf(tmp, "%d", ntohs(tcp_header->th_sport));
            srcPort = string(tmp);
            sprintf(tmp, "%d", ntohs(tcp_header->th_dport));
            dstPort = string(tmp);
        }
        else if (ip_header->ip_p == IPPROTO_UDP)
        {
            sprintf(tmp, "%d", ntohs(udp_header->uh_sport));
            srcPort = string(tmp);
            sprintf(tmp, "%d", ntohs(udp_header->uh_dport));
            dstPort = string(tmp);
        }
    }
    else{
        struct ether_arp *arp_header = (struct ether_arp *)(packet + sizeof(struct ether_header));
        char arpSrcIP[INET_ADDRSTRLEN];
        char arpDstIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, arp_header->arp_spa, arpSrcIP, INET_ADDRSTRLEN);
        inet_ntop(AF_INET, arp_header->arp_tpa, arpDstIP, INET_ADDRSTRLEN);
        srcIP = string(arpSrcIP);
        dstIP = string(arpDstIP);
    }

    int offset = 0;
    const u_char *data;
    while (offset < (int)pkthdr->len)
    {
        char tmp[44];
        string line = "";
        data = packet + offset;

        sprintf(tmp, "0x%04x:", offset);
        line += string(tmp);

        for (int i = 0; i < widthOfData; i++)
        {
            if (i + offset < (int)pkthdr->len)
            {
                sprintf(tmp, " %02x", data[i]);
                line += string(tmp);
            }
            else // there are less than 16 bytes left
            {
                line += "   "; // spacer to align the last line
            }
        }

        line += " ";

        for (int i = 0; i < widthOfData; i++)
        {
            if (i + offset < (int)pkthdr->len)
            {
                if (i % 8 == 0 && i / 8 == 1)
                {
                    line += " ";
                }

                if (isprint(data[i]))
                {
                    sprintf(tmp, "%c", data[i]);
                    line += string(tmp);
                }
                else
                {
                    line += ".";
                }
            }
            else
            {
                line += " ";
            }
        }

        byteOffset.push_back(line);
        offset += widthOfData;
    }
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
    
    for (int i = 0; i < (int)byteOffset.size(); i++)
    {
        cout << byteOffset[i] << endl;
    }
}