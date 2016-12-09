using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    // The interface to work with common armor parameters
    interface IArmorStats
    {
        int PhysicalDefense
        {
            get;
            set;
        }
        int MagicalDefense
        {
            get;
            set;
        }
        int Evasion
        {
            get;
            set;
        }
    }
}
