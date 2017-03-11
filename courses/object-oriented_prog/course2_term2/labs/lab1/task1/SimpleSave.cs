using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class SimpleSave : ISave
    {
        public void Save(string[] text, string filename)
        {
            System.IO.File.WriteAllLines(filename, text);
        }
    }
}
