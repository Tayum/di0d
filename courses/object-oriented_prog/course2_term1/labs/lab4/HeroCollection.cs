using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    // IEnumereable <-> IEnumerator
    class HeroCollection: IEnumerable<Hero>, ICollectionExtension, IDisposable
    {
        bool isDisposed;
        private ArrayList heroArray;

        public HeroCollection()
        {
            isDisposed = false;
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
                if (thyHero.Name == hero.Name)
                {
                    heroArray.RemoveAt(i);
                    return true;
                }
            }
            return false;
        }

        // Fauler: Refactoring
        // >> Inline Temp
        // Do not use temp if it's not needed;
        // Take a look on this two variants of implementation:
        public bool Contains(Hero hero)
        {
            // string name = hero.Name;
            foreach (Hero thyHero in heroArray)
            {
                if (thyHero.Name == hero.Name) // thyHero.Name == name
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

        public void Dispose()
        {
            Dispose(true);

            GC.SuppressFinalize(this);
        }

        // Fauler: Refactoring
        // >> Inline Method
        // Do not extract method instead of using the inline variant (if it's small);
        public bool isNull(Hero hero)
        {
            return hero == null;
        }

        protected void Dispose(bool isCalledFromDispose)
        {
            if (!isDisposed)
            {
                if (isCalledFromDispose)
                {
                    if (heroArray != null)
                    {
                        for (int i = 0; i < heroArray.Count; i++)
                        {
                            if (heroArray[i] != null) // Refactoring: if(!isNull)
                            {
                                ((Hero)heroArray[i]).Dispose();
                            }
                        }
                        heroArray = null;
                    }
                }

                isDisposed = true;
            }
        }

        // This function is invoked when we create a collection
        public IEnumerator<Hero> GetEnumerator()
        {
            return new HeroEnumerator(this);
        }

        // This function is NOT actually invoked
        IEnumerator IEnumerable.GetEnumerator()
        {
            return new HeroEnumerator(this);
        }

    }
}
