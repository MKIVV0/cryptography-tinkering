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
#include <ctype.h>

#define ENGLISH_ALPHABET_LETTERS 26
#define ITALIAN_ALPHABET_LETTERS 21
#define FIRST_ASCII_LETTER_CODE 97  // lowercase a
#define LAST_ASCI_LETTER_CODE 122   // lowercase z

void read_file(char* file_name);
void write_file(char *file_name);
void encrypt(char *file_name);
int verify(char* f1, char* f2);

int main(int argc, char **argv) {
    int en_letter_freqs[ENGLISH_ALPHABET_LETTERS]; 
    
    //printf("Hello, %s", argv[1]);
    //read_file(argv[1]);
    char* source_file = "content.txt";
    //encrypt(source_file);
    printf("Encryption correctness: %d\n", verify("content.txt", "encrypted.txt"));
    return 0;
}

/*
* This function reads the given file in input.
* Time complexity: Θ(n), counting the file time access as Θ(1)
* Space complexity: O(1)
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
/* 
* Time complexity: Θ(n), counting the file time access and creation as Θ(1)
* Space complexity: O(1)
*/
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

/* 
* This function encrypts a plain-text file and writes copies its content to
* a new file named "encrypted.txt".
 */
void encrypt(char* file_name) {
    FILE *dest_file = fopen("encrypted.txt", "w");
    FILE *source_file = fopen(file_name, "r");

    printf("WRITING CONTENT ON THE NEW FILE...\n");
    if (source_file == NULL || dest_file == NULL) {
        fprintf(stderr, "\nError while creating the new file.\n");
        exit(EXIT_FAILURE);
    }

    char ch;
    int shifted;
    while (ch != EOF) {
        ch = tolower(fgetc(source_file));
        if (ch != EOF && ch != ' ' && ch != ',' && ch != '.') 
            shifted = ((ch + 13)%LAST_ASCI_LETTER_CODE);
        if (shifted < 97) ch = (char) (shifted + 97 + 1);
        printf("%c", ch);
        fputc(ch, dest_file);
    }
    fclose(source_file);
    fclose(dest_file);
    printf("\nWRITING OPERATION FINISHED.\n");
}

/* 
* This function verifies whether the given file has been correctly encrypted.
* The first file given in input has to be the unencrypted one.
*/
int verify(char* f1, char* f2) {
    int counter_f1, counter_f2 = 0;
    
    FILE* source_file = fopen(f1, "r");
    FILE* dest_file = fopen(f2, "r");

    /*if (source_file || dest_file == NULL) {
        fprintf(stderr,"Something went wrong with either of the files.\n");
        printf("%d %d\n", *source_file, *dest_file);
        exit(EXIT_FAILURE);
    }*/

    char ch1, ch2;
    int shifted;
    while (ch1 = EOF && ch2 == EOF && ch1 != ch2) {
        ch1 = tolower(fgetc(source_file));
        if (ch1 != EOF && ch1 != ' ' && ch1 != ',' && ch1 != '.') shifted = ((ch1 + 13)%LAST_ASCI_LETTER_CODE);
        if (shifted < 97) ch1 = (char) (shifted + 97 + 1);
        if (ch1 == ch2) {
            counter_f1++;
            counter_f2++;
        } /*else {
            fprintf(stderr, "The two given files' lengths are not equal.\nExiting...");
            exit(EXIT_FAILURE);
        }*/
    }
    printf("f1 cnt: %d\nf2 cnt: %d\n", counter_f1, counter_f2);

    return 0;
}