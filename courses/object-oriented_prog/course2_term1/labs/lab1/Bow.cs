using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Bow : Range
    {
        // Static variable, that will be changing in all of the objects of the class at the same time
        static int arrowsInQuiver;

        // Overriden propeties
        protected override WPN_TYPE Type { get { return WPN_TYPE.BOW; } }
        protected override double atkSpeedMltp { get { return 0.850; } }


        public Bow(int lbDmg, int ubDmg)
            : base(lbDmg, ubDmg)
        {

        }

        public Bow(int lbDmg, int ubDmg, int range)
            : base(lbDmg, ubDmg, range)
        {

        }

        static Bow()
        {
            Console.WriteLine("Static constructor of bow has been run.");
            arrowsInQuiver = 1000;
            Console.WriteLine("Arrows in the quiver: " + arrowsInQuiver);
        }

        // Perform a shot. Costs 1 arrow.
        public void shoot()
        {
            Console.Write("The shot is performed.");
            arrowsInQuiver--;
            Console.WriteLine(" There are " + arrowsInQuiver + " arrows in quiver.");
        }
    }
}
