using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CourseWork
{
    public class ConsoleUI
    {
        private Menu curMenu;
        private Menu prevMenu;

        public Menu CurMenu
        {
            get { return curMenu; }
            set { curMenu = value; }
        }

        public Menu PrevMenu
        {
            get { return prevMenu; }
            set { prevMenu = value; }
        }

        public ConsoleUI(CommandFactory fact)
        {
            curMenu = new MainMenu(fact);
            prevMenu = null;
        }
    }


    public class MenuOption
    {
        private string desc;
        public Command command;

        public string Description
        {
            get { return desc; }
            set { desc = value; }
        }

        public MenuOption(string desc, Command com)
        {
            this.desc = desc;
            command = com;
        }
    }


    public abstract class Menu
    {
        private string hint;
        protected List<MenuOption> options = new List<MenuOption>();
        protected Dictionary<string, MenuOption> additionalOptions = new Dictionary<string, MenuOption>();

        public virtual string Hint
        {
            get { return hint; }
            set { hint = value; }
        }

        public virtual void PrintMenu()
        {
            Console.Clear();
            Console.WriteLine(hint);
            for (int i = 0; i < options.Count; i++) 
            {
                Console.WriteLine((i + 1) + ". " + options[i].Description);
            }
            Console.WriteLine();
            for (int i = 0; i < additionalOptions.Count; i++)
            {
                Console.WriteLine(additionalOptions.ElementAt(i).Value.Description);
            }
            Console.WriteLine("[Q]uit");
        }

        public virtual bool AnalyzeInput()
        {
            string input = Console.ReadKey(true).KeyChar.ToString().ToUpper();

            // Quit
            if (input == "Q")
            {
                return false;
            }

            else
            {
                if (additionalOptions.ContainsKey(input))
                {
                    Command command = additionalOptions[input].command;
                    command.Execute();
                }
                else
                {
                    int number;
                    bool isNumber = Int32.TryParse(input, out number);
                    if (isNumber && (number > 0 && number <= options.Count))
                    {
                        Command command = options[number - 1].command;
                        command.Execute();
                    }
                    else
                    {
                        AnalyzeInput();
                    }
                }
                return true;
            }
        }

        public virtual bool RunMenu()
        {
            PrintMenu();
            return AnalyzeInput();
        }
    }


    class MainMenu: Menu
    {
        public MainMenu(CommandFactory fact)
        {
            Hint =
                "====================\n" +
                "Welcome to the Snack'n'Brew!\n" +
                "Press [1] to go to Shop;\n" +
                "Press [2] to go to Cart;\n" +
                "You can press [Q] any time to quit our Shop.\n" +
                "====================\n\n";
            RouteCommand command = (RouteCommand)fact.CreateCommand(COMMAND.ROUTE);
            command.MenuCreator = new ShopMenuCreator();
            command.PrevMenuCreator = new MainMenuCreator();
            options.Add(new MenuOption("Shop", command));

            command = (RouteCommand)fact.CreateCommand(COMMAND.ROUTE);
            command.MenuCreator = new CartMenuCreator();
            command.PrevMenuCreator = new MainMenuCreator();
            options.Add(new MenuOption("My Cart", command));
        }
    }


    class ShopMenu: Menu
    {
        public ShopMenu(CommandFactory fact)
        {
            Hint =
                "====================\n" +
                "Press [1] to go to <Snacks> list;\n" +
                "Press [2] to go to <Brews> list;\n" +
                "Press [B] to return to Main Menu\n" +
                "====================\n\n";
            RouteCommand command = (RouteCommand)fact.CreateCommand(COMMAND.ROUTE);
            command.MenuCreator = new SnackMenuCreator();
            command.PrevMenuCreator = new ShopMenuCreator();
            options.Add(new MenuOption("Snacks", command));

            command = (RouteCommand)fact.CreateCommand(COMMAND.ROUTE);
            command.MenuCreator = new BrewMenuCreator();
            command.PrevMenuCreator = new ShopMenuCreator();
            options.Add(new MenuOption("Brews", command));

            BackCommand backCommand = (BackCommand)fact.CreateCommand(COMMAND.BACK);
            backCommand.PrevMenuCreator = null;
            additionalOptions.Add("B", new MenuOption("[B]ack", backCommand));
        }
    }


    public interface IPageMenu
    {
        int Page
        {
            get; set;
        }

        void SetPage(int page, Terminal termItems, CommandFactory fact);
    }


    class SnackMenu: Menu,
        IPageMenu
    {
        private int page = 0;

        public int Page
        {
            get { return page; }
            set { page = value; }
        }

        public SnackMenu(Terminal term, CommandFactory fact)
        {
            Hint =
                "====================\n" +
                "Press [1]-[9] to add certain Snack to cart;\n" +
                "Press [P] to proceed to Prev page;\n" +
                "Press [N] to proceed to Next page;\n" +
                "Press [B] to return to Shop Menu\n" +
                "====================\n\n";

            SetPage(0, term, fact);
            additionalOptions.Add("P", new MenuOption("< [P]rev", (PrevCommand)fact.CreateCommand(COMMAND.PREV)));
            additionalOptions.Add("N", new MenuOption("[N]ext >", (NextCommand)fact.CreateCommand(COMMAND.NEXT)));

            BackCommand backCommand = (BackCommand)fact.CreateCommand(COMMAND.BACK);
            backCommand.PrevMenuCreator = new MainMenuCreator();
            additionalOptions.Add("B", new MenuOption("[B]ack", backCommand));
        }

        public void SetPage(int page, Terminal term, CommandFactory fact)
        {
            List<Snack> snacks = term.Snacks;
            if ((page * 9 < snacks.Count) && (page >= 0))
            {
                Page = page;
                options.Clear();
                int counter = 0;
                for (int i = Page * 9; (i < snacks.Count && counter < 9); i++)
                {
                    AddToCartCommand command = (AddToCartCommand)fact.CreateCommand(COMMAND.ADD_TO_CART);
                    command.Item = snacks[i];
                    options.Add(new MenuOption(snacks[i].Name + " (" + snacks[i].Netto + " grams) (" + snacks[i].Cost + " crowns)", command));
                    counter++;
                }
            }
        }
    }


    class BrewMenu: Menu,
        IPageMenu
    {
        private int page = 0;

        public int Page
        {
            get { return page; }
            set { page = value; }
        }

        public BrewMenu(Terminal term, CommandFactory fact)
        {
            Hint =
                "====================\n" +
                "Press [1]-[9] to add certain Brew to cart;\n" +
                "Press [P] to proceed to Prev page;\n" +
                "Press [N] to proceed to Next page;\n" +
                "Press [B] to return to Shop Menu\n" +
                "====================\n\n";

            SetPage(0, term, fact);
            additionalOptions.Add("P", new MenuOption("< [P]rev", (PrevCommand)fact.CreateCommand(COMMAND.PREV)));
            additionalOptions.Add("N", new MenuOption("[N]ext >", (NextCommand)fact.CreateCommand(COMMAND.NEXT)));

            BackCommand backCommand = (BackCommand)fact.CreateCommand(COMMAND.BACK);
            backCommand.PrevMenuCreator = new MainMenuCreator();
            additionalOptions.Add("B", new MenuOption("[B]ack", backCommand));
        }

        public void SetPage(int page, Terminal term, CommandFactory fact)
        {
            List<Brew> brews = term.Brews;
            if ((page * 9 < brews.Count) && (page >= 0))
            {
                Page = page;
                options.Clear();
                int counter = 0;
                for (int i = Page * 9; (i < brews.Count && counter < 9); i++)
                {
                    AddToCartCommand command = (AddToCartCommand)fact.CreateCommand(COMMAND.ADD_TO_CART);
                    command.Item = brews[i];
                    options.Add(new MenuOption(brews[i].Name + " (" + brews[i].AgeRestriction + "+) (" + brews[i].Cost + " crowns)", command));
                    counter++;
                }
            }
        }
    }

    class CartMenu: Menu,
        IPageMenu
    {
        private int page = 0;

        public int Page
        {
            get { return page; }
            set { page = value; }
        }

        public CartMenu(Terminal term, CommandFactory fact)
        {
            Hint =
                "====================\n" +
                "Press [1]-[9] to delete certain Item from cart;\n" +
                "Press [P] to proceed to Prev page;\n" +
                "Press [N] to proceed to Next page;\n" +
                "Press [A] to Acquire (pay for) all the Items;\n" +
                "Press [B] to return to Main Menu\n" +
                "====================\n\n";

            SetPage(0, term, fact);
            additionalOptions.Add("P", new MenuOption("< [P]rev", (PrevCommand)fact.CreateCommand(COMMAND.PREV)));
            additionalOptions.Add("N", new MenuOption("[N]ext >", (NextCommand)fact.CreateCommand(COMMAND.NEXT)));
            additionalOptions.Add("A", new MenuOption("[A]cquire", (AcquireCommand)fact.CreateCommand(COMMAND.ACQUIRE)));

            BackCommand backCommand = (BackCommand)fact.CreateCommand(COMMAND.BACK);
            backCommand.PrevMenuCreator = new MainMenuCreator();
            additionalOptions.Add("B", new MenuOption("[B]ack", backCommand));
        }

        public void SetPage(int page, Terminal term, CommandFactory fact)
        {
            List<Item> items = term.user.Cart;
            if ((page * 9 < items.Count) && (page >= 0))
            {
                Page = page;
                options.Clear();
                int counter = 0;
                for (int i = Page * 9; (i < items.Count && counter < 9); i++)
                {
                    RemoveFromCartCommand command = (RemoveFromCartCommand)fact.CreateCommand(COMMAND.REMOVE_FROM_CART);
                    command.Item = items[i];
                    options.Add(new MenuOption(items[i].Name + " (" + items[i].Cost + " crowns)", command));
                    counter++;
                }
            }
        }
    }

    // PATTERN: Decorator
    // ALSO USED: Observer
    class NotifyMenu: Menu, IPageMenu, IEventListener
    {
        private Menu menu;
        private string notifier;

        public NotifyMenu(Menu menu)
        {
            this.menu = menu;
            notifier = null;
        }

        public override string Hint
        {
            get { return menu.Hint; }
            set { menu.Hint = value; }
        }

        public int Page
        {
            get {
                IPageMenu pageMenu = (IPageMenu)menu;
                return pageMenu.Page;
            }
            set
            {
                IPageMenu pageMenu = (IPageMenu)menu;
                pageMenu.Page = value;
            }
        }

        public override bool RunMenu()
        {
            menu.PrintMenu();
            if(notifier != null)
            {
                Console.WriteLine("\n~~~~~~~~~~~~~~~~~~~~");
                Console.WriteLine(notifier);
                Console.WriteLine("~~~~~~~~~~~~~~~~~~~~\n");
                notifier = null;
            }
            return menu.AnalyzeInput();
        }

        public void update(EVENT_TYPE ev, string info)
        {
            notifier = info;
        }

        public void SetPage(int page, Terminal term, CommandFactory fact)
        {
            IPageMenu pageMenu = (IPageMenu)menu;
            pageMenu.SetPage(page, term, fact);
        }
    }

}
