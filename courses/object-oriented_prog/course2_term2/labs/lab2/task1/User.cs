using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    // public enum of access levels
    public enum AccessLevel
    {
        REGISTERED = 0,
        SUBSCRIBED = 1
    }


    class User
    {
        public string nickname;
        public AccessLevel ac_lvl;

        public User(string nick, AccessLevel lvl)
        {
            nickname = nick;
            ac_lvl = lvl;
        }
    }


    // Interface for Message
    abstract class A_Message
    {
        public abstract void showMessageString();
        public abstract void SendMessage(List<User> users);
    }


    // Send message function implementation
    class Message : A_Message
    {
        public string messageString;


        public Message(string message)
        {
            messageString = message;
        }


        public override void showMessageString()
        {
            Console.WriteLine("\nActual message: \"" + messageString + "\"\n");
        }

        public override void SendMessage(List<User> users)
        {
            foreach(User user in users)
            {
                Console.WriteLine("@" + user.nickname + ": " + messageString);
            }
        }
    }


    // Check access level for the message sent
    class ControlledMessage : A_Message
    {
        public Message message;
        public AccessLevel reqLvl;


        public ControlledMessage(Message message, AccessLevel lvl)
        {
            this.message = message;
            reqLvl = lvl;
        }


        public override void showMessageString()
        {
            message.showMessageString();
        }

        public override void SendMessage(List<User> users)
        {
            foreach (User user in users)
            {
                if((int)user.ac_lvl >= (int)reqLvl)
                {
                    Console.WriteLine("@" + user.nickname + ": " + message.messageString);
                }
                
            }
        }
    }
}