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
            List<Discipline> discList = new List<Discipline>();

            discList.Add(new Discipline("Calculus", 65, new Exam()));
            discList.Add(new Discipline("OOP", 100, new Credit()));
            discList.Add(new Discipline("Computer Logic", 40, new Credit()));
            discList.Add(new Discipline("Physics", 90, new Exam()));

            for (int i = 0; i < discList.Count; i++) 
            {
                Discipline curDisc = discList.ElementAt(i);
                Console.WriteLine("[" + curDisc.name + "] >> " + curDisc.Verdict());
            }

            // End of program
            Console.WriteLine("\n\nPress ANY KEY to exit the program...\n\n");
            Console.ReadKey(true);
        }
    }
}
