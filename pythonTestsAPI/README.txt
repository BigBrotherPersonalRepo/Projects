Dobrý den, 

jedná se o sadu automatických testů v jazyce python. Testovací data jsou uložena v souborech "config.json", "PostBarrelsData.json" a "PostMeasurementsData.json"
Testovací scripty jsou "DeleteBarrel.py", "GetBarrel.py", "GetBarrels.py", "GetMeasurements.py", "PostBarrels.py", "PostMeasurements.py".
Sdílená custom knihovna pro sadu je soubor "common.py". Program dale pouziva knihovnu requests a pytest. 
Vsechny tyto soubory musi byt ve stejnem repozitari. 
Program uklada vzdy posledni zaznam ze spusteneho skriptu do souboru "log.txt"
Scripty jsou spustitelne standartne prikazem "pytest -v -s {cesta k repozitari s testy}".
Kazdy skript obsahuje detailni testovaci scenar a komentare v kodu. (scenare primo v kodu nejsou standartni, nicmene pro lepsi citelnost jsem zvolil tento pristup)

Dekuji. S pozdravem,
Dominik Tomecek