import messages
import my_functions
import random

#funcke pro ziskani vstupu od uzivatele v prubehu hry
def ziskej_vstup():
    return str(input(messages.vstup))

#funkce pro vygenerovani zadani bez duplikace cislic
#a bez 0 na zacatku
def ziskej_zadani():
    while True:
        zadani = str(random.randint(1000,9999))
        if bez_duplikace(zadani):
            return zadani

#validace vstupu od uzivatele
#cyklus konci pouze spravnym zadanim
def vstup_validace():
    while True:
        vstup = my_functions.ziskej_vstup()
        if len(vstup) == 4 and vstup.isdigit() and vstup[0] != '0' and my_functions.bez_duplikace(vstup):
            return vstup
        else:
            print(messages.spatny_vstup)
            print(messages.oddelovac)
            continue

#bool funce pro zjisteni zda je cislo bez duplikace cislic
def bez_duplikace(cislo): 
    cisla_list = dej_cisla(cislo) 
    if len(cisla_list) == len(set(cisla_list)): 
        return True
    else: 
        return False
#funkce dostane cislo a vrati seznam jeho cislic
def dej_cisla(num): 
    return [int(i) for i in str(num)] 

#funkce ktera dostane uzivatelsky vstup a zadani
#vraci dvoumistny seznam
#prvni cislo je pocet buls
#druhe pocet cows
def bulls_and_cows(vstup, zadani):
    bulls_cows = [0,0]
    vstup_list = dej_cisla(vstup)
    zadani_list = dej_cisla(zadani)

    for x,y in zip(zadani_list, vstup_list):

        if y in zadani_list:

            if x == y:
                bulls_cows[0] += 1
            else:
                bulls_cows[1] += 1

    return bulls_cows

#funkce pro ukonceni programu po hre
def again_or_exit():
    if input() != "yes":

        exit()
