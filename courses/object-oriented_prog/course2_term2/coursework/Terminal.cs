using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CourseWork
{
    public class Terminal
    {
        private List<Snack> snacks = new List<Snack>();
        private List<Brew> brews = new List<Brew>();
        public User user;

        public List<Snack> Snacks
        {
            get { return snacks; }
        }

        public List<Brew> Brews
        {
            get { return brews; }
        }

        public Terminal(User user)
        {
            this.user = user;
        }
        
        public Terminal(User user, List<Snack> snacks, List<Brew> brews):
            this(user)
        {
            this.snacks = snacks;
            this.brews = brews;
        }

        public void AddToShop(Item item)
        {
            switch (item.Type)
            {
                case ITEM_TYPE.SNACK:
                    if(!snacks.Contains(item))
                    {
                        snacks.Add((Snack)item);
                    }
                    break;
                case ITEM_TYPE.BREW:
                    if (!brews.Contains(item))
                    {
                        brews.Add((Brew)item);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
