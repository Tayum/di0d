using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Range: Weapon
    {
        int range;
        

        public Range(int lbDmg, int ubDmg)
            : base(lbDmg, ubDmg)
        {

        }

        public Range(int lbDmg, int ubDmg, int range)
            : this(lbDmg, ubDmg)
        {
            this.range = range;
        }



        public override void printStats()
        {
            base.printStats();
            Console.WriteLine("\t\tRange: " + range + " units");
        }

        // Does the specified range lay in range of the weapon? 
        public bool isInRange(int range)
        {
            return (this.range >= range);
        }

        // Does the specified range lay in random-generated range?
        public bool isInRange()
        {
            Random rnd = new Random();
            int rndNumber = rnd.Next(1000);
            Console.WriteLine("A random generated range is: " + rndNumber + " units");
            return (range >= rndNumber);
        }
    }
}
