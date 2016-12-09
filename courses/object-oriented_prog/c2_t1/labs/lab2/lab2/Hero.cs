using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab2
{
    class Hero<T>
        where T: IPrice
    {
        // Fields
        private string name;


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


        // Constructors
        public Hero()
        {
            name = "NoName";
        }
        public Hero(string name)
        {
            this.name = name;
        }


        // Methods
        // =====EVENTS=====
        public void ExpositionAddEquipmentHandler(T equipment, EventArgs args)
        {
            Console.WriteLine(name + " was notified about that new item is added. Its price: " + equipment.Price);
        }
    }
}
