using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;
using System.Runtime.Serialization;
using System.Xml.Serialization;
using System.Runtime.Serialization.Json;

namespace lab3
{
    class Program
    {
        static void Main(string[] args)
        {
            // Bow sample
            Bow bow = new Bow(5, 10, 183, 606);
            Spear spear = new Spear(7, 11, 100, 205, 505);
            Sword sword = new Sword(4, 5, 50, 136, 200);
            Armor boots = new Armor(Armor.ARMOR_TYPE.PLATE, Armor.ARMOR_SLOT.BOOTS, 5, 3, 2);
            Armor gloves = new Armor(Armor.ARMOR_TYPE.PLATE, Armor.ARMOR_SLOT.GLOVES, 4, 2, 1);
            Armor body = new Armor(Armor.ARMOR_TYPE.PLATE, Armor.ARMOR_SLOT.BODY, 15, 5, 3);
            // Shoot() function error handler
            for (int i = 0; i < 2; i++)
            {
                Console.WriteLine("****************************\n");
                try
                {
                    bow.shoot();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Message: {0}", ex.Message);
                    Console.WriteLine("TargetSite: {0}", ex.TargetSite);
                    Console.WriteLine("InnerException: {0}", ex.InnerException);
                }
                Console.WriteLine("\n****************************\n");
            }

            // =====EVENTS=====
            Exposition exposition = Exposition.getInstance();
            exposition.newEquipment(spear);
            exposition.newEquipment(sword);
            // Anon function
            exposition.AddEquipment += delegate (Weapon equipment)
            {
                // <Func>
                Func<Weapon, double> calcAvgDmg = (thyWeapon) =>
                {
                    return ((double)(thyWeapon.LbDmg + thyWeapon.UbDmg)) / 2;
                };
                Console.WriteLine("[Anon/<Func>]: The new weapon was added. The AVG DMG of it is: " + calcAvgDmg(equipment));

            };
            // Lambada function
            exposition.AddEquipment += (Weapon equipment) =>
            {
                // <Action>
                Action<Weapon> printWeaponType = (thyWeapon) =>
                {
                    Console.WriteLine(" The type of the weapon is: " + thyWeapon.Type);
                };
                Console.Write("[Lambada/<Action>]: The new weapon was added. ");
                printWeaponType(equipment);
            };
            exposition.newEquipment(bow);
            Console.WriteLine("\n****************************\n");

            // The result of working with <List> for <Weapon>:
            exposition.printWeaponList();
            Console.WriteLine("\n****************************\n");

            // Creating the (static) array and showing the result of working with it
            Armor[] armorArr = new Armor[3];
            armorArr[0] = boots;
            armorArr[1] = gloves;
            armorArr[2] = body;
            foreach(Armor piece in armorArr)
            {
                Console.WriteLine("Equip SLOT for armor: " + piece.Slot);
            }
            Console.WriteLine("\n****************************\n");

            // The self-made Hero collection
            Hero hawkeye = new Hero("Hawkeye");
            Hero sniper = new Hero("Sniper");

            HeroCollection heroCollection = new HeroCollection();
            heroCollection.Add(hawkeye);
            heroCollection.Add(sniper);


            foreach (Hero thyHero in heroCollection)
            {
                Console.WriteLine("\nHero info:");
                thyHero.printStats();
            }
            Console.WriteLine("\nGet the Hero from this array by name [\"Hawkeye\"]:");
            Hero sampleHero = heroCollection["Hawkeye"];
            sampleHero.printStats();
            Console.WriteLine("\n****************************\n");

            // Sorting the elements
            Console.WriteLine("\nHero info [UNSORTED ARMOR]:");
            sampleHero.addArmor(gloves);
            sampleHero.addArmor(body);
            sampleHero.addArmor(boots);
            sampleHero.printStats();
            Console.WriteLine("\nHero info [SORTED (by Physical Defense) ARMOR]:");
            sampleHero.sortArmor();
            sampleHero.printStats();
            Console.WriteLine("\n****************************\n");

            // Combined ENUM (armor equip-slot):
            Armor.ARMOR_SLOT bodySlot = Armor.ARMOR_SLOT.BODY;
            Armor.ARMOR_SLOT legsSlot = Armor.ARMOR_SLOT.LEGS;
            Console.WriteLine(bodySlot + " + " + legsSlot + " = " + (bodySlot | legsSlot));
            Console.WriteLine("\n****************************\n");

            // Extension methods
            bow.calc_PhysicalAccuracy();
            Console.WriteLine("====================");
            bow.calc_PhysicalAccuracy(100);
            Console.WriteLine("====================");
            heroCollection.Clear("I dont need it anymore.");
            Console.WriteLine("Now the collection contains " + heroCollection.Count + " entries.");
            Console.WriteLine("\n****************************\n");

            Armor[] armorToSer = { body, gloves, boots };
            // Serialization [JSON]:
            DataToJSON(armorToSer);
            // Deserialization [JSON]:
            Armor[] armorFromDeserJSON = JSONToData();
            Console.WriteLine("SERIALIZED THESE THINGS FROM JSON:\n");
            for (int i = 0; i < armorFromDeserJSON.Length; i++)
            {
                armorFromDeserJSON[i].printStats();
                Console.WriteLine("");
            }
            Console.WriteLine("\n****************************\n");

            // Serialization [XML]:
            DataToXML(armorToSer);
            // Deserialization [XML]:
            Armor[] armorFromDeserXML = XMLToData();
            Console.WriteLine("SERIALIZED THESE THINGS FROM XML:\n");
            for (int i = 0; i < armorFromDeserXML.Length; i++)
            {
                armorFromDeserXML[i].printStats();
                Console.WriteLine("");
            }
            Console.WriteLine("\n****************************\n");


            // End of program
            Console.WriteLine("Press ANY KEY to proceed...");
            Console.ReadKey();
        }

        // Write program entries TO XML-file
        private static void DataToXML(Armor[] armorArr)
        {
            XmlSerializer serializerFromData = new XmlSerializer(armorArr.GetType());

            TextWriter writerToFile = new StreamWriter("..\\..\\ArmorSerialization\\Armor.xml");

            serializerFromData.Serialize(writerToFile, armorArr);

            // Close the writerToFile [StreamWriter]
            writerToFile.Close();
        }

        // Initialize program entries FROM XML-file
        private static Armor[] XMLToData()
        {
            XmlSerializer deserializerFromReader = new XmlSerializer(typeof(Armor[]));

            TextReader readerFromFile = new StreamReader("..\\..\\ArmorSerialization\\Armor.xml");

            object objectGotFromReader = deserializerFromReader.Deserialize(readerFromFile);
            Armor[] armorArr = (Armor[])objectGotFromReader;

            // Close the readerFromFile [StreamReader]
            readerFromFile.Close();

            return armorArr;
        }

        // Write program entries TO JSON-file
        private static string DataToJSON(Armor[] armorArr)
        {
            MemoryStream stream = new MemoryStream();
            DataContractJsonSerializer serializerFromData = new DataContractJsonSerializer(typeof(Armor[]));
            serializerFromData.WriteObject(stream, armorArr);

            stream.Position = 0;
            StreamReader readerFromStream = new StreamReader(stream);
            string jsonString = (readerFromStream.ReadToEnd());
            System.IO.File.WriteAllText("..\\..\\ArmorSerialization\\Armor.json", jsonString);
            return jsonString;
        }

        // Initialize program entries FROM JSON-file
        private static Armor[] JSONToData()
        {
            string jsonString = System.IO.File.ReadAllText(("..\\..\\ArmorSerialization\\Armor.json"));
            MemoryStream stream = new MemoryStream();
            StreamWriter writerToStream = new StreamWriter(stream);
            writerToStream.Write(jsonString);
            writerToStream.Flush();
            stream.Position = 0;

            DataContractJsonSerializer serializerFromStream = new DataContractJsonSerializer(typeof(Armor[]));
            Armor[] armorArr = (Armor[])serializerFromStream.ReadObject(stream);
            
            return armorArr;
        }
    }

}