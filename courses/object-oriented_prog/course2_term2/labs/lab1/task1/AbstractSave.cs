using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class AbstractSave
    {
        ISave saveType;
        

        public AbstractSave(ISave sType)
        {
            saveType = sType;
        }

        
        public void Save(string[] text, string filename)
        {
            saveType.Save(text, filename);
        }
    }
}
