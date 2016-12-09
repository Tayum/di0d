using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    // IEnumereable <-> IEnumerator
    class HeroCollection: IEnumerable<Hero>, ICollectionExtension
    {
        private ArrayList heroArray;

        public HeroCollection()
        {
            heroArray = new ArrayList();
        }


        public Hero this[int index]
        {
            get {
                return (Hero)heroArray[index];
            }
            set {
                heroArray[index] = value;
            }
        }

        public Hero this[string name]
        {
            get
            {
                for (int i = 0; i < heroArray.Count; i++)
                {
                    Hero thyHero = (Hero)heroArray[i];
                    if (thyHero.Name == name)
                    {
                        return thyHero;
                    }
                }
                return null;
            }
        }

        public int Count
        {
            get
            {
                return heroArray.Count;
            }
        }


        public void Add(Hero hero)
        {
            heroArray.Add(hero);
        }

        public bool Remove(Hero hero)
        {
            for (int i = 0; i < heroArray.Count; i++)
            {
                Hero thyHero = (Hero)heroArray[i];
                if (thyHero.ObjectId == hero.ObjectId)
                {
                    heroArray.RemoveAt(i);
                    return true;
                }
            }
            return false;
        }

        public bool Contains(Hero hero)
        {
            foreach (Hero thyHero in heroArray)
            {
                if (thyHero.ObjectId == hero.ObjectId)
                {
                    return true;
                }
            }
            return false;
        }

        public void Clear()
        {
            heroArray.Clear();
        }


        public IEnumerator<Hero> GetEnumerator()
        {
            return new HeroEnumerator(this);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return new HeroEnumerator(this);
        }

    }
}
