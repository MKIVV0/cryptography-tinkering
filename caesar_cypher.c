/*
* Simple implementation of the Caesar Cypher.
* The goal of this program is to encrypt a given text and give it as a
* sample to another program, which task is to decrypt it, without prior 
* knowledge of the decryption key.
* @author Matteo Huang
* @version 1.0   
*/

#include <stdio.h>
#include <stdlib.h>

#define ENGLISH_ALPHABET_LETTERS 26
#define ITALIAN_ALPHABET_LETTERS 21
#define FIRST_ASCII_LETTER_CODE 97  // lowercase a
#define LAST_ASCI_LETTER_CODE 122   // lowercase z

void read_file(char* file_name);

int main(int argc, char **argv) {
    int en_letter_freqs[ENGLISH_ALPHABET_LETTERS]; 
    
    //printf("Hello, %s", argv[1]);
    //read_file(argv[1]);
    printf("%c and %c", FIRST_ASCII_LETTER_CODE, LAST_ASCI_LETTER_CODE);
    return 0;
}

/*
+ This method reads the encrypted file given in input.
*/
void read_file(char* file_name) {
    FILE *ifp;
    char a[100];
    
    ifp = fopen(file_name, "r");
    fscanf(ifp, "%s", a);
    fread(a, sizeof(char), 15, ifp);
}

