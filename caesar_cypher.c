/*
* Simple implementation of the Caesar Cypher.
* The goal of this program is to encrypt a given text and give it as a
* sample to another program, which task is to decrypt it, without prior 
* knowledge of the decryption key.
* The text contained inside the file "content.txt" has been 
* generated at https://randomwordgenerator.com/paragraph.php
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
    char* source_file = "content.txt";
    write_file(source_file);
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
    fclose(file_pointer);
}

// This function copies the given file's content to a new file named "encrypted.txt".
void write_file(char *file_name) {
    FILE *dest_file = fopen("encrypted.txt", "w");
    FILE *source_file = fopen(file_name, "r");

    printf("WRITING CONTENT ON THE NEW FILE...\n");
    if (source_file == NULL || dest_file == NULL) {
        fprintf(stderr, "\nError while creating the new file.\n");
        exit(EXIT_FAILURE);
    }

    char ch;
    while (ch != EOF) {
        ch = fgetc(source_file);
        fputc(ch, dest_file);
    }
    fclose(source_file);
    fclose(dest_file);
    printf("\nWRITING OPERATION FINISHED.\n");
}
 
int verify(char* f1, char* f2) {
    //while () {

    //}
    return 0;
}

// This function encrypts a plain-text file.
void encrypt() {
    
}