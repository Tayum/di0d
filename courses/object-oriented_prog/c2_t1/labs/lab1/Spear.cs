using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Spear : Melee
    {
        // Overriden propeties
        protected override WPN_TYPE Type { get { return WPN_TYPE.SPEAR; } }
        protected override double atkSpeedMltp { get { return 0.5; } }


        public Spear(int lbDmg, int ubDmg)
            : base(lbDmg, ubDmg)
        {

        }

        public Spear(int lbDmg, int ubDmg, double chanceToParry)
            : base(lbDmg, ubDmg, chanceToParry)
        {

        }


        public void throwSpear() {
            Console.WriteLine("The spear has been thrown.");
        }

    }
}
