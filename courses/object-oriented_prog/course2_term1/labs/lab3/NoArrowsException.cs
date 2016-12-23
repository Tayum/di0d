using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab3
{
    class NoArrowsException : Exception
    {
        const string noArrowsMessage = "There are no arrows in quiver";


        public NoArrowsException(string auxMessage, Exception inner)
            : base(String.Format("{0} - {1}", noArrowsMessage, auxMessage ), inner)
        {

        }
    }
}
