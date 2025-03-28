#include "filter.h"

/**
 * @brief Create a filter based on the arguments
 * 
 * @param args object of class Args
 * @return string filter
 
*/
string createFilter(Args args)
{
    string content = "";
    if (args.tcp)
    {
        content += "tcp";
    }

    if (args.udp)
    {
        if (args.tcp)
        {
            content += " or ";
        }
        content += "udp";
    }

    // add conjunction if there is a port
    if ((args.port != -1 || args.portSource != -1 || args.portDestination != -1) && !content.empty())
    {
        content += " and ";
    }

    if (args.port != -1)
    {
        content += "port " + to_string(args.port);
    }

    if (args.portSource != -1)
    {
        content += "src port " + to_string(args.portSource);
    }

    if (args.portDestination != -1)
    {
        content += "dst port " + to_string(args.portDestination);
    }

    if (args.icmp4)
    {
        if (!content.empty())
        {
            content += " or ";
        }
        content += "icmp";
    }

    if (args.icmp6)
    {
        if (!content.empty())
        {
            content += " or ";
        }
        content += "icmp6";
    }

    if (args.arp)
    {
        if (!content.empty())
        {
            content += " or ";
        }
        content += "arp";
    }

    if (args.ndp)
    {
        if (!content.empty())
        {
            content += " or ";
        }
        content += "(icmp6 nad icmp6[0] > 132 and icmp6[1] < 138)";
    }

    if (args.igmp)
    {
        if (!content.empty())
        {
            content += " or ";
        }
        content += "igmp";
    }

    if (args.mld)
    {
        if (!content.empty())
        {
            content += " or ";
        }
        content += "(icmp6 and icmp6[0] > 129 and icmp6[1] < 133)";
    }

    return content;
}