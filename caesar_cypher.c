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
#include <errno.h>
#include <string.h>

#define ENGLISH_ALPHABET_LETTERS 26
#define ITALIAN_ALPHABET_LETTERS 21
#define FIRST_ASCII_LETTER_CODE 97  // lowercase a
#define LAST_ASCII_LETTER_CODE 122   // lowercase z

void read_file(char* file_name);
void write_encrypted_file(char *src_file, char *dst_file, int shift_num);
void write_decrypted_file(char *src_file, char *dst_file, int shift_num);
char *encrypt_message(char *message, int shift);
char *decrypt_message(char *message, int shift);

int main(int argc, char **argv) {
    int shift = 4;
    printf("Encryption process:\n");
    write_encrypted_file("content.txt", "encrypted.txt", shift);
    printf("Decryption process:\n");
    write_decrypted_file("encrypted.txt", "decrypted.txt", shift);
    
   return 0;
}

/*
* This function reads the given file in input.
* Time complexity: Θ(n), counting the file time access as Θ(1)
* Space complexity: O(1)
*/
void read_file(char* file_name) {
    FILE *file_pointer;
    char ch = 0;
    
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
void write_encrypted_file(char *src_file, char *dst_file, int shift_num) {
    FILE *dest_file = fopen(dst_file, "w");
    FILE *source_file = fopen(src_file, "r"); // apparently, this pointer is null

    printf("WRITING CONTENT ON THE NEW FILE...\n");
    if (source_file == NULL  || dest_file == NULL) {
        fprintf(stderr, "\nFile error.\n");
        printf("ERROR CODE: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char ch;
    char *character_pointer = &ch;
    char *modified_character;
    while (ch != EOF) {
        ch = tolower(fgetc(source_file));
        modified_character = encrypt_message(character_pointer, shift_num);
        fputc(*modified_character, dest_file);
    }
    fclose(source_file);
    fclose(dest_file);
    printf("\nWRITING OPERATION FINISHED.\n");
}

// This function copies the given file's content to a new file named "encrypted.txt".
/* 
* Time complexity: Θ(n), counting the file time access and creation as Θ(1)
* Space complexity: O(1)
*/
void write_decrypted_file(char *src_file, char *dst_file, int shift_num) {
    FILE *dest_file = fopen(dst_file, "w");
    FILE *source_file = fopen(src_file, "r"); // apparently, this pointer is null

    printf("WRITING CONTENT ON THE NEW FILE...\n");
    if (source_file == NULL  || dest_file == NULL) {
        fprintf(stderr, "\nFile error.\n");
        printf("ERROR CODE: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char ch;
    char *character_pointer = &ch;
    char *modified_character;
    while (ch != EOF) {
        ch = tolower(fgetc(source_file));
        modified_character = encrypt_message(character_pointer, shift_num);
        fputc(*modified_character, dest_file);
    }
    fclose(source_file);
    fclose(dest_file);
    printf("\nWRITING OPERATION FINISHED.\n");
}

/*
* This method encrypts a given message by shifting each character
* by n positions.
*/
char *encrypt_message(char *message, int shift_num) {
    int message_length = 0;
    int idx = 0;
    int shift = shift_num;
    int shifted_char_val = 0;

    // To get the message length
    while (message[idx] != '\0') {
        message_length++;
        idx++;
    }

    char *ch = (char*)calloc(message_length+1, sizeof(char));
    for (int i = 0; message[i] != '\0'; i++) {
        ch[i] = tolower(message[i]);
        if (ch[i] != '\0' && ch[i] != ' ' && ch[i] != ',' && ch[i] != '.' && ch[i] != '\'' && ch[i] != '?') {
            shifted_char_val = ch[i] + shift;
            if (shifted_char_val > LAST_ASCII_LETTER_CODE) 
                ch[i] = FIRST_ASCII_LETTER_CODE + (shifted_char_val - LAST_ASCII_LETTER_CODE - 1);
            else 
                ch[i] = ch[i] + shift;
        }
    }
    return ch;
}

// TO REVIEW
char *decrypt_message(char *message, int shift_num) {
    int message_length = 0;
    int idx = 0;
    int shift = shift_num;
    int shifted_char_val = 0;

    while (message[idx] != '\0') {
        message_length++;
        idx++;
    }

    char *ch = (char*)calloc(message_length+1, sizeof(char));
    int shifted;
    for (int i = 0; message[i] != '\0'; i++) {
        ch[i] = tolower(message[i]);
       if (ch[i] != '\0' && ch[i] != ' ' && ch[i] != ',' && ch[i] != '.' && ch[i] != '\'' && ch[i] != '?') {
            shifted_char_val = ch[i] - shift;
            if (shifted_char_val < FIRST_ASCII_LETTER_CODE) 
                ch[i] = LAST_ASCII_LETTER_CODE - (FIRST_ASCII_LETTER_CODE - shifted_char_val) + 1;
            else 
                ch[i] = ch[i] - shift;
        } 
    }
    return ch; 
}