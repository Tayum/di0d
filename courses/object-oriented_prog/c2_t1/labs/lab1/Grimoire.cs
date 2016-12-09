using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Grimoire : Range
    {
        int spellPower;

        // Overriden propeties
        protected override WPN_TYPE Type { get { return WPN_TYPE.GRIMOIRE; } }
        protected override double atkSpeedMltp { get { return 0.825; } }


        public Grimoire(int lbDmg, int ubDmg)
            : base(lbDmg, ubDmg)
        {

        }

        public Grimoire(int lbDmg, int ubDmg, int range, int spellPower)
            : base(lbDmg, ubDmg, range)
        {
            this.spellPower = spellPower;
        }


        public override void printStats()
        {
            base.printStats();
            Console.WriteLine("\t\t\tSpell damage: " + spellPower);
        }

    }
}
