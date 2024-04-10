namespace IPK_2nd_project
{
    abstract class Program
    {
        static int Main(string[] arguments)
        {
            // parse and prepare the arguments
            Args args = new Args();
            args.Parse(arguments);

            return 0;
        }
    }
}

