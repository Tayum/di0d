using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class Program
    {
        static void Main(string[] args)
        {
            Director constructor = Director.getInstance();

            Console.WriteLine("====================FRESHMAN====================");
            // Build
            InfolistBuilder freshmanBuilder = new FreshmanBuilder();
            Infolist freshmanInfolist = constructor.GenerateInfolist(freshmanBuilder);
            // Print
            Console.WriteLine(freshmanInfolist.infolistType);
            Console.WriteLine(freshmanInfolist.map);
            Console.WriteLine(freshmanInfolist.courses_info);
            Console.WriteLine(freshmanInfolist.diplomas_info);

            Console.WriteLine("\n========================================\n");

            Console.WriteLine("====================MASTER====================");
            // Build
            InfolistBuilder masterBuilder = new MasterBuilder();
            Infolist masterInfolist = constructor.GenerateInfolist(masterBuilder);
            // Print
            Console.WriteLine(masterInfolist.infolistType);
            Console.WriteLine(masterInfolist.map);
            Console.WriteLine(masterInfolist.courses_info);
            Console.WriteLine(masterInfolist.diplomas_info);

            // End of program
            Console.WriteLine("\nPress ANY KEY to exit the program...");
            Console.ReadKey(false);
        }
    }
}