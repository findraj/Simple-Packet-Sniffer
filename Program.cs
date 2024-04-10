using System;

namespace IPK_2nd_project
{
    abstract class Program
    {
        static int Main(string[] arguments)
        {
            // parse and prepare the arguments
            Args args = new Args();
            args.Parse(arguments);

            if (args.Interface == null)
            {
                Console.WriteLine("usage: ./ipk-sniffer [-i interface | --interface interface] {-p|--port-source|--port-destination port [--tcp|-t] [--udp|-u]} [--arp] [--icmp4] [--icmp6] [--igmp] [--mld] {-n num}");
                Console.WriteLine("interface: name of the network interface");
                Console.WriteLine("port: port number");
                Console.WriteLine("tcp: filter TCP packets");
                Console.WriteLine("udp: filter UDP packets");
                Console.WriteLine("arp: filter ARP packets");
                Console.WriteLine("icmp4: filter ICMPv4 packets");
                Console.WriteLine("icmp6: filter ICMPv6 packets");
                Console.WriteLine("igmp: filter IGMP packets");
                Console.WriteLine("mld: filter MLD packets");
                Console.WriteLine("num: number of packets to capture");
                return 0;
            }

            return 0;
        }
    }
}

