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
            // All the musicians
            ProdCentre prodcentre = new ProdCentre();
            prodcentre.AddMusician(new Antitela());
            prodcentre.AddMusician(new OkeanElzy());
            prodcentre.AddMusician(new Skryabin());
            prodcentre.AddMusician(new DDT());

            // Three orders of "clients"
            List<string> desiredList1 = new List<string>();
            desiredList1.Add("Antitela");
            desiredList1.Add("OkeanElzy");
            desiredList1.Add("Metallica");
            List<string> desiredList2 = new List<string>();
            desiredList2.Add("OkeanElzy");
            desiredList2.Add("Skryabin");
            List<string> desiredList3 = new List<string>();
            desiredList3.Add("Skryabin");
            desiredList3.Add("DDT");

            // Formed programs for clients
            string program = "";
            program = prodcentre.CreateProgram(desiredList1);
            Console.WriteLine(program);
            program = prodcentre.CreateProgram(desiredList2);
            Console.WriteLine(program);
            program = prodcentre.CreateProgram(desiredList3);
            Console.WriteLine(program);

            // End of program
            Console.WriteLine("Press ANY KEY to exit the program...");
            Console.ReadKey(true);
        }
    }
}
