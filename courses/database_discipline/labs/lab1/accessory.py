class Accessory:
    def __init__(self, id, name, type):
        self.id = id
        self.name = name
        self.type = type

    def __str__(self):
        key = "\n"
        info = list()
        info.append("\tID: " + str(self.id))
        info.append("\tName: " + str(self.name))
        info.append("\tType: " + str(self.type) + "\n")
        return key.join(info)


class Accessories:
    def __init__(self):
        self.accessories = list()

    def _create_new_id(self):
        id_list = list()
        for acs in self.accessories:
            id_list.append(int(acs.id))
        if id_list.__len__() == 0:
            return 1
        else:
            return int(max(id_list) + 1)

    def add(self, name, type):
        for acs in self.accessories:
            if acs.name == name and acs.type == type:
                return False
        else:
            new_acs = Accessory(self._create_new_id(), name, type)
            self.accessories.append(new_acs)
            return new_acs

    def get_by_id(self, id):
        for acs in self.accessories:
            if acs.id == id:
                return acs
        else:
            return None

    def update(self, id, name, type):
        for acs in self.accessories:
            if acs.id == id:
                acs.name = name
                acs.type = type
                return acs
        else:
            return None

    def delete(self, id):
        for i in range(0, self.accessories.__len__(), 1):
            if self.accessories[i].id == id:
                return self.accessories.pop(i)
        else:
            return None

    def __str__(self):
        key = "\n"
        acs_list = list()
        if self.accessories.__len__() != 0:
            for acs in self.accessories:
                acs_list.append(acs.__str__())
            return key.join(acs_list)
        else:
            return "<Empty>"
