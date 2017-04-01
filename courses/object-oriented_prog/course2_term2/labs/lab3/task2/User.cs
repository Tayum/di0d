using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    // Abstract User (common fields for every type of user)
    public abstract class User : ICloneable
    {
        public enum Access_level
        {
            REGISTERED = 2,
            ADMIN = 10
        }


        private string username;
        private string password;
        private Access_level lvl;
        private string realname;


        public object Clone()
        {
            object clone = null;
            try
            {
                clone = MemberwiseClone();
            }
            catch (Exception e)
            {
                Console.WriteLine("ERROR WHILE CLONING: " + e.Message);
            }
            return clone;
        }


        public string GetUsername()
        {
            return username;
        }

        public void SetUsername(string username)
        {
            this.username = username;
        }

        public string GetPassword()
        {
            return password;
        }

        public void SetPassword(string pass)
        {
            password = pass;
        }

        public Access_level GetAccessLevel()
        {
            return lvl;
        }

        public void SetAccessLevel(Access_level level)
        {
            lvl = level;
        }

        public string GetName()
        {
            return realname;
        }

        public void SetName(string name)
        {
            realname = name;
        }
    }


    // Simple user (the user which is created when you want to register)
    public class SimpleUser : User
    {
        private int age;
        private string city;


        public int GetAge()
        {
            return age;
        }

        public void SetAge(int age)
        {
            this.age = age;
        }

        public string GetCity()
        {
            return city;
        }

        public void SetCity(string city)
        {
            this.city = city;
        }
    }


    // User-admin: user who has another capabilities and do not need some of (SimpleUser)'s fields
    public class Admin : User
    {
        private ConsoleColor textColor;


        public ConsoleColor GetTextColor()
        {
            return textColor;
        }

        public void SetTextColor(ConsoleColor color)
        {
            textColor = color;
        }
    }


    // User Cache
    public class UserCache
    {
        private static Dictionary<string, User> dict = new Dictionary<string, User>();

        public static User GetUser(string username)
        {
            User cachedUser = dict[username];
            return (User)cachedUser.Clone();
        }

        public static void LoadCache()  
        {
            SimpleUser s1mpl3 = new SimpleUser();
            s1mpl3.SetUsername("s1mpl3");
            s1mpl3.SetPassword("s1mpl3");
            s1mpl3.SetAccessLevel(User.Access_level.REGISTERED);
            s1mpl3.SetName("SimpleUser");
            s1mpl3.SetCity("SimpleCity");
            s1mpl3.SetAge(18);
            dict[s1mpl3.GetUsername()] = s1mpl3;

            Admin adm1n = new Admin();
            adm1n.SetUsername("adm1n");
            adm1n.SetPassword("adm1n");
            adm1n.SetAccessLevel(User.Access_level.ADMIN);
            adm1n.SetName("AdminUser");
            adm1n.SetTextColor(ConsoleColor.Red);
            dict[adm1n.GetUsername()] = adm1n;
        }
    }
}
