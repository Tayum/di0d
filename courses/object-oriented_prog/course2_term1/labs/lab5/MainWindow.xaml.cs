using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace lab5
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private MainViewModel DataContext;

        public MainWindow()
        {
            InitializeComponent();
            DataContext = new MainViewModel();
            NameField.TextChanged += TextBoxOnChange;
            PhysicalDefenseField.TextChanged += TextBoxOnChange;
            MagicalDefenseField.TextChanged += TextBoxOnChange;
            EvasionField.TextChanged += TextBoxOnChange;
        }

        private void TextBoxOnChange(object sender, System.EventArgs eventArgs)
        {
            if (NameField.Text.Length < 4 ||
                PhysicalDefenseField.Text.Length == 0 ||
                MagicalDefenseField.Text.Length == 0 ||
                EvasionField.Text.Length == 0)
            {
                btnAddArmor.IsEnabled = false;
            }
            else
            {
                try
                {
                    int pdef = Int32.Parse(PhysicalDefenseField.Text);
                    int mdef = Int32.Parse(MagicalDefenseField.Text);
                    int evasion = Int32.Parse(EvasionField.Text);
                    if (pdef < 0 || mdef < 0 || evasion < 0 ||
                        pdef > 500 || mdef > 500 || evasion > 100)
                    {
                        btnAddArmor.IsEnabled = false;
                    }
                    else
                    {
                        btnAddArmor.IsEnabled = true;
                    }
                }
                catch (Exception exception)
                {
                    if (exception is FormatException || exception is OverflowException)
                    {
                        btnAddArmor.IsEnabled = false;
                    }
                }
            }
        }

        public void MW_deleteArmor(object sender, RoutedEventArgs e)
        {
            DataContext.deleteArmor((Armor)ArmorList.SelectedItem);
        }

        public void MW_editArmor(object sender, RoutedEventArgs e)
        {
            if (NameEditField.Text.Length < 4 ||
                PhysicalDefenseEditField.Text.Length == 0 ||
                MagicalDefenseEditField.Text.Length == 0 ||
                EvasionEditField.Text.Length == 0)
            {
                btnAddArmor.IsEnabled = false;
            }
            else
            {
                try
                {
                    int pdef = Int32.Parse(PhysicalDefenseEditField.Text);
                    int mdef = Int32.Parse(MagicalDefenseEditField.Text);
                    int evasion = Int32.Parse(EvasionEditField.Text);
                }
                catch (Exception exception)
                {
                    if (exception is FormatException || exception is OverflowException)
                    {
                        btnAddArmor.IsEnabled = false;
                    }
                }
            }
            // update the corresponding fields via Properties
            DataContext.ANameToEdit = NameEditField.Text;
            DataContext.APhysicalDefenseToEdit = Int32.Parse(PhysicalDefenseEditField.Text);
            DataContext.AMagicalDefenseToEdit = Int32.Parse(MagicalDefenseEditField.Text);
            DataContext.AEvasionToEdit = Int32.Parse(EvasionEditField.Text);
            // start the EDIT function
            DataContext.editArmor((Armor)ArmorList.SelectedItem);
        }

    }
}
