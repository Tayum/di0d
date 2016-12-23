using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    class Blunt: Mixed,
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
                return WPN_TYPE.BLUNT;
            }
        }
        // overriden from Weapon:
        public override WPN_SLOT Slot
        {
            get
            {
                return WPN_SLOT.ONEHANDED;
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
                return 1.5;
            }
        }
        // overriden from Weapon->Physical:
        public override int PhysicalCrit
        {
            get
            {
                return 10;
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
        public Blunt(int lbDmg, int ubDmg, int magicalAccuracy, int physicalAccuracy, int magicPower)
            : base(lbDmg, ubDmg, magicalAccuracy, physicalAccuracy, magicPower)
        {

        }

        public Blunt(int lbDmg, int ubDmg, int magicalAccuracy, int physicalAccuracy, int magicPower, int parry)
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
