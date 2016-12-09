using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{
    class Armor:
        IArmorStats, IPrice
    {
        // Enums
        // enum for the type of armor
        public enum ARMOR_TYPE
        {
            NOTYPE,
            ROBE,
            LEATHER,
            CHAINMAIL,
            PLATE
        }

        // enum for the type of piece of armor
        public enum ARMOR_SLOT
        {
            NOSLOT,
            BODY,
            LEGS,
            FOOTS,
            HANDS,
            SHOULDERS
        }


        // Fields
        private int physicalDefense;
        private int magicalDefense;
        private int evasion;
        private ARMOR_TYPE type;
        private ARMOR_SLOT slot;


        // Properties
        // readonly
        public ARMOR_TYPE Type
        {
            get
            {
                return type;
            }
        }
        // readonly
        public ARMOR_SLOT Slot
        {
            get
            {
                return slot;
            }
        }

        public int PhysicalDefense
        {
            get
            {
                return physicalDefense;
            }
            set
            {
                if (value >= 0)
                {
                    physicalDefense = value;
                }
            }
        }

        public int MagicalDefense
        {
            get
            {
                return MagicalDefense;
            }
            set
            {
                if (value >= 0)
                {
                    MagicalDefense = value;
                }
            }
        }

        public int Evasion
        {
            get
            {
                return evasion;
            }
            set
            {
                if (value >= 0)
                {
                    evasion = value;
                }
            }
        }

        // random cost
        // readonly
        public int Price
        {
            get
            {
                Random rndValue = new Random();
                return rndValue.Next(1000);
            }
        }


        // Constructors
        public Armor()
        {
            type = ARMOR_TYPE.NOTYPE;
            slot = ARMOR_SLOT.NOSLOT;
            physicalDefense = 0;
            magicalDefense = 0;
            evasion = 0;
        }

        public Armor(ARMOR_TYPE type, ARMOR_SLOT slot)
            : this()
        {
            this.type = type;
            this.slot = slot;
        }

        public Armor(ARMOR_TYPE type, ARMOR_SLOT slot, int physicalDefense, int magicalDefense, int evasion)
            : this(type, slot)
        {
            this.physicalDefense = physicalDefense;
            this.magicalDefense = magicalDefense;
            this.evasion = evasion;
        }

    }
}
