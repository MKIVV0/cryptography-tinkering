/*
* English letter frequencies source: https://www3.nd.edu/~busiforc/handouts/cryptography/letterfrequencies.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ENGLISH_ALPHABET_LETTERS 26
#define FIRST_ASCII_LETTER_CODE 97  // lowercase a
#define LAST_ASCII_LETTER_CODE 122   // lowercase z
#define ENG_ALPHABET_NUMBER (LAST_ASCII_LETTER_CODE - FIRST_ASCII_LETTER_CODE + 1) // 26

struct letterinfo {
    double percentage;
    char ch;
};

typedef struct letterinfo LETTER;

void count_occurrencies(char* file_name, int occurrencies_list[]);


int main(int argc, char **argv) {
    LETTER E; E.ch = 'e'; E.percentage = 13;
    LETTER T; T.ch = 't'; T.percentage = 9.1;
    LETTER A; A.ch = 'a'; A.percentage = 8.2;
    LETTER O; O.ch = 'o'; O.percentage = 7.5;
    LETTER I; I.ch = 'i'; I.percentage = 7.0;
    LETTER N; N.ch = 'n'; N.percentage = 6.7;
    LETTER S; S.ch = 's'; S.percentage = 6.3;
    LETTER H; H.ch = 'h'; H.percentage = 6.1;
    LETTER R; R.ch = 'r'; R.percentage = 6;
    LETTER D; D.ch = 'd'; D.percentage = 4.3;
    LETTER L; L.ch = 'l'; L.percentage = 4;
    LETTER C; C.ch = 'c'; C.percentage = 2.8;
    LETTER U; U.ch = 'u'; U.percentage = 2.8;
    LETTER M; M.ch = 'm'; M.percentage = 2.4;
    LETTER W; W.ch = 'w'; W.percentage = 2.4;
    LETTER F; F.ch = 'f'; F.percentage = 2.2;
    LETTER G; G.ch = 'g'; G.percentage = 2;
    LETTER Y; Y.ch = 'y'; Y.percentage = 2;
    LETTER P; P.ch = 'p'; P.percentage = 1.9;
    LETTER B; B.ch = 'b'; B.percentage = 1.5;
    LETTER V; V.ch = 'v'; V.percentage = 0.98;
    LETTER K; K.ch = 'k'; K.percentage = 0.77;
    LETTER J; J.ch = 'j'; J.percentage = 0.15;
    LETTER X; X.ch = 'x'; X.percentage = 0.15;
    LETTER Q; Q.ch = 'q'; Q.percentage = 0.095;
    LETTER Z; Z.ch = 'z'; Z.percentage = 0.074;

    LETTER eng_letters_occurrencies[] = {E, T, A, O, I, N, S, H, R, D, L, C, U, M, W, F, G, Y, P, B, V, K, J, X, Q, Z};

    /* 
    * This list's purpouse is to explicit the logic behind the occurrency counting for a given text at code level. 
    * E.g: the counter in position 0 is reserved for the letter 'e' and so on. 
    * */
    int text_occurrencies_list[] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++)
        text_occurrencies_list[i] = 0;
    
    char* encrypted_file = "encrypted.txt";
    count_occurrencies(encrypted_file, text_occurrencies_list);

    // prints each letter occurrency in the given text
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++)
        printf("index %d, letter %c count: %d\n", i, eng_letters_occurrencies[i], text_occurrencies_list[i]);
    
    // Counts the total number of characters of the given file
    int total_ch_num = 0;
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++)
        total_ch_num += text_occurrencies_list[i];
    printf("TOTAL LETTER NUMBER: %d\n\n", total_ch_num);


    // Converts the given file occurrencies in percentages
    LETTER ch_percentage_list[26];
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++) {
       ch_percentage_list[i].ch = eng_letters_occurrencies[i].ch;
       ch_percentage_list[i].percentage = (text_occurrencies_list[i]/((double)total_ch_num))*100;
    }

    printf("DEBUG TEST h: %.2f\n", ch_percentage_list[7].percentage);

    // Prints the percentages
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++)
       printf("letter %c percentage: %.2f\n", eng_letters_occurrencies[i].ch, ch_percentage_list[i]);


    return 0;
}

/*
* This function counts the letter occurrencies of a given text file.
*/
void count_occurrencies(char* file_name, int occurrencies_list[]) {
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
        ch = tolower(fgetc(file_pointer));

        switch (ch) {
            case 'e':
                occurrencies_list[0]++;
                break;
            case 't':
                occurrencies_list[1]++;
                break;
            case 'a':
                occurrencies_list[2]++;
                break;
            case 'o':
                occurrencies_list[3]++;
                break;
            case 'i':
                occurrencies_list[4]++;
                break;
            case 'n':
                occurrencies_list[5]++;
                break;
            case 's':
                occurrencies_list[6]++;
                break;
            case 'h':
                occurrencies_list[7]++;
                break;
            case 'r':
                occurrencies_list[8]++;
                break;
            case 'd':
                occurrencies_list[9]++;
                break;
            case 'l':
                occurrencies_list[10]++;
                break;
            case 'c':
                occurrencies_list[11]++;
                break;
            case 'u':
                occurrencies_list[12]++;
                break;
            case 'm':
                occurrencies_list[13]++;
                break;
            case 'w':
                occurrencies_list[14]++;
                break;
            case 'f':
                occurrencies_list[15]++;
                break;
            case 'g':
                occurrencies_list[16]++;
                break;
            case 'y':
                occurrencies_list[17]++;
                break;
            case 'p':
                occurrencies_list[18]++;
                break;
            case 'b':
                occurrencies_list[19]++;
                break;
            case 'v':
                occurrencies_list[20]++;
                break;
            case 'k':
                occurrencies_list[21]++;
                break;
            case 'j':
                occurrencies_list[22]++;
                break;
            case 'x':
                occurrencies_list[23]++;
                break;
            case 'q':
                occurrencies_list[24]++;
                break;
            case 'z':
                occurrencies_list[25]++;
                break;
        }

        //printf("%c", ch);
    }
    printf("\n");
    fclose(file_pointer);
}

int partition() {
    
}

void quicksort() {

}