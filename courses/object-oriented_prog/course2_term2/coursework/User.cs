using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CourseWork
{
    public class User
    {
        private int money;
        private List<Item> inventory = new List<Item>();
        private List<Item> cart = new List<Item>();
        private int age;


        public virtual int Money
        {
            get { return money; }
        }

        public virtual List<Item> Cart
        {
            // return the copy of the list
            get { return cart.ToList(); }
        }

        public virtual int Age
        {
            get { return age; }
        }


        public User()
        {
            money = 0;
            age = 0;
        }

        public User(int money, int age)
        {
            this.money = money;
            this.age = age;
        }


        public virtual bool AddToCart(Item item)
        {
            cart.Add(item);
            return true;
        }

        public virtual void RemoveFromCart(Item item)
        {
            cart.Remove(item);
        }

        public virtual bool BuyItems()
        {
            if (cart.Count == 0)
            {
                return false;
            }
            else
            {
                int moneyNeeded = 0;
                foreach (Item item in cart)
                {
                    moneyNeeded += item.Cost;
                }
                if (money < moneyNeeded)
                {
                    return false;
                }
                else
                {
                    money -= moneyNeeded;
                    inventory.AddRange(cart);
                    cart.Clear();
                    return true;
                }
            }
        }

        public virtual void PrintInventory()
        {
            Console.WriteLine("\n--------------------");
            Console.WriteLine("User money:");
            Console.WriteLine("-- " + Money);
            Console.WriteLine("User inventory:");
            if (inventory.Count == 0)
            {
                Console.WriteLine("<Empty>");
            }
            else
            {
                foreach (Item item in inventory)
                {
                    Console.WriteLine("-- " + item.Name);
                }
            }
            Console.WriteLine("--------------------\n");
        }
    }

    // PATTERN: Proxy (as Protection Proxy)
    public class ControlledUser: User
    {
        private User user;


        public override int Money
        {
            get { return user.Money; }
        }

        public override List<Item> Cart
        {
            get { return user.Cart; }
        }

        public override int Age
        {
            get { return user.Age; }
        }


        public ControlledUser(int money, int age)
        {
            user = new User(money, age);
        }

        public ControlledUser(User user)
        {
            this.user = user;
        }


        public override bool AddToCart(Item item)
        {
            if(item.Type != ITEM_TYPE.BREW)
            {
                return user.AddToCart(item);
            }
            else
            {
                Brew brew = (Brew)item;
                if (brew.AgeRestriction <= user.Age)
                {
                    return user.AddToCart(item);
                }
                else
                {
                    return false;
                }
            }
        }

        public override void RemoveFromCart(Item item)
        {
            user.RemoveFromCart(item);
        }

        public override bool BuyItems()
        {
            return user.BuyItems();
        }

        public override void PrintInventory()
        {
            user.PrintInventory();
        }
    }
}
