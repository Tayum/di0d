using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    // Abstract command
    abstract class Command
    {
        public abstract void Execute();
    }

    // Concrete command
    class EditText : Command
    {
        protected char operation;
        protected string text;
        protected int line;
        protected TextFile textfile;


        public EditText(TextFile textfile, char operation, int line, string text)
        {
            this.textfile = textfile;
            this.operation = operation;
            this.line = line;
            this.text = text;
        }


        public char Operation
        {
            set { operation = value; }
        }

        public int Operand
        {
            set { line = value; }
        }

        // list of commands that can be performed by the object of this class:
        // [A]dd / make [B]old / make [I]talic
        public override void Execute()
        {
            textfile.Operation(operation, text, line);
        }
    }


    // "Receiver" of operations: the thing the operations are inflicted on
    // (It is "text_in_file" - the list of strings)
    class TextFile
    {
        private List<string> text_in_file = new List<string>();


        public void Operation(char operation, string text, int line)
        {
            switch (operation)
            {
                case 'A':
                    text_in_file.Insert(line, text);
                    break;
                case 'B':
                    text_in_file[line] = "*bold*" + text_in_file[line].TrimEnd('\n') + "*bold*";
                    break;
                case 'I':
                    text_in_file[line] = "_italic_" + text_in_file[line].TrimEnd('\n') + "_italic_";
                    break;
            }
        }

        // Print all the text
        public void PrintText()
        {
            Console.WriteLine("TEXT IN THE FILE: <<");
            foreach (string str in text_in_file)
            {
                Console.WriteLine(str);
            }
            Console.WriteLine(">>");
        }

        // Delete all the text
        public void ClearText()
        {
            Console.WriteLine("\n\n...clearing the text in file...\n");
            text_in_file = new List<string>();
        }
    }


    // "Invoker": user that performs different operations
    class User
    {
        private TextFile textfile = new TextFile();
        private List<Command> commands = new List<Command>();
        private int currentOperation = 0;
        

        public void Redo(int operations_amount)
        {
            Console.WriteLine("\n\n...redoing " + operations_amount + " operations...\n\n");

            for (int i = 0; i < operations_amount; i++)
            {
                if (currentOperation < commands.Count)
                {
                    commands[currentOperation++].Execute();
                }
            }
        }

        public void EditText(char operation, int line, string text)
        {
            // Create and run the command
            Command command = new EditText(textfile, operation, line, text);
            command.Execute();

            // Add the operation to the "Undo"-list
            commands.Add(command);
            currentOperation++;
        }

        public void PrintText()
        {
            textfile.PrintText();
        }

        public void ClearText()
        {
            textfile.ClearText();
            // set the counter back to 0: all operations are reverted
            currentOperation = 0;
        }
    }

}
