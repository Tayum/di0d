using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    // IEnumerator <-> IEnumerable
    // IDisposable is included in IEnumerator
    class HeroEnumerator : IEnumerator<Hero>
    {
        private HeroCollection collection;
        private int index;
        private Hero current;

        public HeroEnumerator(HeroCollection collection)
        {
            this.collection = collection;
            index = -1;
            current = default(Hero);
        }


        public Hero Current
        {
            get
            {
                return current;
            }
        }

        object IEnumerator.Current
        {
            get
            {
                return current;
            }
        }


        public void Dispose()
        {
            collection = null;
            current = default(Hero);
            index = -1;
        }

        public bool MoveNext()
        {
            index++;
            if (index >= collection.Count)
            {
                return false;
            }
            else
            {
                current = collection[index];
            }

            return true;
        }

        public void Reset()
        {
            current = default(Hero);
            index = -1;
        }
    }
}
