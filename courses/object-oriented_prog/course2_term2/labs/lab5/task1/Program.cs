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
            User user = new User();

            // Perform some actions
            user.EditText('A', 0, "First string"); // add "First string" at [0]
            user.EditText('A', 1, "Third string"); // add "Third string" at [1]
            user.EditText('A', 1, "Second string"); // add "Second string" at [1]
            user.EditText('B', 1, ""); // make string at [1] ("Second string") *bold*
            user.EditText('I', 2, ""); // make string at [2] ("Third string") _italic_
            user.PrintText();
            Console.WriteLine("\n\nPress ANY KEY to continue...\n\n");
            Console.ReadKey(true);

            // redo (first) 3 operations
            user.ClearText();
            user.PrintText();
            user.Redo(3);
            user.PrintText();
            Console.WriteLine("\n\nPress ANY KEY to continue...\n\n");
            Console.ReadKey(true);

            // redo (last) 2 operations
            user.Redo(2);
            user.PrintText();

            // End of program
            Console.WriteLine("\n\nPress ANY KEY to exit the program...");
            Console.ReadKey(true);
        }
    }
}
