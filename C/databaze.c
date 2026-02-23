#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <funkce.h>

// kotrola, zda je prikazu pri spusteni 5, jak ma byt
int main (int argc, char* argv[]) {
    if (argc != 5){
        fprintf(stderr, "%s", ERROR_USAGE);
        return 1;
    }

    // vytiskni prikazy
    for (int i = 0; i < argc; i++){
        fprintf(stdout, "argument %d: %s\n", i+1, argv[i]);
    }

    fprintf(stdout, "\n");

    // kontrola, zda prikaz 2 a 4 je: "-i" a "-o" jak ma byt
    if ( (strncmp(INPUT_STRING, argv[1], sizeof(INPUT_STRING)) != 0 ) || (strncmp(OUTPUT_STRING, argv[3], sizeof(OUTPUT_STRING))  != 0 ) )  {
        fprintf(stderr, "%s", ERROR_USAGE);
        return 1;
    }

    // otevri vstupni soubor pro cteni
    FILE* p_file = fopen(argv[2], "r");
    if (p_file == NULL) {
        fprintf(stderr, "%s", ERROR_OPENING);
        return 1;
    }

    // vytiskni na standartni vystup obsah souboru, Jmeno souboru, Pocet radku, Pocet sloupcu
    int radky = 0;
    int sloupce = 1;
    char c;
    do {
        c = fgetc (p_file);
        fprintf(stdout, "%c", c);
        if (c == '\n'){
            ++radky;
        }
        if (c == ',' && radky == 1){
            ++sloupce;
        }
    } while (c != EOF);
    
    fclose(p_file);
    fprintf (stdout, "\nSoubor: %s, Počet řádků: %d, Počet sloupců %d\n", argv[2], radky, sloupce);

    int return_value = 0;

    while(1){
        fprintf (stdout, "Zadejte příkaz: ");

        char input[201];   // prostor pro prikaz, max delka 200
        int spaces = 0;
        char* p_Input = input;

        // nacti prikaz, pokud je prikaz NULL, ukonci s chybou
        if (fgets(p_Input, sizeof(input), stdin) == NULL){
            fprintf(stderr, "%s", INPUT_ERROR);
            return 1;
        }

        int delka_vstupu = strnlen(p_Input, sizeof(input));

        // kontrola delky vstupu
        if (delka_vstupu > 200){
            fprintf(stderr, "%s", INPUT_ERROR);
            return 1;
        }

        // definovani poctu mezer ve vstupu (bude dulezite pro kontrolu korektnosti vstupu u funkci)
        for (int i = 0; i < delka_vstupu; i++){
            if (input[i] == ' '){
                spaces++;
                continue;
            }
            else{
                continue;
            }
        }

        // definice konce prikazu
        char* p_Konec_prikazu = strstr(p_Input, " ");  // mezera za prikazem v inputu udava oddeleni prikazu od argumentu vstupu
        if (p_Konec_prikazu == NULL){  // pokud davame prikaz SHOW nebo EXIT, konec prikazu je konec input stringu
            p_Konec_prikazu = p_Input + delka_vstupu - 1;
        }
        if (p_Konec_prikazu == NULL) {  // kontrola, zda input neni NULL. nevim jestli to muze nekdy nastat, ale pro jistotu...
            fprintf(stderr, "%s", INPUT_ERROR);
            return 1;
        }

        // kontrola korektnosti vstupu (poctem argumentu)
        if (strncmp(ADDROW, p_Input, p_Konec_prikazu - p_Input) == 0){
            return_value = addrow(radky, spaces, sloupce, p_Konec_prikazu, p_Input, delka_vstupu, argv[2]);
            if (return_value != 0){
                return 1;
            }
            continue;
        }

        // kontrola korektnosti vstupu (poctem argumentu)
        if (strncmp(ADDCOL, p_Input, p_Konec_prikazu - p_Input) == 0){
            return_value = addcol(spaces, radky, p_Input, sloupce, argv[2]);
            if (return_value != 0){
                return 1;
            }
            continue;
        }

        // funkce pro maximum
        if (strncmp(MAX, p_Input, p_Konec_prikazu - p_Input) == 0){
            return_value = max(sloupce, radky, p_Input, argv[2]);
            if (return_value != 0){
                return 1;
            }
            continue;
        }

        // minimum funguje stejne jako maximum, jen je zde jiny vypocet hodnoty
        if (strncmp(MIN, p_Input, p_Konec_prikazu - p_Input) == 0){
            return_value = min(sloupce, radky, p_Input, argv[2]);
            if (return_value != 0){
                return 1;
            }
            continue;
        }

        // suma je v podstate uplne stejna jako maximu, jen se hodnoty proste scitaji :-)
        if (strncmp(SUM, p_Input, p_Konec_prikazu - p_Input) == 0){
            return_value = sum(sloupce, radky, p_Input, argv[2]);
            if (return_value != 0){
                return 1;
            }
            continue;
        }

        // average opet velmi podobny maximu, pouze je zde potreba vyjadrit vypocet jako typ (double)
        if (strncmp(AVERAGE, p_Input, p_Konec_prikazu - p_Input) == 0){
            return_value = average(sloupce, radky, p_Input, argv[2]);
            if (return_value != 0){
                return 1;
            }
            continue;
        }

        // show nam vypise aktualni obsah souboru se kterym pracujeme. Po prikazu show musi byt mezera, protoze pointer p_Konec_prikazu hleda mezeru
        if (strncmp(SHOW, p_Input, p_Konec_prikazu - p_Input) == 0){
            return_value = show(argv[2]);
            if (return_value != 0){
                return 1;
            }
            continue;
        }

        // exit ukonci praci s databazi a ulozi soubor na zadanou cestu.
        if (strncmp(EXIT, p_Input, p_Konec_prikazu - p_Input) == 0){
            return_value = exit_out(argv[2], argv[4]);
            if (return_value != 0){
                return 1;
            }
            break;
        }

        else {
            fprintf(stderr, INPUT_ERROR);
            return 1;
        }

    return 0;
    }
}