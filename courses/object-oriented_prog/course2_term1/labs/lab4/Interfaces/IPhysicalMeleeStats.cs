using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    // The interface to work with common physical melee weapon parameters
    interface IPhysicalMeleeStats
    {
        int Parry
        {
            get;
            set;
        }
    }
}
