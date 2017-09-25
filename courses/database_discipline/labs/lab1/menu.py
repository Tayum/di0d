from pckl import File
from accessory import Accessories
from computer import Computers


class Menu:

    def run(self):
        file = File()
        accessories = file.load_accessories()
        computers = file.load_computers()
        if not accessories:
            accessories = Accessories()
        if not computers:
            computers = Computers()

        self._print_menu()
        while True:
            choice = input("\n>")

            if choice == "0":
                self._print_menu()
            elif choice == "1":
                self._add_accessory(accessories)
            elif choice == "2":
                self._print_accessories(accessories)
            elif choice == "3":
                self._update_accessory(accessories)
            elif choice == "4":
                self._delete_accessory(accessories, computers)
            elif choice == "5":
                self._add_computer(computers)
            elif choice == "6":
                self._print_computers(computers)
            elif choice == "7":
                self._update_computer(computers)
            elif choice == "8":
                self._add_accessory_to_computer(computers, accessories)
            elif choice == "9":
                self._delete_accessory_from_computer(computers, accessories)
            elif choice == "10":
                self._delete_computer(computers)
            elif choice == "11":
                self._print_specific_computers(computers, accessories)
            elif choice == "q" or choice == "Q" or choice == "quit":
                file.save_accessories(accessories)
                file.save_computers(computers)
                break
            elif choice == "disc" or choice == "disconnect":
                break
            else:
                print("<invalid option>")

    def _print_menu(self):
        menu = ""
        menu_str = list()
        menu_str.append("Create new accessory")
        menu_str.append("Print all accessories")
        menu_str.append("Update an accessory by its <id>")
        menu_str.append("Delete an accessory by its <id>\n")
        menu_str.append("Create new computer")
        menu_str.append("Print all computers")
        menu_str.append("Update the name of the computer by its <id>")
        menu_str.append("Add an accessory by <id> to the computer by <id>")
        menu_str.append("Remove an accessory by <id> from the computer by <id>")
        menu_str.append("Delete the computer by its <id>\n")
        menu_str.append("Print all the specific computers\n" +
                        "'0' to print this menu\n" +
                        "'quit' to SAVE THE DATABASE CHANGES and quit\n" +
                        "'disc' to quit WITHOUT SAVING DATABASES")
        for i in range(0, menu_str.__len__(), 1):
            menu += "%d" % (i + 1) + ". " + menu_str[i] + "\n"
        print(menu)

    def _add_accessory(self, accessories):
        name = input("\nName: ")
        type = input("\nType: ")
        if name and type:
            rslt = accessories.add(name, type)
            if not rslt:
                print("\nSuch accessory already exists")
            else:
                print("\nThe new accessory is added:")
                print(rslt.__str__())
        else:
            print("\nThe fields cannot be <Empty>")

    def _print_accessories(self, accessories):
        print("\nThe list of all accessories:")
        print(accessories.__str__())

    def _update_accessory(self, accessories):
        try:
            id = int(input("\nID: "))
            acs = accessories.get_by_id(id)
            if acs is None:
                print("No accessory with such ID")
            else:
                print(acs.__str__())
                name = input("\nNew name: ")
                type = input("\nNew type: ")
                if name and type:
                    rslt = accessories.update(id, name, type)
                    print("\nThe accessory is updated:")
                    print(rslt.__str__())
                else:
                    print("\nThe fields cannot be <Empty>")
        except ValueError:
            print("The ID must be <Integer>")

    def _delete_accessory(self, accessories, computers):
        try:
            id = int(input("\nID: "))
            acs = accessories.delete(id)
            if acs is None:
                print("No accessory with such ID")
            else:
                computers.delete_all_accessories(acs.id)
                print("This accessory was deleted:")
                print(acs.__str__())
        except ValueError:
            print("The ID must be <Integer>")

    def _add_computer(self, computers):
        name = input("\nName: ")
        if name:
            rslt = computers.add(name)
            if not rslt:
                print("\nThe computer with such name already exists")
            else:
                print("\nThe new computer is added:")
                print(rslt.__str__())
        else:
            print("\nThe field cannot be <Empty>")

    def _print_computers(self, computers):
        print("\nThe list of all computers:")
        print(computers.__str__())

    def _update_computer(self, computers):
        try:
            id = int(input("\nID: "))
            comp = computers.get_by_id(id)
            if comp is None:
                print("No computer with such ID")
            else:
                print(comp.__str__())
                name = input("\nNew name: ")
                if name:
                    rslt = computers.update(id, name)
                    print("\nThe computer's name is updated:")
                    print(rslt.__str__())
                else:
                    print("\nThe name field cannot be <Empty>")
        except ValueError:
            print("The ID must be <Integer>")

    def _add_accessory_to_computer(self, computers, accessories):
        try:
            id_comp = int(input("\nID of computer to add an accessory to: "))
            id_acs = int(input("\nID of accessory to add to the computer: "))
            acs = accessories.get_by_id(id_acs)
            if not acs:
                print("\nNo accessory with such ID")
            else:
                rslt = computers.add_accessory(id_comp, id_acs)
                if not rslt:
                    print("\nNo computer with such ID")
                else:
                    print("The accessory with <%d> ID was added to the computer with <%d> ID" % (id_acs, id_comp))
        except ValueError:
            print("The ID(s) must be <Integer>")

    def _delete_accessory_from_computer(self, computers, accessories):
        try:
            id_comp = int(input("\nID of computer to remove an accessory from: "))
            id_acs = int(input("\nID of accessory to remove from the computer: "))
            acs = accessories.get_by_id(id_acs)
            if not acs:
                print("\nNo accessory with such ID")
            else:
                rslt = computers.delete_accessory(id_comp, id_acs)
                if isinstance(rslt, str):
                    print("\n" + rslt)
                else:
                    print("The accessory with <%d> ID was removed from the computer with <%d> ID" % (id_acs, id_comp))
        except ValueError:
            print("The ID(s) must be <Integer>")

    def _delete_computer(self, computers):
        try:
            id = int(input("\nID: "))
            comp = computers.delete(id)
            if comp is None:
                print("No computer with such ID")
            else:
                print("This computer was deleted:")
                print(comp.__str__())
        except ValueError:
            print("The ID must be <Integer>")

    def _print_specific_computers(self, computers, accessories):
        print("Task: to print the computers that has <Accessory> with <Type> 'Videocard'")
        comp_list = computers.get_by_task(accessories)
        if not comp_list:
            print("<No 'Videocard' accessory found OR no computers with 'Videocard' accessory found>")
        else:
            comps_to_print = ""
            for comp in comp_list:
                comps_to_print += comp.__str__()
            print(comps_to_print)
