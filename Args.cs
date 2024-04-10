namespace IPK_2nd_project;

public class Args
{
    public ushort PortSource;
    public ushort PortDestination;
    public ushort Port;
    public bool Tcp;
    public bool Udp;
    public string? Interface;
    public int NumberOfPackets;
    public bool Icmp4;
    public bool Icmp6;
    public bool Arp;
    public bool Ndp;
    public bool Igmp;
    public bool Mld;


    public void Parse(string[] args)
    {
        Tcp = false;
        Udp = false;
        Icmp4 = false;
        Icmp6 = false;
        Arp = false;
        Ndp = false;
        Igmp = false;
        Mld = false;
        NumberOfPackets = 1;
        Interface = null;
        
        if (args.Length == 0)
        {
            Stderr.Write("No arguments");
            return;
        }

        // ./ipk-sniffer [-i interface | --interface interface] {-p|--port-source|--port-destination port [--tcp|-t] [--udp|-u]} [--arp] [--icmp4] [--icmp6] [--igmp] [--mld] {-n num}
        for (int index = 0; index < args.Length; index++)
        {
            string current = args[index];
            if (current == "--port-destinations" || current == "--port-source" || current == "-p")
            {
                if (index + 1 < args.Length)
                {
                    if (current == "--port-destinations")
                    {
                        PortDestination = ushort.Parse(args[++index]);
                    }
                    else if (current == "--port-source")
                    {
                        PortSource = ushort.Parse(args[++index]);
                    }
                    else
                    {
                        Port = ushort.Parse(args[++index]);
                    }
                }

                if (index + 1 < args.Length)
                {
                    if (args[++index] == "--tcp" || args[index] == "-t")
                    {
                        Tcp = true;
                    }
                    else if (args[index] == "--udp" || args[index] == "-u")
                    {
                        Udp = true;
                    }
                }
            }
            else if (current == "-i" || current == "--interface")
            {
                if (index + 1 < args.Length)
                {
                    Interface = args[++index];
                }
            }
            else if (current == "--icmp4")
            {
                Icmp4 = true;
            }
            else if (current == "--icmp6")
            {
                Icmp6 = true;
            }
            else if (current == "--arp")
            {
                Arp = true;
            }
            else if (current == "--ndp")
            {
                Ndp = true;
            }
            else if (current == "--igmp")
            {
                Igmp = true;
            }
            else if (current == "--mld")
            {
                Mld = true;
            }
            else if (current == "-n")
            {
                if (index + 1 < args.Length)
                {
                    NumberOfPackets = int.Parse(args[++index]);
                }
            }
            else
            {
                Stderr.Write("Wrong argument");
            }
        }
    }
}