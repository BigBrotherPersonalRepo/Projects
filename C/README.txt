Vitejte u testovani 1. semestralniho projektu předmětu UPR 1. ročník kombinovaneho studia.

pouzivate csv databazi.

spoustejte z prikazove radky vstupem typu:

$ ./databaze -i input.csv -o modified.csv

./databaze  // povinny argument
-i  // povinny argument
-o  // povinny argument
input.csv  // cesta ke vstupnimu souboru (musi existovat, jinak program ukonci chybova hlaska)
output.csv  // cesta k vystupnimu souboru (existovat nemusi, pokud neexistuje, program ho vytvori. Pokud existuje, program ho po ukonceni prepise)


pracujeme se souborem, jehoz obsah muze byt napr. nasledujici:

name,surname,points
jakub,cocka,51
adam,lezak,60
jarmila,konikova,30
lenka,laskoradova,95

program vas po spusteni vyzve k zadani prikazu (s argumenty, ktere prikaz potrebuje)

prikaz zadavejte jako prvni, potrebne argumenty pak oddelene mezerou od prikazu a od sebe navzajem

povolene prikazy pro pouziti

addrow (prida radek)
addcol (prida sloupec)
max (vrati maximum zvoleneho sloupce, pokud sloupec neni ciselny, vrati 0)
min (vrati minimum zvoleneho sloupce, pokud sloupec neni ciselny, vrati 0)
average (vrati prumernou hodnotu zvoleneho sloupce, pokud sloupec neni ciselny, vrati 0)
sum (vrati soucet hodnot zvoleneho sloupce)
show (ukaze aktualni obsah se kterym pracujete)
exit (ukonci program a aktualni obsah ulozi na adresu zadanou pri spusteni)

PRI ZADANI PRIKAZU SHOW A EXIT STACI ZADAT POUZE TYTO SLOVA, MEZERA ANI NIC PODOBNEHO ZA NIMI BYT NEMUSI!!!

maximální povolená délka prikazu s argumenty je 200 znaku
maximalni povolena delka hodnoty nebo slova na radku je 20 znaku


priklad pouziti:

$ ./databaze -i input.csv -o modified.csv
Soubor: input.csv, sloupce: 3, radky: 4
Zadejte prikaz: addrow jarek nohavica 78
Radek byl pridan.
Zadejte prikaz: average points
Prumer sloupce points: 68.2
Zadejte prikaz: sum points
Soucet sloupce points: 314 
Zadejte prikaz: addcol age 19 25 44 75
Sloupec age byl pridan.
Zadejte prikaz: average age
Prumer sloupce age: 40.75
Zadejte prikaz: sum age
Soucet sloupce age: 163
Zadejte prikaz: sum name
Soucet sloupce name: 0
Zadejte prikaz: exit
Ukladam soubor do modified.csv.