Project: System for analysing athletes' performance
---
Only five competitions are processed here:
2000/2004/2008/2012/2016 Olympic Games
<br/>
<br/>
Quickstart Launch (no Replica Set):
1. Install ```MongoDB [>=3.2]```
2. Launch ```mongod``` on ```host='localhost'``` and ```port=27017```
3. Create database with name ```wa```
4. Change the link in ```wa_api.py```:
```
self.base_url = "https://secret.net"
```
to link, provided by World Archery.

5. Launch the application with this lines in ```main.py```:
```
fdb = FillDB()
fdb.fill_archers_collection()
fdb.fill_competitions_collection()
fdb.fill_qualifications_collection()
fdb.fill_qualifications_arrows_collection()
```
and wait for the application to gather information into database.
6. Re-Launch the application with this lines in ```main.py```:
```
menu = Menu()
menu.init_menu()
```
7. Enjoy!
---
