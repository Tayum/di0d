using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    abstract class BookholderC
    {
        protected string name;
        protected int books;


        public BookholderC(string name)
        {
            this.name = name;
        }


        public abstract void Add(BookholderC comp);
        public abstract void Remove(BookholderC comp);
        public abstract int GetBooksInfo();
        public abstract void Display(int depth);

        public abstract List<Book> GetAllBooks();
    }


    class Bookholder : BookholderC
    {
        private List<BookholderC> holders = new List<BookholderC>();
        private static List<int> books_uCodes = new List<int>();


        public Bookholder(string name) : base(name)
        {
            books = 0;
        }


        public override void Add(BookholderC comp)
        {
            if (comp.GetType() == typeof(Book))
            {
                Book thyBook = (Book)comp;
                bool isAval = true;
                foreach (int uCode in books_uCodes)
                {
                    if(uCode == thyBook.uCode)
                    {
                        isAval = false;
                        break;
                    }
                }
                if (isAval)
                {
                    holders.Add(comp);
                    books_uCodes.Add(thyBook.uCode);
                }
                else
                {
                    Console.WriteLine("\nCannot add the <<" + thyBook.GetName() + ">> book with such a code: " + thyBook.uCode + ". Such unique code is already in use.\n");
                }
            }
            else
            {
                holders.Add(comp);
            }
        }

        public override void Remove(BookholderC comp)
        {
            holders.Remove(comp);
        }

        public override void Display(int depth)
        {
            Console.WriteLine(new String('-', depth) + name + " " + "(" + GetBooksInfo() + ")");

            foreach (BookholderC comp in holders)
            {
                comp.Display(depth + 3);
            }
        }

        public override int GetBooksInfo()
        {
            books = 0;
            foreach (BookholderC comp in holders)
            {
                books += comp.GetBooksInfo();
            }
            return books;
        }

        public override List<Book> GetAllBooks() {
            List<Book> allBooksList = new List<Book>();
            foreach (BookholderC comp in holders)
            {
                allBooksList.AddRange(comp.GetAllBooks());
                // allBooksList = allBooksList.Concat(comp.GetAllBooks()).ToList();
            }
            return allBooksList;
            // return holders.SelectMany(comp => comp.GetAllBooks()).ToList();
        }


        public int GetAllBooksWithUniqueCipher()
        {
            List<Book> thyList = GetAllBooks();
            List<Book> noDuplicatesList = thyList.Distinct().ToList();
            return noDuplicatesList.Count;
        }

    }

    class Book : BookholderC
    {
        public int cipher;
        public int uCode;


        public Book(string name) : base(name)
        {
            this.name = name;
            Random rnd = new Random();
            uCode = rnd.Next(1, 10);
            cipher = rnd.Next(1, 10);
        }

        private Book(string name, int uCode, int cipher) : this(name)
        {
            this.uCode = uCode;
            this.cipher = cipher;
        }

        
        public override void Add(BookholderC comp)
        {
            // do nothing
        }

        public override void Remove(BookholderC comp)
        {
            // do nothing
        }

        public override void Display(int depth)
        {
            Console.WriteLine(new String('-', depth) + GetSingleBookInfo());
        }

        public override int GetBooksInfo()
        {
            return 1;
        }
       
        public string GetName()
        {
            return name;
        }

        public string GetSingleBookInfo()
        {
            return "<<" + name + ">> [cipher:" + cipher + "] " + "[uCode: " + uCode + "]";
        }

        public override List<Book> GetAllBooks()
        {
            List<Book> oneBookAsList = new List<Book>();
            oneBookAsList.Add(new Book(this.name, this.uCode, this.cipher));
            return oneBookAsList;
        }

        #region Equals
        public override bool Equals(object obj)
        {
            Book other = (Book)obj;
            return (this.cipher == other.cipher);
        }

        public static bool operator ==(Book book1, Book book2)
        {
            if(object.ReferenceEquals(book1, null))
            {
                return object.ReferenceEquals(book2, null);
            }

            return book1.Equals(book2);
        }

        public static bool operator !=(Book book1, Book book2)
        {
            return !(book1 == book2);
        }

        public override int GetHashCode()
        {
            return cipher.GetHashCode();
        }
        #endregion
    }
}