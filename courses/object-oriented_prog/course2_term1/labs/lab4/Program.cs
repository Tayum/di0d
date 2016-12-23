using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using System.Runtime.Serialization.Json;

// Martin: Clean Code [F1]:
// >> Function should not take more than 3 arguments;
// Not a single function in this program [except for Constructors] takes more than 3 arguments;

// Martin: Clean Code [F3]:
// >> Function should not take the flag as the argument;
// Not a single function in this program takes a flag as the argument;

// Martin: Clean Code [F4]:
// >> Function should not be unused in program. Delete it if it is unneeded;
// Not a single function in this program [except for unused in current lab4] is being unused;


// Martin: Clean Code [N1]:
// >> Variable names are describing the data they are in a charge of;

// Martin: Clean Code [N5]:
// >> Use long names for 'long' scopes*
//  * - and small (1-char) names if the variable is used in next <=5 LOCs.

// Martin: Clean Code [N6]:
// >> Do not use prefixes in variable names (for example, to describe variable type or scope);


// Martin: Clean Code [G1]:
// >> Do not use several languages in one file;
// There are no other languages except for C# used in all of files.

// Martin: Clean Code [G4]:
// >> Do not ignore the compiler WARNINGs;
// Not a single warning appears when this program is being compiled;

// Martin: Clean Code [G7]:
// >> Base classes should not know anything about their Derivative classes;

// Martin: Clean Code [G9]:
// >> Dead/unreachable code should be deleted;
// >> Do not check impossible statements in if()/switch blocks;


namespace lab4
{
    class Program
    {
        private static WeakReference weakRef;

        private static void refTest()
        {
            // Martin: Clean Code [G5]:
            // >> Do not duplicate code;
            // Martin: Clean Code [G29]:
            // >> Try not to use negative statements;
            // Fauler: Refactoring
            // >> Consolidate Conditional Expression

            if (weakRef == null || ((Hero)weakRef.Target) == null)
            {
                weakRef = new WeakReference(new Hero());
            }


            /* [G5] / [G29]
            Hero thyHero = null;
            if (weakRef != null)
            {
                thyHero = (Hero)weakRef.Target;
                if (thyHero == null)
                {
                    thyHero = new Hero();
                    weakRef = new WeakReference(thyHero);
                }
            }
            else
            {
                thyHero = new Hero();
                weakRef = new WeakReference(thyHero);
            }*/

            /*// [Refactoring]
            if (weakRef == null)
            {
                weakRef = new WeakReference(new Hero());
            }
            else
            {
                if ((Hero)weakRef.Target == null)
                {
                    weakRef = new WeakReference(new Hero());
                }
            }*/
        }


        static void Main(string[] args)
        {
            // Weak Reference
            Console.Write("RIGHT NOW ");
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.Write(GC.GetTotalMemory(true));
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine(" BYTES ARE ALLOCATED...");
            for (int i = 0; i < 10; i++)
            {
                refTest();
                Console.Write("[" + i + "] ITERATION: ");
                Console.ForegroundColor = ConsoleColor.DarkRed;
                Console.Write(GC.GetTotalMemory(true));
                Console.ForegroundColor = ConsoleColor.Gray;
                Console.WriteLine(" BYTES ARE ALLOCATED;");
            }
            Console.WriteLine("\n****************************\n");

            // Dispose
            Console.Write("RIGHT NOW ");
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.Write(GC.GetTotalMemory(true));
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine(" BYTES ARE ALLOCATED...");
            HeroCollection heroCollection = new HeroCollection();
            for (int i = 0; i < 4; i++)
            {
                heroCollection.Add(new Hero());
            }

            Console.Write("[" + heroCollection.Count + "] HEROES ADDED: ");
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.Write(GC.GetTotalMemory(true));
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine(" BYTES ARE ALLOCATED...");

            heroCollection.Dispose();
            Console.Write("HERO COLLECTION DISPOSED: ");
            Console.ForegroundColor = ConsoleColor.DarkRed;
            Console.Write(GC.GetTotalMemory(true));
            Console.ForegroundColor = ConsoleColor.Gray;
            Console.WriteLine(" BYTES ARE ALLOCATED...");

            // GC.Collect() will invoke the Hero Destructor
            Hero thyHero = new Hero();
            thyHero = null;
            GC.Collect();

            // End of program
            Console.WriteLine("Press ANY KEY to proceed...");
            Console.ReadKey();
        }


    }
}
