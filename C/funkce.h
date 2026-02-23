#ifndef TOMECEK_DATABAZE
#define TOMECEK_DATABAZE

// jmena moznych prikazu
static const char ERROR_USAGE[] = "Expected usage: ./database -i input.csv -o modified.csv\n";
static const char ERROR_OPENING[] = "Opening failed\n";
static const char INPUT_ERROR[] = "Unexpected input\n";
static const char MEMORY_ERROR[] = "Memory alloc error\n";
static const char INPUT_STRING[] = "-i";
static const char OUTPUT_STRING[] = "-o";
static const char COMMAND_ERROR[] = "Invalid command. Try it again\n";
static const char LINE_ERROR[] = "New line not found\n";
static const char SPACE_ERROR[] = "Space not fount\n";

// jmena moznych prikazu
static const char ADDROW[] = "addrow";
static const char ADDCOL[] = "addcol";
static const char AVERAGE[] = "average";
static const char MAX[] = "max";
static const char MIN[] = "min";
static const char SUM[] = "sum";
static const char EXIT[] = "exit"; 
static const char SHOW[] = "show"; 

int addrow (int radky, int spaces, int sloupce, const char* p_Konec_prikazu, char* p_Input, int delka_vstupu, const char* p_filename);

int addcol (int spaces, int radky, char* p_Input, int sloupce, const char* p_filename);

int max (int sloupce, int radky, char* p_Input, const char* p_filename);

int min (int sloupce, int radky, char* p_Input, const char* p_filename);

int sum (int sloupce, int radky, char* p_Input, const char* p_filename);

int average (int sloupce, int radky, char* p_Input, const char* p_filename);

int show (const char* p_filename);

int exit_out (const char* p_filename, const char* p_filename_output);

#endif