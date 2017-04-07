using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    public interface Recipe
    {
        string PerformStage1();
        string PerformStage2();
    }


    public class Dish
    {
        public void CreateByRecipe(Recipe recipe)
        {
            Console.WriteLine("\n\n> COOKING DA DISH BY R3C1P3...\n");
            Console.WriteLine("#0th stage: ...wash and chop vegetables...");
            Console.WriteLine("#1st stage: ..." + recipe.PerformStage1() + "...");
            Console.WriteLine("#2nd stage: ..." + recipe.PerformStage2() + "...");
            Console.WriteLine("\nTHE DISH IS DONE! Bon appetit!\n\n");
        }
    }


    public class MixAndSalt : Recipe
    {
        public string PerformStage1()
        {
            return "mixing vegetables";
        }
        public string PerformStage2()
        {
            return "adding salt";
        }
    }


    public class FryAndSugar : Recipe
    {
        public string PerformStage1()
        {
            return "frying vegetables";
        }
        public string PerformStage2()
        {
            return "adding sugar";
        }
    }


    public class BoilAndSpices : Recipe
    {
        public string PerformStage1()
        {
            return "boiling vegetables";
        }
        public string PerformStage2()
        {
            return "adding different spices";
        }
    }
}
