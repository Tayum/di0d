using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    abstract class Magical: Weapon
    {
        // Martin: Clean Code [G17]:
        // >> The wrong position for function/variable/etc;
        // This enum is located right where they should be located.


        // Enums
        // Enum for the element type of weapon
        public enum ELEMENT_TYPE
        {
            NOTYPE,
            FIRE,
            WATER
        }


        // Fields
        private int magicPower;


        // Properties
        // readonly in derived classes
        public virtual ELEMENT_TYPE ElementType
        {
            get
            {
                return ELEMENT_TYPE.NOTYPE;
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
        public Magical(int lbDmg, int ubDmg, int magicalAccuracy)
            : base(lbDmg, ubDmg, magicalAccuracy)
        {

        }

        public Magical(int lbDmg, int ubDmg, int magicalAccuracy, int magicPower)
            : this(lbDmg, ubDmg, magicalAccuracy)
        {
            this.magicPower = magicPower;
        }


        // Methods
        public override void printStats()
        {
            base.printStats();
            Console.WriteLine("\t\tElement type: " + ElementType.ToString());
            Console.WriteLine("\t\tMagic power: " + magicPower);
        }

    }
}
