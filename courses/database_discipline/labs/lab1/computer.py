from pckl import File


class Computer:
    def __init__(self, id, name):
        self.id = id
        self.name = name
        self.accessories = list()

    def __str__(self):
        key = "\n"
        info = list()
        info.append("ID: " + str(self.id))
        info.append("Name:" + str(self.name))
        info.append("Accessories:")
        file = File()
        accessories_class_obj = file.load_accessories()
        if self.accessories.__len__() == 0:
            info.append("\t<Empty>\n")
        else:
            for id_acs in self.accessories:
                for db_acs in accessories_class_obj.accessories:
                    if id_acs == int(db_acs.id):
                        info.append(db_acs.__str__())
                        break

        return key.join(info)

class Computers:
    def __init__(self):
        self.computers = list()

    def _create_new_id(self):
        id_list = list()
        for comp in self.computers:
            id_list.append(int(comp.id))
        if id_list.__len__() == 0:
            return 1
        else:
            return int(max(id_list) + 1)

    def add(self, name):
        for comp in self.computers:
            if comp.name == name:
                return False
        else:
            new_comp = Computer(self._create_new_id(), name)
            self.computers.append(new_comp)
            return new_comp

    def get_by_id(self, id):
        for comp in self.computers:
            if comp.id == id:
                return comp
        else:
            return None

    def update(self, id, name):
        for comp in self.computers:
            if comp.id == id:
                comp.name = name
                return comp
        else:
            return None

    def add_accessory(self, id_comp, id_acs):
        for comp in self.computers:
            if comp.id == id_comp:
                comp.accessories.append(id_acs)
                return id_acs
        else:
            return None

    def delete_accessory(self, id_comp, id_acs):
        for comp in self.computers:
            if comp.id == id_comp:
                try:
                    return comp.accessories.remove(id_acs)
                except ValueError:
                    return "No accessory with such ID in this computer"
        else:
            return "No computer with such ID"

    def delete_all_accessories(self, id_acs_to_remove):
        for comp in self.computers:
            comp.accessories = [acs for acs in comp.accessories if acs != id_acs_to_remove]

    def delete(self, id):
        for i in range(0, self.computers.__len__(), 1):
            if self.computers[i].id == id:
                return self.computers.pop(i)
        else:
            return None

    def get_by_task(self, accessories_class_obj):
        acs_id_list = list()
        for acs in accessories_class_obj.accessories:
            if str(acs.type).lower() == "videocard":
                acs_id_list.append(acs.id)
        if acs_id_list.__len__() == 0:
            return None
        else:
            comp_list = list()
            for comp in self.computers:
                for acs_id in acs_id_list:
                    if acs_id in comp.accessories:
                        comp_list.append(comp)
                        break
            if comp_list.__len__() == 0:
                return None
            else:
                return comp_list

    def __str__(self):
        key = "\n"
        comp_list = list()
        if self.computers.__len__() != 0:
            for comp in self.computers:
                comp_list.append(comp.__str__())
            return key.join(comp_list)
        else:
            return "<Empty>"
