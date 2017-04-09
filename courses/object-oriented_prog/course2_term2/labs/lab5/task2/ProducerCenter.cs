using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    abstract class ProdCentreA
    {
        public abstract void AddMusician(Musician musician);
        public abstract string CreateProgram(List<string> desiredMusicianList);
        protected abstract bool AskMusician(Musician musician);
    }


    class ProdCentre : ProdCentreA
    {
        private Dictionary<string, Musician> musicians = new Dictionary<string, Musician>();


        public override void AddMusician(Musician musician)
        {
            if(!musicians.ContainsKey(musician.Name))
            {
                musicians.Add(musician.Name, musician);
            }
        }


        public override string CreateProgram(List<string> desiredMusicianList)
        {
            string program = "\n\nThe program is next:\n";
            int counter = 0;
            for (int i = 0; i < desiredMusicianList.Count; i++) 
            {
                string name = desiredMusicianList.ElementAt(i);
                if (musicians.ContainsKey(name)) {
                    Musician artist = musicians[name];
                    bool isWorking = AskMusician(artist);
                    if (!isWorking)
                    {
                        artist.Work = true;
                        counter++;
                        program += "> " + counter + ": " + artist.Name + "\n";
                    }
                    else
                    {
                        program += "(sorry, the <" + name + "> artist is currently busy!\n";
                    }
                }
                else
                {
                    program += "(sorry, we are not working with <" + name + "> artist!\n";
                }
            }
            program += "This will be your program. We hope that you'll enjoy it!\n\n";
            return program;
        }


        protected override bool AskMusician(Musician musician)
        {
            if (musician.Work)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }


    class Musician
    {
        private string name;
        private bool isWorking;


        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public bool Work
        {
            get { return isWorking; }
            set { isWorking = value; }
        }


        public Musician()
        {
            isWorking = false;
        }
    }


    class OkeanElzy : Musician
    {
        public OkeanElzy()
            : base()
        {
            Name = "OkeanElzy";
        }
    }


    class Antitela: Musician
    {
        public Antitela()
            : base()
        {
            Name = "Antitela";
        }
    }


    class Skryabin : Musician
    {
        public Skryabin()
            : base()
        {
            Name = "Skryabin";
        }
    }


    class DDT : Musician
    {
        public DDT()
            : base()
        {
            Name = "DDT";
        }
    }

}
