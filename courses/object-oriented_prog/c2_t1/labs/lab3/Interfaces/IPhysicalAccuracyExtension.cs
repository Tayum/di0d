using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    public interface IPhysicalAccuracyExtension
    {
        int PhysicalAccuracy
        {
            get;
        }
    }
    public static class AccuracyExtension
    {
        public static void calc_PhysicalAccuracy(this IPhysicalAccuracyExtension extension)
        {
            int accuracy = extension.PhysicalAccuracy;
            Console.WriteLine("The weapon with this accuracy: " + accuracy);
            Random rnd = new Random();
            int evasion = rnd.Next(1000);
            Console.WriteLine("Will hit the target with this (random generated) evasion: " + evasion);
            if(evasion >= accuracy)
            {
                Console.WriteLine("With no chance!");
            }
            else
            {
                Console.WriteLine("With the chance of: " + ((accuracy - evasion) / (double)accuracy * 100).ToString("0.00") + "%");
            }
        }

        public static void calc_PhysicalAccuracy(this IPhysicalAccuracyExtension extension, int number)
        {
            int accuracy = extension.PhysicalAccuracy;
            Console.WriteLine("The weapon with this accuracy: " + accuracy);
            int evasion = number;
            Console.WriteLine("Will hit the target with this (passed as parameter) evasion: " + evasion);
            if (evasion >= accuracy)
            {
                Console.WriteLine("With no chance! [0% chance]");
            }
            else
            {
                Console.WriteLine("With the chance of: " + ((accuracy - evasion) / (double)accuracy * 100).ToString("0.00") + "%");
            }
        }
    }
}
