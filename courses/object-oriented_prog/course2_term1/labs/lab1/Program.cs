using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            // Grimoire
            Grimoire grimoire = new Grimoire(1, 2, 600, 40);
            Console.WriteLine("==========");
            grimoire.printStats();
            int range = 500;
            Console.WriteLine("Is " + range + " in a range of this grimoire: " + grimoire.isInRange(range) + "\n");
            Console.WriteLine("==========\n");

            //Bow
            Bow bow = new Bow(1, 2);
            Console.WriteLine("==========");
            bow.printStats();
            bow.shoot();
            // Another Bow
            Bow secondBow = new Bow(2, 4, 800);
            Console.WriteLine("==========");
            secondBow.printStats();
            bow.shoot();
            Console.WriteLine("Is this number in the range of bow's range? - " + secondBow.isInRange());
            Console.WriteLine("==========\n");

            // Spear
            Spear spear = new Spear(5, 10, 0.6);
            Console.WriteLine("==========");
            spear.throwSpear();
            Console.WriteLine("==========\n");

            // Sword
            Sword sword = new Sword(6, 7, 0.25);
            Console.WriteLine("==========");
            sword.printStats();
            sword.sharpen();
            Console.WriteLine("Can this hit be parried by sword? - " + sword.isParried());
            Console.WriteLine("==========\n");

            // Weaponary
            Weaponary thyWeaponary = Weaponary.getInstance();
            Console.WriteLine("\nWelcome to " + thyWeaponary.Name + "!");
            string newName = "Very secret weaponary!";
            thyWeaponary.Name = newName;
            Console.WriteLine("You've changed the Weaponary name to: " + newName);
            Console.WriteLine("Now welcome to " + thyWeaponary.Name + "!");
            LinkedList<Weapon> listOfWeapons = new LinkedList<Weapon>();
            listOfWeapons.AddLast(grimoire);
            listOfWeapons.AddLast(bow);
            listOfWeapons.AddLast(secondBow);
            listOfWeapons.AddLast(spear);
            listOfWeapons.AddLast(sword);
            Console.WriteLine("Amount of weapons here: " + thyWeaponary.Amount + "\n");
            for (int i = 0; i < listOfWeapons.Count; i++)
            {
                thyWeaponary.addWeapon(listOfWeapons.ElementAt(i));
            }
            thyWeaponary.printWeaponList();

            // End of program
            Console.WriteLine("Press ANY KEY to proceed...");
            Console.ReadKey();
        }
    }
}
