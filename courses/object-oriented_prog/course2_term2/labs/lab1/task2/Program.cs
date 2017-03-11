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
            // Library
            Bookholder library = new Bookholder("MY LIBRARY");

            // Branches
            Bookholder branch1 = new Bookholder("Branch_A");
            library.Add(branch1);
            Bookholder branch2 = new Bookholder("Branch_B");
            library.Add(branch2);

            // Racks
            Bookholder rack1 = new Bookholder("Literature rack");
            Bookholder rack2 = new Bookholder("Detectives rack");
            Bookholder rack3 = new Bookholder("FairyTales rack");
            branch1.Add(rack1);
            branch1.Add(rack2);
            branch2.Add(rack3);

            // Books
            Book b1 = new Book("Book");
            System.Threading.Thread.Sleep(25);
            Book b2 = new Book("Booker");
            System.Threading.Thread.Sleep(25);
            Book b3 = new Book("MoreBook");
            System.Threading.Thread.Sleep(25);
            Book b4 = new Book("TheBookest");

            rack1.Add(b1);
            rack2.Add(b2);
            rack2.Add(b3);
            rack3.Add(b4);

            // Display all the info
            library.GetBooksInfo();
            library.Display(3);

            Console.WriteLine("\nUNIQUE BOOKS IN LIBRARY: " + library.GetAllBooksWithUniqueCipher() + " BOOKS!");

            // End of program
            Console.WriteLine("\n\nPress ANY KEY to exit the program...");
            Console.ReadKey();
        }
    }
}
