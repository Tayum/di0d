using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    class Orb : Magical
    {
        // Properties
        // overriden from Weapon:
        public override WPN_TYPE Type
        {
            get
            {
                return WPN_TYPE.ORB;
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
                return DAMAGE_TYPE.MAGICAL;
            }
        }
        // overriden from Weapon:
        public override double atkSpeedMltp
        {
            get
            {
                return 2.2;
            }
        }
        // overriden from Weapon->Magical:
        public override ELEMENT_TYPE ElementType
        {
            get
            {
                return ELEMENT_TYPE.FIRE;
            }
        }


        // Constructors
        public Orb(int lbDmg, int ubDmg, int magicalAccuracy, int magicPower)
            : base(lbDmg, ubDmg, magicalAccuracy, magicPower)
        {

        }


        // Methods
        public override void printStats()
        {
            base.printStats();
        }
    }
}
