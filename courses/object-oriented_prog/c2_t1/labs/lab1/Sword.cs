using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Sword : Melee
    {
        // Overriden propeties
        protected override WPN_TYPE Type { get { return WPN_TYPE.SWORD; } }
        protected override double atkSpeedMltp { get { return 1.0; } }


        public Sword(int lbDmg, int ubDmg)
            : base(lbDmg, ubDmg)
        {

        }

        public Sword(int lbDmg, int ubDmg, double chanceToParry)
            : base(lbDmg, ubDmg, chanceToParry)
        {
            
        }

        public void sharpen()
        {
            lbDmg += 1000;
            ubDmg += 1000;
            Console.Write("The sword has been sharpened.");
            Console.WriteLine(" Damage now:" + lbDmg + "-" + ubDmg);
        }

    }
}
