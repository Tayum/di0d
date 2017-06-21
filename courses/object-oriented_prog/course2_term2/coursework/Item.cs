using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CourseWork
{
    public enum ITEM_TYPE
    {
        ITEM = 0,
        SNACK = 1,
        BREW = 2
    }


    public abstract class Item
    {
        private string name;
        private int cost;
        protected ITEM_TYPE type;

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public int Cost
        {
            get { return cost; }
            set { cost = value; }
        }

        public ITEM_TYPE Type
        {
            get { return type; }
        }

        public Item(string name, int cost)
        {
            Name = name;
            Cost = cost;
            type = ITEM_TYPE.ITEM;
        }

        public override bool Equals(object other)
        {
            Item it = other as Item;
            if (it.Name == name)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public override int GetHashCode()
        {
            return name.GetHashCode();
        }
    }

    public class Snack : Item
    {
        private int netto;

        public int Netto
        {
            get { return netto; }
            set { netto = value; }
        }

        public Snack(string name, int cost)
            : base(name, cost)
        {
            Netto = 0;
            type = ITEM_TYPE.SNACK;
        }

        public Snack(string name, int cost, int netto)
            : this(name, cost)
        {
            Netto = netto;
        }
    }

    public class Brew : Item
    {
        private int ageRestriction;

        public int AgeRestriction
        {
            get { return ageRestriction; }
            set { ageRestriction = value; }
        }

        public Brew(string name, int cost)
            : base(name, cost)
        {
            ageRestriction = 0;
            type = ITEM_TYPE.BREW;
        }

        public Brew(string name, int cost, int age)
            : this(name, cost)
        {
            ageRestriction = age;
        }
    }
}
