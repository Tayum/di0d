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
            List<string> ballotList = new List<string>();
            ballotList.Add("ArnoldSchwarznegger");
            ballotList.Add("LawrenceOfArabia");
            ballotList.Add("ChuckNorris");
            ballotList.Add("LawrenceOfArabia");
            ballotList.Add("ChuckNorris");
            ballotList.Add("ArnoldSchwarznegger");
            ballotList.Add("ChuckNorris");
            
            BallotFactory factory = new BallotFactory();
            // Outer state
            int counterMark = 1;
            
            foreach (string ballotString in ballotList)
            {
                Console.WriteLine("====================");
                Ballot ballot = factory.GetBallot(ballotString);
                ballot.Display(counterMark);
                Console.WriteLine("<<\nOUTER COUNTER-MARK: " + counterMark + "\n<<");
                Console.WriteLine("====================");
                counterMark++;
            }

            // End of the program
            Console.WriteLine("\nPress ANY KEY to exit the program...\n");
            Console.ReadKey(true);
        }
    }
}
