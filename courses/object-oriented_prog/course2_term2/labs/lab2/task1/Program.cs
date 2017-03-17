using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    class Program
    {
        static void Main(string[] args)
        {
            User user1 = new User("Alpha", AccessLevel.SUBSCRIBED);
            User user2 = new User("Beta", AccessLevel.REGISTERED);
            User user3 = new User("Gamma", AccessLevel.REGISTERED);
            User user4 = new User("Omega", AccessLevel.SUBSCRIBED);

            List<User> userlist = new List<User>();
            userlist.Add(user1);
            userlist.Add(user2);
            userlist.Add(user3);
            userlist.Add(user4);

            Message publicMsg = new Message("HELLO TO ALL GUYZ!");
            publicMsg.showMessageString();
            publicMsg.SendMessage(userlist);

            ControlledMessage subscribersMsg = new ControlledMessage(new Message("Thank you for being subscribed, dude!"), AccessLevel.SUBSCRIBED);
            subscribersMsg.showMessageString();
            subscribersMsg.SendMessage(userlist);

            // End of the program
            Console.WriteLine("\nPress ANY KEY to exit the program...\n");
            Console.ReadKey();
        }
    }
}