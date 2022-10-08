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
int verify_decryption_correctness(char *f1_name, char *f2_name);

int main(int argc, char **argv) {
    char* plaintext_file = "content.txt";
    char* encrypted_text_file = "encrypted.txt";
    char* decrypted_text_file = "decrypted.txt";
    int shift = 3;
    printf("Encryption process:\n");
    write_encrypted_file(plaintext_file, encrypted_text_file, shift);
    printf("Decryption process:\n");
    write_decrypted_file(encrypted_text_file, decrypted_text_file, shift);

    printf("VERIFICATION OF DECRYPTION CORRECTNESS: %d\n", verify_decryption_correctness(plaintext_file, decrypted_text_file));    
   return 0;
}

/*
* This function reads the given file in input.
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

/* 
* This method decrypts a file and writes its content to another file.
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

/* 
* This method decrypts a file and writes its content to another file.
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
        modified_character = decrypt_message(character_pointer, shift_num);
        fputc(*modified_character, dest_file);
    }
    fclose(source_file);
    fclose(dest_file);
    printf("\nWRITING OPERATION FINISHED.\n");
}

/*
* This function encrypts a given message by shifting each character
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
        if (ch[i] != '\0' && ch[i] != ' ' && ch[i] != ',' && ch[i] != '.' && ch[i] != '\'' && ch[i] != '?' && ch[i] != '"' && ch[i] != '-' && ch[i] != '\n' && ch[i] != ((char)13)) {
            shifted_char_val = ch[i] + shift;
            if (shifted_char_val > LAST_ASCII_LETTER_CODE) 
                ch[i] = FIRST_ASCII_LETTER_CODE + (shifted_char_val - LAST_ASCII_LETTER_CODE - 1);
            else 
                ch[i] = ch[i] + shift;
        }
    }
    return ch;
}

/*
* This function decrypts a given message by shifting each character
* by n positions.
*/
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
       if (ch[i] != '\0' && ch[i] != ' ' && ch[i] != ',' && ch[i] != '.' && ch[i] != '\'' && ch[i] != '?' && ch[i] != '"' && ch[i] != '-' && ch[i] != '\n' && ch[i] != ((char)13)) {
            shifted_char_val = ch[i] - shift;
            if (shifted_char_val < FIRST_ASCII_LETTER_CODE) 
                ch[i] = LAST_ASCII_LETTER_CODE - (FIRST_ASCII_LETTER_CODE - shifted_char_val) + 1;
            else 
                ch[i] = ch[i] - shift;
        } 
    }
    return ch; 
}

/*
* This function verifies the correctness of two given file: one is the plaintext, 
* the other is the decrypted file.
*/
int verify_decryption_correctness(char *f1_name, char *f2_name) {
    FILE* f1 = fopen(f1_name, "r");
    FILE* f2 = fopen(f1_name, "r");

    if (f1 == NULL || f2 == NULL) {
        fprintf(stderr, "\nFile error.\n");
        printf("ERROR CODE: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char ch_f1, ch_f2;
    while (ch_f1 != EOF && ch_f2 != EOF) {
        ch_f1 = tolower(getc(f1));
        ch_f2 = tolower(getc(f2));
        if (ch_f1 != ch_f2) {
            printf("%c and %c are different.", ch_f1, ch_f2);
            return 0;
        }
    }
    return 1;
}