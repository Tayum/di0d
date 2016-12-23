using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    // The interface to work with common physical weapon parameters
    interface IPhysicalStats
    {
        int PhysicalCrit
        {
            get;
        }

        int PhysicalAccuracy
        {
            get;
            set;
        }
    }
}
