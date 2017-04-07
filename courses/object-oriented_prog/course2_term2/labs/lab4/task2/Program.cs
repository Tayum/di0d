using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    class Program
    {
        static void Main(string[] args)
        {
            Dish dish = new Dish();
            MixAndSalt rec1 = new MixAndSalt();
            FryAndSugar rec2 = new FryAndSugar();
            BoilAndSpices rec3 = new BoilAndSpices();


            dish.CreateByRecipe(rec1);
            dish.CreateByRecipe(rec2);
            dish.CreateByRecipe(rec3);


            // End of program
            Console.WriteLine("\n\nPress ANY KEY to exit the program...\n\n");
            Console.ReadKey(true);
        }
    }
}
