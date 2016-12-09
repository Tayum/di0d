using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{
    // Singletone Class
    // A class, which represents the Exposition (collection) of
    // the T-type elements.
    // T-type elements may be ANY elements that implement IPrice interface.
    class Exposition<T>
        where T: IPrice
    {
        // =====EVENTS=====
        public delegate void ExpositionAddEquipmentHandler(T equipment, EventArgs args);
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
        private static Exposition<T> instance = null;
        private string name = "Secret Exposition";
        private List<T> equipmentList;

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
            equipmentList = new List<T>();
        }


        public static Exposition<T> getInstance()
        {
            if (instance == null)
            {
                instance = new Exposition<T>();
            }
            return instance;
        }

        // =====EVENT IMPLEMENTED=====
        public void newEquipment(T equipment)
        {
            equipmentList.Add(equipment);
            addEquipment?.Invoke(equipment, new EventArgs());
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
                    T equipment = equipmentList[i];
                    Console.WriteLine("Equipment at stand #" + i);
                    Console.WriteLine("Its price: " + equipment.Price);
                    Console.WriteLine();
                }
            }
        }

    }
}
