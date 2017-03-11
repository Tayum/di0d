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
            const string path = "C:\\Users\\Student\\Documents\\Different\\Course_2\\vsProjects\\lab1\\Task1\\Task1\\";
            const string inputFilename = path + "input.txt";
            const string outputFilename = path + "output.txt";
            const string outputEncFilename = path + "outputEnc.txt";
            const string outputTrimFilename = path + "outputTrim.txt";
            string[] input = System.IO.File.ReadAllLines(inputFilename);

            List<AbstractSave> saveMethods = new List<AbstractSave>
            {
                new AbstractSave(new SimpleSave()),
                new AbstractSave(new EncSave()),
                new AbstractSave(new TrimSave())
            };
            saveMethods[0].Save(input, outputFilename);
            saveMethods[1].Save(input, outputEncFilename);
            saveMethods[2].Save(input, outputTrimFilename);

            /*string text = Encoding.ASCII.GetString(System.IO.File.ReadAllBytes(outputEncFilename));
            Console.WriteLine(text);*/
            Console.WriteLine("\n=====OUTPUT======\n");
            string[] output = System.IO.File.ReadAllLines(outputFilename);
            foreach (string str in output)
            {
                Console.WriteLine(str);
            }
            Console.WriteLine("\n=====ENCODED OUTPUT======\n");
            output = Decode(System.IO.File.ReadAllLines(outputEncFilename));
            foreach (string str in output)
            {
                Console.WriteLine(str);
            }
            output = System.IO.File.ReadAllLines(outputTrimFilename);
            Console.WriteLine("\n=====TRIM OUTPUT======\n");
            foreach (string str in output)
            {
                Console.WriteLine(str);
            }

            // End of program
            Console.ReadKey();
        }

        static string[] Decode(string[] text)
        {
            string[] decText = new string[text.Length];
            for (int i = 0; i < text.Length; i++)
            {
                for (int j = 0; j < text[i].Length; j += 3)
                {
                    // Evil ASCII-decoding
                    int asciiNumber = (text[i].ElementAt(j) - 48) * 100 + (text[i].ElementAt(j + 1) - 48) * 10 + (text[i].ElementAt(j + 2) - 48);
                    decText[i] += Convert.ToChar(asciiNumber);
                }
            }
            return decText;
        }
    }
}
