using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{
    abstract class Physical: Weapon,
        IPhysicalStats
    {
        // Fields
        private int physicalAccuracy;


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


        // Constructors
        public Physical(int lbDmg, int ubDmg, int magicalAccuracy)
            : base(lbDmg, ubDmg, magicalAccuracy)
        {

        }

        public Physical(int lbDmg, int ubDmg, int magicalAccuracy, int physicalAccuracy)
            : this(lbDmg, ubDmg, magicalAccuracy)
        {
            this.physicalAccuracy = physicalAccuracy;
        }


        // Methods
        public override void printStats()
        {
            base.printStats();
            Console.WriteLine("\t\tPhysical crit: " + PhysicalCrit);
            Console.WriteLine("\t\tPhysical accuracy: " + physicalAccuracy);
        }


    }
}
