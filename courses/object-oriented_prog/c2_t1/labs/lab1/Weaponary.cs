using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    // Singletone Class
    class Weaponary
    {
        // Fields
        private static Weaponary instance = null;
        private string name = "Secret Weaponary";
        private List<Weapon> weaponList;

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
        public int Amount { get { return weaponList.Count; } }


        private Weaponary()
        {
            weaponList = new List<Weapon>();
        }


        public static Weaponary getInstance()
        {
            if (instance == null)
            {
                instance = new Weaponary();
            }
            return instance;
        }
        
        public void addWeapon(Weapon weapon)
        {
            weaponList.Add(weapon);
        }

        public void printWeaponList()
        {
            if (weaponList.Count == 0)
            {
                Console.WriteLine("[]");
            }
            else
            {
                for (int i = 0; i < weaponList.Count; i++)
                {
                    Weapon weapon = weaponList[i];
                    Console.WriteLine("Weapon at stand #" + i);
                    weapon.printStats();
                    Console.WriteLine();
                }
            }
        }

    }
}
