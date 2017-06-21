using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CourseWork
{
    // PATTERN: Facade
    // ALSO USED: Observer
    public class VendorMachine
    {
        private Terminal terminal;
        private ConsoleUI ui;
        private CommandFactory factory;
        public EventManager events;

        public Terminal Terminal
        {
            get { return terminal; }
        }

        public ConsoleUI UI
        {
            get { return ui; }
        }

        public CommandFactory Factory
        {
            get { return factory; }
        }

        public VendorMachine(User user)
        {
            terminal = new Terminal(user);
            factory = new CommandFactory(this);
            ui = new ConsoleUI(factory);
            events = new EventManager(EVENT_TYPE.ADDTOCART, EVENT_TYPE.REMOVEFROMCART, EVENT_TYPE.BUYITEMS);
        }

        public bool RunMenu()
        {
            return ui.CurMenu.RunMenu();
        }

        public void AddToShop(Item item)
        {
            terminal.AddToShop(item);
        }

        public void AddToCart(Item item)
        {
            bool isAdded = terminal.user.AddToCart(item);
            if(isAdded)
            {
                events.notify(EVENT_TYPE.ADDTOCART, "You have added '" + item.Name + "' to your cart!");
            }
            else
            {
                events.notify(EVENT_TYPE.ADDTOCART, "Sorry, you are not allowed to buy this product :(");
            }
        }

        public void RemoveFromCart(Item item)
        {
            terminal.user.RemoveFromCart(item);
            // Build new Menu with updated Cart
            SetCurMenu(new CartMenuCreator());
            events.notify(EVENT_TYPE.REMOVEFROMCART, "You have removed '" + item.Name + "' from your cart.");
        }

        public void BuyItems() {
            bool hasBought = terminal.user.BuyItems();
            // Build new Menu with updated Cart
            SetCurMenu(new CartMenuCreator());
            if (hasBought)
            {
                events.notify(EVENT_TYPE.BUYITEMS, "You have bought the items!");
            }
            else
            {
                events.notify(EVENT_TYPE.BUYITEMS, "You haven't bought items. You don't have enough money or your cart is empty.");
            }
        }

        public void SetCurMenu()
        {
            ui.CurMenu = ui.PrevMenu;
        }

        public void SetCurMenu(IMenuFactory curMenuCreator)
        {
            ui.CurMenu = curMenuCreator.createMenu(this);
        }

        public void SetPrevMenu(IMenuFactory prevMenuCreator)
        {
            ui.PrevMenu = prevMenuCreator.createMenu(this);
        }

        public void PrevPage()
        {
            IPageMenu menu = (IPageMenu)ui.CurMenu;
            menu.SetPage(menu.Page - 1, terminal, factory);
        }

        public void NextPage()
        {
            IPageMenu menu = (IPageMenu)ui.CurMenu;
            menu.SetPage(menu.Page + 1, terminal, factory);
        }
    }
}
