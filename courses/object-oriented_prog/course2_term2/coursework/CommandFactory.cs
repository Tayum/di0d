using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CourseWork
{
    public enum COMMAND
    {
        ROUTE,
        ADD_TO_CART,
        BACK,
        REMOVE_FROM_CART,
        QUIT,
        NEXT,
        PREV,
        ACQUIRE
    }

    // PATTERN: Simple Factory
    public class CommandFactory
    {
        private VendorMachine vendor;

        public CommandFactory(VendorMachine vm)
        {
            vendor = vm;
        }

        public Command CreateCommand(COMMAND desiredType)
        {
            switch(desiredType)
            {
                case COMMAND.ROUTE:
                    return new RouteCommand(vendor);
                case COMMAND.ADD_TO_CART:
                    return new AddToCartCommand(vendor);
                case COMMAND.BACK:
                    return new BackCommand(vendor);
                case COMMAND.REMOVE_FROM_CART:
                    return new RemoveFromCartCommand(vendor);
                case COMMAND.NEXT:
                    return new NextCommand(vendor);
                case COMMAND.PREV:
                    return new PrevCommand(vendor);
                case COMMAND.ACQUIRE:
                    return new AcquireCommand(vendor);
                // INVALID COMMAND
                default:
                    throw new ArgumentException("Invalid command type");
            }
        }
    }
}
