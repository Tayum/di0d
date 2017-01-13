using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Runtime.Serialization;
using System.Xml.Serialization;

namespace lab5
{
    public class Armor
    {
        // Fields
        private string name;
        private int physicalDefense;
        private int magicalDefense;
        private int evasion;


        // Properties
        // readonly
        [XmlElement]
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                if (!String.IsNullOrEmpty(value))
                {
                    name = value;
                }
            }
        }

        [XmlElement]
        public int PhysicalDefense
        {
            get
            {
                return physicalDefense;
            }
            set
            {
                if (value >= 0)
                {
                    physicalDefense = value;
                }
            }
        }

        [XmlElement]
        public int MagicalDefense
        {
            get
            {
                return magicalDefense;
            }
            set
            {
                if (value >= 0)
                {
                    magicalDefense = value;
                }
            }
        }

        [XmlElement]
        public int Evasion
        {
            get
            {
                return evasion;
            }
            set
            {
                if (value >= 0)
                {
                    evasion = value;
                }
            }
        }


        // Constructors
        public Armor()
        {
            name = "NoName";
            physicalDefense = 0;
            magicalDefense = 0;
            evasion = 0;
        }

        public Armor(string name)
            : this()
        {
            this.name = name;
        }

        public Armor(string name, int physicalDefense, int magicalDefense, int evasion)
            : this(name)
        {
            this.physicalDefense = physicalDefense;
            this.magicalDefense = magicalDefense;
            this.evasion = evasion;
        }

    }

    public class ArmorModel : ObservableCollection<Armor>
    {
        private static object _threadLock = new Object();
        private static ArmorModel current = null;

        public static ArmorModel Current
        {
            get
            {
                lock (_threadLock)
                    if (current == null)
                        current = new ArmorModel();

                return current;
            }
        }

        private ArmorModel()
        {
            Armor[] armorArr = XMLToData();

            foreach(Armor thyArmor in armorArr)
            {
                Add(thyArmor);
            }
        }   

        public int getArmorIndex(Armor armor)
        {
            return IndexOf(armor);
        }

        public void removeArmor(Armor armor)
        {
            Remove(armor);
        }

        public void addArmor(Armor armor, int index)
        {
            Insert(index, armor);
        }

        public void addArmor(string name, int physicalDefense, int magicalDefense, int evasion)
        {
            Armor armorPiece = new Armor(name, physicalDefense, magicalDefense, evasion);
            Add(armorPiece);
        }

        public void saveArmor()
        {
            DataToXML(Current.ToArray());
        }


        // Write program entries TO XML-file
        private static void DataToXML(Armor[] armorArr)
        {
            XmlSerializer serializerFromData = new XmlSerializer(armorArr.GetType());

            TextWriter writerToFile = new StreamWriter("..\\..\\Armor.xml");

            serializerFromData.Serialize(writerToFile, armorArr);

            // Close the writerToFile [StreamWriter]
            writerToFile.Close();
        }

        // Initialize program entries FROM XML-file
        private static Armor[] XMLToData()
        {
            XmlSerializer deserializerFromReader = new XmlSerializer(typeof(Armor[]));

            TextReader readerFromFile = new StreamReader("..\\..\\Armor.xml");

            object objectGotFromReader = deserializerFromReader.Deserialize(readerFromFile);
            Armor[] armorArr = (Armor[])objectGotFromReader;

            // Close the readerFromFile [StreamReader]
            readerFromFile.Close();

            return armorArr;
        }
    }
}
