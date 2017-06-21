using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CourseWork
{
    class Program
    {
        static void Main(string[] args)
        {
            ControlledUser user = new ControlledUser(1000, 17);
            VendorMachine vm = new VendorMachine(user);

            vm.AddToShop(new Snack("Snickers", 20, 69));
            vm.AddToShop(new Snack("Twix", 15, 60));
            vm.AddToShop(new Snack("Mars", 14, 50));
            vm.AddToShop(new Snack("Bounty", 16, 43));
            vm.AddToShop(new Snack("Picnic", 13, 78));
            vm.AddToShop(new Snack("Nuts", 14, 56));
            vm.AddToShop(new Snack("Lion", 11, 48));
            vm.AddToShop(new Snack("KitKat", 13, 48));
            vm.AddToShop(new Snack("Aero", 10, 48));
            vm.AddToShop(new Snack("Milky Way", 10, 50));
            vm.AddToShop(new Brew("BonAqua", 11));
            vm.AddToShop(new Brew("7Up", 13, 4));
            vm.AddToShop(new Brew("Mojo", 17, 4));
            vm.AddToShop(new Brew("CocaCola", 15, 6));
            vm.AddToShop(new Brew("Pepsi", 14, 6));
            vm.AddToShop(new Brew("Sprite", 15, 6));
            vm.AddToShop(new Brew("Corona Extra", 33, 18));
            vm.AddToShop(new Brew("Hoegaarden", 40, 18));
            vm.AddToShop(new Brew("Trooper", 65, 18));
            vm.AddToShop(new Brew("Inkerman Classic", 150, 18));

            bool toContinue = true;
            while(toContinue)
            {
                toContinue = vm.RunMenu();
            }

            Console.Clear();
            user.PrintInventory();

            // End of program
            Console.WriteLine("\n\nPress ANY KEY to exit the program...\n\n");
            Console.ReadKey(true);
        }
    }
}
