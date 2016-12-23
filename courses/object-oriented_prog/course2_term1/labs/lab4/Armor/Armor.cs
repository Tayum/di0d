using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Xml.Serialization;

namespace lab4
{
    [DataContract]
    public class Armor: IDisposable,
        // IComparable, used in Human where he has a list of armor pieces
        IArmorStats, IComparable<Armor>
    {
        // Martin: Clean Code [G17]:
        // >> The wrong position for function/variable/etc;
        // This enums are located right where they should be located.


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
            NOSLOT = 0,
            BODY = 1,
            LEGS = 2,
            BOOTS = 4,
            GLOVES = 8,
            SHOULDERS = 16,
            BRIGANDINE = BODY | LEGS
        }


        // Fields
        bool isDisposed = false;

        private int physicalDefense;
        private int magicalDefense;
        private int evasion;
        private ARMOR_TYPE type;
        private ARMOR_SLOT slot;


        // Properties
        // readonly
        [DataMember]
        [XmlAttribute]
        public ARMOR_TYPE Type
        {
            get
            {
                return type;
            }
            // For serialization
            set
            {
                type = value;
            }
        }
        // readonly
        [DataMember]
        [XmlAttribute]
        public ARMOR_SLOT Slot
        {
            get
            {
                return slot;
            }
            // For serialization
            set
            {
                slot = value;
            }
        }

        [DataMember]
        [XmlElement]
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

        [DataMember]
        [XmlElement]
        public int MagicalDefense
        {
            get
            {
                return magicalDefense;
            }
            set
            {
                if (value >= 0)
                {
                    magicalDefense = value;
                }
            }
        }

        [DataMember]
        [XmlElement]
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


        // Constructors
        public Armor()
        {
            isDisposed = false;
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

        // Destructor
        // (comment here)
        ~Armor()
        {
            ConsoleColor curColor = Console.ForegroundColor;
            Console.ForegroundColor = ConsoleColor.DarkGray;
            Dispose();
            Console.WriteLine("\n|Inside Armor Destructor|");
            Console.ForegroundColor = curColor;
        }

        // for IComparable implementation
        public int CompareTo(Armor thyArmor)
        {
            if (physicalDefense < thyArmor.physicalDefense)
            {
                return 1;
            }
            else if (physicalDefense > thyArmor.physicalDefense)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }

        public void printStats()
        {
            Console.WriteLine("\t\tType: " + Type.ToString());
            Console.WriteLine("\t\tEquip slot: " + Slot.ToString());
            Console.WriteLine("\t\tPhysical defense: " + physicalDefense);
            Console.WriteLine("\t\tMagical defense: " + magicalDefense);
            Console.WriteLine("\t\tEvasion: " + evasion);
        }

        public void Dispose()
        {
            Dispose(true);

            GC.SuppressFinalize(this);
        }

        protected void Dispose(bool isCalledFromDispose)
        {
            if (!isDisposed)
            {
                if (isCalledFromDispose)
                {
                    physicalDefense = 0;
                    magicalDefense = 0;
                    evasion = 0;
                    type = ARMOR_TYPE.NOTYPE;
                    slot = ARMOR_SLOT.NOSLOT;

                    GC.Collect();
                }

               isDisposed = true;
            }
        }

    }
}
