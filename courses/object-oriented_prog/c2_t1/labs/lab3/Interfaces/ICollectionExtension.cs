using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    public interface ICollectionExtension
    {
        void Clear();
    }

    public static class CollectionExtension
    {
        public static void Clear(this ICollectionExtension extension, string reason)
        {
            Console.WriteLine("The collection will be cleared due to the next reason:");
            Console.WriteLine(reason);
            extension.Clear();
        }
    }
}
