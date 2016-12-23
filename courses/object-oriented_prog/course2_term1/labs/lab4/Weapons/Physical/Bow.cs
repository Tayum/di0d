using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    class Bow: Physical
    {
        // Static variable, that will be changing in all of the objects
        // of the class at the same time
        static uint arrowsInQuiver;


        // Martin: Clean Code [G25]:
        // >> Replace Magic Numbers with named constants*
        // * - the ENUM is used as a lot of named constants instead of using 'magic' numbers;


        // Properties
        // overriden from Weapon:
        public override WPN_TYPE Type
        {
            get
            {
                return WPN_TYPE.BOW;
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
                return 2.4;
            }
        }
        // overriden from Weapon->Physical:
        public override int PhysicalCrit
        {
            get
            {
                return 50;
            }
        }


        // Constructors
        public Bow(int lbDmg, int ubDmg, int magicalAccuracy, int physicalAccuracy)
            : base(lbDmg, ubDmg, magicalAccuracy, physicalAccuracy)
        {

        }

        // Static constructor, which will be called only once when the first object
        // of this class will be created.
        static Bow()
        {
            Console.WriteLine("Static constructor of bow has been called.");
            arrowsInQuiver = 1;
            Console.WriteLine("Arrows in the quiver: " + arrowsInQuiver);
        }


        // Methods

        // Martin: Clean Code [G36]:
        // >> Avoid the transitive calls;
        // Here, the BOW class is using a function from base (PHYSICAL) class,
        // but not from the class the base class is derivative from (WEAPON).
        public override void printStats()
        {
            base.printStats();
        }

        // A function in which we check the condition
        // Perform a shot. Costs 1 arrow.
        public void shoot()
        {
            checked
            {
                try
                {
                    arrowsInQuiver--;
                    Console.WriteLine("The shot is performed.");
                    Console.WriteLine("There are " + arrowsInQuiver + " arrows in quiver.");
                }
                catch (OverflowException e)
                {
                    throw new NoArrowsException(String.Format("The shot cannot be performed."), e);
                }
                finally
                {
                    Console.WriteLine("The shoot() function was called.");
                }
            }
        }

    }
}
