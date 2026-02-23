"""
projekt_2.py: druhý projekt do Engeto Online Python Akademie

author: Pavlína Kummerova
email: paja.kummerova@seznam.cz
"""

import my_functions
import messages

#pocet kol
kola = 0

#cyklus opakujicich se her
#pokazde nove zadani
while True:

    #pozdrav + vytvoreni zadani
    print(messages.pozdrav)
    zadani = my_functions.ziskej_zadani()

    #cyklus opakujicich se kol hry
    #kazda iterace zvysuje pocet kol o 1
    #cyklus ukoncuje pouze spravna odpoved
    while True:

        kola += 1
        vstup = my_functions.vstup_validace()
        vysledek = my_functions.bulls_and_cows(vstup, zadani)
        
        #vetev pro spravnou odpoved
        if vysledek[0] == 4:
            print(f"{messages.konec1} {kola} {messages.konec2}")
            print(messages.oddelovac)
            print(messages.konec3)
            print(messages.oddelovac)
            print(messages.again_or_exit)

            #moznost ukoncit program po uspesnem kole
            #pokud neukonci zacina nova hra
            my_functions.again_or_exit()

            #vynulovani poctu kol
            kola = 0
            break
        
        #vetev pro spatnou odpoved
        #vrati bulls and cows a nasleduje dalsi kolo
        else:

            #rozhodnuti bull/bulls a cow/cows
            if vysledek[0] == 1:
                b = messages.bull
            else:
                b = messages.bulls

            if vysledek[1] == 1:
                c = messages.cow
            else:
                c = messages.cows

            #vypis vysledku
            print(f"{vysledek[0]} {b}, {vysledek[1]} {c}")
            print(messages.oddelovac)