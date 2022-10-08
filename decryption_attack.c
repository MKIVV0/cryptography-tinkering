/*
* English letter frequencies source: https://www3.nd.edu/~busiforc/handouts/cryptography/letterfrequencies.html
*/

#include <stdio.h>
#include <stdlib.h>

#define ENGLISH_ALPHABET_LETTERS 26
#define FIRST_ASCII_LETTER_CODE 97  // lowercase a
#define LAST_ASCII_LETTER_CODE 122   // lowercase z
#define ENG_ALPHABET_NUMBER (LAST_ASCII_LETTER_CODE - FIRST_ASCII_LETTER_CODE + 1) // 26

struct letterinfo {
    char ch;
    float percentage;
};

typedef struct letterinfo LETTER;

int main(int argc, char **argv) {
    LETTER E; E.ch = 'e'; E.percentage = 11.1607;
    LETTER A; A.ch = 'a'; A.percentage = 8.4966;
    LETTER R; R.ch = 'r'; R.percentage = 7.5809;
    LETTER I; I.ch = 'i'; I.percentage = 7.5448;
    LETTER O; O.ch = 'o'; O.percentage = 7.1635;
    LETTER T; T.ch = 't'; T.percentage = 6.9509;
    LETTER N; N.ch = 'n'; N.percentage = 6.6544;
    LETTER S; S.ch = 's'; S.percentage = 5.7351;
    LETTER L; L.ch = 'l'; L.percentage = 5.4893;
    LETTER C; C.ch = 'c'; C.percentage = 4.5388;
    LETTER U; U.ch = 'u'; U.percentage = 3.6308;
    LETTER D; D.ch = 'd'; D.percentage = 3.3844;
    LETTER P; P.ch = 'p'; P.percentage = 3.1671;
    LETTER M; M.ch = 'm'; M.percentage = 3.0129;
    LETTER H; H.ch = 'h'; H.percentage = 3.0034;
    LETTER G; G.ch = 'g'; G.percentage = 2.4705;
    LETTER B; B.ch = 'b'; B.percentage = 2.0720;
    LETTER F; F.ch = 'f'; F.percentage = 1.8121;
    LETTER Y; Y.ch = 'y'; Y.percentage = 1.7779;
    LETTER W; W.ch = 'w'; W.percentage = 1.2899;
    LETTER K; K.ch = 'k'; K.percentage = 1.1016;
    LETTER V; V.ch = 'v'; V.percentage = 1.0074;
    LETTER X; X.ch = 'x'; X.percentage = 0.2902;
    LETTER Z; Z.ch = 'z'; Z.percentage = 0.2722;
    LETTER J; J.ch = 'j'; J.percentage = 0.1965;
    LETTER Q; Q.ch = 'q'; Q.percentage = 0.1962;

    LETTER eng_letters_occurrencies[] = {E, A, R, I, O, T, N, S, L, C, U, D, P, M, H, G, B, F, Y, W, K, V, X, Z, J, Q};

    int occurrencies_list[] = {'e', 'a', 'r', 'i', 'o', 't', 'n', 's', 'l', 'c', 'u', 'd', 'p', 'm', 'h', 'g', 'b', 'f', 'y', 'w', 'k', 'v', 'x', 'z', 'j', 'q'};
    for (int i = 0; i < ENG_ALPHABET_NUMBER; i++)
        occurrencies_list[i] = 0;
    
    

    return 0;
}

char* count_occurrencies(char* occurrencies_list[]) {

    return *occurrencies_list; 
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