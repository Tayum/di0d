import pickle


class File:
    def load_computers(self):
        try:
            with open('computers.db', 'rb') as f:
                return pickle.load(f)
        except EOFError:
            return False

    def load_accessories(self):
        try:
            with open('accessories.db', 'rb') as f:
                return pickle.load(f)
        except EOFError:
            return False

    def save_computers(self, comps):
        with open('computers.db', 'wb') as f:
            pickle.dump(comps, f)

    def save_accessories(self, access):
        with open('accessories.db', 'wb') as f:
            pickle.dump(access, f)