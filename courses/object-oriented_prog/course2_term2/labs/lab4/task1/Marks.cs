using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    public interface MarksStrategy
    {
        string Summarize(int curPoints);
    }


    public class Credit : MarksStrategy
    {
        private enum CreditResult
        {
            FAILED,
            PASSED
        }


        public Credit()
        {
            // nothing is done
        }


        public string Summarize(int points)
        {
            if (points < 60)
            {
                return points + ": " + CreditResult.FAILED.ToString();
            }
            else
            {
                return points + ": " + CreditResult.PASSED.ToString();
            }
        }
    }


    public class Exam : MarksStrategy
    {
        private enum ExamResult
        {
            F,
            E,
            D,
            C,
            B,
            A
        }


        public Exam()
        {
            // nothing is done
        }


        public string Summarize(int points)
        {
            if(points < 60)
            {
                return points + ": " + ExamResult.F.ToString();
            }
            else if(points >= 60 && points < 65)
            {
                return points + ": " + ExamResult.E.ToString();
            }
            else if (points >= 65 && points < 75)
            {
                return points + ": " + ExamResult.D.ToString();
            }
            else if (points >= 75 && points < 85)
            {
                return points + ": " + ExamResult.C.ToString();
            }
            else if (points >= 85 && points < 95)
            {
                return points + ": " + ExamResult.B.ToString();
            }
            else
            {
                return points + ": " + ExamResult.A.ToString();
            }
        }
    }


    public class Discipline
    {
        private MarksStrategy strategy;
        public string name;
        private int points;


        public Discipline(string name, int points, MarksStrategy str)
        {
            this.name = name;
            this.points = points;
            strategy = str;
        }


        public string Verdict()
        {
            return strategy.Summarize(points);
        }
    }
}
