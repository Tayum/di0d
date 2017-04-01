using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    // Infolist structure
    public class Infolist
    {
        public string infolistType;
        public string map;
        public string courses_info;
        public string diplomas_info;
    }


    // Infolist abstract Builder
    public abstract class InfolistBuilder
    {
        public Infolist infolist;


        public void CreateInfolist()
        {
            infolist = new Infolist();
        }


        public abstract void SetInfolistType();
        public abstract void SetMap();
        public abstract void SetCoursesInfo();
        public abstract void SetDiplomasInfo();
        public Infolist DispatchInfolist()
        {
            return infolist;
        }
    }


    // 'Freshman' infolist builder
    public class FreshmanBuilder : InfolistBuilder
    {
        public override void SetInfolistType()
        {
            infolist.infolistType = "Freshman";
        }

        public override void SetMap()
        {
            infolist.map = "[KPI Map with all main Buildings for the Freshman]";
        }

        public override void SetCoursesInfo()
        {
            infolist.courses_info = "[Additional info for 1-4 courses]";
        }

        public override void SetDiplomasInfo()
        {
            infolist.diplomas_info = "[Additional info about how to earn RED DIPLOMA in future]";
        }

    }


    // 'Master' infolist builder
    public class MasterBuilder : InfolistBuilder
    {
        public override void SetInfolistType()
        {
            infolist.infolistType = "Master";
        }

        public override void SetMap()
        {
            infolist.map = "[KPI Map with the main faculty for the Master]";
        }

        public override void SetCoursesInfo()
        {
            infolist.courses_info = "[Additional info for 5, 6 courses]";
        }

        public override void SetDiplomasInfo()
        {
            infolist.diplomas_info = "[Additional info about how to WRITE DIPLOMA]";
        }
    }

    // Director-constructor
    public class Director
    {
        private static Director instance;


        protected Director()
        {
            // does nothing
        }


        public static Director getInstance()
        {
            if (instance == null)
            {
                instance = new Director();
            }
            return instance;
        }

        public Infolist GenerateInfolist(InfolistBuilder infolistBuilder)
        {
            infolistBuilder.CreateInfolist();
            infolistBuilder.SetInfolistType();
            infolistBuilder.SetMap();
            infolistBuilder.SetCoursesInfo();
            infolistBuilder.SetDiplomasInfo();

            return infolistBuilder.DispatchInfolist();
        }
    }

}