using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace lab5
{
    public class ViewModelBase : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            OnPropertyChanged(new PropertyChangedEventArgs(propertyName));
        }

        protected virtual void OnPropertyChanged(PropertyChangedEventArgs args)
        {
            var handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, args);
            } 
        }
    }

    public class DelegateCommand : ICommand
    {
        public delegate void ICommandOnExecute(object parameter);
        public delegate bool ICommandOnCanExecute(object parameter);

        private ICommandOnExecute _execute;
        private ICommandOnCanExecute _canExecute;

        public DelegateCommand(ICommandOnExecute onExecuteMethod, ICommandOnCanExecute onCanExecuteMethod)
        {
            _execute = onExecuteMethod;
            _canExecute = onCanExecuteMethod;
        }

        // ICommand Members
        public event EventHandler CanExecuteChanged
        {
            add
            {
                CommandManager.RequerySuggested += value;
            }
            remove
            {
                CommandManager.RequerySuggested -= value;
            }
        }

        public bool CanExecute(object parameter)
        {
            return _canExecute.Invoke(parameter);
        }

        public void Execute(object parameter)
        {
            _execute.Invoke(parameter);
        }

    }

    public class MainViewModel : ViewModelBase
    {
        private DelegateCommand exitCommand;

        // Constructor
        public ArmorModel ArmorArr {
            get;
            set;
        }

        // CREATE NEW ARMOR
        private string aNameToAdd;
        private int aPhysicalDefenseToAdd;
        private int aMagicalDefenseToAdd;
        private int aEvasionToAdd;

        public string ANameToAdd
        {
            get
            {
                return aNameToAdd;
            }
            set
            {
                aNameToAdd = value;
            }
        }
        public int APhysicalDefenseToAdd
        {
            get
            {
                return aPhysicalDefenseToAdd;
            }
            set
            {
                aPhysicalDefenseToAdd = value;
            }
        }
        public int AMagicalDefenseToAdd
        {
            get
            {
                return aMagicalDefenseToAdd;
            }
            set
            {
                aMagicalDefenseToAdd = value;
            }
        }
        public int AEvasionToAdd
        {
            get
            {
                return aEvasionToAdd;
            }
            set
            {
                aEvasionToAdd = value;
            }
        }

        // UPDATE EXISTING ARMOR
        private string aNameToEdit;
        private int aPhysicalDefenseToEdit;
        private int aMagicalDefenseToEdit;
        private int aEvasionToEdit;

        public string ANameToEdit
        {
            get
            {
                return aNameToEdit;
            }
            set
            {
                aNameToEdit = value;
            }
        }
        public int APhysicalDefenseToEdit
        {
            get
            {
                return aPhysicalDefenseToEdit;
            }
            set
            {
                aPhysicalDefenseToEdit = value;
            }
        }
        public int AMagicalDefenseToEdit
        {
            get
            {
                return aMagicalDefenseToEdit;
            }
            set
            {
                aMagicalDefenseToEdit = value;
            }
        }
        public int AEvasionToEdit
        {
            get
            {
                return aEvasionToEdit;
            }
            set
            {
                aEvasionToEdit = value;
            }
        }

        public MainViewModel()
        {
            ArmorArr = ArmorModel.Current;
        }


        public ICommand ExitCommand
        {
            get
            {
                if (exitCommand == null)
                {
                    exitCommand = new DelegateCommand(Exit, CanExecuteCommandTrue);
                }
                return exitCommand;
            }
        }

        private void Exit(object parameter)
        {
            // Save before the exit
            ArmorArr.saveArmor();
            Application.Current.Shutdown();
        }


        public bool CanExecuteCommandTrue(object parameter)
        {
            return true;
        }

        private ICommand addArmor;
        public ICommand AddArmor
        {
            get
            {
                if (addArmor == null)
                {
                    addArmor = new DelegateCommand(ExecuteCommand_First, CanExecuteCommandTrue);

                }

                return addArmor;
            }
        }

        public void ExecuteCommand_First(object parameter)
        {
            if ((ANameToAdd == null) || (aNameToAdd.Length < 4))
            {
                throw new ArgumentException("Name field should be at least 4 characters long.");
            }
            if ((APhysicalDefenseToAdd <= 0) || (APhysicalDefenseToAdd > 500))
            {
                throw new ArgumentException("Physical Defense should lay between 0 and 500.");
            }
            if ((AMagicalDefenseToAdd <= 0) || (AMagicalDefenseToAdd > 500))
            {
                throw new ArgumentException("Magical Defense should lay between 0 and 500.");
            }
            if ((AEvasionToAdd <= 0) || (AEvasionToAdd > 100))
            {
                throw new ArgumentException("Evasion should lay between 0 and 100.");
            }

            ArmorArr.addArmor(ANameToAdd, APhysicalDefenseToAdd, AMagicalDefenseToAdd, AEvasionToAdd);
        }

        public void deleteArmor(object armorObj)
        {
            ArmorArr.Remove((Armor)armorObj);
        }

        public void editArmor(object armorObj)
        {
            if ((ANameToEdit == null) || (aNameToEdit.Length < 4))
            {
                throw new ArgumentException("Name field should be at least 4 characters long.");
            }
            if ((APhysicalDefenseToEdit <= 0) || (APhysicalDefenseToEdit > 500))
            {
                throw new ArgumentException("Physical Defense should lay between 0 and 500.");
            }
            if ((AMagicalDefenseToEdit <= 0) || (AMagicalDefenseToEdit > 500))
            {
                throw new ArgumentException("Magical Defense should lay between 0 and 500.");
            }
            if ((AEvasionToEdit <= 0) || (AEvasionToEdit > 100))
            {
                throw new ArgumentException("Evasion should lay between 0 and 100.");
            }

            Armor oldArmor = (Armor)armorObj;
            int index = ArmorArr.getArmorIndex(oldArmor);
            ArmorArr.removeArmor(oldArmor);

            Armor newArmor = new Armor();
            newArmor.Name = ANameToEdit;
            newArmor.PhysicalDefense = APhysicalDefenseToEdit;
            newArmor.MagicalDefense = AMagicalDefenseToEdit;
            newArmor.Evasion = AEvasionToEdit;

            ArmorArr.addArmor(newArmor, index);
        }
    }
}