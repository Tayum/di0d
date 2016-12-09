using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    // Singletone Class
    // A class, which represents the Exposition (collection) of the <Weapon>-based elements.
    class Exposition
    {
        // =====EVENTS=====
        public delegate void ExpositionAddEquipmentHandler(Weapon equipment);
        private ExpositionAddEquipmentHandler addEquipment;
        public event ExpositionAddEquipmentHandler AddEquipment
        {
            add
            {
                addEquipment += value;
            }
            remove
            {
                addEquipment -= value;
            }
        }


        // Fields
        private static Exposition instance = null;
        private string name = "Secret Exposition";
        private List<Weapon> equipmentList;

        // Properties
        public string Name
        {
            get { return name; }
            set
            {
                if (!string.IsNullOrEmpty(value))
                {
                    name = value;
                }
            }
        }
        public int Amount { get { return equipmentList.Count; } }


        private Exposition()
        {
            equipmentList = new List<Weapon>();
        }


        public static Exposition getInstance()
        {
            if (instance == null)
            {
                instance = new Exposition();
            }
            return instance;
        }

        // =====EVENT IMPLEMENTED=====
        public void newEquipment(Weapon equipment)
        {
            equipmentList.Add(equipment);
            addEquipment?.Invoke(equipment);
        }

        public void printWeaponList()
        {
            if (equipmentList.Count == 0)
            {
                Console.WriteLine("[]");
            }
            else
            {
                for (int i = 0; i < equipmentList.Count; i++)
                {
                    Weapon equipment = equipmentList[i];
                    Console.WriteLine("Equipment at stand #" + i);
                    equipment.printStats();
                    Console.WriteLine();
                }
            }
        }

    }
}
