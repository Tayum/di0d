using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    class Hero: IDisposable
    {
        // Fields
        bool isDisposed;

        private string name;
        // Pieces of armor hero possesses
        // private List<Armor> armorList;

        // Properties
        public string Name
        {
            get {
                return name;
            }
            set
            {
                // Martin: Clean Code [G26]:
                // >> Be strict in what you will*
                // * - if the method may receive null or empty value - check it.
                if (!string.IsNullOrEmpty(value))
                {
                    name = value;
                }
            }
        }


        // Constructors
        public Hero()
        {
            isDisposed = false;
            name = "NoName";
            // armorList = new List<Armor>();
        }
        public Hero(string name)
        {
            isDisposed = false;
            this.name = name;
            // armorList = new List<Armor>();
        }
        // Destructor
        ~Hero()
        {
            ConsoleColor curColor = Console.ForegroundColor;
            Console.ForegroundColor = ConsoleColor.DarkGray;
            Dispose();
            Console.WriteLine("\n|Inside Human Destructor|");
            Console.ForegroundColor = curColor;
        }


        // Methods
        /*public void addArmor(Armor armor)
        {
            armorList.Add(armor);
        }

        public void sortArmor()
        {
            armorList.Sort();
        }*/

        public void printStats()
        {
            Console.WriteLine("\tName: " + name);
            Console.WriteLine("\tArmor that hero possesses:");
            /*foreach (Armor thyArmor in armorList)
            {
                Console.WriteLine("");
                thyArmor.printStats();
            }*/
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
                    name = string.Empty;
                    /*if(armorList != null)
                    {
                        for (int i = 0; i < armorList.Count; i++)
                        {
                            if (armorList.ElementAt(i) != null)
                            {
                                armorList.ElementAt(i).Dispose();
                            }
                        }
                        //armorList = null;
                    }*/

                    GC.Collect();
                    GC.WaitForPendingFinalizers();
                }

                isDisposed = true;
            }
        }

    }
}
