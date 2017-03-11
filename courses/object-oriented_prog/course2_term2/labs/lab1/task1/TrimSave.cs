using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace Task1
{
    class TrimSave : ISave
    {
        public void Save(string[] text, string filename)
        {
            for (int i = 0; i < text.Length; i++)
            {
                text[i] = Regex.Replace(text[i], "[ ]{2,}", " ");
            }
            System.IO.File.WriteAllLines(filename, text);
        }
    }
}
