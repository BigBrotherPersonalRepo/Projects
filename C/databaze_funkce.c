#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <funkce.h>
#include <stddef.h>


int addrow (int radky, int spaces, int sloupce, const char* p_Konec_prikazu, char* p_Input, int delka_vstupu, const char* p_filename) {
    if (spaces != sloupce){
            fprintf(stderr, INPUT_ERROR);
            return 1;
        }  

        // zmen mezery ve vstupu na ","
        for (int i = (p_Konec_prikazu - p_Input + 1); i < delka_vstupu; i++){
            if (p_Input[i] == ' '){
                p_Input[i] = ',';
            }
            else {
                continue; 
            }
        } 

        // vypis na konec souboru radek
        FILE* p_file = fopen(p_filename, "a");
        if (p_file == NULL) {
            fprintf(stderr, "%s", ERROR_OPENING);
            return 1;
        }

        fprintf(p_file, "%s", p_Konec_prikazu + 1);
        radky++;
        fclose(p_file);
        fprintf(stdout, "Řádek byl přidán.\n");
        return 0;
}

int addcol (int spaces, int radky, char* p_Input, int sloupce, const char* p_filename) {
    if (spaces != radky){
        fprintf(stderr, INPUT_ERROR);
        return 1;
    } 

    // otevreni souboru + kontrola 
    FILE* p_file = fopen(p_filename, "r+");
    if (p_file == NULL) {
        fprintf(stderr, "%s", ERROR_OPENING);
        return 1;
    }

    // zjisteni velikosti souboru            
    fseek(p_file, 0, SEEK_END);
    long int size = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);


    // alokace pole pro obsah souboru
    char* content = (char*) malloc (size * (sizeof(char)) + 1 );
    if (content == NULL){
        fprintf(stderr, "%s", MEMORY_ERROR);
        return 1;
    }

    char* p_Content = content;

    // prepis obsahu souboru do pole + zavreni souboru
    fread (p_Content, sizeof(char), size, p_file);
    fclose(p_file);

    // otebreni souboru pro zapis
    p_file = fopen(p_filename, "w");
    if (p_file == NULL) {
        fprintf(stderr, "%s", ERROR_OPENING);
        return 1;
    }

    char* p_Content_start = content;  
    char* p_Content_end = content; // definice pointeru pro ohraniceni casti obsahu souboru
    char* p_Input_start = (p_Input + sizeof(ADDCOL));
    char* p_Input_end = (p_Input + sizeof(ADDCOL));  // definice pointeru pro ohraniceni casti vstupu

    // cyklus pro vlozeni noveho sloupce do pole s obsahem
    for(int i = 0; i < radky; i++){

        // nalezeni konce radku v dosavadnim obsahu
        p_Content_end = strstr(p_Content_start, "\n");
        if (p_Content_end == NULL){ // kontrola
            fprintf(stderr, LINE_ERROR);
            break;
        }

        // nalezeni konce nove hodnoty daneho radku ve vstupu (pokud jsme u posledniho radku, poiter se musi zastavit na "\n")
        if (i == (radky - 1)){ 
            p_Input_end = strstr(p_Input_start, "\n");
            if (p_Content_end == NULL){
                fprintf(stderr, "%s", SPACE_ERROR);
                break; // kontrola
            }
        }
        // nalezeni konce nove hodnoty daneho radku ve vstupu (pokud nejsme na poslednim, hledame mezeru, protoze hodnoty vstupu jsou oddeleny mezerami)
        else{  
            p_Input_end = strstr(p_Input_start, " ");
            if (p_Content_end == NULL){
                fprintf(stderr, SPACE_ERROR);
                break; // kontrola
            }
        }

        fprintf(p_file, "%.*s,",(int)(p_Content_end - p_Content_start), p_Content_start); // zapis dosavadniho radku do souboru pomoci pointeru na zacatek a konec radku
        fprintf(p_file, "%.*s\n",(int)(p_Input_end - p_Input_start), p_Input_start);  // zapis nevo hodnoty daneho radku pomoci pointeru

        // posunuti pointeru
        p_Content_start = p_Content_end + 1;
        p_Input_start = p_Input_end + 1;

    }
    sloupce++;  // hodnota poctu sloupcu +1
    free(p_Content);
    fclose(p_file);  // uvolneni pameti a zavreni souboru
    fprintf(stdout, "Sloupec byl přidán.\n");
    return 0;
}


int max (int sloupce, int radky, char* p_Input, const char* p_filename) {
    
    int maximum = 0;
    int position = 0;
    char col_name[20] = {};  // prostor pro jmeno sloupce

    // otevreni souboru a kontrola
    FILE* p_file = fopen(p_filename, "r+");
    if (p_file == NULL) {
        fprintf(stderr, "%s", ERROR_OPENING);
        return 1;
    }

    // definice velikosti obsahu souboru
    fseek(p_file, 0, SEEK_END);
    long int size = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);

    // pole pro obsah souboru a kontrola
    char* content = (char*) malloc (size * (sizeof(char)) + 1 );
    if (content == NULL){
        fprintf(stderr, "%s", MEMORY_ERROR);
        return 1;
    }
    char* p_Content = content;

    // prepis obsahu souboru do pole
    fread (p_Content, sizeof(char), size, p_file);
    fclose(p_file);

    char* p_Input_start = (p_Input + sizeof(MAX));
    char* p_Input_end = strstr(p_Input_start, "\n");
    char* p_Content_start = content;
    char* p_Content_end = strstr(p_Content_start, ",");

    // cyklus pro urceni nazvu sloupce pro vypocet maxima
    for (int i = 0; i < (p_Input_end - p_Input_start); i++){
        col_name[i] = *(p_Input_start + i);
    }

    // cyklus pro urceni, kolikaty radek v poradi je sloupec pro vypocet maxima
    for (int i = 0; i < sloupce; i++){

        // porovnani jmena sloupce v obsahu a ve stringu row_name (jmeno hledaneho radku)
        if (strncmp(p_Content_start, col_name, strlen(col_name)) == 0){
            position = i + 1;
            break;
        }
        p_Content_start = p_Content_end + 1; // posunuti pointeru pro dalsi cyklus hledani
        if (i == radky - 1){  // pokud jsme v poslednim cyklu, konec porovnavaneho stringu v obsahu definuje konec radku
            p_Content_end = strstr(p_Content_start, "\n"); 
        }
        else{  // v kazdem jinem cyklu je to ","
            p_Content_end = strstr(p_Content_start, ",");
        }
    }

    // elegantni kontrola, zda se zadane jmeno sloupce vyskytuje ve vyctu jmen sloupcu souboru
    if (position == 0){
        fprintf(stderr, INPUT_ERROR);
        free(p_Content);
        return 1;
    }

    p_Content_start = strstr(p_Content, "\n") + 1; // nastaveni pointeru na zacatek druheho radku v souboru (1. radek kde se vyskytuji hodnoty sloupcu)
    p_Content_end = strstr(p_Content_start, "\n"); // nastaveni pointeru na konec 2. radku

    // cyklus pro prochazeni hodnot sloupce
    for(int i = 0; i < radky; i++){

        int actual_position = 0;  // promenna udavajici, v jakem sloupci se nachazime
        char cislice[20] = {};  // misto pro zapis cisla, ale datoveho typu str
        int wrote = 0;  // promena udavajici, kolik cisli bylo jiz z hodnoty sloupce vypsanych

        // podminka, ktera v cyklu pocita sloupce. pri dosazeni znaku "," ktery oddeluje sloupce se zvysi o 1
        for(int p = 0; p < (p_Content_end-p_Content_start); p++){
            if (*(p_Content_start + p) == ',' ){
                actual_position++;
                continue;
            }

            // podminka, ktera kontroluje, zda jsme ve spravnem sloupci
            if ((actual_position + 1) == position && *(p_Content_start + p) != ','){
                cislice[wrote] = *(p_Content_start + p); // zapis cislice do prostoru pro hodnotu sloupce typu str
                wrote++;  // zvyseni promenne udavajici pocet zapsanych cislic o 1
            }
        }  // nyni mame string hodnoty sloupce

        // prevod stringu s cislem ze sloupce na jeho ciselnou hodnotu
        int cislo = atoi(cislice);

        // porovnani, zda je cislo vetsi nez dosavadni maxiumum
        if (cislo > maximum){
            maximum = cislo;
        }

        // posunuti pointeru na dalsi radek pro vykonani dalsi iterace cyklu (pokud jsme na poslednim radku, pointery se posouvat nemusi)
        if (i != radky - 1 && i != radky - 2){
            p_Content_start = strstr(p_Content_end, "\n") + 1;
            p_Content_end = strstr(p_Content_start, "\n");
        }
        
        // zajimava vec, strstr neumi hledat "\0" takze tu musi byt podminka, ze pokud jsme na predposlednim radku, nastavime pointer nakonec rucne
        if (i == radky - 2){
            p_Content_start = strstr(p_Content_end, "\n") + 1;
            p_Content_end = p_Content + size;
        }
    }

    fprintf(stdout, "%d\n", maximum); // tisk maxima
    free(p_Content);  // uvolneni pameti
    return 0;
}

int min (int sloupce, int radky, char* p_Input, const char* p_filename) {
    
    int minimum = 0;
    int position = 0;
    char col_name[20] = {};

    FILE* p_file = fopen(p_filename, "r+");
    if (p_file == NULL) {
        fprintf(stderr, "%s", ERROR_OPENING);
        return 1;
    }
    
    fseek(p_file, 0, SEEK_END);
    long int size = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);

    char* content = (char*) malloc (size * (sizeof(char)) + 1 );
    if (content == NULL){
        fprintf(stderr, "%s", MEMORY_ERROR);
        return 1;
    }
    char* p_Content = content;

    fread (p_Content, sizeof(char), size, p_file);
    fclose(p_file);

    char* p_Input_start = (p_Input + sizeof(MIN));
    char* p_Input_end = strstr(p_Input_start, "\n");
    char* p_Content_start = content;
    char* p_Content_end = strstr(p_Content_start, ",");

    for (int i = 0; i < (p_Input_end - p_Input_start); i++){  // stejne jako u maxima
        col_name[i] = *(p_Input_start + i);
    }

    for (int i = 0; i < sloupce; i++){  // stejne jako u maxima

        if (strncmp(p_Content_start, col_name, strlen(col_name)) == 0){
            position = i + 1;
            break;
        }
        p_Content_start = p_Content_end + 1;
        if (i == radky - 1){
            p_Content_end = strstr(p_Content_start, "\n"); 
        }
        else{
            p_Content_end = strstr(p_Content_start, ",");
        }
    }

    if (position == 0){
        fprintf(stderr, INPUT_ERROR);
        free(p_Content);
        return 1;
    }

    p_Content_start = strstr(p_Content, "\n") + 1;  // stejne jako u maxima
    p_Content_end = strstr(p_Content_start, "\n");

    for(int i = 0; i < radky; i++){

        int actual_position = 0;
        char cislice[20] = {};
        int wrote = 0;

        for(int p = 0; p < (p_Content_end-p_Content_start); p++){  // stejne jako u maxima
            if (*(p_Content_start + p) == ',' ){
                actual_position++;
                continue;
            }
            if ((actual_position + 1) == position && *(p_Content_start + p) != ','){
                cislice[wrote] = *(p_Content_start + p);
                wrote++;
            }
        }
        int cislo = atoi(cislice);

        // pouze zde se lisi minimum od maxima. pokud jsme v prvni iteraci cyklu, cislo je vychozi maximum
        if (i == 0){
            minimum = cislo;
            continue;
        }

        // pro ostatni iterace porovnavame, zda je cislo mensi nez dosavadni maximum
        if (cislo < minimum){
            minimum = cislo;
        }

        // stejne jako u maxima
        if (i != radky - 1 && i != radky - 2){
            p_Content_start = strstr(p_Content_end, "\n") + 1;
            p_Content_end = strstr(p_Content_start, "\n");
        }
        if (i == radky - 2){
            p_Content_start = strstr(p_Content_end, "\n") + 1;
            p_Content_end = content + size;
        }
    }

    fprintf(stdout, "%d\n", minimum);
    free(p_Content);
    return 0;
}

int sum (int sloupce, int radky, char* p_Input, const char* p_filename) {

    int sum = 0;
    int position = 0;
    char col_name[20] = {};

    FILE* p_file = fopen(p_filename, "r+");
    if (p_file == NULL) {
        fprintf(stderr, "%s", ERROR_OPENING);
        return 1;
    }

    fseek(p_file, 0, SEEK_END);
    long int size = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);

    char* content = (char*) malloc (size * (sizeof(char)) + 1 );
    if (content == NULL){
        fprintf(stderr, "%s", MEMORY_ERROR);
        return 1;
    }
    char* p_Content = content;

    fread (p_Content, sizeof(char), size, p_file);
    fclose(p_file);

    char* p_Input_start = (p_Input + sizeof(SUM));
    char* p_Input_end = strstr(p_Input_start, "\n");
    char* p_Content_start = content;
    char* p_Content_end = strstr(p_Content_start, ",");

    for (int i = 0; i < (p_Input_end - p_Input_start); i++){  // stejne jako maximum
        col_name[i] = *(p_Input_start + i);
    }

    for (int i = 0; i < sloupce; i++){  // stejne jako maximum

        if (strncmp(p_Content_start, col_name, strlen(col_name)) == 0){  // stejne jako maximum
            position = i + 1;
            break;
        }
        p_Content_start = p_Content_end + 1;
        if (i == radky - 1){
            p_Content_end = strstr(p_Content_start, "\n"); 
        }
        else{
            p_Content_end = strstr(p_Content_start, ",");
        }
    }

    if (position == 0){  // stejne jako maximum
        fprintf(stderr, INPUT_ERROR);
        free(p_Content);
        return 1;
    }

    p_Content_start = strstr(p_Content, "\n") + 1;
    p_Content_end = strstr(p_Content_start, "\n");

    for(int i = 0; i < radky; i++){  // stejne jako maximum

        int actual_position = 0;
        char cislice[20] = {};
        int wrote = 0;

        for(int p = 0; p < (p_Content_end-p_Content_start); p++){  // stejne jako maximum
            if (*(p_Content_start + p) == ',' ){
                actual_position++;
                continue;
            }
            if ((actual_position + 1) == position && *(p_Content_start + p) != ','){
                cislice[wrote] = *(p_Content_start + p);
                wrote++;
            }
        }
        int cislo = atoi(cislice);

        // ***** zde jest rozdil oproti maximu *****
        sum = sum + cislo;

        if (i != radky - 1 && i != radky - 2){  // stejne jako maximum
            p_Content_start = strstr(p_Content_end, "\n") + 1;
            p_Content_end = strstr(p_Content_start, "\n");
        }
        if (i == radky - 2){
            p_Content_start = strstr(p_Content_end, "\n") + 1;
            p_Content_end = p_Content + size;
        }
    }

    fprintf(stdout, "%d\n", sum);
    free(p_Content);
    return 0;
}

int average (int sloupce, int radky, char* p_Input, const char* p_filename) {
    
    int sum = 0;
    double average = 0;  // promenna pro vysledny vypocet
    int position = 0;
    char row_name[20] = {};

    FILE* p_file = fopen(p_filename, "r+");
    if (p_file == NULL) {
        fprintf(stderr, "%s", ERROR_OPENING);
        return 1;
    }

    fseek(p_file, 0, SEEK_END);
    long int size = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);

    char* content = (char*) malloc (size * (sizeof(char)) + 1 );
    if (content == NULL){
        fprintf(stderr, "%s", MEMORY_ERROR);
        return 1;
    }
    char* p_Content = content;

    fread (p_Content, sizeof(char), size, p_file);
    fclose(p_file);

    char* p_Input_start = (p_Input + sizeof(AVERAGE));
    char* p_Input_end = strstr(p_Input_start, "\n");
    char* p_Content_start = content;
    char* p_Content_end = strstr(p_Content_start, ",");

    for (int i = 0; i < (p_Input_end - p_Input_start); i++){  // stejne jako maximum
        row_name[i] = *(p_Input_start + i);
    }

    for (int i = 0; i < sloupce; i++){  // stejne jako maximum

        if (strncmp(p_Content_start, row_name, strlen(row_name)) == 0){  // stejne jako maximum
            position = i + 1;
            break;
        }
        p_Content_start = p_Content_end + 1;
        if (i == radky - 1){
            p_Content_end = strstr(p_Content_start, "\n"); 
        }
        else{
            p_Content_end = strstr(p_Content_start, ",");
        }
    }

    if (position == 0){  // stejne jako maximum
        fprintf(stderr, INPUT_ERROR);
        free(p_Content);
        return 1;
    }

    p_Content_start = strstr(p_Content, "\n") + 1;
    p_Content_end = strstr(p_Content_start, "\n");

    for(int i = 0; i < radky; i++){  // stejne jako maximum

        int actual_position = 0;
        char cislice[20] = {};
        int wrote = 0;

        for(int p = 0; p < (p_Content_end-p_Content_start); p++){  // stejne jako maximum
            if (*(p_Content_start + p) == ',' ){
                actual_position++;
                continue;
            }
            if ((actual_position + 1) == position && *(p_Content_start + p) != ','){
                cislice[wrote] = *(p_Content_start + p);
                wrote++;
            }
        }
        int cislo = atoi(cislice);

        // stejne jako u sumy, pro vypocet maxima potrebujeme soucet vsech hodnot
        sum = sum + cislo;

        if (i != radky - 1 && i != radky - 2){
            p_Content_start = strstr(p_Content_end, "\n") + 1;
            p_Content_end = strstr(p_Content_start, "\n");
        }
        if (i == radky - 2){
            p_Content_start = strstr(p_Content_end, "\n") + 1;
            p_Content_end = p_Content + size;
        }
    }

    // prumer vypocitame klasickym vzorcem, staci to jen natvrdo pretypovat
    average = (double) sum/(radky - 1);

    fprintf(stdout, "%.2f\n", average);  // %.2f znamená na 2 desetinna mista
    free(p_Content);
    return 0;
}

int show (const char* p_filename) {
    
    fprintf(stdout, "\n");

    FILE* p_file = fopen(p_filename, "r+");
    if (p_file == NULL) {
        fprintf(stderr, "%s", ERROR_OPENING);
        return 1;
    }

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
    fprintf (stdout, "\nSoubor: %s, Počet řádků: %d, Počet sloupců %d\n", p_filename, radky, sloupce);

    return 0;
}

int exit_out (const char* p_filename, const char* p_filename_output) {
    
    // otevreni souboru + kontrola 
    FILE* p_file = fopen(p_filename, "r+");
    if (p_file == NULL) {
        fprintf(stderr, "%s", ERROR_OPENING);
        return 1;
    }

    // zjisteni velikosti souboru            
    fseek(p_file, 0, SEEK_END);
    long int size = ftell(p_file);
    fseek(p_file, 0, SEEK_SET);


    // alokace pole pro obsah souboru
    char* content = (char*) malloc (size * (sizeof(char)) + 1 );
    if (content == NULL){
        fprintf(stderr, "%s", MEMORY_ERROR);
        return 1;
    }

    char* p_Content = content;

    // prepis obsahu souboru do pole + zavreni souboru
    fread (p_Content, sizeof(char), size, p_file);
    fclose(p_file);

    FILE* p_file_output = fopen(p_filename_output, "w");
    if (p_file == NULL) {
        fprintf(stderr, "%s", ERROR_OPENING);
        return 1;
    }

    // prepis pole s obsahem modifikovaneho databazoveho souboru do vystupniho souboru
    fprintf(p_file_output, "%.*s", (int) size, p_Content);
    fclose(p_file_output);
    free(content);

    fprintf(stdout, "Soubor se ukládá na zadanou adresu.\n");

    return 0;
}