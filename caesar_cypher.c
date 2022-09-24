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
void write_file(char *ch);

int main(int argc, char **argv) {
    int en_letter_freqs[ENGLISH_ALPHABET_LETTERS]; 
    
    //printf("Hello, %s", argv[1]);
    //read_file(argv[1]);
    write_file("BELLAAAAAAAAAAAAAAA\0");
    return 0;
}

/*
* This function reads the given file in input.
*/
void read_file(char* file_name) {
    FILE *file_pointer;
    char ch;
    
    // Opens the file in reading mode
    file_pointer = fopen(file_name, "r");

    printf("%s CONTENT:\n", file_name);
    if (file_pointer == NULL) {
        fprintf(stderr,"File not available.\n");
        exit(EXIT_FAILURE);
    }

    /* Prints the file content character by character, until 
    * until the end of file character is encountered.
    */
    while (ch != EOF){
        ch = fgetc(file_pointer);
        printf("%c", ch);
    }
    printf("\n");
    fflush(file_pointer);
    fclose(file_pointer);
}

// This function writes to file some given content.
void write_file(char *ch) {
    FILE *file_pointer;
    file_pointer = fopen("encrypted.txt", "w");

    printf("\nWRITING CONTENT ON THE NEW FILE...\n");
    if (file_pointer == NULL) {
        fprintf(stderr, "\nError while creating the new file.\n");
        exit(EXIT_FAILURE);
    }

    while (*ch != EOF) {
        fputc(*ch, file_pointer);
        ch++;
    }
    fflush(file_pointer);
    fclose(file_pointer);
    printf("\nWRITING OPERATION FINISHED.\n");
}

// This function encrypts a plain-text file.
void encrypt() {
    
}