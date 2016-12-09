using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{
    class Staff: Mixed,
        IPhysicalMeleeStats
    {

        //Fields
        private int parry;


        // Properties
        // overriden from Weapon:
        public override WPN_TYPE Type
        {
            get
            {
                return WPN_TYPE.STAFF;
            }
        }
        // overriden from Weapon:
        public override WPN_SLOT Slot
        {
            get
            {
                return WPN_SLOT.TWOHANDED;
            }
        }
        // overriden from Weapon:
        public override DAMAGE_TYPE DmgType
        {
            get
            {
                return DAMAGE_TYPE.PHYSICAL;
            }
        }
        // overriden from Weapon:
        public override double atkSpeedMltp
        {
            get
            {
                return 2;
            }
        }
        // overriden from Weapon->Physical:
        public override int PhysicalCrit
        {
            get
            {
                return 60;
            }
        }

        public int Parry
        {
            get
            {
                return parry;
            }
            set
            {
                if (value > 0)
                {
                    parry = value;
                }
            }
        }


        // Constructors
        public Staff(int lbDmg, int ubDmg, int magicalAccuracy, int physicalAccuracy, int magicPower)
            : base(lbDmg, ubDmg, magicalAccuracy, physicalAccuracy, magicPower)
        {

        }

        public Staff(int lbDmg, int ubDmg, int magicalAccuracy, int physicalAccuracy, int magicPower, int parry)
            : this(lbDmg, ubDmg, magicalAccuracy, physicalAccuracy, magicPower)
        {
            this.parry = parry;
        }


        // Methods
        public override void printStats()
        {
            base.printStats();
            Console.WriteLine("\t\t\tParry: " + parry);
        }
    }
}
