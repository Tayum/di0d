using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            // Bow sample
            Bow bow = new Bow(5, 10, 183, 606);
            Console.WriteLine("==========");
            bow.printStats();
            Console.WriteLine("==========\n");

            // Shoot() function error handler
            for (int i = 0; i < 2; i++)
            {
                Console.WriteLine("****************************\n");
                try
                {
                    bow.shoot();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Message: {0}", ex.Message);
                    Console.WriteLine("TargetSite: {0}", ex.TargetSite);
                    Console.WriteLine("InnerException: {0}", ex.InnerException);
                }
                Console.WriteLine("\n****************************\n");
            }

            // IDamage interface in use:
            Console.WriteLine("\n******WEAPON STATS INTERFACE: ******\n");
            Console.WriteLine("Bow lower border damage: " + bow.LbDmg);
            Console.WriteLine("Bow upper border damage: " + bow.UbDmg);
            Console.WriteLine("Bow average expected damage: " + bow.AvgDmg);
            Console.WriteLine("Bow magical accuracy: " + bow.MagicalAccuracy);
            Console.WriteLine("\n****************************\n");

            // =====EVENTS=====
            Hero<Weapon> hawkeye = new Hero<Weapon>("Hawkeye");
            Hero<Weapon> sniper = new Hero<Weapon>("Sniper");
            Exposition<Weapon> exposition = Exposition<Weapon>.getInstance();
            exposition.AddEquipment += hawkeye.ExpositionAddEquipmentHandler;
            exposition.AddEquipment += sniper.ExpositionAddEquipmentHandler;
            exposition.newEquipment(bow);
            /*
            Armor plateBoots = new Armor(Armor.ARMOR_TYPE.PLATE, Armor.ARMOR_SLOT.FOOTS);
            Hero<Armor> hawkeye = new Hero<Armor>("Hawkeye");
            Hero<Armor> sniper = new Hero<Armor>("Sniper");
            Exposition<Armor> exposition = Exposition<Armor>.getInstance();
            exposition.AddEquipment += hawkeye.ExpositionAddEquipmentHandler;
            exposition.AddEquipment += sniper.ExpositionAddEquipmentHandler;
            exposition.newEquipment(plateBoots);
            */

            // End of program
            Console.WriteLine("Press ANY KEY to proceed...");
            Console.ReadKey();
        }
    }

}
