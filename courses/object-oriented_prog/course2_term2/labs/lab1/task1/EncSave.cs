using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class EncSave: ISave
    {
        public void Save(string[] text, string filename)
        {
            
            /*
             * string myString = "";
            byte[] encText;
            for (int i = 0; i < text.Length; i++)
            {
                myString += text[i] + '\r' + '\n';
            }
            encText = Encoding.ASCII.GetBytes(myString);
            System.IO.File.WriteAllBytes(filename, encText);
            */
            string[] encText = new string[text.Length];
            for (int i = 0; i < text.Length; i++)
            {
                for (int j = 0; j < text[i].Length; j++)
                {
                    encText[i] += ((int)text[i].ElementAt(j)).ToString("000"); // Evil data ASCII-encoding
                }
                
            }
            System.IO.File.WriteAllLines(filename, encText);
        }
    }
}
