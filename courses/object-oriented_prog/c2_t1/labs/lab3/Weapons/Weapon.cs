using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    abstract class Weapon:
        IWeaponStats
    {
        // Enums
        // Enum for weapon type
        public enum WPN_TYPE
        {
            NOTYPE,
            ORB,
            GRIMOIRE,
            BLUNT,
            STAFF,
            SWORD,
            SPEAR,
            BOW
            // THSWORD
            // DAGGER
        }

        // Enum for weapon slot
        public enum WPN_SLOT
        {
            NOSLOT,
            ONEHANDED,
            TWOHANDED
        }

        // Enum for weapon damage type
        public enum DAMAGE_TYPE
        {
            NOTYPE,
            PHYSICAL,
            MAGICAL
        }


        // Fields
        protected int lbDmg;
        protected int ubDmg;
        protected int magicalAccuracy;


        // Properties
        // readonly in derived classes
        public virtual WPN_TYPE Type
        {
            get
            {
                return WPN_TYPE.NOTYPE;
            }
        }
        // readonly in derived classes
        public virtual WPN_SLOT Slot
        {
            get
            {
                return WPN_SLOT.NOSLOT;
            }
        }
        // readonly in derived classes
        public virtual DAMAGE_TYPE DmgType
        {
            get
            {
                return DAMAGE_TYPE.NOTYPE;
            }
        }
        // readonly in derived classes
        public virtual double atkSpeedMltp
        {
            get
            {
                return 0;
            }

        }

        public int LbDmg
        {
            get
            {
                return lbDmg;
            }
            set
            {
                if (value >= 0)
                {
                    lbDmg = value;
                }
            }
        }

        public int UbDmg
        {
            get
            {
                return ubDmg;
            }
            set
            {
                if (value >= 0 && value >= ubDmg)
                {
                    ubDmg = value;
                }
            }
        }

        public int MagicalAccuracy
        {
            get
            {
                return magicalAccuracy;
            }
            set
            {
                if (value >= 0)
                {
                    magicalAccuracy = value;
                }
            }
        }


        // Constructors
        public Weapon()
        {
            lbDmg = 1;
            ubDmg = 1;
        }

        public Weapon(int lbDmg, int ubDmg)
        {
            this.lbDmg = lbDmg;
            this.ubDmg = ubDmg;
        }

        public Weapon(int lbDmg, int ubDmg, int magicalAccuracy)
            :this(lbDmg, ubDmg)
        {
            this.magicalAccuracy = magicalAccuracy;
        }


        // Methods
        public virtual void printStats()
        {
            Console.WriteLine("\tType: " + Type.ToString());
            Console.WriteLine("\tDamage type: " + DmgType.ToString());
            Console.WriteLine("\tEquip slot: " + Slot.ToString());
            Console.WriteLine("\tDamage: " + lbDmg + "-" + ubDmg);
            Console.WriteLine("\tMagical accuracy: " + magicalAccuracy);
            Console.WriteLine("\tAttack speed: " + atkSpeedMltp);
        }
    }
}
