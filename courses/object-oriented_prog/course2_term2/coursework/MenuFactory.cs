using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CourseWork
{
    // PATTERN: Factory Method
    // ALSO USED: Observer
    public interface IMenuFactory
    {
        Menu createMenu(VendorMachine vendor);
    }

    public class BrewMenuCreator: IMenuFactory
    {
        public Menu createMenu(VendorMachine vendor)
        {
            BrewMenu menu = new BrewMenu(vendor.Terminal, vendor.Factory);
            NotifyMenu notifyMenu = new NotifyMenu(menu);
            vendor.events.subscribe(EVENT_TYPE.ADDTOCART, notifyMenu);
            return notifyMenu;
        }
    }

    public class CartMenuCreator : IMenuFactory
    {
        public Menu createMenu(VendorMachine vendor)
        {
            CartMenu menu = new CartMenu(vendor.Terminal, vendor.Factory);
            NotifyMenu notifyMenu = new NotifyMenu(menu);
            vendor.events.subscribe(EVENT_TYPE.REMOVEFROMCART, notifyMenu);
            vendor.events.subscribe(EVENT_TYPE.BUYITEMS, notifyMenu);
            return notifyMenu;
        }
    }

    public class SnackMenuCreator : IMenuFactory
    {
        public Menu createMenu(VendorMachine vendor)
        {
            SnackMenu menu = new SnackMenu(vendor.Terminal, vendor.Factory);
            NotifyMenu notifyMenu = new NotifyMenu(menu);
            vendor.events.subscribe(EVENT_TYPE.ADDTOCART, notifyMenu);
            return notifyMenu;
        }
    }

    // THIS IS OPTIONAL CLASS! This Menu can be created without 'Terminal term'
    public class ShopMenuCreator : IMenuFactory
    {
        public Menu createMenu(VendorMachine vendor)
        {
            return new ShopMenu(vendor.Factory);
        }
    }

    // THIS IS OPTIONAL CLASS! This Menu can be created without 'Terminal term'
    public class MainMenuCreator : IMenuFactory
    {
        public Menu createMenu(VendorMachine vendor)
        {
            return new MainMenu(vendor.Factory);
        }
    }
}
