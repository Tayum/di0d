using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    abstract class Mixed: Weapon,
        IPhysicalStats, IPhysicalAccuracyExtension, IMagicalStats
    {
        // Fields
        private int physicalAccuracy;
        private int magicPower;

        // Properties
        // readonly in derived classes
        public virtual int PhysicalCrit
        {
            get
            {
                return 0;
            }

        }

        public int PhysicalAccuracy
        {
            get
            {
                return physicalAccuracy;
            }
            set
            {
                if (value > 0)
                {
                    physicalAccuracy = value;
                }
            }

        }

        public int MagicPower
        {
            get
            {
                return magicPower;
            }
            set
            {
                if (value > 0)
                {
                    magicPower = value;
                }
            }
        }


        // Constructors
        public Mixed(int lbDmg, int ubDmg, int magicalAccuracy)
            : base(lbDmg, ubDmg, magicalAccuracy)
        {

        }

        public Mixed(int lbDmg, int ubDmg, int magicalAccuracy, int physicalAccuracy, int magicPower)
            : this(lbDmg, ubDmg, magicalAccuracy)
        {
            this.physicalAccuracy = physicalAccuracy;
            this.magicPower = magicPower;
        }


        // Methods

        // Fauler: Refactoring
        // >> Extract Method
        // Split method for better understanding;


        // Take a look on this two variants of implementation:
        /*public override void printStats()
        {
            base.printStats();
            Console.WriteLine("\t\tPhysical crit: " + PhysicalCrit);
            Console.WriteLine("\t\tPhysical accuracy: " + physicalAccuracy);
            Console.WriteLine("\t\tMagic power: " + magicPower);
        }*/

        private void printMixedStats()
        {
            Console.WriteLine("\t\tPhysical crit: " + PhysicalCrit);
            Console.WriteLine("\t\tPhysical accuracy: " + physicalAccuracy);
            Console.WriteLine("\t\tMagic power: " + magicPower);
        }

        public override void printStats()
        {
            base.printStats();
            printMixedStats();
        }
    }
}
