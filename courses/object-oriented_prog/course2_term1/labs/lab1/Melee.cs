using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Melee : Weapon
    {
        double chanceToParry;


        // Basic constructor
        public Melee(int lbDmg, int ubDmg)
            : base(lbDmg, ubDmg)
        {

        }

        public Melee(int lbDmg, int ubDmg, double chanceToParry)
            : this(lbDmg, ubDmg)
        {
            this.chanceToParry = chanceToParry;
        }


        public override void printStats()
        {
            base.printStats();
            Console.WriteLine("\t\tChance to Parry: " + chanceToParry * 100 + "%");
        }

        // Will the hit with random accuracy be parried?
        public bool isParried()
        {
            Random rnd = new Random();
            double rndNumber = rnd.NextDouble();
            Console.WriteLine("A hit will be landed with this chance: " + rndNumber*100 + "%");
            return (chanceToParry >= rndNumber);
        }


    }
}
