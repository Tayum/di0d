using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    abstract class Weapon
    {
        // enum for the type of weapons, must be seen everywhere
        public enum WPN_TYPE
        {
            NOTYPE,
            SWORD,
            SPEAR,
            BOW,
            GRIMOIRE
        }

        // Fields
        protected int lbDmg;
        protected int ubDmg;

        // Properties: both of them are readonly in derived classes
        protected virtual WPN_TYPE Type { get { return WPN_TYPE.NOTYPE; } }
        protected virtual double atkSpeedMltp { get { return 0; } }


        // Basic constructor
        public Weapon()
        {
            lbDmg = 1;
            ubDmg = 1;
        }

        // Constructor with specified dmg
        public Weapon(int lbDmg, int ubDmg)
        {
            this.lbDmg = lbDmg;
            this.ubDmg = ubDmg;
        }



        public virtual void printStats()
        {
            Console.WriteLine("\tType: " + Type.ToString());
            Console.WriteLine("\tDamage: " + lbDmg + "-" + ubDmg);
            Console.WriteLine("\tAttack speed: " + atkSpeedMltp);
        }

    }
}
