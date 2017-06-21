using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CourseWork
{
    // PATTERN: Command
    public abstract class Command
    {
        protected VendorMachine vendor;

        public Command(VendorMachine vm)
        {
            vendor = vm;
        }

        public abstract void Execute();
    }


    class RouteCommand: Command
    {
        private IMenuFactory menuCreator;
        private IMenuFactory prevMenuCreator;

        public IMenuFactory MenuCreator
        {
            get { return menuCreator; }
            set { menuCreator = value; }
        }

        public IMenuFactory PrevMenuCreator
        {
            get { return prevMenuCreator; }
            set { prevMenuCreator = value; }
        }

        public RouteCommand(VendorMachine vm)
            :base(vm)
        {

        }

        public override void Execute()
        {
            if (MenuCreator != null)
            {
                vendor.SetCurMenu(menuCreator);
            }

            if (PrevMenuCreator != null)
            {
                vendor.SetPrevMenu(prevMenuCreator);
            }
        }
    }


    class AddToCartCommand: Command
    {
        private Item item;

        public Item Item
        {
            get { return item; }
            set { item = value; }
        }

        public AddToCartCommand(VendorMachine vm)
            :base(vm)
        {

        }

        public override void Execute()
        {
            vendor.AddToCart(item);
        }
    }


    class BackCommand :
        Command
    {
        private IMenuFactory prevMenuCreator;

        public IMenuFactory PrevMenuCreator
        {
            get { return prevMenuCreator; }
            set { prevMenuCreator = value; }
        }

        public BackCommand(VendorMachine vm)
            :base(vm)
        {

        }

        public override void Execute()
        {
            vendor.SetCurMenu();

            if(PrevMenuCreator != null)
            {
                vendor.SetPrevMenu(prevMenuCreator);
            }
        }
    }

    class RemoveFromCartCommand:
        Command
    {
        private Item item;

        public Item Item
        {
            get { return item; }
            set { item = value; }
        }

        public RemoveFromCartCommand(VendorMachine vm)
            :base(vm)
        {

        }


        public override void Execute()
        {
            vendor.RemoveFromCart(item);
        }
    }

    class NextCommand :
        Command
    {
        public NextCommand(VendorMachine vm)
            :base(vm)
        {

        }

        public override void Execute()
        {
            vendor.NextPage();
        }
    }

    class PrevCommand :
        Command
    {
        public PrevCommand(VendorMachine vm)
            :base(vm)
        {

        }

        public override void Execute()
        {
            vendor.PrevPage();
        }
    }

    class AcquireCommand :
        Command
    {
        public AcquireCommand(VendorMachine vm)
            :base(vm)
        {

        }

        public override void Execute()
        {
            vendor.BuyItems();
        }
    }

}