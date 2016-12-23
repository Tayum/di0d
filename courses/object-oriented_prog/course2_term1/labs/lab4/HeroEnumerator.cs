using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    // IEnumerator <-> IEnumerable
    // IDisposable is included in IEnumerator
    class HeroEnumerator : IEnumerator<Hero>
    {
        bool isDisposed;
        private HeroCollection collection;
        private int index;
        private Hero current;

        public HeroEnumerator(HeroCollection collection)
        {
            isDisposed = false;
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

        // This function is NOT actually invoked
        public void Dispose()
        {
            Dispose(true);

            GC.SuppressFinalize(this);
        }

        // This function is NOT actually invoked
        protected void Dispose(bool isCalledFromDispose)
        {
            if (!isDisposed)
            {
                if (isCalledFromDispose)
                {
                    if (collection != null)
                    {
                        collection.Dispose();
                    }
                }

                isDisposed = true;
            }
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
