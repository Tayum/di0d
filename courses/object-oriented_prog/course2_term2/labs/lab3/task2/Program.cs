using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    class Program
    {
        static void Main(string[] args)
        {
            UserCache.LoadCache();
            Console.WriteLine("====================USERS====================");

            SimpleUser simpleClone = (SimpleUser)UserCache.GetUser("s1mpl3");
            Console.WriteLine("Username: " + simpleClone.GetUsername());
            Console.WriteLine("Password: " + simpleClone.GetPassword());
            Console.WriteLine("Access level: " + simpleClone.GetAccessLevel().ToString());
            Console.WriteLine("Name: " + simpleClone.GetName());
            Console.WriteLine("Age: " + simpleClone.GetAge());
            Console.WriteLine("City: " + simpleClone.GetCity());

            Console.WriteLine("\n");

            Admin adminClone = (Admin)UserCache.GetUser("adm1n");
            Console.WriteLine("Username: " + adminClone.GetUsername());
            Console.WriteLine("Password: " + adminClone.GetPassword());
            Console.WriteLine("Access level: " + adminClone.GetAccessLevel().ToString());
            Console.WriteLine("Name: " + adminClone.GetName());
            Console.WriteLine("Text color: " + adminClone.GetTextColor().ToString());

            // End of program
            Console.WriteLine("\nPress ANY KEY to exit the program...");
            Console.ReadKey(true);
        }
    }
}
