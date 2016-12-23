using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4
{
    // The interface to work with common weapon parameters
    interface IWeaponStats
    {
        int LbDmg
        {
            get;
            set;
        }

        int UbDmg
        {
            get;
            set;
        }

        int MagicalAccuracy
        {
            get;
            set;
        }
    }
}
