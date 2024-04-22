#include "Packet.h"

/**
 * @brief Constructor of object of class Packet
 */
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

/**
 * @brief Handle the packet
 * 
 * @param userData user data
 * @param pkthdr packet header
 * @param packet packet
 */
void Packet::handler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet)
{
    char tmp[35]; // temporary variable for snprintf

    struct tm *ltime = localtime(&pkthdr->ts.tv_sec); // get the local time
    char timestr[20]; // time string
    char zone[10]; // time zone
    strftime(timestr, sizeof(timestr), "%FT%T", ltime); // format the time
    strftime(zone, sizeof(zone), "%z", ltime); // get the time zone
    snprintf(tmp, 35, "%s.%.3d%.3s:%.2s", timestr, (int)pkthdr->ts.tv_usec / 1000, zone, zone + 3); // format the time according to the RFC 3339
    timestamp = string(tmp);

    // get the source MAC addresses
    for (int i = 0; i < 6; i++)
    {
        snprintf(tmp, 35, "%02x", packet[i]);
        srcMAC += string(tmp);
        if (i < 5)
        {
            srcMAC += ":";
        }
    }

    // get the destination MAC addresses
    for (int i = 6; i < 12; i++)
    {
        snprintf(tmp, 35, "%02x", packet[i]);
        dstMAC += string(tmp);
        if (i < 11)
        {
            dstMAC += ":";
        }
    }

    // get the frame length
    snprintf(tmp, 35, "%d", pkthdr->len);
    frameLength = string(tmp);

    const struct ether_header *eth_header = (const struct ether_header *)packet; // get the ethernet header
    const struct ip *ip_header = (const struct ip *)(packet + sizeof(struct ether_header)); // get the IP header
    struct tcphdr *tcp_header = (struct tcphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip)); // get the TCP header
    struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip)); // get the UDP header

    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) // if the ethernet type is IP(v4)
    {
        char srcIP4[INET_ADDRSTRLEN];
        char dstIP4[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(ip_header->ip_src), srcIP4, INET_ADDRSTRLEN); // get the source IP address
        inet_ntop(AF_INET, &(ip_header->ip_dst), dstIP4, INET_ADDRSTRLEN); // get the destination IP address
        srcIP = string(srcIP4);
        dstIP = string(dstIP4);

        if (ip_header->ip_p == IPPROTO_TCP) // if the protocol is TCP
        {
            snprintf(tmp, 35, "%d", ntohs(tcp_header->th_sport)); // get the source port
            srcPort = string(tmp);
            snprintf(tmp, 35, "%d", ntohs(tcp_header->th_dport)); // get the destination port
            dstPort = string(tmp);
        }
        else if (ip_header->ip_p == IPPROTO_UDP) // if the protocol is UDP
        {
            snprintf(tmp, 35, "%d", ntohs(udp_header->uh_sport)); // get the source port
            srcPort = string(tmp);
            snprintf(tmp, 35, "%d", ntohs(udp_header->uh_dport)); // get the destination port
            dstPort = string(tmp);
        }
    }
    else if (ntohs(eth_header->ether_type) == ETHERTYPE_IPV6) // if the ethernet type is IPv6
    {
        char srcIP6[INET6_ADDRSTRLEN];
        char dstIP6[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(ip_header->ip_src), srcIP6, INET6_ADDRSTRLEN); // get the source IP address
        inet_ntop(AF_INET6, &(ip_header->ip_dst), dstIP6, INET6_ADDRSTRLEN); // get the destination IP address
        srcIP = string(srcIP6);
        dstIP = string(dstIP6);

        if (ip_header->ip_p == IPPROTO_TCP) // if the protocol is TCP
        
        {
            snprintf(tmp, 35, "%d", ntohs(tcp_header->th_sport)); // get the source port
            srcPort = string(tmp);
            snprintf(tmp, 35, "%d", ntohs(tcp_header->th_dport)); // get the destination port
            dstPort = string(tmp);
        }
        else if (ip_header->ip_p == IPPROTO_UDP) // if the protocol is UDP
        {
            snprintf(tmp, 35, "%d", ntohs(udp_header->uh_sport)); // get the source port
            srcPort = string(tmp);
            snprintf(tmp, 35, "%d", ntohs(udp_header->uh_dport)); // get the destination port
            dstPort = string(tmp);
        }
    }
    else{
        struct ether_arp *arp_header = (struct ether_arp *)(packet + sizeof(struct ether_header)); // get the ARP header
        char arpSrcIP[INET_ADDRSTRLEN];
        char arpDstIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, arp_header->arp_spa, arpSrcIP, INET_ADDRSTRLEN); // get the source IP address
        inet_ntop(AF_INET, arp_header->arp_tpa, arpDstIP, INET_ADDRSTRLEN); // get the destination IP address
        srcIP = string(arpSrcIP);
        dstIP = string(arpDstIP);
    }

    int offset = 0;
    const u_char *data;
    while (offset < (int)pkthdr->len) // go through the packet
    {
        char tmp[44]; // temporary variable for snprintf
        string line = "";
        data = packet + offset;

        snprintf(tmp, 35, "0x%04x:", offset); // get the offset
        line += string(tmp);

        // hexadecimal representation
        for (int i = 0; i < widthOfData; i++) // go through the data
        {
            if (i + offset < (int)pkthdr->len) // if there are more bytes left
            {
                snprintf(tmp, 35, " %02x", data[i]);
                line += string(tmp);
            }
            else // there are less than 16 bytes left
            {
                line += "   "; // spacer to align the last line
            }
        }

        line += " "; // spacer

        // ASCII representation
        for (int i = 0; i < widthOfData; i++) // go through the data
        {
            if (i + offset < (int)pkthdr->len) // if there are more bytes left
            {
                if (i % 8 == 0 && i / 8 == 1) // spacer after 8 bytes
                {
                    line += " ";
                }

                if (isprint(data[i])) // if the character is printable
                {
                    snprintf(tmp, 35, "%c", data[i]);
                    line += string(tmp);
                }
                else // if the character is not printable
                {
                    line += ".";
                }
            }
            else // there are less than 16 bytes left
            {
                line += " ";
            }
        }

        byteOffset.push_back(line);
        offset += widthOfData;
    }

    // unused variable, just to avoid the warning
    (void)userData;
}

void Packet::print()
{
    cout << "timestamp: " << timestamp << endl;
    cout << "src MAC: " << srcMAC << endl;
    cout << "dst MAC: " << dstMAC << endl;
    cout << "frame length: " << frameLength << " bytes" << endl;
    cout << "src IP: " << srcIP << endl;
    cout << "dst IP: " << dstIP << endl;
    if (srcPort != "") // if port source was given
    {
        cout << "src port: " << srcPort << endl;
    }
    if (dstPort != "") // if port destination was given
    {
        cout << "dst port: " << dstPort << endl;
    }
    
    for (int i = 0; i < (int)byteOffset.size(); i++) // print all data
    {
        cout << byteOffset[i] << endl;
    }
}