using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    class Hero
    {
        // Fields
        private string name;
        private Guid objectId;
        // Pieces of armor hero possesses
        private List<Armor> armorList;

        // Properties
        public string Name
        {
            get {
                return name;
            }
            set
            {
                if (!string.IsNullOrEmpty(value))
                {
                    name = value;
                }
            }
        }

        public Guid ObjectId
        {
            get
            {
                return objectId;
            }
        }


        // Constructors
        public Hero()
        {
            name = "NoName";
            objectId = Guid.NewGuid();
            armorList = new List<Armor>();
        }
        public Hero(string name)
        {
            this.name = name;
            objectId = Guid.NewGuid();
            armorList = new List<Armor>();
        }


        // Methods
        public void addArmor(Armor armor)
        {
            armorList.Add(armor);
        }

        public void sortArmor()
        {
            armorList.Sort();
        }

        public void printStats()
        {
            Console.WriteLine("\tName: " + name);
            Console.WriteLine("\tObjectId: " + objectId);
            Console.WriteLine("\tArmor that hero possesses:");
            foreach (Armor thyArmor in armorList)
            {
                Console.WriteLine("");
                thyArmor.printStats();
            }
        }

    }
}
