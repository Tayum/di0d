using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    class BallotFactory
    {
        private Dictionary<string, Ballot> ballotList = new Dictionary<string, Ballot>();


        public Ballot GetBallot(string key)
        {
            Ballot ballot = null;

            if (ballotList.ContainsKey(key))
            {
                ballot = ballotList[key];
            }
            else
            {
                switch (key)
                {
                    case "ArnoldSchwarznegger":
                        ballot = new BallotArnoldSchwarzenegger();
                        break;
                    case "LawrenceOfArabia":
                        ballot = new BallotLawrenceOfArabia();
                        break;
                    case "ChuckNorris":
                        ballot = new BallotChuckNorris();
                        break;
                }

                ballotList.Add(key, ballot);
            }

            return ballot;
        }
    }


    abstract class Ballot
    {
        protected string name;
        protected string slogan;
        protected string desc;
        protected int counterMark;
        public abstract void Display(int counterMark);
    }


    class BallotArnoldSchwarzenegger : Ballot
    {


        public BallotArnoldSchwarzenegger()
        {
            this.counterMark = -1;
            this.name = "Arnold Schwarznegger";
            this.slogan = "I'll always be back!";
            this.desc = "Hi. I'm Arnie. Most of you know me as bodybuilder and Terminator. Choose me and we will defeat the Skynet together!";
        }


        public override void Display(int counterMark)
        {
            if (this.counterMark == -1)
            {
                this.counterMark = counterMark;
            }
            Console.WriteLine("Name: " + this.name);
            // Console.WriteLine("Slogan: " + this.slogan);
            // Console.WriteLine("Description: " + this.desc);
            Console.WriteLine(">>\nINNER COUNTER-MARK: " + this.counterMark + "\n>>");
        }
    }


    class BallotLawrenceOfArabia : Ballot
    {


        public BallotLawrenceOfArabia()
        {
            this.counterMark = -1;
            this.name = "Lawrence Of Arabia";
            this.slogan = "Let's perform Great Arab Revolt!";
            this.desc = "My greetings! Enslaved states of Near East, It's time to unite and earn the independency! Choose me and let the Revolt begin!";
        }


        public override void Display(int counterMark)
        {
            if (this.counterMark == -1)
            {
                this.counterMark = counterMark;
            }
            Console.WriteLine("Name: " + this.name);
            // Console.WriteLine("Slogan: " + this.slogan);
            // Console.WriteLine("Description: " + this.desc);
            Console.WriteLine(">>\nINNER COUNTER-MARK: " + this.counterMark + "\n>>");
        }
    }


    // Probably other potential presidents to ballot


    class BallotChuckNorris : Ballot
    {


        public BallotChuckNorris()
        {
            this.counterMark = -1;
            this.name = "Chuck Norris";
            this.slogan = "I can kill two stones with one bird.";
            this.desc = "I do not need description. Description needs me.";
        }


        public override void Display(int counterMark)
        {
            if(this.counterMark == -1)
            {
                this.counterMark = counterMark;
            }
            Console.WriteLine("Name: " + this.name);
            // Console.WriteLine("Slogan: " + this.slogan);
            // Console.WriteLine("Description: " + this.desc);
            Console.WriteLine(">>\nINNER COUNTER-MARK: " + this.counterMark + "\n>>");
        }
    }
}
