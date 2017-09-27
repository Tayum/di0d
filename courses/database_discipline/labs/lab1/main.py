from pckl import File
from accessory import Accessories
from computer import Computers
from menu import Menu


if __name__ == '__main__':
    file = File()
    accessories = file.load_accessories()
    computers = file.load_computers()
    if not accessories:
        accessories = Accessories()
    if not computers:
        computers = Computers()
    menu = Menu(accessories, computers)
    menu.run()
